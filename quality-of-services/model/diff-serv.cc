//
// Created by manalipatil on 4/23/19.
//
#include "ns3/log.h"
#include "ns3/log-macros-enabled.h"
#include "ns3/log-macros-disabled.h"
#include "ns3/enum.h"
#include "ns3/pointer.h"
#include "ns3/uinteger.h"
#include "diff-serv.h"
#include <iostream>
#include <vector>
#include "stdint.h"
#include "ns3/traffic-class.h"

namespace ns3 {
    NS_LOG_COMPONENT_DEFINE("Diffserv");
    NS_OBJECT_ENSURE_REGISTERED(Diffserv);

    TypeId Diffserv::GetTypeId(void) {
        static TypeId tid = TypeId("ns3::Diffserv")
                .SetParent<Queue>()
                .SetGroupName("TrafficControl");
        return tid;
    }

    Diffserv::Diffserv():Queue() {
    }

    Diffserv::~Diffserv() {
    }

    void Diffserv::SetMode(Diffserv::QueueMode mode) {
        m_mode = mode;
    }

    Diffserv::QueueMode Diffserv::GetMode() {
        return m_mode;
    }

    std::vector<TrafficClass *> Diffserv::GetQ_Class() {
		return this->q_class;
	}

    bool Diffserv::Enqueue(Ptr <Packet> p){
    	return this->DoEnqueue(p);
    }

    bool Diffserv::DoEnqueue(Ptr <Packet> p) {
    	uint32_t i = Classify(p);
		TrafficClass tc = this->GetTrafficClassAtIndex(int(i));
		return tc.Enqueue(p);
    }

    Ptr<Packet> Diffserv::Dequeue(){
		return this->DoDequeue();
	}

    Ptr<Packet> Diffserv::DoDequeue() {
		return Schedule();
    }


    Ptr<const Packet> Diffserv::Peek(){
    	return this->DoPeek();
    }

    Ptr<Packet> Diffserv::Remove() {
		return this->DoRemove();
	}

    TrafficClass Diffserv::GetTrafficClassAtIndex(int index) {
        TrafficClass* tc;
        tc = q_class[index];
        return *tc ;
    }

    uint32_t Diffserv::Classify(Ptr <Packet> packet) {
        int i = 0;
        for(TrafficClass* trafficClass: q_class) {
            i = i+1;
            if(trafficClass->Match(packet)) {
                return i;
            }
        }
        return 0;
    }
}
