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
#include "ns3/pointer.h"
#include "filter.h"
#include "ns3/packet.h"
#include "ns3/uinteger.h"
#include "ns3/queue.h"

using namespace ns3;

class TrafficClass {
    public:
		TrafficClass (uint32_t maxBytes,uint32_t maxPackets,uint32_t priority, double weight, bool isDefault);
        static TypeId GetTypeId (void);
        bool IfEmpty();
        bool Match(Ptr<ns3::Packet> packet);
        bool Enqueue(Ptr<ns3::Packet> packet);
        Ptr<ns3::Packet> Dequeue(void);
        Ptr<ns3::Packet> Peek(void);
        uint32_t GetPriorityLevel(void);
        uint32_t GetQueueSize(void);

    private:
        std::vector<Filter*> filters;
        uint32_t bytes;
        uint32_t packets;
        uint32_t maxPackets;
        uint32_t maxBytes;
        double weight;
        uint32_t priority_level;
        bool isDefault;
        std::queue<Ptr<Packet>> m_queue;
};
#endif //NS_3_ALLINONE_TRAFFIC_CLASS_H
