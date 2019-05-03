//
// Created by manalipatil on 4/23/19.
//

#ifndef NS_3_ALLINONE_TRAFFIC_CLASS_H
#define NS_3_ALLINONE_TRAFFIC_CLASS_H
#include <vector>
#include <queue>
#include "ns3/object.h"
#include "ns3/log.h"
#include "ns3/pointer.h"
#include "filter.h"
#include "ns3/packet.h"
//#include "ns3/ptr.h"
//#include "diff-serv.h"
#include "ns3/uinteger.h"
#include "ns3/queue.h"

namespace ns3 {

    //class TrafficClass;

/**
 * \ingroup traffic-control
 *
 * PacketFilter is the abstract base class for filters used by queue discs
 * to classify packets.
 */
class TrafficClass{
    public:
        /**
         * \brief Get the type ID.
         * \return the object TypeId
         */
        static TypeId GetTypeId (void);

        TrafficClass (uint32_t maxPackets,uint32_t maxBytes, double weight, uint32_t priority, bool isDefault,std::vector<Filter *> filters);
        ~TrafficClass ();

        bool IfEmpty();
        bool Enqueue(Ptr<ns3::Packet> packet);

       // Ptr<ns3::Packet> Dequeue(void);

        Ptr<ns3::Packet> Dequeue(void);

        Ptr<ns3::Packet> Peek(void);

        Ptr<ns3::Packet> Remove(void);

        bool Match(Ptr<ns3::Packet> packet);

        uint32_t GetQueueSize(void);


        uint32_t GetPriorityLevel(void);
        double GetWeight(void);

        bool isDefault;

        uint32_t priority_level;

        std::vector<Filter*> filters;

        std::queue<Ptr<Packet>> m_queue;


    /**
     * \brief Classify a packet.
     *
     * \param item the packet to classify.
     *
     * \return -1 if this filter is not able to classify packets of the same protocol
     * as item or the item does not match the filter conditions, the configured return
     * value otherwise.
     */
        // int32_t Classify (Ptr<QueueDiscItem> item) const;

    private: //was private

        uint32_t bytes;
        double weight;
        uint32_t packets;
        uint32_t maxPackets;
        uint32_t maxBytes;
    };
} // namespace ns3
#endif //NS_3_ALLINONE_TRAFFIC_CLASS_H
