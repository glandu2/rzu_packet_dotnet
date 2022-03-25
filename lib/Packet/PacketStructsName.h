#pragma once

#include "PacketEpics.h"
#include <stdint.h>

using namespace System;
using namespace System::Collections::Generic;

namespace RappelzPackets {
    public enum class SessionType { Any, AuthClient, AuthGame, GameClient, UploadClient, UploadGame, NUMBER };
    public enum class SessionPacketOrigin { Any, Server, Client, NUMBER };
    typedef int32_t packet_type_id_t;

    delegate uint16_t GetIdFunction(packet_version_t version);

    private value struct PacketInfo {
        GetIdFunction^ getId;
        packet_type_id_t id;
        SessionType sessionType;
        SessionPacketOrigin packetDir;
        String^ name;
    };

    public ref class PacketMetadata {
    public:
        static SessionPacketOrigin getPacketOriginFromDirection(bool outgoing, SessionPacketOrigin selfSessionPacketOrigin);
        static void getPacketOriginName(bool outgoing,
            SessionType sessionType,
            SessionPacketOrigin selfSessionPacketOrigin,
            String^% fromNamePtr,
            String^% toNamePtr);

        static String^ getPacketName(unsigned int id,
            SessionType sessionType,
            SessionPacketOrigin packetDir,
            packet_version_t version);

        static packet_type_id_t convertPacketIdToTypeId(uint16_t id,
            SessionType sessionType,
            SessionPacketOrigin packetDir,
            packet_version_t version);

        static void PacketMetadata::addPacketMetadataForId(uint16_t packetId,
            SessionType sessionType,
            SessionPacketOrigin packetDir,
            GetIdFunction^ getId,
            packet_type_id_t id,
            String^ name);

    private:
        static void PacketMetadata::initPacketsInfo();

        static const PacketInfo^ PacketMetadata::getPacketMetadata(uint16_t id,
            SessionType sessionType,
            SessionPacketOrigin packetDir,
            packet_version_t version);

        static Dictionary<uint16_t, List<PacketInfo>^>^ packetsInfo = gcnew Dictionary<uint16_t, List<PacketInfo>^>;
    };  // namespace PacketMetadata
}