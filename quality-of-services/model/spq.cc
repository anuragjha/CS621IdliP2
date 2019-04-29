//
// Created by manalipatil on 4/23/19.
//

#include "ns3/log.h"
#include "ns3/log-macros-enabled.h"
#include "ns3/log-macros-disabled.h"
#include "diff-serv.h"
#include "ns3/packet.h"
#include <cstring>
#include <iostream>
#include <vector>
#include "ns3/object.h"
#include "ns3/uinteger.h"
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
        //NS_LOG_FUNCTION(this);//we
    }

    SPQ::~SPQ() {
        //NS_LOG_FUNCTION(this);//we
    }

   // bool SPQ::DoEnqueue(Ptr <Packet> packet) {
       // NS_LOG_FUNCTION(this);//we
   //    return true;
    //}

    //Ptr<Packet> SPQ::Schedule() {

        //take from the appropriate queue and return



    //    Ptr<Packet> p = new Packet();
    //    return p;
    //}


    Ptr<Packet> SPQ::Schedule() {
        uint32_t maxPriority = 9999;
        Ptr<Packet> packet;
        TrafficClass* trafficClass;
        for(TrafficClass* tc : GetQ_Class()){
           uint32_t priority = tc->GetPriorityLevel();
           if(priority > maxPriority){
               maxPriority = priority;
               trafficClass = tc;
           }
        }

		packet = trafficClass->Dequeue();
		return packet;
    }

    Ptr<Packet> SPQ::ScheduleForPeek() {
        uint32_t maxPriority = 9999;
        Ptr<Packet> packet;
        TrafficClass* trafficClass;
        for(TrafficClass* tc : GetQ_Class()){
            uint32_t priority = tc->GetPriorityLevel();
            if(priority > maxPriority){
                maxPriority = priority;
                trafficClass = tc;
            }
        }
        if(maxPriority < 9999) {
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
}
