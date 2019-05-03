//
// Created by manalipatil on 4/24/19.
//

#include "filter-element.h"
#include "ns3/log.h"
#include "ns3/packet.h"
#include "ns3/pointer.h"
#include "ns3/object.h"

namespace ns3{
    NS_LOG_COMPONENT_DEFINE("FilterElement");
    NS_OBJECT_ENSURE_REGISTERED(FilterElement);

    TypeId FilterElement::GetTypeID() {
        static TypeId tid = TypeId ("ns3::FilterElement")
                .SetParent<Object> ()
                .SetGroupName ("TrafficControl")
        ;
        return tid;
    }

    FilterElement::FilterElement() {

    }

    FilterElement::~FilterElement() {

    }

//    virtual bool FilterElement::Match(Ptr <Packet> packet);// {
      //  return true;
  //  }
}

