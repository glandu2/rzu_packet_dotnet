#pragma once

#include "Packet/PacketDeclaration.h"

#define TS_AG_ITEM_PURCHASED_DEF(_) \
	_(string)(account, 61) \
	_(simple)(uint32_t, nAccountID)

CREATE_PACKET(TS_AG_ITEM_PURCHASED, 30000, SessionType::AuthGame, SessionPacketOrigin::Server);
