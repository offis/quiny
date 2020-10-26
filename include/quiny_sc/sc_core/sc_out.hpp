// 2006-03-27, Thorsten Schubert, OFFIS

#ifndef QUINY_SC_SC_CORE_SC_OUT_INCLUDED
#define QUINY_SC_SC_CORE_SC_OUT_INCLUDED

#include "quiny_sc/sc_core/sc_inout.hpp"

namespace quiny_sc
{

  namespace sc_core
  {
    template<typename IFace>
    class sc_out : public sc_inout<IFace>
    {
      public:
      
        sc_out();
        explicit sc_out(const char *name);

        virtual
        ~sc_out();
    };

    // ===============================================================================================
    // IMPLEMENTATION
    // ===============================================================================================     
      
    template<typename IFace>
    sc_out<IFace>::
    ~sc_out()
    {
      /* TODO */
    }
    
    template<typename IFace>
    sc_out<IFace>::
    sc_out()
    {
      ::quiny::collector::outputPortCreated(this->id(), this->basename(), 
                                            this->m_typeHelper);
    }

    template<typename IFace>
    sc_out<IFace>::
    sc_out(const char *name)
    : sc_inout<IFace>(name)
    {
      ::quiny::collector::outputPortCreated(this->id(), this->basename(), 
                                            this->m_typeHelper);
    }
    
  }

}

#endif
