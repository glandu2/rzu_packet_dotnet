#pragma managed
#include "CliSerializer.h"
#include <algorithm>

namespace RappelzPackets {

	CliSerializer::CliSerializer(Stream^ stream, packet_version_t version, Encoding^ encoding) {
		this->version = version;
		this->stream_ = stream;
		this->reader = gcnew BinaryReader(stream);
		this->writer = gcnew BinaryWriter(stream);
		this->messageSize = 0;
		this->encoding = encoding;
	}


	void CliSerializer::writeString(String^ fieldName, String^ val, size_t maxSize) {
		checkAvailableBuffer(fieldName, maxSize);
		size_t stringSize;

		if (val == nullptr) {
			stringSize = 0;
		}
		else {
			stringSize = val->Length;
		}
		
		stringSize = std::min(stringSize, maxSize - 1);  // keep room for nul terminator (truncate val if too long)

		if (stringSize > 0) {
			array<unsigned char>^ data = encoding->GetBytes(val);

			stream_->Write(data, 0, stringSize);
		}

		for (size_t i = 0; i < maxSize - stringSize; i++)
			stream_->WriteByte(0);
	}

	void CliSerializer::writeDynString(String^ fieldName, String^ val, size_t count) {
		checkAvailableBuffer(fieldName, count);
		size_t stringSize;

		if (val == nullptr) {
			stringSize = 0;
		}
		else {
			stringSize = val->Length;
		}

		stringSize = std::min(stringSize, count);  // keep room for nul terminator (truncate val if too long)

		if (stringSize > 0) {
			array<unsigned char>^ data = encoding->GetBytes(val);

			stream_->Write(data, 0, stringSize);
		}
		for (size_t i = 0; i < count - stringSize; i++)
			stream_->WriteByte(0);
	}

	void CliSerializer::readString(String^ fieldName, String^% val, size_t maxSize) {
		checkAvailableBuffer(fieldName, maxSize);
		array<uint8_t>^ data = reader->ReadBytes((int)maxSize);

		int endOfString = Array::IndexOf(data, '\0');

		if (endOfString >= 0)
			val = encoding->GetString(data, 0, endOfString);
		else
			val = encoding->GetString(data);
	}

	void CliSerializer::readDynString(String^ fieldName,
		String^% val,
		uint32_t sizeToRead,
		bool hasNullTerminator) {
		checkAvailableBuffer(fieldName, sizeToRead);

		if (sizeToRead > 0) {
			array<uint8_t>^ data = reader->ReadBytes((int)sizeToRead);
			int endOfString = Array::IndexOf(data, '\0', 0, sizeToRead - hasNullTerminator);

			if (endOfString >= 0)
				val = encoding->GetString(data, 0, endOfString);
			else
				val = encoding->GetString(data);
		}
		else {
			val = String::Empty;
		}
	}

	void CliSerializer::readEndString(String^ fieldName, String^% val, bool hasNullTerminator) {
		size_t remainingSize = 0;

		if (messageSize > stream_->Position)
			remainingSize = messageSize - stream_->Position;

		checkAvailableBuffer(fieldName, remainingSize);
		if (remainingSize > 0) {
			array<uint8_t>^ data = reader->ReadBytes((int)remainingSize);

			int endOfString = Array::IndexOf(data, '\0');

			if (endOfString >= 0)
				val = encoding->GetString(data, 0, endOfString);
			else
				val = encoding->GetString(data);
		}
		else
			val = String::Empty;
	}
}
