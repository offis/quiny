// 2006-03-27, Thorsten Schubert, OFFIS

#include "quiny_sc/sc_core/sc_event_finder.hpp"

namespace quiny_sc
{

  namespace sc_core
  {

//     namespace
//     {
//       sc_event_finder sc_event_finder_posedge_inst;
//     }
    
    sc_event_finder::
    sc_event_finder(const sc_port_base &portBase, Edge edge)
    : m_portBase(portBase)
    , m_edge(edge)
    {      
    }

    const sc_port_base&
    sc_event_finder::
    getPortBase() const
    {
      return m_portBase; 
    }
    
    sc_event_finder::Edge
    sc_event_finder::
    getEdge() const
    {
      return m_edge;
    }
    
        
//     sc_event_finder&
//     sc_event_finder::
//     sc_event_finder_posedge()
//     {
//       return sc_event_finder_posedge_inst;
//     }
  }


}

