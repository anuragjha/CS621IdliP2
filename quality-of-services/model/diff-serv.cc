//
// Created by manalipatil on 4/23/19.
//

#include "ns3/log.h"
#include "ns3/enum.h"
#include "ns3/uinteger.h"
#include "diff-serv.h"

namespace ns3 {
    NS_LOG_COMPONENT_DEFINE("Diffserv");
    NS_OBJECT_ENSURE_REGISTERED(Diffserv);

    TypeId Diffserv::GetTypeId(void) {
        static TypeId tid = TypeId("ns3::DropTailQueue")
                .SetParent<Queue>()
                .SetGroupName("Network");
        return tid;
    }

    Diffserv::Diffserv() : Queue() {
        NS_LOG_FUNCTION(this);
    }

    void Diffserv::SetMode(Diffserv::QueueMode mode) {
        NS_LOG_FUNCTION(this);
        m_mode = mode;
    }

    Diffserv::QueueMode Diffserv::GetMode() {
        NS_LOG_FUNCTION(this);
        return m_mode;
    }

    bool Diffserv::DoEnqueue(Ptr <Packet> packet) {
        NS_LOG_FUNCTION(this<<packet);
    }

    Ptr<Packet> Diffserv::DoDequeue() {
        NS_LOG_FUNCTION(this);

    }
}
