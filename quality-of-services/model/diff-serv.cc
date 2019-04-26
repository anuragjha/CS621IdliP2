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
       // NS_LOG_FUNCTION(this); //we
    }

    Diffserv::~Diffserv() {
       // NS_LOG_FUNCTION(this);//we
    }

    void Diffserv::SetMode(Diffserv::QueueMode mode) {
       // NS_LOG_FUNCTION(this); //we
        m_mode = mode;
    }

    Diffserv::QueueMode Diffserv::GetMode() {
        //NS_LOG_FUNCTION(this);//we
        return m_mode;
    }

    bool Diffserv::DoEnqueue(Ptr <Packet> p) {
        bool resultOfEnqueue = false;
       uint32_t i = Classify(p);
       TrafficClass tc = GetTrafficClassAtIndex(int(i));
       resultOfEnqueue = tc.Enqueue(p);
       return resultOfEnqueue;
    }

    std::vector<TrafficClass *> Diffserv::GetQ_Class() {
        return this->q_class;
    }

    //todo
    Ptr<Packet> Diffserv::DoDequeue() {

        //do dequeue

        Ptr<Packet> p = new Packet();
        return p;
    }

    //todo
    Ptr<const Packet> Diffserv::DoPeek() const {

        //do peek;
        Ptr<Packet> p = new Packet();
        return p;
    }

    TrafficClass Diffserv::GetTrafficClassAtIndex(int index) {
        TrafficClass* tc;
        tc = q_class[index];
       return *tc ;
    }

   //todo
    uint32_t Diffserv::Classify(Ptr <Packet> packet) {
        //NS_LOG_FUNCTION(this<<packet);//we
        int i = 0;
        for(TrafficClass* trafficClass: q_class) {
            i = i+1;
            if (trafficClass->Match(packet)) {
                return i;
            }
        }
        return 0;
    }

    Ptr<Packet> Diffserv::Schedule() {
        Ptr<Packet> p = new Packet();
        return p;
    }
}
