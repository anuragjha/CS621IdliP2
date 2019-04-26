//
// Created by manalipatil on 4/23/19.
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

    class SPQ:public Diffserv{
    public:
        static TypeId GetTypeId (void);
        SPQ();
        ~SPQ();

        Ptr<Packet> Schedule(void);

        Ptr<Packet> ScheduleForPeek(void);

    private:
       // bool DoEnqueue(Ptr<Packet> packet);
        Ptr<Packet> DoDequeue(void);
        Ptr<const Packet> DoPeek(void);
      //  Ptr<Packet> DoRemove(void);
    };
}

#endif //NS_3_ALLINONE_SPQ_H
