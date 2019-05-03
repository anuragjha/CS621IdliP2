//
// Created by vikas ramaneti on 4/23/19.
//

#include "ns3/drr.h"
#include "ns3/log.h"
#include "ns3/log-macros-disabled.h"
#include "ns3/packet.h"
#include "ns3/object.h"
#include "ns3/uinteger.h"
#include <cstring>
#include <iostream>
#include <vector>


namespace ns3{
	NS_LOG_COMPONENT_DEFINE ("DRR");
	NS_OBJECT_TEMPLATE_CLASS_DEFINE(DRR, Packet);

	template <typename Packet>
	TypeId
	DRR<Packet>::GetTypeId() {
		static TypeId tid =
				TypeId (("ns3::DRR<" + GetTypeParamName<DRR<Packet>> () + ">").c_str ())
						.SetParent<Diffserv<Packet>> ()
						.SetGroupName ("TrafficControl")
						.template AddConstructor<DRR<Packet>> () //)//TODO: I may need to add 2 parameters
		;
		return tid;
	}

	template <typename Packet>
	DRR<Packet>::DRR():Diffserv<Packet>(),NS_LOG_TEMPLATE_DEFINE ("DRR") {
	}

    template <typename Packet>
	DRR<Packet>::DRR(ns3::QueueMode mode, std::vector<TrafficClass *> trafficClassVector, uint32_t deficit): NS_LOG_TEMPLATE_DEFINE ("DRR") {
		this->m_mode = mode;
		this->q_class = trafficClassVector;
		this->deficit = deficit;
		std::cout << "DRR.q_class.size: " << this->q_class.size () << std::endl;
	}

    template <typename Packet>
    DRR<Packet>::~DRR() {
    }

    template <typename Packet>
    uint32_t DRR<Packet>::GetDeficit(){
    	return this->deficit;
    }
    template <typename Packet>
    void DRR<Packet>::SetDeficit(uint32_t deficit){
    	this->deficit = deficit;
    }

    template <typename Packet>
    std::vector<std::uint32_t> DRR<Packet>::GetCredit(){
    	return this->credit;
    }

    template <typename Packet>
    void DRR<Packet>::SetCredit(std::vector<std::uint32_t> credit){
    	this->credit = credit;
    }

    template <typename Packet>
    void DRR<Packet>::UpdateCredit(std::vector<std::uint32_t> creditVector){
    	std::vector<TrafficClass *> q_class = this->GetQ_Class();
		double aggregatedWeight = 0;

		for(TrafficClass* trafficClass: q_class) {
			aggregatedWeight = aggregatedWeight + trafficClass->GetWeight();
		}

		for(std::size_t i=0; i<creditVector.size(); ++i){
			creditVector[i] = creditVector[i] + (q_class[i]->GetWeight()/aggregatedWeight)*this->GetDeficit();
		}
    }

    template <typename Packet>
    Ptr<Packet> DRR<Packet>::Schedule() {
    	std::vector<TrafficClass *> q_class = this->GetQ_Class();
    	int q_size = static_cast<int>(q_class.size());
    	TrafficClass tc = this->GetTrafficClassAtIndex(this->trafficIndex);

    	Ptr<Packet> packet = tc.Peek();
    	std::uint32_t packetSize = packet->GetSize();

    	std::vector<std::uint32_t> creditVector = this->GetCredit();
    	std::uint32_t & tcCurrentCredit = creditVector[this->trafficIndex];

    	if(packetSize <= tcCurrentCredit){
    		this->counter=0;
    		packet = tc.Dequeue();
    		creditVector[this->trafficIndex] = tcCurrentCredit-packetSize;
    		if(this->trafficIndex == q_size-1){
    			this->UpdateCredit(creditVector);
    			this->trafficIndex = 0;
    		}else{
    			this->trafficIndex++;
    		}
    		return packet;
    	}else{
    		this->counter++;
    		if(this->counter==q_size){
    			if(this->trafficIndex == q_size-1){
					this->UpdateCredit(creditVector);
					this->trafficIndex = 0;
				}
    			this->counter = 0;
    			return 0;
    		}else{
    			if(this->trafficIndex == q_size-1){
					this->UpdateCredit(creditVector);
					this->trafficIndex = 0;
				}else{
					this->trafficIndex++;
				}
    			packet = this->Schedule();
				return packet;
			}
    	}
    }

    template <typename Packet>
    Ptr<Packet> DRR<Packet>::ScheduleForPeek() {
    	std::vector<TrafficClass *> q_class = this->GetQ_Class();
		int q_size = static_cast<int>(q_class.size());
		TrafficClass tc = this->GetTrafficClassAtIndex(this->trafficIndex);

		Ptr<Packet> packet = tc.Peek();
		std::uint32_t packetSize = packet->GetSize();

		std::vector<std::uint32_t> creditVector = this->GetCredit();
		std::uint32_t & tcCurrentCredit = creditVector[this->trafficIndex];
		if(packetSize <= tcCurrentCredit){
			this->counter=0;
			return tc.Peek();
		}else{
			if(this->trafficIndex == q_size-1){
				this->UpdateCredit(creditVector);
				this->trafficIndex = 0;
			}else{
				this->trafficIndex++;
			}
			this->counter++;
			if(this->counter==q_size){
				this->counter = 0;
				return 0;
			}
			else{
				return this->ScheduleForPeek();
			}
		}
    }

    template <typename Packet>
    Ptr<Packet> DRR<Packet>::DoDequeue() {
      return this->Schedule();
    }

    template <typename Packet>
    Ptr<const Packet> DRR<Packet>::DoPeek() {
        return this->ScheduleForPeek();
    }

    template <typename Packet>
    Ptr<Packet> DRR<Packet>::DoRemove() {
    	return this->DoDequeue();
	}
}
