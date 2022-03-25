#include "PacketUtilWrapperCli.h"

namespace RappelzPackets {
	void ISerializableStruct::serialize(Stream^ serializationStream, packet_version_t version, Encoding^ encoding) {
		CliSerializer^ serializer = gcnew CliSerializer(serializationStream, version, encoding);
		serialize(serializer);
	}
	void ISerializableStruct::deserialize(Stream^ serializationStream, packet_version_t version, Encoding^ encoding) {
		CliSerializer^ serializer = gcnew CliSerializer(serializationStream, version, encoding);
		deserialize(serializer);
	}

	array<System::Byte>^ ISerializableStruct::ToArray(packet_version_t version) {
		return ToArray(version, Encoding::Default);
	}

	array<System::Byte>^ ISerializableStruct::ToArray(packet_version_t version, Encoding^ encoding) {
		MemoryStream^ stream = gcnew MemoryStream();
		serialize(stream, version, encoding);
		return stream->GetBuffer();
	}

	void ISerializableStruct::FromArray(array<System::Byte>^ data, packet_version_t version) {
		FromArray(data, version, Encoding::Default);
	}

	void ISerializableStruct::FromArray(array<System::Byte>^ data, packet_version_t version, Encoding^ encoding) {
		MemoryStream^ stream = gcnew MemoryStream(data);
		deserialize(stream, version, encoding);
	}

}  // namespace PacketVersionUtils
