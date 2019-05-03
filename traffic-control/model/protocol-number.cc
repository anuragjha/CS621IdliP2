//
// Created by manalipatil on 4/22/19.
//
#include "ns3/log.h"
#include "ns3/ipv4-header.h"
#include "protocol-number.h"

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

    ProtocolNumber::ProtocolNumber(uint32_t value):FilterElement() {
        this->value = value;
    }

    ProtocolNumber::~ProtocolNumber() {

    }

    bool
    ProtocolNumber::Match (Ptr<ns3::Packet> packet)
    {
        NS_LOG_FUNCTION (this);

        Ipv4Header ipv4Header;
        packet->PeekHeader(ipv4Header);

        uint8_t protocolNumber = ipv4Header.GetProtocol();

        if(protocolNumber==value ){
            std::cout<<" Matched protocolNumber:" << protocolNumber <<std::endl;
            return true;
        }  else{
            std::cout<<" Not Matched protocolNumber:" << protocolNumber <<std::endl;
            return false;
        }
    }
}
