//
// Created by manalipatil on 4/23/19.
//

#include "ns3/log.h"
#include "diff-serv.h"
#include "ns3/packet.h"
#include "ns3/object.h"
#include "ns3/uinteger.h"
#include <cstring>
#include <iostream>
#include <vector>
#include "spq.h"

namespace ns3{
    NS_LOG_COMPONENT_DEFINE("SPQ");
    NS_OBJECT_ENSURE_REGISTERED(SPQ);

    TypeId SPQ::GetTypeId(void) {
        static TypeId tid = TypeId("ns3::SPQ")
                .SetParent<Diffserv>()
                .SetGroupName("TrafficControl");
        return tid;
    }

    SPQ::SPQ():Diffserv(){
    }

    SPQ::~SPQ() {
    }

    Ptr<Packet> SPQ::Schedule() {
        uint32_t maxPriority = -1;
        Ptr<Packet> packet;
        TrafficClass* trafficClass;
        for(TrafficClass* tc : GetQ_Class()){
           uint32_t priority = tc->GetPriorityLevel();
           if(priority > maxPriority && !trafficClass->IfEmpty() ){
               maxPriority = priority;
               trafficClass = tc;
           }
        }
        if(maxPriority!=uint32_t(-1)){
        	packet = trafficClass->Dequeue();
			return packet;
        }
        return 0;
    }

    Ptr<Packet> SPQ::ScheduleForPeek() {
        uint32_t maxPriority = -1;
        Ptr<Packet> packet;
        TrafficClass* trafficClass;
        for(TrafficClass* tc : GetQ_Class()){
            uint32_t priority = tc->GetPriorityLevel();
            if(priority > maxPriority){
                maxPriority = priority;
                trafficClass = tc;
            }
        }
        if(maxPriority!=uint32_t(-1)) {
            packet = trafficClass->Peek();
            return packet;
        }
        return 0;
    }

    Ptr<Packet> SPQ::DoDequeue() {
      return this->Schedule();
    }

    Ptr<const Packet> SPQ::DoPeek() {
        return this->ScheduleForPeek();
    }

    Ptr<Packet> SPQ::DoRemove() {
    	return this->DoDequeue();
	}

}
