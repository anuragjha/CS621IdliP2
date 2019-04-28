
#include "ns3/log.h"
#include "ns3/integer.h"
#include "ns3/ppp-header.h"
#include "ns3/udp-header.h"
#include "ns3/ipv4-header.h"
#include "ns3/uinteger.h"
#include "source-port-number.h"
#include "stdio.h"
#include <iostream>

namespace ns3 {

    NS_LOG_COMPONENT_DEFINE ("SourcePortNumber");
    NS_OBJECT_ENSURE_REGISTERED (SourcePortNumber);

    TypeId SourcePortNumber::GetTypeId(void){
    	static TypeId tid = TypeId ("ns3::SourcePortNumber")
        .SetParent<Object> ()
        .SetGroupName ("TrafficControl");
    	return tid;
    }

    SourcePortNumber::SourcePortNumber(uint16_t value){
    	// NS_LOG_FUNCTION (this);
    	this->value = value;
    }

    bool SourcePortNumber::Match(Ptr<Packet> packet){
    	// NS_LOG_FUNCTION (this << packet);
    	Ptr<Packet> copy = packet->Copy ();
    	PppHeader ppph;
		Ipv4Header iph;
		UdpHeader udph;

		copy->RemoveHeader(ppph);
		copy->RemoveHeader(iph);
		copy->RemoveHeader(udph);

		uint16_t sourcePort = udph.GetSourcePort();
		if(sourcePort == this->value){
			std::cout<<" Matched sourcePort:" << sourcePort <<std::endl;
			return true;
		}else{
			std::cout<<" Not Matched sourcePort:" << sourcePort <<std::endl;
			return false;
		}
    }
}// namespace ns3
