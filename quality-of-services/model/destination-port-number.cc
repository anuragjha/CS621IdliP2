
#include "ns3/log.h"
#include "ns3/integer.h"
#include "ns3/ppp-header.h"
#include "ns3/udp-header.h"
#include "ns3/ipv4-header.h"
#include "ns3/uinteger.h"
#include "destination-port-number.h"
#include "stdio.h"
#include <iostream>

namespace ns3 {

    NS_LOG_COMPONENT_DEFINE ("DestinationPortNumber");
    NS_OBJECT_ENSURE_REGISTERED (DestinationPortNumber);

    TypeId DestinationPortNumber::GetTypeId(void){
    	static TypeId tid = TypeId ("ns3::DestinationPortNumber")
        .SetParent<Object> ()
        .SetGroupName ("TrafficControl");
    	return tid;
    }

    DestinationPortNumber::DestinationPortNumber(uint16_t value){
    	// NS_LOG_FUNCTION (this);
    	this->value = value;
    }

    bool DestinationPortNumber::Match(Ptr<Packet> packet){
    	// NS_LOG_FUNCTION (this << packet);
    	Ptr<Packet> copy = packet->Copy ();
    	PppHeader ppph;
		Ipv4Header iph;
		UdpHeader udph;

		copy->RemoveHeader(ppph);
		copy->RemoveHeader(iph);
		copy->RemoveHeader(udph);

		uint16_t destinationPort = udph.GetDestinationPort();
		if(destinationPort == this->value){
			std::cout<<" Matched sourcePort:" << destinationPort <<std::endl;
			return true;
		}else{
			std::cout<<" Not Matched sourcePort:" << destinationPort <<std::endl;
			return false;
		}
    }
}// namespace ns3
