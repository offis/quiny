// 2006-03-27, Thorsten Schubert, OFFIS

#ifndef QUINY_SC_SC_CORE_SC_IN_INCLUDED
#define QUINY_SC_SC_CORE_SC_IN_INCLUDED

#include "quiny_sc/sc_core/sc_port.hpp"
#include "quiny_sc/sc_core/sc_signal_in_if.hpp"

#include "quiny_sc/sc_core/sc_event_finder.hpp"

#include "quiny_sc/cpp_dt/Bool.hpp"
#include "quiny/collector/collector.hpp"
#include "quiny/collector/TypeHelper.hpp"

namespace quiny_sc
{

  namespace sc_core
  {
    template<typename T>
    class sc_in : public sc_port<sc_signal_in_if<T>, 1>
    {
      public:
      
        sc_in();
        explicit sc_in(const char *name);

        virtual
        ~sc_in();
        
      protected:
        ::quiny::collector::TypeHelper<T>   m_typeHelper;
    };

    // Specialisation for bool
    template<>
    class sc_in<cpp_dt::Bool> : public sc_port<sc_signal_in_if<cpp_dt::Bool>, 1>
    {
      public:
        sc_in();
        explicit sc_in(const char *name);

        sc_event_finder&
        pos() const;
        
        const cpp_dt::Bool&
        read() const;
        
        virtual
        ~sc_in();
        
      private:
        mutable cpp_dt::Bool                          *m_dummy;
        ::quiny::collector::TypeHelper<cpp_dt::Bool>   m_typeHelper;
        mutable sc_event_finder                        m_posEdge;
    };
    
    // ===============================================================================================
    // IMPLEMENTATION
    // ===============================================================================================     
      
    template<typename T>
    sc_in<T>::
    ~sc_in()
    {
      /* TODO */
    }
    
    template<typename T>
    sc_in<T>::
    sc_in()
    {
      ::quiny::collector::inputPortCreated(this->id(), this->basename(), 
                                           this->m_typeHelper);
    }
    
    template<typename T>
    sc_in<T>::
    sc_in(const char *name)
    : sc_port<sc_signal_in_if<T>, 1>(name)
    {
      ::quiny::collector::inputPortCreated(this->id(), this->basename(), 
                                           this->m_typeHelper);
    }
    
    // ===============================================================================================
    
    sc_in<cpp_dt::Bool>::
    sc_in()
    : m_dummy(0)
    , m_posEdge(*this, ::quiny::ir::Process::Sensitivity::PosEdge)    
    {
      ::quiny::collector::inputPortCreated(this->id(), this->basename(), 
                                           this->m_typeHelper);
    }
    
    sc_in<cpp_dt::Bool>::
    sc_in(const char *name)
    : sc_port<sc_signal_in_if<cpp_dt::Bool>, 1>(name)
    , m_dummy(0)
    , m_posEdge(*this, ::quiny::ir::Process::Sensitivity::PosEdge)    
    {
      ::quiny::collector::inputPortCreated(this->id(), this->basename(), 
                                           m_typeHelper);
    }

    sc_in<cpp_dt::Bool>::
    ~sc_in()
    {
      /* TODO */
    }
    
    sc_event_finder&
    sc_in<cpp_dt::Bool>::
    pos() const
    {
      return m_posEdge; 
    }

    const cpp_dt::Bool&
    sc_in<cpp_dt::Bool>::
    read() const
    {
      delete m_dummy;
      m_dummy = new cpp_dt::Bool();
      ::quiny::collector::isPortRead(m_dummy->id(), this->id());
      return *m_dummy;
    }

            
  }

}

#endif
