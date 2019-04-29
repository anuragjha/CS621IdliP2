#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/point-to-point-net-device.h"
#include "build/ns3/traffic-control-module.h"
#include <vector>
#include "ns3/uinteger.h"
#include "ns3/packet.h"
#include <libxml/tree.h>
#include <libxml/parser.h>
#include "ns3/spq.h"
#include "ns3/source-port-number.h"
#include "ns3/destination-port-number.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("cs621P2Idli");

static Filter*
create_filter(xmlNode * node){
    Filter* result = new Filter();

    xmlNode *cur_node = nullptr;

    for(cur_node=node->children; cur_node; cur_node=cur_node->next){
        if(cur_node->type==XML_ELEMENT_NODE){
            // if(strcmp((char*)cur_node->name,"source_address")==0){
            //     Ipv4Address address((char*)xmlGetProp(cur_node,(xmlChar *)"value"));
            //     result->filterElements.push_back(new SourceIpAddress(address));
            // }
            // if(strcmp((char*)cur_node->name,"source_mask")==0){
            //   Ipv4Mask mask((char*)xmlGetProp(cur_node,(xmlChar *)"value"));
            //   result->elements.push_back(new SourceMask(mask));
            // }
            if(strcmp((char*)cur_node->name,"source_port")==0){
                uint32_t port = atoi((char*)xmlGetProp(cur_node,(xmlChar *)"value"));
                result->filterElements.push_back(new SourcePortNumber(port));
            }
            // if(strcmp((char*)cur_node->name,"destination_address")==0){
            //     Ipv4Address address((char*)xmlGetProp(cur_node,(xmlChar *)"value"));
            //     result->filterElements.push_back(new DestinationIpAddress(address));
            // }
            // if(strcmp((char*)cur_node->name,"destination_mask")==0){
            //   Ipv4Mask mask((char*)xmlGetProp(cur_node,(xmlChar *)"value"));
            //   result->elements.push_back(new DestinationMask(mask));
            // }
            if(strcmp((char*)cur_node->name,"destination_port")==0){
                uint32_t port = atoi((char*)xmlGetProp(cur_node,(xmlChar *)"value"));
                result->filterElements.push_back(new DestinationPortNumber(port));
            }
            if(strcmp((char*)cur_node->name,"protocol")==0){
                uint32_t protocol = atoi((char*)xmlGetProp(cur_node,(xmlChar *)"value"));
                result->filterElements.push_back(new ProtocolNumber(protocol));
            }
        }
    }
    return result;
}

static TrafficClass*
create_from_xml(xmlNode * node){
    xmlNode *cur_node = nullptr;
    uint32_t max_packets = 0;
    uint32_t max_bytes = 0;
    double_t weight = 0;
    uint32_t priority_level = 0;
    bool is_default = false;

    std::vector<Filter*> filters;

    for(cur_node=node; cur_node; cur_node=cur_node->next){
        if(cur_node->type==XML_ELEMENT_NODE){
            if(strcmp((char*)cur_node->name,"maxPackets")==0){
                max_packets = atoi((char*)xmlGetProp(cur_node,(xmlChar *)"value"));
            }
            if(strcmp((char*)cur_node->name,"maxBytes")==0){
                max_bytes = atoi((char*)xmlGetProp(cur_node,(xmlChar *)"value"));
            }
            if(strcmp((char*)cur_node->name,"weight")==0){
                weight = atoi((char*)xmlGetProp(cur_node,(xmlChar *)"value"));
            }
            if(strcmp((char*)cur_node->name,"priority_level")==0){

                priority_level = atoi((char*)xmlGetProp(cur_node,(xmlChar *)"value"));
                std::cout << "priority:" << priority_level;
            }
            if(strcmp((char*)cur_node->name,"isDefault")==0){
                is_default = atoi((char*)xmlGetProp(cur_node,(xmlChar *)"value"));
            }
            if(strcmp((char*)cur_node->name,"filters")==0){
                xmlNode *cur_filter = nullptr;
                for(cur_filter=cur_node->children; cur_filter; cur_filter=cur_filter->next){
                    Filter* filter = create_filter(cur_filter);

                    //test.LOG...
                    for(uint32_t i=0;i<filter->filterElements.size();i++){
                        std::cout<<"filter element[i]: "<<filter->filterElements[i]<<std::endl;
                    }

                    if(filter->filterElements.size()!=0){
                        std::cout<<"filter elements: "<<filter->filterElements.size()<<std::endl;
                        filters.push_back(filter);
                    }
                }
            }
        }
    }
    TrafficClass* tc = new TrafficClass(max_packets,max_bytes, weight, priority_level, is_default, filters);
    return tc;
}

static void
get_traffic_class(xmlNode * node, int level, std::vector<TrafficClass*> & result){
    xmlNode *cur_node = nullptr;
    for(cur_node=node; cur_node; cur_node=cur_node->next){//Loop through traffic
        if(cur_node->type==XML_ELEMENT_NODE){
            printf("in get_traffic_class\n");
            result.push_back(create_from_xml(cur_node->children));
        }
    }
}

static void
readConfigurationFile(const std::string filename, std::vector<TrafficClass*> & result){
    char char_array[filename.length()+1];
    strcpy(char_array, filename.c_str());

    xmlDocPtr doc;
    doc = xmlReadFile(char_array,nullptr,0);
    if(doc==nullptr){
        fprintf(stderr, "Failed to parse %s\n", char_array);
        return;
    }

    xmlNode *root_ele = nullptr;
    root_ele = xmlDocGetRootElement(doc);

    get_traffic_class(root_ele->children,1, result);

    xmlFreeDoc(doc);

    xmlCleanupParser();
}

int
main(int argc, char *argv[])
{
    std::cout<<"cs621 Idli P2\n\n";
    Time::SetResolution(Time::NS);
    LogComponentEnable ("PointToPointNetDevice", LOG_LEVEL_INFO);
    LogComponentEnable ("UdpClient", LOG_LEVEL_INFO);
    LogComponentEnable ("UdpServer", LOG_LEVEL_INFO);

    std::string file_name = "";

    CommandLine cmd;
    cmd.AddValue("filename","Name of the configuration file", file_name);
    cmd.Parse (argc, argv);
    //Packet::EnablePrinting();
    //Packet::EnableChecking();

    //creating 3 nodes
    NodeContainer nodes;
    nodes.Create(3);

    //internetstackhelper to install protocols(tcp,udp,ip,etc)

    //creating pointtopoint helper - net device and channel
    //real world corresponds to ethernet card and network cables
    PointToPointHelper pointToPoint;

    pointToPoint.SetDeviceAttribute("DataRate", StringValue ("10Mbps"));
    pointToPoint.SetChannelAttribute("Delay", StringValue ("1ms"));
    //create netDeviceContainer - makes use of pointtopoint helper
    NetDeviceContainer ndc01 = pointToPoint.Install (nodes.Get (0), nodes.Get (1));
    std::vector<TrafficClass*> tcs;
    readConfigurationFile(file_name, tcs);

    pointToPoint.SetDeviceAttribute("DataRate", StringValue ("500bps"));
    pointToPoint.SetChannelAttribute("Delay", StringValue ("1ms"));
    NetDeviceContainer ndc12 = pointToPoint.Install (nodes.Get (1), nodes.Get (2));

    Ptr<PointToPointNetDevice> sending_router = DynamicCast<PointToPointNetDevice>(ndc12.Get(0));

    Ptr<SPQ<Packet>> queue2 = new SPQ<Packet>(QueueMode::QUEUE_MODE_PACKETS,tcs);
    sending_router->SetQueue(queue2);

    InternetStackHelper stack;
    stack.Install (nodes);


//    uint32_t number = 2048;
//    uint32_t number2 = 2048;
//
//    ProtocolNumber pn1(number);
//    ProtocolNumber pn2(number2);
//
//    Filter filter;
//    filter.filterElements.push_back(&pn1);
//    filter.filterElements.push_back(&pn2);
//
//    filter.PrintFilterElements();



    //use ipv4addresshelper for allocation of ip address
    Ipv4AddressHelper address;
    address.SetBase("10.1.1.0", "255.255.255.0");

    // SourceIpAddress add = new SourceIpAddress();

    //use ipv4interfacecontainer to associate netdevice and ipaddress
    Ipv4InterfaceContainer ifc01 = address.Assign(ndc01);
    address.SetBase ("10.1.2.0", "255.255.255.0");
    Ipv4InterfaceContainer ifc12 = address.Assign(ndc12);

    // Create router nodes, initialize routing database and set up the routing
    // tables in the nodes.
    Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

    //// now at this point we have network built,
    ////  at this point now we need applications to generate traffic

    NS_LOG_INFO ("Create Applications.");
    //
    // Create one udpServer applications on node one.
    //
    //uint16_t port = 9;
    UdpServerHelper server1 (9);
    ApplicationContainer serverApps1 = server1.Install (nodes.Get (2));
    serverApps1.Start (Seconds (0.0));
    serverApps1.Stop (Seconds (1000.0));


    UdpServerHelper server2 (10);
    ApplicationContainer serverApps2 = server2.Install(nodes.Get(2));
    serverApps2.Start(Seconds (0.0));
    serverApps2.Stop(Seconds (1000.0));

    //uint32_t MaxPacketSize = 1024;
    //	Time interPacketInterval = Seconds (0.01);
    //uint32_t maxPacketCount = 5;

    //1st clientApps to start will take port - 49153 !!!
    //2nd clientApps to start will take port - 49154 !!!
    UdpClientHelper client1 (ifc12.GetAddress(1), 9); //giving client address of the server
    client1.SetAttribute ("MaxPackets", UintegerValue (1000));
    client1.SetAttribute ("Interval", TimeValue (Seconds(0.01)));
    client1.SetAttribute ("PacketSize", UintegerValue (1024));
    ApplicationContainer clientApps1 = client1.Install (nodes.Get (0));
    clientApps1.Start (Seconds (10.000));
    clientApps1.Stop (Seconds (5000.0));


    UdpClientHelper client2 (ifc12.GetAddress (1), 10);
    client2.SetAttribute ("MaxPackets", UintegerValue (1000));
    client2.SetAttribute ("Interval", TimeValue (Seconds (0.01)));
    client2.SetAttribute ("PacketSize", UintegerValue (1000));
    ApplicationContainer clientApps2 = client2.Install (nodes.Get (0));
    clientApps2.Start (Seconds (15.000));
    clientApps2.Stop (Seconds (5000.0));


    pointToPoint.EnablePcapAll("spq");
    //start and then destroy simulator
    Simulator::Run();
    Simulator::Destroy ();
    /**/
    return 0;
}