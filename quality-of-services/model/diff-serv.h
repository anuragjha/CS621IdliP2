//
// Created by manalipatil on 4/23/19.
//

#ifndef NS_3_ALLINONE_DIFF_SERV_H
#define NS_3_ALLINONE_DIFF_SERV_H

#include "ns3/log.h"
#include "ns3/packet.h"
#include "ns3/queue.h"
#include "ns3/traffic-class.h"
#include <vector>

namespace ns3 {

	class Diffserv : public ns3::Queue<ns3::Packet> {
		public:
			enum QueueMode {
				QUEUE_MODE_PACKETS,
				QUEUE_MODE_BYTES,
			};
			static TypeId GetTypeId(void);
			Diffserv();
			virtual ~Diffserv();

			Diffserv::QueueMode GetMode(void);
			void SetMode(Diffserv::QueueMode mode);
			std::vector<TrafficClass*> GetQ_Class(void);

			bool Enqueue(Ptr <Packet> p);
			Ptr<Packet> Dequeue();
			Ptr<const Packet> Peek();
			Ptr<Packet> Remove();
			virtual Ptr<Packet> Schedule(void) = 0;
			uint32_t Classify(Ptr<Packet> p);
			TrafficClass GetTrafficClassAtIndex(int index);

		private:
			QueueMode m_mode;
			std::vector<TrafficClass*> q_class;

			bool DoEnqueue(Ptr<Packet> p);
			Ptr<Packet> DoDequeue(void);
			virtual Ptr<const Packet> DoPeek(void) const = 0;
			virtual Ptr<Packet> DoRemove(void) = 0;
	};
}
#endif //NS_3_ALLINONE_DIFF_SERV_H
