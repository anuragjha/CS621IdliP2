//
// Created by manalipatil on 4/23/19.
//
#include "ns3/log.h"
#include "ns3/object-base.h"
#include "ns3/log-macros-disabled.h"
#include "diff-serv.h"

namespace ns3 {
    NS_LOG_COMPONENT_DEFINE("Diffserv");

    NS_OBJECT_TEMPLATE_CLASS_DEFINE (Diffserv,Packet);

    template <typename Packet>
    TypeId Diffserv<Packet>::GetTypeId() {
        static TypeId tid = TypeId (("ns3::Diffserv<" + GetTypeParamName<Diffserv<Packet>> () + ">").c_str ())
                                    .SetParent<Queue<Packet>> ()
                .SetGroupName ("TrafficControl")
                .template AddConstructor<Diffserv<Packet> > ()
        ;
        return tid;
    }

    template <typename Packet>
    Diffserv<Packet>::Diffserv():Queue<Packet>(),
                                 NS_LOG_TEMPLATE_DEFINE ("Diffserv")
    {
    }

    template <typename Packet>
    Diffserv<Packet>::~Diffserv(){
    }

    template <typename Packet>
    QueueMode
    Diffserv<Packet>::GetMode() {
        return m_mode;
    }

    template <typename Packet>
    void Diffserv<Packet>::SetMode(QueueMode mode) {
        m_mode = mode;
    }

    template <typename Packet>
    bool Diffserv<Packet>::DoEnqueue(Ptr <Packet> item) {
//        bool resultOfEnqueue = false;
//        uint32_t i = Classify(item);
//        TrafficClass tc = GetTrafficClassAtIndex(int(i));
//        resultOfEnqueue = tc.Enqueue(item);
//        return resultOfEnqueue;
    return 1;
    }


    template <typename Packet>
    Ptr<Packet> Diffserv<Packet>::DoDequeue() {
//        for(TrafficClass *tc:q_class){
//            if(tc->Peek() != 0){
//                return tc->Dequeue();
//            }
//        }
        return 0;
    }


    template <typename Packet>
    Ptr<const Packet> Diffserv<Packet>::DoPeek() const {
        Ptr<Packet> p = new Packet();
        return p;
    }


    template <typename Packet>
    bool Diffserv<Packet>::Enqueue(Ptr <Packet> item) {
        return Enqueue(item);
    }

    template <typename Packet>
    Ptr<Packet> Diffserv<Packet>::Dequeue() {
        return Dequeue();
    }

    template <typename Packet>
    Ptr<Packet> Diffserv<Packet>::Remove() {
        return Remove();
    }

    template <typename Packet>
    Ptr<const Packet> Diffserv<Packet>::Peek() const {
        return Peek();
    }


    template <typename Packet>
    uint32_t Diffserv<Packet>::Classify(Ptr <Packet> item) {
        int i = 0;
        for(TrafficClass* trafficClass: q_class) {
            i = i+1;
            if (trafficClass->Match(item)) {
                return i;
            }
        }
        return 0;
    }

    //todo
    template <typename Packet>
    Ptr<Packet>
    Diffserv<Packet>::Schedule() {
        Ptr<Packet> p = new Packet();
        return p;
    }

    template <typename Packet>
    TrafficClass Diffserv<Packet>::GetTrafficClassAtIndex(int index) {
        TrafficClass* tc;
        tc = q_class[index];
        return *tc ;
    }

    template <typename Packet>
    std::vector<TrafficClass *> Diffserv<Packet>::GetQ_Class() {
        return this->q_class;
    }
}