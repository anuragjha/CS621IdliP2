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

using namespace ns3;

class Diffserv : public ns3::Queue<ns3::Packet> {
    public:
    	enum QueueMode {
    		QUEUE_MODE_PACKETS,
			QUEUE_MODE_BYTES,
    	};
        static TypeId GetTypeId(void);
        Diffserv();
        virtual ~Diffserv();

        void SetMode(Diffserv::QueueMode mode);
        Diffserv::QueueMode GetMode(void);

        virtual Ptr<Packet> Schedule(void);
        uint32_t Classify(Ptr<Packet> p);

        std::vector<TrafficClass*> GetQ_Class(void);
        TrafficClass GetTrafficClassAtIndex(int index);

    private:
        QueueMode m_mode;
        std::vector<TrafficClass*> q_class;
        bool DoEnqueue(Ptr<Packet> p);
        virtual Ptr<Packet> DoDequeue(void);
        virtual Ptr<const Packet> DoPeek(void) const;
}
#endif //NS_3_ALLINONE_DIFF_SERV_H
