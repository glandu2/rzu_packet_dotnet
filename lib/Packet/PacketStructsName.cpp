#include "PacketStructsName.h"
#include "PacketDeclaration.h"
#include "PacketEpics.h"

#include "PacketIterator.h"

namespace RappelzPackets {

	struct PacketNameInfo {
		unsigned short id;
		const char* name;
	};

	template<class Packet> struct FunctorAddPacketType {
		void operator()() {
			for (auto packetId : Packet::PACKET_IDS::getAsInitializerList()) {
				PacketMetadata::addPacketMetadataForId(
					packetId, Packet::SESSION_TYPE, Packet::ORIGIN, gcnew GetIdFunction(&Packet::getId), Packet::packetID, Packet::getName());
			}
		}
	};

	void PacketMetadata::addPacketMetadataForId(uint16_t packetId,
		SessionType sessionType,
		SessionPacketOrigin packetDir,
		GetIdFunction^ getId,
		packet_type_id_t id,
		String^ name) {
		PacketInfo packetInfoData = { getId, id, sessionType, packetDir, name };

		List<PacketInfo>^ packetInfo;
		if (!packetsInfo->TryGetValue(packetId, packetInfo)) {
			packetInfo = gcnew List<PacketInfo>();
			packetsInfo[packetId] = packetInfo;
		}

		packetInfo->Add(packetInfoData);
	}

	void PacketMetadata::initPacketsInfo() {
		iteratePackets<FunctorAddPacketType>();
	}

	const PacketInfo^ PacketMetadata::getPacketMetadata(uint16_t id,
		SessionType sessionType,
		SessionPacketOrigin packetDir,
		packet_version_t version) {
		if (packetsInfo->Count == 0)
			initPacketsInfo();
		if (packetsInfo->ContainsKey(id)) {
			const auto& packetsForId = packetsInfo[id];
			for each (PacketInfo ^ packetInfo in packetsForId) {
				if (sessionType != SessionType::Any && packetInfo->sessionType != SessionType::Any &&
					packetInfo->sessionType != sessionType)
					continue;
				if (packetDir != SessionPacketOrigin::Any && packetInfo->packetDir != SessionPacketOrigin::Any &&
					packetInfo->packetDir != packetDir)
					continue;
				if (packetInfo->getId(version) == id)
					return packetInfo;
			}
		}
		//Object::logStatic(Object::LL_Debug,
		//                  "convertPacketIdToTypeId",
		//                  "Unknown packet ID %u for session type %u, origin %u and version 0x%x\n",
		//                  id,
		//                  (uint32_t) sessionType,
		//                  (uint32_t) packetDir,
		//                  version.getAsInt());
		return nullptr;
	}

	packet_type_id_t PacketMetadata::convertPacketIdToTypeId(uint16_t id,
		SessionType sessionType,
		SessionPacketOrigin packetDir,
		packet_version_t version) {
		const PacketInfo^ packetInfo = getPacketMetadata(id, sessionType, packetDir, version);
		if (packetInfo)
			return packetInfo->id;
		return static_cast<packet_type_id_t>(id);
	}

	String^ PacketMetadata::getPacketName(unsigned int id,
		SessionType sessionType,
		SessionPacketOrigin packetDir,
		packet_version_t version) {
		const PacketInfo^ packetInfo = getPacketMetadata(id, sessionType, packetDir, version);
		if (packetInfo)
			return packetInfo->name;

		return nullptr;
	}

	SessionPacketOrigin PacketMetadata::getPacketOriginFromDirection(bool outgoing, SessionPacketOrigin selfSessionPacketOrigin) {
		if (selfSessionPacketOrigin == SessionPacketOrigin::Any)
			return SessionPacketOrigin::Any;

		if (outgoing)
			return selfSessionPacketOrigin;

		// If ingoing, return opposite origin

		if (selfSessionPacketOrigin == SessionPacketOrigin::Client)
			return SessionPacketOrigin::Server;

		return SessionPacketOrigin::Client;
	}

	void PacketMetadata::getPacketOriginName(bool outgoing,
		SessionType sessionType,
		SessionPacketOrigin selfSessionPacketOrigin,
		String^% fromNamePtr,
		String^% toNamePtr) {
		String^ serverName = nullptr;
		String^ clientName = nullptr;

		switch (sessionType) {
		case SessionType::AuthClient:
			serverName = "Auth";
			clientName = "Client";
			break;
		case SessionType::AuthGame:
			serverName = "Auth";
			clientName = "Game";
			break;
		case SessionType::GameClient:
			serverName = "Game";
			clientName = "Client";
			break;
		case SessionType::UploadClient:
			serverName = "Upload";
			clientName = "Client";
			break;
		case SessionType::UploadGame:
			serverName = "Upload";
			clientName = "Game";
			break;
		default:
			break;
		}

		SessionPacketOrigin origin = getPacketOriginFromDirection(outgoing, selfSessionPacketOrigin);
		String^ fromName = nullptr;
		String^ toName = nullptr;

		if (origin == SessionPacketOrigin::Client) {
			fromName = clientName;
			toName = serverName;
		}
		else if (origin == SessionPacketOrigin::Server) {
			fromName = serverName;
			toName = clientName;
		}

		if (fromName == nullptr) {
			if (outgoing)
				fromName = "local";
			else
				fromName = "remote";
		}
		if (toName == nullptr) {
			if (outgoing)
				toName = "remote";
			else
				toName = "local";
		}

		fromNamePtr = fromName;
		toNamePtr = toName;
	}
}