/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2016 Universita' degli Studi di Napoli Federico II
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "ns3/log.h"
#include "ns3/integer.h"
#include "queue-disc.h"
#include "source-mask.h"
#include "ns3/inet-socket-address.h"
#include "ns3/ipv4-address.h"
#include "ns3/ipv4-header.h"
#include "ns3/ppp-header.h"
#include "ns3/packet.h"
#include "ns3/filter-element.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("SourceMask");

NS_OBJECT_ENSURE_REGISTERED (SourceMask);

TypeId 
SourceMask::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::SourceMask")
    .SetParent<FilterElement> ()
    .SetGroupName ("TrafficControl")
  ;
  return tid;
}

SourceMask::SourceMask (Ipv4Address startAddr, Ipv4Mask mask)
{
  NS_LOG_FUNCTION (this);
	startAddress = startAddr;
    ipv4mask = mask;
	//startBits = startAddr.Get ();
	//endAddress = endAddr;
	//endBits = endAddr.Get ();
}

SourceMask::~SourceMask()
{
  NS_LOG_FUNCTION (this);
}

bool
SourceMask::Match (Ptr<Packet> packet)
{
  NS_LOG_FUNCTION (this);
    Ptr<Packet> copy = packet->Copy ();
    PppHeader ppph;
    Ipv4Header iph;
    copy->RemoveHeader(ppph);
    copy->RemoveHeader(iph);

    Ipv4Address packetIpv4Address = iph.GetSource();
    Ipv4Address networkAddress = startAddress.CombineMask (ipv4mask);
    if(packetIpv4Address.IsEqual(networkAddress)){
       // std::cout<<" Matched Ipv4Address:" << Ipv4Address <<std::endl;
        return true;
    }  else{
      //  std::cout<<" Not Matched Ipv4Address:" << Ipv4Address <<std::endl;
        return false;
    }
}

} // namespace ns3
