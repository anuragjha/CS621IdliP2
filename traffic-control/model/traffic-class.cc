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

    TrafficClass::TrafficClass(uint32_t maxPackets,uint32_t maxBytes, double weight, uint32_t priority, bool isDefault,std::vector<Filter *> filters)
    {
        //TrafficClass(max_packets,max_bytes, weight, priority_level, is_default, filters);
      //  NS_LOG_FUNCTION (this);
      this->maxBytes = maxBytes;
      this->maxPackets = maxPackets;
      this->priority_level = priority;
      std::cout << "priority level in constructor of TrafficClass : " << priority << "\n";
      this->weight = weight;
      this->isDefault = isDefault;
      this->filters = filters;
    }

    TrafficClass::~TrafficClass()
    {
       // NS_LOG_FUNCTION (this);
    }

    bool TrafficClass::Match(Ptr <Packet> packet) {
        // NS_LOG_FUNCTION(this<<packet);
        int i =0;
        for(Filter* filter: filters){
            if (filter->Match(packet)){
               i++;
            }
        }

        std::cout<<"Number of filters matched:"<<i<<std::endl;
        std::cout<<"static_cast<int>(filters.size()):"<<static_cast<int>(filters.size())<<std::endl;
      //  if(i== static_cast<int>(filters.size())){
        if(i>0){
            return true;
        }
        std::cout<<"Returning FALSE!!!!!!!!!!!!!!!!"<<std::endl;
        return false;
    }

    bool TrafficClass::IfEmpty() {
        return m_queue.empty();
    }

    bool TrafficClass::Enqueue(Ptr <Packet> packet) {
       // if(m_queue.size() >= maxPackets){

       //     std::cout<<"TrafficClass Enqueue Error 1 !!!!!!!:"<<std::endl;
            // Drop(packet);
       //     return false;
        //}
       // if(bytes + packet->GetSize() >= maxBytes){
       //     std::cout<<"Bytes already in the queue:"<<bytes<<std::endl;
      //      std::cout<<"TrafficClass Enqueue Error 2 !!!!!!!"<<std::endl;
            //Drop(packet);
      //      return false;
       // }
        bytes += packet->GetSize();
        packets += packets;
        m_queue.push(packet);
        std::cout<<"Pushed the packet in the queue!! Returning true!";
        return true;
    }

    Ptr<Packet> TrafficClass::Dequeue() {
        if(m_queue.empty()){
            return 0;
        }
        Ptr<Packet> p = m_queue.front();
        m_queue.pop();
        bytes -= p->GetSize();
        packets -= packets;
        return p;
    }

    Ptr<Packet> TrafficClass::Peek() {
        Ptr<Packet> p = m_queue.front();
        return p;
    }

    uint32_t TrafficClass::GetQueueSize(){
        return m_queue.size();
    }

    uint32_t TrafficClass::GetPriorityLevel() {
      return this->priority_level;
    }
}
//classify in diffserv will call match