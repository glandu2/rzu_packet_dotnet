#pragma once

#include <stdint.h>

//typedef uint32_t packet_version_t;

namespace RappelzPackets {
	public value struct packet_version_t {
		packet_version_t(unsigned int epic) { version = epic;  }

		int compare(unsigned int epic) { return (this->version & 0x00FFFFFF) - epic; }
		int compare(packet_version_t other) { return this->version - other.version; }

		bool operator==(unsigned int epic) { return compare(epic) == 0; }
		bool operator==(packet_version_t other) { return compare(other) == 0; }

		bool operator!=(unsigned int epic) { return !operator==(epic); }
		bool operator!=(packet_version_t other) { return !operator==(other); }

		bool operator>=(unsigned int epic) { return compare(epic) >= 0; }
		bool operator>=(packet_version_t other) { return compare(other) >= 0; }

		bool operator>(unsigned int epic) { return compare(epic) > 0; }
		bool operator>(packet_version_t other) { return compare(other) > 0; }

		bool operator<=(unsigned int epic) { return compare(epic) <= 0; }
		bool operator<=(packet_version_t other) { return compare(other) <= 0; }

		bool operator<(unsigned int epic) { return compare(epic) < 0; }
		bool operator<(packet_version_t other) { return compare(other) < 0; }

		int flag(unsigned int flag) { return (version >> 24) & flag; }
		unsigned int getAsInt() { return version; }

		uint32_t version;
	};

	public ref struct Epics {
		// Epics

		static initonly packet_version_t EPIC_2 = packet_version_t(0x020100);
		static initonly packet_version_t EPIC_3 = packet_version_t(0x030100);
		static initonly packet_version_t EPIC_4_1 = packet_version_t(0x040100);
		static initonly packet_version_t EPIC_4_1_1 = packet_version_t(0x040101);
		static initonly packet_version_t EPIC_5_1 = packet_version_t(0x050100);
		static initonly packet_version_t EPIC_5_2 = packet_version_t(0x050200);
		static initonly packet_version_t EPIC_6_1 = packet_version_t(0x060100);
		static initonly packet_version_t EPIC_6_2 = packet_version_t(0x060200);
		static initonly packet_version_t EPIC_6_3 = packet_version_t(0x060300);
		static initonly packet_version_t EPIC_7_1 = packet_version_t(0x070100);
		static initonly packet_version_t EPIC_7_2 = packet_version_t(0x070200);
		static initonly packet_version_t EPIC_7_3 = packet_version_t(0x070300);
		static initonly packet_version_t EPIC_7_4 = packet_version_t(0x070400);
		static initonly packet_version_t EPIC_8_1 = packet_version_t(0x080100);
		static initonly packet_version_t EPIC_8_1_1_RSA = packet_version_t(0x080101);
		static initonly packet_version_t EPIC_8_2 = packet_version_t(0x080200);
		static initonly packet_version_t EPIC_8_3 = packet_version_t(0x080300);
		static initonly packet_version_t EPIC_9_1 = packet_version_t(0x090100);
		static initonly packet_version_t EPIC_9_2 = packet_version_t(0x090200);
		static initonly packet_version_t EPIC_9_3 = packet_version_t(0x090300);
		static initonly packet_version_t EPIC_9_4 = packet_version_t(0x090400);
		static initonly packet_version_t EPIC_9_4_AR = packet_version_t(0x090401);
		static initonly packet_version_t EPIC_9_4_2 = packet_version_t(0x090402);  // newer login packet id
		static initonly packet_version_t EPIC_9_5 = packet_version_t(0x090500);
		static initonly packet_version_t EPIC_9_5_1 = packet_version_t(0x090501);  // 2017/09/26
		static initonly packet_version_t EPIC_9_5_2 = packet_version_t(0x090502);  // GS Version packet modified, 2018 02 27
		static initonly packet_version_t EPIC_9_5_3 = packet_version_t(0x090503);  // GS Version packet modified, 20181211
		static initonly packet_version_t EPIC_9_6 = packet_version_t(0x090600);    // GS Version packet modified, 20190102

		// KTS 9.6 20190123 doesn't support the changes in TS_SC_INVENTORY, so remap them as 9.6.1 instead of 9.6
		static initonly packet_version_t EPIC_9_6_1 = packet_version_t(0x090601);

		// Defined from FR version on 2020-03-07
		// Tested packets: 0, 2, 3, 8, 9, 11, 12, 13, 20, 22, 23, 25, 26, 27, 51, 55, 56, 62, 63, 64, 67, 71, 72, 100, 101, 102,
		// 150, 200, 201, 202, 204, 207, 210, 211, 212, 216, 217, 221, 222, 223, 240, 250, 251, 253, 255, 256, 257, 264, 282,
		// 283, 286, 287, 301, 303, 305, 324, 351, 400, 401, 402, 403, 404, 406, 407, 500, 503, 505, 507, 508, 509, 511, 514,
		// 516, 517, 600, 604, 625, 626, 627, 629, 631, 636, 702, 703, 704, 707, 708, 900, 901, 902, 1000, 1001, 1002, 1003,
		// 1004, 1005, 1100, 1101, 1300, 1301, 2004, 2005, 2007, 3000, 3001, 3002, 4250, 4251, 4252, 4253, 4700, 5000, 5001,
		// 7000, 7001, 7002, 8000, 9001, 9999, 10000, 10001, 10003, 10004, 10010, 10014, 10021, 10022, 10023, 10024
		// Notes: some items have new ID now, which breaks old client that doesn't know how to handle these.
		//        also, NPC dialogs are broken: the text is ok but there is no choice available
		static initonly packet_version_t EPIC_9_6_2 = packet_version_t(0x090602);

		// Packet ID mapping:
		// >= 0 && < 2000: += 1000
		// >= 2000 < 3000: += 400
		// >= 9000 < 9999: -= 900
		// >= 10000: -= 1000
		static initonly packet_version_t EPIC_9_6_3 = packet_version_t(0x090603);  // GS packet ID modified with version 20200713

		static initonly packet_version_t EPIC_9_6_4 = packet_version_t(0x090604);  // GS packet ID modified with version 20200922

		static initonly packet_version_t EPIC_9_6_5 = packet_version_t(0x090605);  // some int16_t fields were replaced with int32_t

		static initonly packet_version_t EPIC_9_6_6 = packet_version_t(0x090606);  // GS packet ID modified with version 20210128

		static initonly packet_version_t EPIC_9_6_7 = packet_version_t(0x090607);  // changes to player and item data


#define EPIC_2 Epics::EPIC_2
#define EPIC_3 Epics::EPIC_3
#define EPIC_4_1 Epics::EPIC_4_1
#define EPIC_4_1_1 Epics::EPIC_4_1_1
#define EPIC_5_1 Epics::EPIC_5_1
#define EPIC_5_2 Epics::EPIC_5_2
#define EPIC_6_1 Epics::EPIC_6_1
#define EPIC_6_2 Epics::EPIC_6_2
#define EPIC_6_3 Epics::EPIC_6_3
#define EPIC_7_1 Epics::EPIC_7_1
#define EPIC_7_2 Epics::EPIC_7_2
#define EPIC_7_3 Epics::EPIC_7_3
#define EPIC_7_4 Epics::EPIC_7_4
#define EPIC_8_1 Epics::EPIC_8_1
#define EPIC_8_1_1_RSA Epics::EPIC_8_1_1_RSA
#define EPIC_8_2 Epics::EPIC_8_2
#define EPIC_8_3 Epics::EPIC_8_3
#define EPIC_9_1 Epics::EPIC_9_1
#define EPIC_9_2 Epics::EPIC_9_2
#define EPIC_9_3 Epics::EPIC_9_3
#define EPIC_9_4 Epics::EPIC_9_4
#define EPIC_9_4_AR Epics::EPIC_9_4_AR
#define EPIC_9_4_2 Epics::EPIC_9_4_2
#define EPIC_9_5 Epics::EPIC_9_5
#define EPIC_9_5_1 Epics::EPIC_9_5_1
#define EPIC_9_5_2 Epics::EPIC_9_5_2
#define EPIC_9_5_3 Epics::EPIC_9_5_3
#define EPIC_9_6 Epics::EPIC_9_6
#define EPIC_9_6_1 Epics::EPIC_9_6_1
#define EPIC_9_6_2 Epics::EPIC_9_6_2
#define EPIC_9_6_3 Epics::EPIC_9_6_3
#define EPIC_9_6_4 Epics::EPIC_9_6_4
#define EPIC_9_6_5 Epics::EPIC_9_6_5
#define EPIC_9_6_6 Epics::EPIC_9_6_6
#define EPIC_9_6_7 Epics::EPIC_9_6_7

																			
// Latest released epic
#define EPIC_LATEST EPIC_9_6_7

// Flags

#define EPIC_FLAG_TESTSERVER 1
	};
}