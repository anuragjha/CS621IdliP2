//
// Created by manalipatil on 4/22/19.
//
#include "ns3/log.h"
#include "ns3/ipv4-header.h"
#include "protocol-number.h"
#include "ns3/udp-header.h"
#include "ns3/ppp-header.h"

namespace ns3{
    NS_LOG_COMPONENT_DEFINE ("ProtocolNumber");

    NS_OBJECT_ENSURE_REGISTERED (ProtocolNumber);

    TypeId
    ProtocolNumber::GetTypeID(){
        static TypeId tid = TypeId ("ns3::ProtocolNumber")
                .SetParent<FilterElement> ()
                .SetGroupName ("TrafficControl")
        ;
        return tid;
    }

    ProtocolNumber::ProtocolNumber(uint8_t value):FilterElement() {
        this->value = value;
    }

    ProtocolNumber::~ProtocolNumber() {

    }

    bool
    ProtocolNumber::Match (Ptr<ns3::Packet> p)
    {
        NS_LOG_FUNCTION (this);
        Ptr<Packet> copyPacket = p -> Copy();
        Ipv4Header ipv4Header;
        PppHeader pppHeader;

        copyPacket -> RemoveHeader(pppHeader);
        copyPacket -> RemoveHeader(ipv4Header);

        uint8_t protocolNumber = ipv4Header.GetProtocol();

        if(protocolNumber==value ){
           // std::cout<<" Matched protocolNumber:" << protocolNumber <<std::endl;
            return true;
        }  else{
            //std::cout<<" Not Matched protocolNumber:" << protocolNumber <<std::endl;
            return false;
        }
    }
}
