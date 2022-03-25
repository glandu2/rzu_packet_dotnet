#pragma once

#include "Packet/PacketDeclaration.h"

enum TS_AG_KICK_CLIENT_KickType : uint8_t
{
	KICK_TYPE_ANOTHER_LOGIN = 0x0,  //Gameguard kick ?
	KICK_TYPE_DUPLICATED_LOGIN = 0x1,
	KICK_TYPE_BILLING_EXPIRED = 0x2,
	KICK_TYPE_GAME_ADDICTION = 0x3
};

#define TS_AG_KICK_CLIENT_DEF(_) \
	_(string)(account, 61) \
	_(simple)(TS_AG_KICK_CLIENT_KickType, kick_type, version >= EPIC_6_1)

CREATE_PACKET(TS_AG_KICK_CLIENT, 20013, SessionType::AuthGame, SessionPacketOrigin::Server);
