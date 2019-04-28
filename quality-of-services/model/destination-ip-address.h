
#ifndef DESTINATION_IP_ADDRESS_H
#define DESTINATION_IP_ADDRESS_H

#include "ns3/log.h"
#include "filter-element.h"
#include "ns3/ipv4-address.h"

namespace ns3 {
	class DestinationIpAddress: public FilterElement {
		public:
		  static TypeId GetTypeId (void);
		  DestinationIpAddress (Ipv4Address value);
		  bool Match (Ptr<Packet> packet);
		private:
			  Ipv4Address value;
	};
} // namespace ns3

#endif /* DESTINATION_IP_ADDRESS */
