
#include "source-port-number.h"
#include "ns3/packet.h"
#include "ns3/log.h"
#include "ns3/ipv4-header.h"
#include "ns3/ipv4-address.h"
#include "ns3/udp-header.h"
#include "ns3/ppp-header.h"

namespace ns3{

    NS_LOG_COMPONENT_DEFINE ("SourcePortNumber");
    NS_OBJECT_ENSURE_REGISTERED (SourcePortNumber);

    TypeId
    SourcePortNumber::GetTypeId (void)
    {
        static TypeId tid = TypeId ("ns3::SourcePortNumber")
                .SetParent<FilterElement> ()
                .SetGroupName ("trafficControl")
        ;
        return tid;
    }

    SourcePortNumber::SourcePortNumber (uint32_t val)
    {
        value = val;
        std::cout << " Constructor.SourcePortNumber.value:" << value << std::endl;

    }


    SourcePortNumber::~SourcePortNumber()
    {
        NS_LOG_FUNCTION (this);
    }

    bool 
    SourcePortNumber::Match (Ptr<Packet> p)
    {
       NS_LOG_FUNCTION (this);
	   Ptr<Packet> copyPacket = p -> Copy();
       PppHeader pppHeader;
	   Ipv4Header ipv4Header;
	   UdpHeader udpHeader;
       copyPacket -> RemoveHeader(pppHeader);
	   copyPacket -> RemoveHeader(ipv4Header);
	   copyPacket -> RemoveHeader(udpHeader);
	   uint32_t sourcePort = udpHeader.GetSourcePort();
        std::cout << "source Port number >>>>>>>>>>>>>>>>>>>>>>>>> " << sourcePort << "\n";
	   if(sourcePort == value){
           return true;
	   }
        return false;
       //std::cout << " SourcePortNumber.sourcePort:" << sourcePort << std::endl;              
       //std::cout << " SourcePortNumber.value:" << value << std::endl;
        //std::cout << "source Port number : " << sourcePort << "\n";
	   //return sourcePort;
    }

}

//Ptr<Packet> copyPacket = item -> Copy();
//PppHeader pppHeader;
//Ipv4Header ipv4Header;
//UdpHeader udpHeader;
//copyPacket -> RemoveHeader(pppHeader);
//copyPacket -> RemoveHeader(ipv4Header);
//copyPacket -> RemoveHeader(udpHeader);
//uint32_t sourcePort = udpHeader.GetSourcePort();
//uint32_t destPort = udpHeader.GetDestinationPort();
//std::cout << "source Port number : " << sourcePort << "\n";