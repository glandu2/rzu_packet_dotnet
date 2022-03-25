#pragma once

#include "Packet/PacketDeclaration.h"

#define TS_SU_LOGIN_DEF(_) \
	_(string)(server_name, 21)

CREATE_PACKET(TS_SU_LOGIN, 50001, SessionType::UploadGame, SessionPacketOrigin::Client);


