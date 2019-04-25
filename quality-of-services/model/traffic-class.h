//
// Created by manalipatil on 4/23/19.
//

#ifndef NS_3_ALLINONE_TRAFFIC_CLASS_H
#define NS_3_ALLINONE_TRAFFIC_CLASS_H
#include <cstring>
#include <iostream>
#include <vector>
#include "ns3/object.h"
#include "ns3/log.h"
#include "ns3/integer.h"
#include "ns3/ppp-header.h"
#include "ns3/pointer.h"
//#include "queue-disc.h"
#include "ns3/queue.h"
//#include "filter.h"
#include "stdint.h"
#include "ns3/packet.h"
#include "ns3/ptr.h"
#include "ns3/packet.h"
#include "ns3/ptr.h"
#include <queue>
#include "ns3/uinteger.h"


namespace ns3 {

    class TrafficClass: public Object {
		public:
			static TypeId GetTypeId (void);
			TrafficClass ();
			bool IfEmpty();
			bool Enqueue(Ptr<ns3::Packet> packet);
			bool Match(Ptr<ns3::Packet> packet);
			uint32_t GetQueueSize(void);
			Ptr<ns3::Packet> Dequeue(void);

		private:
//			std::vector<Filter*> filters;
			uint32_t bytes;
			double_t weight;
			uint32_t packets;
			uint32_t maxPackets;
			uint32_t maxBytes;
			uint32_t priority_level;
			bool isDefault;
			std::queue<Ptr<Packet>> m_queue;
	};
}
#endif //NS_3_ALLINONE_TRAFFIC_CLASS_H
