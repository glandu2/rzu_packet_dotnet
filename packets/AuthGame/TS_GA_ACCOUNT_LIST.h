#pragma once

#include "Packet/PacketDeclaration.h"

#define TS_GA_ACCOUNT_LIST__ACCOUNT_INFO_DEF(_) \
	_(string)(account, 61) \
	_(simple)(uint32_t, nAccountID) \
	_(simple)(int8_t, nPCBangUser) \
	_(simple)(uint32_t, nEventCode) \
	_(simple)(uint32_t, nAge) \
	_(string)(ip, 16) \
	_(simple)(uint32_t, loginTime)

CREATE_STRUCT(TS_GA_ACCOUNT_LIST__ACCOUNT_INFO);

#define TS_GA_ACCOUNT_LIST_DEF(_) \
	_(simple)(bool, final_packet) \
	_(count)(uint8_t, accountInfo) \
	_(dynarray)(TS_GA_ACCOUNT_LIST__ACCOUNT_INFO, accountInfo) \
	_(simple)(uint32_t, nEventCode) \
	_(simple)(uint32_t, nAge) \
	_(simple)(uint32_t, nContinuousPlayTime) \
	_(simple)(uint32_t, nContinuousLogoutTime)

CREATE_PACKET(TS_GA_ACCOUNT_LIST, 60003, SessionType::AuthGame, SessionPacketOrigin::Client);
