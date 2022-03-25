#pragma once

#include "Packet/PacketDeclaration.h"

#define TS_GA_CLIENT_KICK_FAILED_DEF(_) \
	_(string)(account, 61)

CREATE_PACKET(TS_GA_CLIENT_KICK_FAILED, 20014, SessionType::AuthGame, SessionPacketOrigin::Client);
