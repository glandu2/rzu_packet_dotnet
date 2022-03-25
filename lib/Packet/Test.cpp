#include "PacketIterator.h"
#include <stdio.h>

using namespace System::Collections::Generic;

namespace RappelzPackets {

	template<class Packet> struct FunctorPrint {
		void operator()() {
			Console::WriteLine("{0}: {1}", Packet::getName(), Packet::getId(EPIC_LATEST));
		}
	};

	template<class Packet> struct FunctorDeserializeSerialize {
		void operator()() {
			MemoryStream^ stream = gcnew MemoryStream();
			Packet^ packet1 = gcnew Packet;
			Packet^ packet2 = gcnew Packet;

			packet1->serialize(stream, RappelzPackets::Epics::EPIC_9_6_7, Encoding::UTF8);
			stream->Seek(0, SeekOrigin::Begin);
			packet2->deserialize(stream, RappelzPackets::Epics::EPIC_9_6_7, Encoding::UTF8);
		}
	};

	template<class Packet> struct FunctorReturnLatestId {
		int operator()() {
			/*printf"   Got %s: %d\n",
				Packet::getName(),
				Packet::getId(EPIC_LATEST));*/
			return Packet::getId(EPIC_LATEST);
		}
	};

	template<class Packet> struct FunctorCheckLatestId {
		void operator()() {
			Console::WriteLine("Checking {0}: {1}",
				Packet::getName(),
				Packet::getId(EPIC_LATEST));
			List<SessionType>^ sessionTypes = gcnew List<SessionType>();
			List<SessionPacketOrigin>^ origins = gcnew List<SessionPacketOrigin>();

			if (Packet::SESSION_TYPE != SessionType::Any) {
				sessionTypes->Add(Packet::SESSION_TYPE);
			}
			else {
				sessionTypes->Add(SessionType::AuthClient);
				sessionTypes->Add(SessionType::GameClient);
			}

			if (Packet::ORIGIN != SessionPacketOrigin::Any) {
				origins->Add(Packet::ORIGIN);
			}
			else {
				origins->Add(SessionPacketOrigin::Client);
				origins->Add(SessionPacketOrigin::Server);
			}

			for (size_t i = 0; i < sessionTypes->Count; i++) {
				for (size_t j = 0; j < origins->Count; j++) {
					int id = 0;
					processPacket<FunctorReturnLatestId>(
						sessionTypes[i], origins[j], EPIC_LATEST, Packet::getId(EPIC_LATEST), id);
					if (id != Packet::getId(EPIC_LATEST)) {
						Console::WriteLine("with session type {0} and origin {1}", (int)sessionTypes[i], (int)origins[j]);
					}
				}
			}
		}
	};

	public ref class Test {
	public:

		void PacketIterator_iterator() {
			switch (0) {
			case TS_SC_RESULT::packetID:
				break;
			}
			iteratePackets<FunctorPrint>();
		}

		void PacketIterator_serialize_deserialize() {
			iteratePackets<FunctorDeserializeSerialize>();
		}

		void PacketIterator_process() {
			iteratePackets<FunctorCheckLatestId>();
		}
	};
}