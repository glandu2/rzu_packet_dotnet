#pragma once

#include "Packet/PacketDeclaration.h"

#define TS_AG_SECURITY_NO_CHECK_DEF(_) \
	_(string)(account, 61) \
	_(simple)(uint32_t, mode, version >= EPIC_6_1) \
	_(simple)(uint32_t, result)

CREATE_PACKET(TS_AG_SECURITY_NO_CHECK, 40000, SessionType::AuthGame, SessionPacketOrigin::Server);
