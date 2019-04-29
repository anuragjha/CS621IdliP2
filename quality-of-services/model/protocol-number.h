
#ifndef PROTOCOL_NUMBER_H
#define PROTOCOL_NUMBER_H

#include "ns3/log.h"
#include "ns3/ipv4-address.h"
#include "filter-element.h"

namespace ns3 {
	class ProtocolNumber: public FilterElement {
		public:
			static TypeId GetTypeId (void);
			ProtocolNumber (uint8_t value);
			bool Match (Ptr<Packet> packet);
		private:
			uint8_t value;
	};
} // namespace ns3

#endif /* PROTOCOL_NUMBER */
