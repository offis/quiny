// 2006-03-27, Thorsten Schubert, OFFIS

#ifndef QUINY_SC_SC_CORE_SC_PORT_INCLUDED
#define QUINY_SC_SC_CORE_SC_PORT_INCLUDED

#include "quiny_sc/sc_core/sc_port_base.hpp"
#include "quiny/collector/collector.hpp"

namespace quiny_sc
{

  namespace sc_core
  {
    enum sc_port_policy
    {
      SC_ONE_OR_MORE_BOUND,
      SC_ZERO_OR_MORE_BOUND,
      SC_ALL_BOUND
    };
    
    template<typename IFace, int NumChannels=1, sc_port_policy Policy=SC_ONE_OR_MORE_BOUND>
    class sc_port : public sc_port_base
    {
      public:
      
        sc_port();
        explicit sc_port(const char *name);
        
        void 
        operator() (IFace &);
        
        void 
        operator() (sc_port<IFace,NumChannels> &);
        
        void 
        bind(IFace &);
        
        void 
        bind(sc_port<IFace,NumChannels> &); 


        virtual
        ~sc_port();
    };

    // ===============================================================================================
    // IMPLEMENTATION
    // ===============================================================================================     
      
    template<typename IFace, int NumChannels, sc_port_policy Policy>     
    sc_port<IFace, NumChannels, Policy>::
    ~sc_port()
    {
      /* TODO */
    }
    
    template<typename IFace, int NumChannels, sc_port_policy Policy>     
    sc_port<IFace, NumChannels, Policy>::
    sc_port()
    {
    }
    
    template<typename IFace, int NumChannels, sc_port_policy Policy>     
    sc_port<IFace, NumChannels, Policy>::
    sc_port(const char *name)
    : sc_port_base(name)
    {
    }
    
    
    template<typename IFace, int NumChannels, sc_port_policy Policy>     
    void 
    sc_port<IFace, NumChannels, Policy>::
    operator() (IFace &iface)
    {
      bind(iface);
    }
   
    template<typename IFace, int NumChannels, sc_port_policy Policy>     
    void 
    sc_port<IFace, NumChannels, Policy>::
    operator() (sc_port<IFace,NumChannels> &port)
    {
      bind(port);
    }
    
    template<typename IFace, int NumChannels, sc_port_policy Policy>     
    void 
    sc_port<IFace, NumChannels, Policy>::
    bind(IFace &i)
    {
      ::quiny::collector::portToInterfaceBinding(this->id(), i.id());
    }
    
    template<typename IFace, int NumChannels, sc_port_policy Policy>     
    void 
    sc_port<IFace, NumChannels, Policy>::
    bind(sc_port<IFace,NumChannels> &p)
    {
      ::quiny::collector::portToPortBinding(this->id(), p.id());
    }
    
  }

}

#endif
