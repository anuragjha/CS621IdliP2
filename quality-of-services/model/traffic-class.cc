//
// Created by manalipatil on 4/23/19.
//
#include "traffic-class.h"
#include "ns3/drop-tail-queue.h"
#include "ns3/log.h"
#include "ns3/pointer.h"
#include "ns3/uinteger.h"
#include <queue>
#include <vector>

namespace ns3{
    NS_LOG_COMPONENT_DEFINE ("TrafficClass");
    NS_OBJECT_ENSURE_REGISTERED (TrafficClass);

    TypeId
    TrafficClass::GetTypeId (void)
    {
        static TypeId tid = TypeId ("ns3::TrafficClass")
                .SetParent<Object> ()
                .SetGroupName ("TrafficControl")
        ;
        return tid;
    }

    TrafficClass::TrafficClass ()
    {
        NS_LOG_FUNCTION (this);
    }

    bool TrafficClass::IfEmpty() {
        return m_queue.empty()
    }

    uint32_t TrafficClass::GetQueueSize(){
        return m_queue.size();
    }


    bool TrafficClass::Enqueue(Ptr <Packet> packet) {
       return m_queue.push(packet);
    }

    Ptr<Packet> TrafficClass::Dequeue() {
       return m_queue.pop();
    }

    bool TrafficClass::Match(Ptr <Packet> packet) {
//        NS_LOG_FUNCTION(this<<packet);
//        for(Filter filter: filters){
//            if (filter.Match(packet)){
//                return true;
//            }
//        }
        return false;
    }
}

