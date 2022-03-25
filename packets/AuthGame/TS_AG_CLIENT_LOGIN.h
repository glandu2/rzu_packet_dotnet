#pragma once

#include "Packet/PacketDeclaration.h"

#define TS_AG_CLIENT_LOGIN_DEF(_) \
	_(string)(account, 61) \
	_(simple)(uint32_t, nAccountID) \
	_(simple)(uint16_t, result) \
	_(simple)(int8_t, nPCBangUser) \
	_(simple)(uint32_t, nEventCode) \
	_(simple)(uint32_t, nAge) \
	_(simple)(uint32_t, nContinuousPlayTime) \
	_(simple)(uint32_t, nContinuousLogoutTime)

CREATE_PACKET(TS_AG_CLIENT_LOGIN, 20011, SessionType::AuthGame, SessionPacketOrigin::Server);


#define TS_AG_CLIENT_LOGIN_EXTENDED_DEF(_) \
	_(string)(account, 61) \
	_(simple)(uint32_t, nAccountID) \
	_(simple)(uint16_t, result) \
	_(simple)(int8_t, nPCBangUser) \
	_(simple)(uint32_t, nEventCode) \
	_(simple)(uint32_t, nAge) \
	_(simple)(uint32_t, nContinuousPlayTime) \
	_(simple)(uint32_t, nContinuousLogoutTime) \
	_(string)(ip, 16) \
	_(simple)(uint32_t, loginTime)

CREATE_PACKET(TS_AG_CLIENT_LOGIN_EXTENDED, 60011, SessionType::AuthGame, SessionPacketOrigin::Server);
