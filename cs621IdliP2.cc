#include "build/ns3/core-module.h"
#include "build/ns3/network-module.h"
#include "build/ns3/internet-module.h"
#include "build/ns3/point-to-point-module.h"
#include "build/ns3/applications-module.h"
#include "build/ns3/traffic-control-module.h"
#include <vector>

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("cs621P2Idli");

int
main(int argc, char const *argv[])
{
	//CommandLine cmd;
    //cmd.Parse (argc, argv);

	std::cout<<"cs621 Idli P2\n\n";
    Time::SetResolution(Time::NS);
    LogComponentEnable ("PointToPointNetDevice", LOG_LEVEL_INFO);
    LogComponentEnable ("UdpClient", LOG_LEVEL_INFO);
    LogComponentEnable ("UdpServer", LOG_LEVEL_INFO);

//Packet::EnablePrinting();
//Packet::EnableChecking();



    //creating 3 nodes
    NodeContainer nodes;
    nodes.Create(3);

    //internetstackhelper to install protocols(tcp,udp,ip,etc)
    InternetStackHelper stack;
    stack.Install (nodes);

    //creating pointtopoint helper - net device and channel
    //real world corresponds to ethernet card and network cables
    PointToPointHelper pointToPoint;

    pointToPoint.SetDeviceAttribute("DataRate", StringValue ("5Mbps"));
    pointToPoint.SetChannelAttribute("Delay", StringValue ("2ms"));
    //create netDeviceContainer - makes use of pointtopoint helper
    NetDeviceContainer ndc01 = pointToPoint.Install (nodes.Get (0), nodes.Get (1));

    pointToPoint.SetDeviceAttribute("DataRate", StringValue ("5Mbps"));
    pointToPoint.SetChannelAttribute("Delay", StringValue ("2ms"));
    NetDeviceContainer ndc12 = pointToPoint.Install (nodes.Get (1), nodes.Get (2));

//   pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
//    pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));
//    NetDeviceContainer ndc23 = pointToPoint.Install (nodes.Get (2), nodes.Get (3));

    uint32_t number = 2048;
    ProtocolNumber pn(number);
    ProtocolNumber pn2(number);

    Filter filter;
    filter.filterElements.push_back(&pn);
    filter.filterElements.push_back(&pn2);

    filter.PrintFilterElements();

    TrafficClass highQueue = TrafficClass(500,500,2,0,false);
    TrafficClass lowQueue = TrafficClass(500,500,1,0,true);

    //use ipv4addresshelper for allocation of ip address
    Ipv4AddressHelper address;
    address.SetBase("10.1.1.0", "255.255.255.0");


   // SourceIpAddress add = new SourceIpAddress();

    //use ipv4interfacecontainer to associate netdevice and ipaddress
    Ipv4InterfaceContainer ifc01 = address.Assign(ndc01);
    Ipv4InterfaceContainer ifc12 = address.Assign(ndc12);
//  Ipv4InterfaceContainer ifc23 = address.Assign(ndc23);

    // Create router nodes, initialize routing database and set up the routing
   // tables in the nodes.
   Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

    //// now at this point we have network built,
    ////  at this point now we need applications to generate traffic

     NS_LOG_INFO ("Create Applications.");
	//
	// Create one udpServer applications on node one.
	//
  	uint16_t port = 9;
  	UdpServerHelper server (port);
  	ApplicationContainer serverApps = server.Install (nodes.Get (2));

  	serverApps.Start (Seconds (1.0));
  	serverApps.Stop (Seconds (10.0));

	uint32_t MaxPacketSize = 1024;
   	Time interPacketInterval = Seconds (1.0);
   	uint32_t maxPacketCount = 5;
 	UdpClientHelper client (ifc12.GetAddress(1), port); //giving client address of the server
 	client.SetAttribute ("MaxPackets", UintegerValue (maxPacketCount));
 	client.SetAttribute ("Interval", TimeValue (interPacketInterval));
  	client.SetAttribute ("PacketSize", UintegerValue (MaxPacketSize));
  	ApplicationContainer clientApps = client.Install (nodes.Get (0));
  	clientApps.Start (Seconds (2.0));
  	clientApps.Stop (Seconds (10.0));

    //start and then destroy simulator
	Simulator::Run();
	Simulator::Destroy ();

	/**/
	return 0;
}
