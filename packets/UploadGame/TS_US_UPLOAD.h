#pragma once

#include "Packet/PacketDeclaration.h"

#define TS_US_UPLOAD_DEF(_) \
	_(simple)(uint32_t, guild_id) \
	_(simple)(uint32_t, file_size) \
	_(count)(uint8_t, file_name) \
	_(simple)(uint8_t, type) \
	_(dynstring)(file_name, true)

CREATE_PACKET(TS_US_UPLOAD, 50009, SessionType::UploadGame, SessionPacketOrigin::Server);
