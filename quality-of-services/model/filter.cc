/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/* Created by manalipatil on 4/24/19.
 *
 */
#include "ns3/log.h"
#include "ns3/packet.h"
#include "ns3/ipv4-address.h"
#include "filter-element.h"
#include "source-ip-address.h"
#include "source-port-number.h"
#include "destination-ip-address.h"
#include "destination-port-number.h"
#include "protocol-number.h"
#include "filter.h"
#include <iostream>

namespace ns3 {

    NS_LOG_COMPONENT_DEFINE("Filter");
    NS_OBJECT_ENSURE_REGISTERED(Filter);

    TypeId Filter::GetTypeId() {
        static TypeId tid = TypeId ("ns3::Filter")
                .SetParent<Object> ()
                .SetGroupName ("TrafficControl");
        return tid;
    }

    // Push this to main method. Change constructor
    // Filter elements to filter at run time
    Filter::Filter(Ipv4Address sourceIpAddress, uint16_t sourcePort, Ipv4Address destinationIpAddress, uint16_t destinationPort, uint8_t protocolNumber){
    	FilterElement* sourceIpFilterElement = new SourceIpAddress(sourceIpAddress);
    	this->AddFilterElement(sourceIpFilterElement);

    	FilterElement* destinationIpFilterElement = new DestinationIpAddress(destinationIpAddress);
    	this->AddFilterElement(destinationIpFilterElement);

    	FilterElement* sourcePortFilterElement = new SourcePortNumber(sourcePort);
		this->AddFilterElement(sourcePortFilterElement);

		FilterElement* destinationPortFilterElement = new DestinationPortNumber(destinationPort);
		this->AddFilterElement(destinationPortFilterElement);

		FilterElement* protocolFilterElement = new ProtocolNumber(protocolNumber);
		this->AddFilterElement(protocolFilterElement);
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

    // Return true iff match is true on all the filter elements
    bool Filter::Match(Ptr<ns3::Packet> packet){
        for(FilterElement* filterElement:filterElements){
            if(!filterElement->Match(packet)){
                std::cout<<"Match not Found"<<std::endl;
                return false;
            }
        }
        return true;
    }
};
