//
// Created by manalipatil on 4/28/19.
//

#ifndef NS_3_ALLINONE_SPQ_H
#define NS_3_ALLINONE_SPQ_H

#include "diff-serv.h"
#include "ns3/log.h"
#include "ns3/packet.h"
#include <vector>

namespace ns3{

    template <typename Packet>
    class SPQ : public Diffserv<Packet>{

    public:
        SPQ();
        SPQ(QueueMode mode, std::vector<TrafficClass *> trafficClassVector);
        virtual ~SPQ();

        static TypeId GetTypeId(void);

        bool Enqueue(Ptr<Packet> item);
        Ptr<Packet> Dequeue(void);
        Ptr<Packet> Remove(void);
        Ptr<const Packet> Peek (void) const;

        u_int32_t Classify (Ptr<Packet> item);

      //  Ptr<Packet> Schedule ();

        Ptr<Packet> Schedule (void);
        bool AddTrafficClass (TrafficClass* trafficClass);

        QueueMode m_mode;
        std::vector<TrafficClass*> q_class;

    private:

        using Diffserv<Packet>::Enqueue;
        using Diffserv<Packet>::Dequeue;
        using Diffserv<Packet>::Remove;
        using Diffserv<Packet>::Peek;

        using Diffserv<Packet>::Schedule;
        using Diffserv<Packet>::Classify;

        NS_LOG_TEMPLATE_DECLARE;
    };
    extern template class SPQ<Packet>;
}

#endif //NS_3_ALLINONE_SPQ_H
