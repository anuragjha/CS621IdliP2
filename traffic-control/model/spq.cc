//
// Created by manalipatil on 4/28/19.
//
#include "ns3/spq.h"
#include "ns3/log.h"
#include "ns3/log-macros-disabled.h"
#include "ns3/source-port-number.h"
#include "ns3/ipv4-header.h"
#include "ns3/ipv4-address.h"
#include "ns3/udp-header.h"
#include "ns3/ppp-header.h"
namespace ns3{
    NS_LOG_COMPONENT_DEFINE ("SPQ");
    NS_OBJECT_TEMPLATE_CLASS_DEFINE (SPQ, Packet);

    template <typename Packet>
    TypeId
    SPQ<Packet>::GetTypeId() {
        static TypeId tid =
                TypeId (("ns3::SPQ<" + GetTypeParamName<SPQ<Packet>> () + ">").c_str ())
                        .SetParent<Diffserv<Packet>> ()
                        .SetGroupName ("TrafficControl")
                        .template AddConstructor<SPQ<Packet>> () //)//TODO: I may need to add 2 parameters
        ;
        return tid;
    }

    template <typename Packet>
    SPQ<Packet>::SPQ():Diffserv<Packet>(),NS_LOG_TEMPLATE_DEFINE ("SPQ") {
    }

    template <typename Packet>
    SPQ<Packet>::SPQ(ns3::QueueMode mode, std::vector<TrafficClass *> trafficClassVector): NS_LOG_TEMPLATE_DEFINE ("SPQ") {
        this->m_mode = mode;
        this->q_class = trafficClassVector;
        std::cout << "SPQ.q_class.size: " << q_class.size () << std::endl;
    }

    template <typename Packet>
    SPQ<Packet>::~SPQ() {
    }

    //todo
    template <typename Packet>
    bool SPQ<Packet>::Enqueue(Ptr <Packet> item) {
        u_int32_t index = Classify (item);
        std::cout<<"Result of Enqueue : "<<q_class[index]->Enqueue (item)<<std::endl;
        std::cout<<"Enqueuing !!!!!"<<std::endl;
        std::cout<<"IfEmpty:"<<q_class[index]->IfEmpty()<<std::endl;
        return true;
    }

    template <typename Packet>
    Ptr<Packet> SPQ<Packet>::Dequeue() {
        Ptr<Packet> p;
        p = Schedule();
        std::cout<<"Schedule p in Dequeue" << &p << std::endl;
        return p;
    }

    template <typename Packet>
    Ptr<Packet> SPQ<Packet>::Remove() {
        Ptr<Packet> p = Diffserv<Packet>::Remove();
        return p;
    }

    template <typename Packet>
    Ptr<const Packet> SPQ<Packet>::Peek() const {
        return Diffserv<Packet>::Peek();
    }

    template <typename Packet>
    uint32_t SPQ<Packet>::Classify(Ptr <Packet> item) {
        std::cout << "Test.SPQ.Classify!" << std::endl;
        uint32_t index = -1;

        for(uint32_t i=0;i<q_class.size();i++){
//            Ptr<Packet> copyPacket = item -> Copy();
//            PppHeader pppHeader;
//            Ipv4Header ipv4Header;
//            UdpHeader udpHeader;
//            copyPacket -> RemoveHeader(pppHeader);
//            copyPacket -> RemoveHeader(ipv4Header);
//            copyPacket -> RemoveHeader(udpHeader);
//            uint32_t sourcePort = udpHeader.GetSourcePort();
//            uint32_t destPort = udpHeader.GetDestinationPort();
//            std::cout << "source Port number : " << sourcePort << "\n";

            if(q_class[i]->Match(item)){
            //if (sourcePort == 49154 && destPort == 9) {
                std::cout<<"Match found::"<<q_class[i]->priority_level<<std::endl;
                std::cout<<"in Classify:: queue "<<i<<std::endl;
                index = i;
                return index;
            }
            else{
                if(q_class[i]->isDefault){
                    std::cout << "SPQ.Not Matched! Putting to Default Queue. Index value is " << i
                              << ", for priority:" << q_class[i]->priority_level << std::endl;
                    index = i;
                    break;
                }
            }
        }
        return index;
    }

    template <typename Packet>
   Ptr<Packet> SPQ<Packet>::Schedule() {
       Ptr<Packet> p;
      // uint32_t priority = 0;
      // uint32_t index = -1;

        std::cout<<" in Schedule : q_class[0].size: "<< q_class[0]->m_queue.size() <<std::endl;
        std::cout<<" in Schedule : q_class[1].size: "<< q_class[1]->m_queue.size() <<std::endl;

        std::cout<<" in Schedule : q_class[0] is EMPTY: "<< q_class[0]->IfEmpty () <<std::endl;
        std::cout<<" in Schedule : q_class[1] is EMPTY: "<< q_class[1]->IfEmpty () <<std::endl;

        if (q_class[0]->priority_level == 77 && q_class[0]->IfEmpty () != true) //HIGH PRIORITY
        {
            //std::cout<<"SPQ.priority_level is SAME!QUEUE is NOT EMPTY!priority:"<<  priority <<std::endl;
            //p = q_class[0]-> Peek (); // Dequeue()
            std::cout << "I am in High Priority !" << std::endl;
            p = q_class[0] -> Dequeue();
            std::cout<<"P is in 77 ----> "<< &p <<std::endl;
            return p;
        }
        else if ( q_class[0]->IfEmpty () == true)
        {

            std::cout << "I am in LOW Priority !" << std::endl;
            //p = q_class[1]-> Peek ();
            p = q_class[1] -> Dequeue();
            std::cout<<"P is in 99 ---->  "<< &p <<std::endl;

            return p;
        }
        else {
            std::cout << "PROBLEM!! Should not be here!" << std::endl;
            return 0;
        }
   }

   template <typename Packet>
   bool SPQ<Packet>::AddTrafficClass(TrafficClass *trafficClass) {
       std::vector<TrafficClass *> trafficClassList;
       trafficClassList.push_back (trafficClass);
       this->q_class = trafficClassList;
       return true;
   }
}