
#include "ns3/log.h"
#include "ns3/integer.h"
#include "ns3/ppp-header.h"
#include "ns3/udp-header.h"
#include "ns3/ipv4-header.h" 
#include "protocol-number.h"
#include "stdio.h"
#include <iostream>

namespace ns3 {

    NS_LOG_COMPONENT_DEFINE ("ProtocolNumber");
    NS_OBJECT_ENSURE_REGISTERED (ProtocolNumber);

    TypeId ProtocolNumber::GetTypeId(void){
    	static TypeId tid = TypeId ("ns3::ProtocolNumber")
        .SetParent<Object> ()
        .SetGroupName ("TrafficControl");
    	return tid;
    }

    ProtocolNumber::ProtocolNumber(uint8_t value){
    	this->value = value;
    }

    bool ProtocolNumber::Match (Ptr<Packet> packet){
    	Ptr<Packet> copy = packet->Copy ();
    	PppHeader ppph;
		Ipv4Header iph;
		copy->RemoveHeader(ppph);
		copy->RemoveHeader(iph);

		uint8_t packetProtocol = iph.GetProtocol();
		if(packetProtocol == this->value){
			std::cout<<" Matched protocol:" << packetProtocol <<std::endl;
			return true;
		}  else{
			std::cout<<" Not Matched protocol:" << packetProtocol <<std::endl;
			return false;
		}
    }
}// namespace ns3
