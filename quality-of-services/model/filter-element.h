//
// Created by manalipatil on 4/22/19.
//

#ifndef NS_3_ALLINONE_FILTER_ELEMENT_H
#define NS_3_ALLINONE_FILTER_ELEMENT_H
#include "ns3/log.h"
#include "ns3/integer.h"
#include "ns3/pointer.h"
#include "ns3/packet.h"

namespace ns3 {
	class FilterElement:public Object{
		public:
			static TypeId GetTypeID (void);
			FilterElement();
			virtual bool Match(Ptr<Packet> packet );
	};
} // namespace ns3

#endif //NS_3_ALLINONE_FILTER_ELEMENT_H
