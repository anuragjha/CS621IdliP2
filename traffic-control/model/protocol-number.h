//
// Created by manalipatil on 4/22/19.
//

#ifndef NS_3_ALLINONE_PROTOCOL_NUMBER_H
#define NS_3_ALLINONE_PROTOCOL_NUMBER_H

#include "filter-element.h"
#include "ns3/packet.h"

namespace ns3{

    class ProtocolNumber:public FilterElement{
    public:
        static TypeId GetTypeID(void);

        ProtocolNumber(uint8_t value);
        ~ProtocolNumber();

        bool Match(Ptr<ns3::Packet> packet);

    private:
        uint8_t value;
    };
}
#endif //NS_3_ALLINONE_PROTOCOL_NUMBER_H
