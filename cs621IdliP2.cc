#include "build/ns3/core-module.h"
#include "build/ns3/network-module.h"
#include "build/ns3/internet-module.h"
#include "build/ns3/point-to-point-module.h"
#include "build/ns3/applications-module.h"
#include "build/ns3/traffic-control-module.h"
#include "build/ns3/spq.h"
#include "build/ns3/traffic-class.h"
#include "build/ns3/filter.h"
#include "build/ns3/filter-element.h"
#include "build/ns3/source-ip-address.h"
#include "build/ns3/source-port-number.h"
#include "build/ns3/destination-ip-address.h"
#include "build/ns3/destination-port-number.h"
#include "build/ns3/protocol-number.h"
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

	Packet::EnablePrinting();

    //creating 3 nodes
    NodeContainer nodes;
    nodes.Create(3);

    //internetstackhelper to install protocols(tcp,udp,ip,etc)
    InternetStackHelper stack;
    stack.Install(nodes);

    //creating pointtopoint helper - net device and channel
    //real world corresponds to ethernet card and network cables
    PointToPointHelper pointToPoint;
	//pointToPoint.SetQueue ("ns3::SPQ");

    pointToPoint.SetDeviceAttribute("DataRate", StringValue ("5Mbps"));
    pointToPoint.SetChannelAttribute("Delay", StringValue ("2ms"));
    NetDeviceContainer ndc01 = pointToPoint.Install (nodes.Get (0), nodes.Get (1));

    pointToPoint.SetDeviceAttribute("DataRate", StringValue ("3Mbps"));
    pointToPoint.SetChannelAttribute("Delay", StringValue ("2ms"));
    NetDeviceContainer ndc12 = pointToPoint.Install (nodes.Get (1), nodes.Get (2));
	
	Ipv4AddressHelper sourceIpAddress1;
    sourceIpAddress1.SetBase("10.1.1.0", "255.255.255.0");
	
	Ipv4AddressHelper sourceIpAddress2;
    sourceIpAddress2.SetBase("10.1.2.0", "255.255.255.0");

	//use ipv4interfacecontainer to associate netdevice and ipaddress
    Ipv4InterfaceContainer ifc01 = sourceIpAddress1.Assign(ndc01);
    Ipv4InterfaceContainer ifc12 = sourceIpAddress2.Assign(ndc12);

    // Create router nodes, initialize routing database and set up the routing
   	// tables in the nodes.
	Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

	//// now at this point we have network built,
    //// at this point now we need applications to generate traffic

	NS_LOG_INFO ("Create Applications.");
	//
	// Create one udpServer applications on node one.
	//
	
	uint16_t serverPort1 = 8000;
  	UdpServerHelper server1(serverPort1);
  	ApplicationContainer serverApps1 = server1.Install(nodes.Get (2));
	serverApps1.Start (Seconds (1.0));
  	serverApps1.Stop (Seconds (10.0));
	
	uint16_t serverPort2 = 8001;
  	UdpServerHelper server2(serverPort2);
  	ApplicationContainer serverApps2 = server2.Install(nodes.Get (2));
	serverApps2.Start (Seconds (1.0));
  	serverApps2.Stop (Seconds (10.0));
  	

	uint32_t client1MaxPacketSize = 1024;
   	Time client1InterPacketInterval = Seconds (1.0);
   	uint32_t client1maxPacketCount = 5;

	//giving client address of the server
 	UdpClientHelper client1(ifc12.GetAddress(1), serverPort1); 
 	client1.SetAttribute ("MaxPackets", UintegerValue (client1maxPacketCount));
 	client1.SetAttribute ("Interval", TimeValue (client1InterPacketInterval));
  	client1.SetAttribute ("PacketSize", UintegerValue (client1MaxPacketSize));
  	ApplicationContainer clientApps1 = client1.Install(nodes.Get (0));
  	clientApps1.Start (Seconds (2.0));
  	clientApps1.Stop (Seconds (10.0));

	UdpClientHelper client2(ifc12.GetAddress(1), serverPort2); 
 	client1.SetAttribute ("MaxPackets", UintegerValue (client1maxPacketCount));
 	client1.SetAttribute ("Interval", TimeValue (client1InterPacketInterval));
  	client1.SetAttribute ("PacketSize", UintegerValue (client1MaxPacketSize));
  	ApplicationContainer clientApps2 = client2.Install(nodes.Get (0));
  	clientApps2.Start (Seconds (2.0));
  	clientApps2.Stop (Seconds (10.0));
	
	pointToPoint.EnablePcapAll("SPQ");
    //start and then destroy simulator
	Simulator::Run();
	Simulator::Destroy ();

	/**/
	return 0;
}
