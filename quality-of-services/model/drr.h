//
// Created by vikas ramaneti on 4/23/19.
//

#ifndef NS_3_ALLINONE_SPQ_H
#define NS_3_ALLINONE_SPQ_H

#include "ns3/log.h"
#include "ns3/log-macros-enabled.h"
#include "ns3/log-macros-disabled.h"
#include "diff-serv.h"
#include "ns3/packet.h"
#include "ns3/pointer.h"
#include <cstring>
#include <iostream>
#include <vector>
#include "ns3/object.h"
#include "ns3/uinteger.h"

namespace ns3{

	template <typename Packet>
    class DRR:public Diffserv<Packet>{
		public:
			static TypeId GetTypeId (void);
			DRR(QueueMode mode, std::vector<TrafficClass *);
			~DRR();
			Ptr<Packet> Schedule(void);
			Ptr<Packet> ScheduleForPeek(void);
			uint32_t GetDeficit();
			void SetDeficit(uint32_t deficit);
			std::vector<std::uint32_t> GetCredit();
			void SetCredit(std::vector<std::uint32_t> credit);
		private:
			std::vector<std::uint32_t> credit;
			std::uint32_t deficit;
			int trafficIndex=0;
			bool DoEnqueue(Ptr<Packet> packet);
			Ptr<Packet> DoDequeue(void);
			Ptr<const Packet> DoPeek(void);
			Ptr<Packet> DoRemove(void);
			using Diffserv<Packet>::Enqueue;
			using Diffserv<Packet>::Dequeue;
			using Diffserv<Packet>::Remove;
			using Diffserv<Packet>::Peek;

			using Diffserv<Packet>::Schedule;
			using Diffserv<Packet>::Classify;
    };
	extern template class DRR<Packet>;
}

#endif //NS_3_ALLINONE_SPQ_H
