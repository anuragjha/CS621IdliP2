//
// Created by manalipatil on 4/23/19.
//

#ifndef NS_3_ALLINONE_DIFF_SERV_H
#define NS_3_ALLINONE_DIFF_SERV_H

#include <queue>
#include "ns3/packet.h"
#include "ns3/queue.h"

using namespace ns3;

class Diffserv: public Queue {
	public:
		static TypeId GetTypeId(void);
		Diffserv();
		void SetMode(Diffserv::QueueMode mode);
		Diffserv::QueueMode GetMode(void); // have to make it const
		Ptr<Packet> Schedule(void);
		uint32_t Classify(Ptr<Packet> p);

	private:
		QueueMode m_mode;
		std::vector<TrafficClass*> q_class;
		virtual bool DoEnqueue(Ptr<Packet> packet);
		virtual Ptr<Packet> DoDequeue(void);
		virtual Ptr<Packet> DoPeek(void);
		virtual Ptr<Packet> DoRemove(void);

};

#endif //NS_3_ALLINONE_DIFF_SERV_H
