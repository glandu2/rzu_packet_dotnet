#pragma once

#include "PacketEpics.h"
#include "CliSerializer.h"

using namespace System::IO;
using namespace System::Text;

namespace RappelzPackets {

public ref class ISerializableStruct abstract {
public:
	void serialize(Stream^ serializationStream, packet_version_t version, Encoding^ encoding);
	void deserialize(Stream^ serializationStream, packet_version_t version, Encoding^ encoding);

	array<System::Byte>^ ToArray(packet_version_t version);
	array<System::Byte>^ ToArray(packet_version_t version, Encoding^ encoding);
	void FromArray(array<System::Byte>^ data, packet_version_t version);
	void FromArray(array<System::Byte>^ data, packet_version_t version, Encoding^ encoding);

internal:
	virtual uint32_t getSize(packet_version_t version) = 0;
	virtual void serialize(CliSerializer^ buffer) = 0;
	virtual void deserialize(CliSerializer^ buffer) = 0;
};

}  // namespace PacketVersionUtils
