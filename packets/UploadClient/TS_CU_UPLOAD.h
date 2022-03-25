#pragma once

#include "Packet/PacketDeclaration.h"

#define TS_CU_UPLOAD_DEF(_) \
	_(count)(uint32_t, file_contents) \
	_(dynstring)(file_contents, true)

CREATE_PACKET(TS_CU_UPLOAD, 50007, SessionType::UploadClient, SessionPacketOrigin::Client);
