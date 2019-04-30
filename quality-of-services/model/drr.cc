//
// Created by vikas ramaneti on 4/23/19.
//

#include "ns3/log.h"
#include "diff-serv.h"
#include "ns3/packet.h"
#include "ns3/object.h"
#include "ns3/uinteger.h"
#include <cstring>
#include <iostream>
#include <vector>
#include "drr.h"

namespace ns3{
    NS_LOG_COMPONENT_DEFINE("DRR");
    NS_OBJECT_ENSURE_REGISTERED(DRR);

    TypeId DRR::GetTypeId(void) {
        static TypeId tid = TypeId("ns3::DRR")
                .SetParent<Diffserv>()
                .SetGroupName("TrafficControl");
        return tid;
    }

    DRR::DRR():Diffserv(){
    }

    DRR::~DRR() {
    }

    uint32_t DRR::GetDeficit(){
    	return this->deficit;
    }

    void DRR::SetDeficit(uint32_t deficit){
    	this->deficit = deficit;
    }

    std::vector<std::uint32_t> DRR::GetCredit(){
    	return this->credit;
    }

    void DRR::SetCredit(std::vector<std::uint32_t> credit){
    	this->credit = credit;
    }

    Ptr<Packet> DRR::Schedule() {

    }

    Ptr<Packet> DRR::ScheduleForPeek() {
        Ptr<Packet> packet;
        return packet;
    }

    Ptr<Packet> DRR::DoDequeue() {
      return this->Schedule();
    }

    Ptr<const Packet> DRR::DoPeek() {
        return this->ScheduleForPeek();
    }

    Ptr<Packet> DRR::DoRemove() {
    	return this->DoDequeue();
	}

}
