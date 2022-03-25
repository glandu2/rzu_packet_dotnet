#pragma once

#include "Packet/PacketDeclaration.h"

#define TS_GA_LOGOUT_DEF(_)

CREATE_PACKET(TS_GA_LOGOUT, 60002, SessionType::AuthGame, SessionPacketOrigin::Client);
