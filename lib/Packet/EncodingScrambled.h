#pragma once

#include "../Extern.h"
#include "EncodingRandomized.h"

namespace RappelzPackets {
	class EncodingScrambled {
	public:
		static uint32_t getSize(packet_version_t version) { return EncodingRandomized::getSize(version); }

		template<class T> static void serialize(T^ buffer, uint32_t value) {
			EncodingRandomized::serialize<T>(buffer, encode(value));
		}

		template<class T> static void deserialize(T^ buffer, uint32_t% value) {
			uint32_t deserializedValue;
			EncodingRandomized::deserialize<T>(buffer, deserializedValue);

			value = decode(deserializedValue);
		}

	private:
		EncodingScrambled();

		static void init();
		static uint32_t encode(uint32_t v);
		static uint32_t decode(uint32_t v);

		static bool mapInitialized;
		static uint8_t encodeMap[32];
		static uint8_t decodeMap[32];
	};
}