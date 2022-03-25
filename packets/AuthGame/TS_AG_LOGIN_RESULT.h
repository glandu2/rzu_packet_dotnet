#pragma once

#include "Packet/PacketDeclaration.h"

#define TS_AG_LOGIN_RESULT_DEF(_) \
	_(simple)(uint16_t, result)

CREATE_PACKET(TS_AG_LOGIN_RESULT, 20002, SessionType::AuthGame, SessionPacketOrigin::Server);
