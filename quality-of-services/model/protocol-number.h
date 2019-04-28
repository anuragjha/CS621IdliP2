
#ifndef SOURCE_IP_ADDRESS_H
#define SOURCE_IP_ADDRESS_H

#include "ns3/log.h"
#include "filter-element.h"
#include "ns3/ipv4-address.h"

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

#endif /* SOURCE_IP_ADDRESS */
