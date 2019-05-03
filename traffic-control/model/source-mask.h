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

#ifndef SOURCE_MASK_H
#define SOURCE_MASK_H

#include "ns3/object.h"
#include "ns3/inet-socket-address.h"
#include "ns3/ipv4-address.h"
#include "ns3/packet.h"
#include "ns3/filter-element.h"

namespace ns3 {

class FilterElement;

class SourceMask: public FilterElement {
public:

  static TypeId GetTypeId (void);

  SourceMask (Ipv4Address, Ipv4Mask);
  ~SourceMask ();

  bool Match (Ptr<Packet> packet);

    Ipv4Address startAddress;
    Ipv4Mask ipv4mask;

private:

	//uint32_t startBits;
	//Ipv4Address endAddress;
	//uint32_t endBits;
};

} // namespace ns3

#endif /* SOURCE_MASK_H */
