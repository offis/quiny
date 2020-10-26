// 2006-03-27, Thorsten Schubert, OFFIS

#ifndef QUINY_SC_SC_CORE_SC_EVENT_FINDER_INCLUDED
#define QUINY_SC_SC_CORE_SC_EVENT_FINDER_INCLUDED

#include "quiny/collector/collector.hpp"

namespace quiny_sc
{

  namespace sc_core
  {
    class sc_port_base;

    class sc_event_finder
    {
      public:
      
        typedef ::quiny::ir::Process::Sensitivity::Edge Edge;
            
        sc_event_finder(const sc_port_base &portBase, Edge edge);
        
        const sc_port_base&
        getPortBase() const;
        
        Edge
        getEdge() const;

//         static
//         sc_event_finder&
//         sc_event_finder_posedge();

      protected:
        const sc_port_base  &m_portBase;
        Edge                 m_edge;

    };

  }

}

#endif
