//
// Created by manalipatil on 4/23/19.
//

#ifndef NS_3_ALLINONE_DIFF_SERV_H
#define NS_3_ALLINONE_DIFF_SERV_H

#include <queue>
#include "ns3/log.h"
#include "ns3/object-base.h"
#include "ns3/log-macros-disabled.h"
#include "ns3/packet.h"
#include "ns3/queue.h"
#include "ns3/traffic-class.h"
#include <vector>
#include "stdio.h"
#include <iostream>

namespace ns3{

    enum QueueMode
    {
        QUEUE_MODE_PACKETS,
        QUEUE_MODE_BYTES,
    };

    //class TraceContainer;
template <typename Packet>
class Diffserv : public Queue<ns3::Packet>{

    public:

        static TypeId GetTypeId(void);
        Diffserv();
        virtual ~Diffserv();

        void SetMode(QueueMode mode);

        QueueMode GetMode(void); // have to make it const

        //virtual Ptr<Packet> Schedule(void);
        //virtual bool Enqueue(Ptr<Packet> item);
        //virtual Ptr<Packet> Dequeue(void);
        //virtual Ptr<Packet> Remove(void);
        //virtual Ptr<const Packet> Peek(void) const;

        Ptr<Packet> Schedule(void);
        bool Enqueue(Ptr<Packet> item);
        Ptr<Packet> Dequeue(void);
        Ptr<Packet> Remove(void);
        Ptr<const Packet> Peek(void) const;

        std::vector<TrafficClass*> GetQ_Class(void);

        //Ptr<TrafficClass> GetTrafficClassAtIndex(int index);

        TrafficClass GetTrafficClassAtIndex(int index);

        uint32_t Classify(Ptr<Packet> item);

    private:

        QueueMode m_mode;
        std::vector<TrafficClass*> q_class;

        bool DoEnqueue(Ptr<Packet> item);
        Ptr<Packet> DoDequeue(void);
        Ptr<const Packet> DoPeek(void) const;
        Ptr<Packet> DoRemove(void);

        NS_LOG_TEMPLATE_DECLARE;
    };
    extern template class Diffserv<Packet>;
}
#endif //NS_3_ALLINONE_DIFF_SERV_H
