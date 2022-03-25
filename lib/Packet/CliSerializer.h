#pragma once

#include "StructSerializer.h"

using namespace System;
using namespace System::IO;
using namespace cli;
using namespace System::Collections::Generic;
using namespace System::Text;

namespace RappelzPackets {
	ref class CliSerializer {
	private:
		packet_version_t version;
		Stream^ stream_;
		BinaryWriter^ writer;
		BinaryReader^ reader;
		uint16_t messageSize;
		Encoding^ encoding;

		inline static uint8_t getMessageChecksum(uint32_t size, uint16_t id) {
			uint8_t value = 0;

			value += size & 0xFF;
			value += (size >> 8) & 0xFF;
			value += (size >> 16) & 0xFF;
			value += (size >> 24) & 0xFF;

			value += id & 0xFF;
			value += (id >> 8) & 0xFF;

			return value;
		}

	public:
		CliSerializer(Stream^ stream, packet_version_t version, Encoding^ encoding);

		packet_version_t getVersion() { return version; }

		int getSize() { return messageSize; }
		int getParsedSize() { return stream_->Position; }

		void checkAvailableBuffer(String^ fieldName, size_t size) {
			bool ok = size < 65536 && getParsedSize() + size <= 65536;
			if (!ok) {
				throw gcnew EndOfStreamException(String::Format(L"Serialization overflow: version: 0x{0:X}, buffer size: {1}, offset: {2}, field: {3}\n",
					version,
					stream_->Length,
					getParsedSize(),
					fieldName));
			}
		}

		// Write functions /////////////////////////

		void writeHeader(uint32_t size, uint16_t id) {
			messageSize = size;
			write<uint32_t>("size", size);
			write<uint16_t>("id", id);
			write<uint8_t>("msg_checksum", getMessageChecksum(size, id));
		}

		// Primitives
		template<typename T>
		typename std::enable_if<is_primitive<T>::value, void>::type write(String^ fieldName, T val) {
			writer->Write(val);
		}

		// Objects
		template<typename T>
		typename std::enable_if<!is_primitive<T>::value, void>::type write(String^ fieldName, T^ val) {
			val->serialize(this);
		}

		// String
		void writeString(String^ fieldName, String^ val, size_t maxSize);
		void writeDynString(String^ fieldName, String^ val, size_t count);


		// Fixed array of primitive
		template<typename T, typename U>
		typename void writeArray(String^ fieldName,
			array<U>^ val,
			size_t size) {
			size_t i;
			for (i = 0; i < size && i < val->Length; i++) {
				write<T>(fieldName, (T) val[i]);
			}
			for (i = 0; i < size; i++) {
				write<T>(fieldName, T{});
			}
		}
		// Fixed array of objects
		template<typename T>
		typename void writeArray(String^ fieldName,
			array<T^>^ val,
			size_t size) {
			size_t i;
			for (i = 0; i < size && i < val->Length; i++) {
				write<T>(fieldName, val[i]);
			}
			for (i = 0; i < size; i++) {
				write<T>(fieldName, gcnew T);
			}
		}

		// Dynamic array of primitive
		template<typename T>
		typename void writeDynArray(String^ fieldName,
			List<T>^ val,
			uint32_t count) {
			for (size_t i = 0; i < count && i < val->Count; i++)
				write(fieldName, val[i]);
		}

		// Dynamic array of objects
		template<typename T>
		typename void writeDynArray(String^ fieldName,
			List<T^>^ val,
			uint32_t count) {
			for (size_t i = 0; i < count && i < val->Count; i++)
				write(fieldName, val[i]);
		}

		template<typename T>
		typename std::enable_if<is_primitive<T>::value, void>::type writeSize(String^ fieldName, T size) {
			write<T>(fieldName, size);
		}

		void pad(String^ fieldName, size_t size) {
			checkAvailableBuffer(fieldName, size);
			for (size_t i = 0; i < size; i++)
				writer->Write((unsigned char)0);
		}

		// Read functions /////////////////////////

		void readHeader(uint16_t% id) {
			read<uint32_t>("size", messageSize);
			read<uint16_t>("id", id);
			discard("msg_checksum", 1);
		}

		// Primitives via arg
		template<typename T, typename U>
		typename std::enable_if<is_primitive<U>::value, void>::type read(String^ fieldName, U% val) {
			checkAvailableBuffer(fieldName, sizeof(T));
			if constexpr (std::is_enum_v<T>) {
				T underlyingTypeVal;
				read<std::underlying_type_t<T>>(fieldName, underlyingTypeVal);
				val = (U)underlyingTypeVal;
			}
			else {
				using underlying_type = T;
				if constexpr (std::is_same<underlying_type, bool>::value) {
					val = (U)reader->ReadByte();
				}
				else if constexpr (std::is_same<underlying_type, uint8_t>::value) {
					val = (U)reader->ReadByte();
				}
				else if constexpr (std::is_same<underlying_type, int8_t>::value) {
					val = (U)reader->ReadSByte();
				}
				else if constexpr (std::is_same<underlying_type, uint16_t>::value) {
					val = (U)reader->ReadUInt16();
				}
				else if constexpr (std::is_same<underlying_type, int16_t>::value) {
					val = (U)reader->ReadInt16();
				}
				else if constexpr (std::is_same<underlying_type, uint32_t>::value) {
					val = (U)reader->ReadUInt32();
				}
				else if constexpr (std::is_same<underlying_type, int32_t>::value) {
					val = (U)reader->ReadInt32();
				}
				else if constexpr (std::is_same<underlying_type, uint64_t>::value) {
					val = (U)reader->ReadUInt64();
				}
				else if constexpr (std::is_same<underlying_type, int64_t>::value) {
					val = (U)reader->ReadInt64();
				}
				else if constexpr (std::is_same<underlying_type, float>::value) {
					val = (U)reader->ReadSingle();
				}
				else if constexpr (std::is_same<underlying_type, double>::value) {
					val = (U)reader->ReadDouble();
				}
				else {
					static_assert(!sizeof(T), "Unsupported type");
				}
			}
		}

		// Objects
		template<typename T>
		typename std::enable_if<!is_primitive<T>::value, void>::type read(String^ fieldName, T^ val) {
			val->deserialize(this);
		}

		// String
		void readString(String^ fieldName, String^% val, size_t size);
		void readDynString(String^ fieldName, String^% val, uint32_t sizeToRead, bool hasNullTerminator);
		void readEndString(String^ fieldName, String^% val, bool hasNullTerminator);


		// Fixed array of primitive
		template<typename T, typename U>
		typename std::enable_if<is_primitive<T>::value, void>::type readArray(String^ fieldName,
			array<U>^ val,
			size_t size) {
			Array::Resize(val, size);

			for (size_t i = 0; i < size; i++) {
				if constexpr (std::is_same_v<T, U>) {
					read<T>(fieldName, val[i]);
				}
				else {
					T item;
					read<T>(fieldName, item);
					val[i] = (U)item;
				}
			}
		}

		// Fixed array of objects
		template<typename T>
		typename std::enable_if<!is_primitive<T>::value, void>::type readArray(String^ fieldName,
			array<T^>^ val,
			size_t size) {
			Array::Resize(val, size);

			for (size_t i = 0; i < size; i++) {
				T^ item = gcnew T;
				read<T>(fieldName, item);
				val[i] = item;
			}
		}

		// Dynamic array of primitive
		template<typename T>
		typename std::enable_if<is_primitive<T>::value, void>::type readDynArray(String^ fieldName,
			List<T>^ val,
			uint32_t sizeToRead) {
			val->Clear();

			for (size_t i = 0; i < sizeToRead; i++) {
				T item;
				read<T>(fieldName, item);
				val->Add(item);
			}
		}

		// Dynamic array of primitive with cast
		template<typename T, typename U>
		typename std::enable_if<is_castable_primitive<T, U>::value, void>::type readDynArray(String^ fieldName,
			List<T>^ val,
			uint32_t sizeToRead) {
			val->Clear();
			val->Reverse(sizeToRead);

			for (size_t i = 0; i < sizeToRead; i++) {
				T item;
				read<T>(fieldName, item);
				val->Add((U)item);
			}
		}

		// Dynamic array of object
		template<typename T>
		typename std::enable_if<!is_primitive<T>::value, void>::type readDynArray(String^ fieldName,
			List<T^>^ val,
			uint32_t sizeToRead) {
			val->Clear();

			for (size_t i = 0; i < sizeToRead; i++) {
				T^ item = gcnew T;
				read(fieldName, item);
				val->Add(item);
			}
		}

		// End array with primitive, read to the end of stream
		template<typename T>
		typename std::enable_if<is_primitive<T>::value, void>::type readEndArray(String^ fieldName,
			List<T>^ val) {
			size_t remainingSize = 0;

			if (getSize() > getParsedSize())
				remainingSize = getSize() - getParsedSize();

			remainingSize = remainingSize / sizeof(T);

			val->Clear();

			for (size_t i = 0; i < remainingSize; i++) {
				T item;
				read<T>(fieldName, item);
				val->Add(item);
			}
		}

		// End array, read to the end of stream
		template<typename T>
		typename std::enable_if<!is_primitive<T>::value, void>::type readEndArray(String^ fieldName,
			List<T^>^ val) {
			// While there are non parsed bytes and the read actually read something, continue
			val->Clear();
			while (stream_->CanRead && getParsedSize() < stream_->Length) {
				try {
					T^ item = gcnew T;
					read<T>(fieldName, item);
					val->Add(item);
				}
				catch (EndOfStreamException^ e) {
					break;
				}
			}
		}

		// read size for objects (std:: containers)
		template<typename T>
		typename std::enable_if<is_primitive<T>::value, void>::type readSize(String^ fieldName, uint32_t% val) {
			read<T>(fieldName, val);
		}

		void discard(String^ fieldName, size_t size) {
			checkAvailableBuffer(fieldName, size);
			reader->ReadBytes(size);
		}
	};
}