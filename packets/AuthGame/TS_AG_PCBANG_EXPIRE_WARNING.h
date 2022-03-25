#pragma once

#include "Packet/PacketDeclaration.h"

#define TS_AG_PCBANG_EXPIRE_WARNING_DEF(_) \
	_(string)(account, 61) \
	_(simple)(uint32_t, remain_minutes)

CREATE_PACKET(TS_AG_PCBANG_EXPIRE_WARNING, 20020, SessionType::AuthGame, SessionPacketOrigin::Server);
