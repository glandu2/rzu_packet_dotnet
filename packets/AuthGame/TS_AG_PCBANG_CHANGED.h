#pragma once

#include "Packet/PacketDeclaration.h"

#define TS_AG_PCBANG_CHANGED_DEF(_) \
	_(string)(account, 61) \
	_(simple)(int32_t, nPCBangMode)

CREATE_PACKET(TS_AG_PCBANG_CHANGED, 20022, SessionType::AuthGame, SessionPacketOrigin::Server);
