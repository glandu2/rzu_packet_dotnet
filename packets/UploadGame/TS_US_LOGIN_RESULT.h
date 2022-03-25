#pragma once

#include "Packet/PacketDeclaration.h"

#define TS_US_LOGIN_RESULT_DEF(_) \
	_(simple)(uint16_t, result)

CREATE_PACKET(TS_US_LOGIN_RESULT, 50002, SessionType::UploadGame, SessionPacketOrigin::Server);
