#pragma once

#include "Packet/PacketDeclaration.h"

#define TS_SU_REQUEST_UPLOAD_DEF(_) \
	_(simple)(uint32_t, client_id) \
	_(simple)(uint32_t, account_id) \
	_(simple)(uint32_t, guild_sid) \
	_(simple)(uint32_t, one_time_password) \
	_(simple)(uint8_t, type)

CREATE_PACKET(TS_SU_REQUEST_UPLOAD, 50003, SessionType::UploadGame, SessionPacketOrigin::Client);
