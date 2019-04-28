/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/* Created by manalipatil on 4/24/19.
 *
 */
#include "ns3/log.h"
#include "ns3/packet.h"
#include "ns3/ipv4-address.h"
#include "filter-element.h"
#include "filter.h"
#include <iostream>

namespace ns3 {

    NS_LOG_COMPONENT_DEFINE("Filter");
    NS_OBJECT_ENSURE_REGISTERED(Filter);

    TypeId Filter::GetTypeId() {
        static TypeId tid = TypeId ("ns3::Filter")
                .SetParent<Object> ()
                .SetGroupName ("TrafficControl")
        ;
        return tid;
    }

    Filter::Filter(Ipv4Address sourceIpAddress, uint16_t sourcePort, Ipv4Address destinationIpAddress, uint16_t destinationPort, uint8_t protocolNumber){
    }

    void Filter::PrintFilterElements() {
        for(FilterElement* filterElement:filterElements){
            std::cout<<"Here Filter Element:"<<(filterElement)<<std::endl;
        }
    }

    std::vector<ns3::FilterElement*> Filter::GetFilterElements(){
    	return filterElements;
    }

    void Filter::AddFilterElement(ns3::FilterElement* filterElement){
    	filterElements.push_back(filterElement);
    }

    bool Filter::Match(Ptr<ns3::Packet> packet){
        for(FilterElement* filterElement:filterElements){
            if(filterElement->Match(packet)){
                std::cout<<"Match Found"<<std::endl;
                return true;
            }
        }
        return false;
    }
};
