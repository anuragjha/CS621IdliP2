//
// Created by manalipatil on 4/22/19.
//
#include "ns3/log.h"
#include "ns3/packet.h"
#include "filter-element.h"
#include "filter.h"
#include <iostream>

namespace ns3 {

    NS_LOG_COMPONENT_DEFINE("Filter");
    NS_OBJECT_ENSURE_REGISTERED(Filter);

    TypeId Filter::GetTypeId() {
        static TypeId tid = TypeId("ns3::Filter")
                .SetParent<Object>()
                .SetGroupName("TrafficControl");
        return tid;
    }

    Filter::Filter() {
        //  NS_LOG_FUNCTION(this);
    }

    Filter::~Filter() {
        //  NS_LOG_fUNCTION(this);
    }

    void Filter::PrintFilterElements() {
        for (FilterElement *filterElement:filterElements) {
            std::cout << "Here Filter Element:" << (filterElement) << std::endl;
        }
    }

    bool Filter::Match(Ptr <ns3::Packet> packet) {
        for (FilterElement *filterElement:filterElements) {
            if (!filterElement->Match(packet)) {
                std::cout << "Match Found" << std::endl;
                return false;
            }
            //  auto iter = filterElements.begin();
            //for(;iter!=filterElements.end();iter++){
            //  std::cout<<*iter<<" ";
            //if ((**iter).Match(packet)==false){
            //  return false;
            //}
            //}
            //return true;
            // auto iter = filterElements.begin();
            // for(;iter != filterElements.end();iter++){
            //     if ((iter**).Match(packet) == false){
            //        return false;
            //    }
        }
        return true;
    }
}
