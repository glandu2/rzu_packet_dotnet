#pragma once

#include "Packet/PacketDeclaration.h"

#define TS_US_REQUEST_UPLOAD_DEF(_) \
	_(simple)(uint16_t, result)

CREATE_PACKET(TS_US_REQUEST_UPLOAD, 50004, SessionType::UploadGame, SessionPacketOrigin::Server);
