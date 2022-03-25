#pragma once

#include "Packet/PacketDeclaration.h"

enum TS_GA_SECURITY_NO_CHECK__Mode : uint32_t
{
	SC_NONE = 0x0,
	SC_OPEN_STORAGE = 0x1,
	SC_DELETE_CHARACTER = 0x2,
};

#define TS_GA_SECURITY_NO_CHECK_DEF(_) \
	_(string)(account, 61) \
	_(string)(security, 19) \
	_(simple)(TS_GA_SECURITY_NO_CHECK__Mode, mode, version >= EPIC_6_1)

CREATE_PACKET(TS_GA_SECURITY_NO_CHECK, 40001, SessionType::AuthGame, SessionPacketOrigin::Client);
