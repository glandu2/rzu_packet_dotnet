#pragma once

#include "PacketEpics.h"
#include <stdint.h>

namespace RappelzPackets {
	template<class Encoder> public ref class EncodedInt {
	public:
		EncodedInt(uint32_t v) : value(v) {}

		EncodedInt^ operator=(uint32_t v) {
			value = v;
			return this;
		}
		bool operator==(uint32_t v) { return v == value; }
		bool operator==(EncodedInt^ v) { return v->value == value; }

		operator uint32_t() { return value; }

		uint32_t getSize(packet_version_t version) { return Encoder::getSize(version); }

		template<class T> void serialize(T^ buffer) { Encoder::template serialize<T>(buffer, value); }

		template<class T> void deserialize(T^ buffer) { Encoder::template deserialize<T>(buffer, value); }

	private:
		uint32_t value;
	};
}