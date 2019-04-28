
#ifndef DESTINATION_PORT_NUMBER_H
#define DESTINATION_PORT_NUMBER_H

#include "ns3/log.h"
#include "filter-element.h"
#include "ns3/uinteger.h"

namespace ns3 {
	class DestinationPortNumber: public FilterElement {
		public:
		  static TypeId GetTypeId (void);
		  DestinationPortNumber (uint16_t value);
		  bool Match (Ptr<Packet> packet);
		private:
		  uint16_t value;
	};
} // namespace ns3

#endif /* DESTINATION_PORT_NUMBER */
