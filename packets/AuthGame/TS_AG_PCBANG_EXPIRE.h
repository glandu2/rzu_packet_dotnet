#pragma once

#include "Packet/PacketDeclaration.h"

#define TS_AG_PCBANG_EXPIRE_DEF(_) \
	_(string)(account, 61)

CREATE_PACKET(TS_AG_PCBANG_EXPIRE, 20021, SessionType::AuthGame, SessionPacketOrigin::Server);
