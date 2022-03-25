#pragma once

#include "Packet/PacketDeclaration.h"

#define TS_GA_LOGIN_DEF(_) \
	_(simple)(uint16_t, server_idx) \
	_(string)(server_name, 21) \
	_(string)(server_screenshot_url, 256) \
	_(simple)(bool, is_adult_server) \
	_(string)(server_ip, 16) \
	_(simple)(int32_t, server_port)

CREATE_PACKET(TS_GA_LOGIN, 20001, SessionType::AuthGame, SessionPacketOrigin::Client);

#define TS_GA_LOGIN_WITH_LOGOUT_DEF(_) \
	_(simple)(uint16_t, server_idx) \
	_(string)(server_name, 21) \
	_(string)(server_screenshot_url, 256) \
	_(simple)(bool, is_adult_server) \
	_(string)(server_ip, 16) \
	_(simple)(int32_t, server_port)

CREATE_PACKET(TS_GA_LOGIN_WITH_LOGOUT, 60001, SessionType::AuthGame, SessionPacketOrigin::Client);

#define TS_GA_LOGIN_WITH_LOGOUT_EXT_DEF(_) \
	_(simple)(uint16_t, server_idx) \
	_(string)(server_name, 21) \
	_(string)(server_screenshot_url, 256) \
	_(simple)(bool, is_adult_server) \
	_(string)(server_ip, 16) \
	_(simple)(int32_t, server_port) \
	_(array)(uint8_t, guid, 16)

CREATE_PACKET(TS_GA_LOGIN_WITH_LOGOUT_EXT, 60004, SessionType::AuthGame, SessionPacketOrigin::Client);


