
#include "ns3/log.h"
#include "ns3/integer.h"
#include "source-ip-address.h"
#include "ns3/log.h"
#include "ns3/queue.h"
#include "ns3/ipv4-header.h"
#include "source-ip-address.h"
#include "stdio.h"
#include <iostream>

namespace ns3 {

    NS_LOG_COMPONENT_DEFINE ("SourceIpAddress");


    NS_OBJECT_ENSURE_REGISTERED (SourceIpAddress);

    TypeId
    SourceIpAddress::GetTypeId (void)
    {
    static TypeId tid = TypeId ("ns3::SourceIpAddress")
        .SetParent<Object> ()
        .SetGroupName ("TrafficControl")
    ;
    return tid;
    }

    SourceIpAddress::SourceIpAddress (Ipv4Address ipv4add)
    {
        NS_LOG_FUNCTION (this);
        value = ipv4add;
    }


    SourceIpAddress::SourceIpAddress ()
    {
        NS_LOG_FUNCTION (this);
    }


    SourceIpAddress::~SourceIpAddress()
    {
    NS_LOG_FUNCTION (this);
    }




    bool
    SourceIpAddress::Match (Ptr<Packet> packet)
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