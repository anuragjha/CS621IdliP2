//
// Created by manalipatil on 4/23/19.
//
#include "traffic-class.h"
#include "ns3/log.h"
#include "ns3/pointer.h"
#include "ns3/uinteger.h"
#include "ns3/object.h"
#include "ns3/enum.h"
#include "ns3/queue.h"
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

    TrafficClass::TrafficClass(uint32_t maxBytes,uint32_t maxPackets,uint32_t priority, double weight, bool isDefault)
    {
      //  NS_LOG_FUNCTION (this);
      this->maxBytes = maxBytes;
      this->maxPackets = maxPackets;
      this->priority_level = priority;
      this->weight = weight;
      this->isDefault = isDefault;
    }

    TrafficClass::~TrafficClass()
    {
       // NS_LOG_FUNCTION (this);
    }

    bool TrafficClass::IfEmpty() {
        return m_queue.empty();
    }

    uint32_t TrafficClass::GetQueueSize(){
        return m_queue.size();
    }

    uint32_t TrafficClass::GetPriorityLevel() {
      return this->priority_level;
    }

    bool TrafficClass::Enqueue(Ptr <Packet> packet) {
      if(m_queue.size() >= maxPackets){
         // Drop(packet);
          return false;
      }
      if(bytes + packet->GetSize() >= maxBytes){
          //Drop(packet);
          return false;
      }
        bytes += packet->GetSize();
        m_queue.push(packet);
        return true;
    }

    Ptr<Packet> TrafficClass::Dequeue() {
        if(m_queue.empty()){
            return 0;
        }
        Ptr<Packet> p = m_queue.front();
        m_queue.pop();
        bytes -= p->GetSize();
        return p;
    }

    Ptr<Packet> TrafficClass::Peek() {
        Ptr<Packet> p = m_queue.front();
        return p;
    }

    bool TrafficClass::Match(Ptr <Packet> packet) {
       // NS_LOG_FUNCTION(this<<packet);
        for(Filter* filter: filters){
            if (filter->Match(packet)){
                return true;
            }
        }
        return false;
    }
}

//classify in diffserv will call match