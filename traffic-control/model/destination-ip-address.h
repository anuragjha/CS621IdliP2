
#ifndef DESTINATION_IP_ADDRESS_H
#define DESTINATION_IP_ADDRESS_H

#include "ns3/log.h"
#include "ns3/integer.h"
#include "ns3/ppp-header.h"
#include "ns3/pointer.h"
#include "queue-disc.h"
#include "filter-element.h"
#include "ns3/ipv4-address.h"

namespace ns3 {

class DestinationIpAddress: public FilterElement {
public:

  static TypeId GetTypeId (void);

    DestinationIpAddress(Ipv4Address);
    DestinationIpAddress ();
  ~DestinationIpAddress ();

  /**
   * Standard value used by packet filters to indicate that no match was possible.
   */
  //static const int PF_NO_MATCH = -1;

  bool Match (Ptr<Packet> packet);


private:
  Ipv4Address value;
};
} // namespace ns3

#endif /* DESTINATION_IP_ADDRESS_H */
