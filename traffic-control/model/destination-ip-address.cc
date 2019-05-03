
#include "ns3/log.h"
#include "ns3/integer.h"
#include "destination-ip-address.h"
#include "ns3/log.h"
#include "ns3/queue.h"
#include "ns3/ipv4-header.h"
#include "stdio.h"
#include <iostream>

namespace ns3 {

    NS_LOG_COMPONENT_DEFINE ("DestinationIpAddress");


    NS_OBJECT_ENSURE_REGISTERED (DestinationIpAddress);

    TypeId
    DestinationIpAddress::GetTypeId (void)
    {
    static TypeId tid = TypeId ("ns3::DestinationIpAddress")
        .SetParent<Object> ()
        .SetGroupName ("TrafficControl")
    ;
    return tid;
    }

    DestinationIpAddress::DestinationIpAddress (Ipv4Address ipv4add)
    {
        NS_LOG_FUNCTION (this);
        value = ipv4add;
    }

    DestinationIpAddress::DestinationIpAddress ()
    {
    NS_LOG_FUNCTION (this);
    }

    DestinationIpAddress::~DestinationIpAddress()
    {
    NS_LOG_FUNCTION (this);
    }


    bool
    DestinationIpAddress::Match (Ptr<Packet> packet)
    {
        NS_LOG_FUNCTION (this);
        Ptr<Packet> copy = packet->Copy ();
        PppHeader ppph;
        Ipv4Header iph;
        copy->RemoveHeader(ppph);
        copy->RemoveHeader(iph);

        Ipv4Address Ipv4Address = iph.GetSource();
        if(Ipv4Address.IsEqual(this->value)){
            std::cout<<" Matched Ipv4Address:" << Ipv4Address <<std::endl;
            return true;
        }  else{
            std::cout<<" Not Matched Ipv4Address:" << Ipv4Address <<std::endl;
            return false;
        }

    }


}// namespace ns3