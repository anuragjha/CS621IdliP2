//
// Created by vikas ramaneti on 4/23/19.
//

#ifndef NS_3_ALLINONE_DRR_H
#define NS_3_ALLINONE_DRR_H

#include "diff-serv.h"
#include "ns3/log.h"
#include "ns3/packet.h"
#include "ns3/pointer.h"
#include <vector>
#include "ns3/object.h"
#include "ns3/uinteger.h"

namespace ns3{

	template <typename Packet>
    class DRR:public Diffserv<Packet>{
		public:
			DRR();
			static TypeId GetTypeId (void);
			DRR(QueueMode mode, std::vector<TrafficClass *>, std::uint32_t deficit);
			virtual ~DRR();
			bool Enqueue(Ptr<Packet> item);
			Ptr<Packet> Dequeue(void);
			Ptr<Packet> Remove(void);
			Ptr<const Packet> Peek (void) const;
			Ptr<Packet> Schedule(void);
			Ptr<Packet> ScheduleForPeek(void);
			uint32_t Classify (Ptr<Packet> item);
			std::vector<TrafficClass*> q_class;
			std::vector<TrafficClass*> GetQ_Class(void);
			QueueMode m_mode;
			uint32_t GetDeficit();
			void SetDeficit(uint32_t deficit);
			std::vector<std::uint32_t> GetCredit();
			void SetCredit();
		private:
			std::vector<std::uint32_t> credit;
			std::uint32_t deficit;
			int trafficIndex=0;
			int counter=0;
			bool DoEnqueue(Ptr<Packet> packet);
			Ptr<Packet> DoDequeue(void);
			Ptr<const Packet> DoPeek(void);
			Ptr<Packet> DoRemove(void);
			void UpdateCredit(std::vector<std::uint32_t> credit);
			using Diffserv<Packet>::Enqueue;
			using Diffserv<Packet>::Dequeue;
			using Diffserv<Packet>::Remove;
			using Diffserv<Packet>::Peek;
			using Diffserv<Packet>::Schedule;
			using Diffserv<Packet>::Classify;

			NS_LOG_TEMPLATE_DECLARE;
    };
	extern template class DRR<Packet>;
}

#endif //NS_3_ALLINONE_DRR_H
