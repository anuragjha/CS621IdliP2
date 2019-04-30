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
    	std::vector<TrafficClass *> q_class = this->GetQ_Class();
    	int q_size = static_cast<int>(q_class.size());
    	TrafficClass tc = this->GetTrafficClassAtIndex(this->trafficIndex);

    	Ptr<Packet> packet = tc.Peek();
    	std::uint32_t packetSize = packet->GetSize();

    	std::vector<std::uint32_t> creditVector = this->GetCredit();
    	std::uint32_t & tcCurrentCredit = creditVector[this->trafficIndex];

    	if(packetSize <= tcCurrentCredit){
    		packet = tc.Dequeue();
    		creditVector[this->trafficIndex] = tcCurrentCredit-packetSize;
    		if(this->trafficIndex == q_size-1){
    			double aggregatedWeight = 0;
    			for(TrafficClass* trafficClass: q_class) {
    				aggregatedWeight = aggregatedWeight + trafficClass->GetWeight();
				}

    			for(std::size_t i=0; i<creditVector.size(); ++i){
    				creditVector[i] = creditVector[i] + (q_class[i]->GetWeight()/aggregatedWeight)*this->deficit;
    			}
    			this->trafficIndex = 0;
    		}else{
    			this->trafficIndex++;
    		}
    		return packet;
    	}else{
    		if(this->trafficIndex == q_size-1){
    			double aggregatedWeight = 0;
				for(TrafficClass* trafficClass: q_class) {
					aggregatedWeight = aggregatedWeight + trafficClass->GetWeight();
				}

				for(std::size_t i=0; i<creditVector.size(); ++i){
					creditVector[i] = creditVector[i] + (q_class[i]->GetWeight()/aggregatedWeight)*this->deficit;
				}
				return 0;
			}else{
				this->trafficIndex++;
				packet = this->Schedule();
				return packet;
			}
    	}
    }

    Ptr<Packet> DRR::ScheduleForPeek() {
    	std::vector<TrafficClass *> q_class = this->GetQ_Class();
		int q_size = static_cast<int>(q_class.size());
		TrafficClass tc = this->GetTrafficClassAtIndex(this->trafficIndex);

		Ptr<Packet> packet = tc.Peek();
		std::uint32_t packetSize = packet->GetSize();

		std::vector<std::uint32_t> creditVector = this->GetCredit();
		std::uint32_t & tcCurrentCredit = creditVector[this->trafficIndex];
		if(packetSize <= tcCurrentCredit){
			return tc.Peek();
		}else{
			if(this->trafficIndex == q_size-1){
				return 0;
			}else{
				this->trafficIndex++;
				return this->ScheduleForPeek();
			}

		}
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
