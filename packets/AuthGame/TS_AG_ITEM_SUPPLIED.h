#pragma once

#include "Packet/PacketDeclaration.h"

#define TS_AG_ITEM_SUPPLIED_DEF(_) \
	_(string)(account, 61)

CREATE_PACKET(TS_AG_ITEM_SUPPLIED, 30001, SessionType::AuthGame, SessionPacketOrigin::Server);
