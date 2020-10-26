// 2006-03-27, Thorsten Schubert, OFFIS

#ifndef QUINY_SC_SC_CORE_SC_INOUT_INCLUDED
#define QUINY_SC_SC_CORE_SC_INOUT_INCLUDED

#include "quiny_sc/sc_core/sc_port.hpp"
#include "quiny_sc/sc_core/sc_signal_inout_if.hpp"

#include "quiny/collector/collector.hpp"
#include "quiny/collector/TypeHelper.hpp"

namespace quiny_sc
{

  namespace sc_core
  {

    template<typename T>
    class sc_inout : public sc_port<sc_signal_inout_if<T>, 1>
    {
      public:
      
        sc_inout();
        explicit sc_inout(const char *name);
      
      
        const T&
        read() const;
        
        void
        write(const T&);
      
        virtual 
        ~sc_inout();
        
      protected:
        
        mutable T                          *m_dummy;
        ::quiny::collector::TypeHelper<T>   m_typeHelper;

    };

    // ===============================================================================================
    // IMPLEMENTATION
    // ===============================================================================================     
      
    template<typename T>
    sc_inout<T>::
    ~sc_inout()
    {
      /* TODO */
    }

    template<typename T>
    sc_inout<T>::
    sc_inout()
    {
    }
    
    template<typename T>
    sc_inout<T>::
    sc_inout(const char *name)
    : sc_port<sc_signal_inout_if<T>, 1>(name)
    {
    }

    template<typename T>
    const T&
    sc_inout<T>::
    read() const
    {
      delete m_dummy;
      m_dummy = new T();
      ::quiny::collector::isPortRead(m_dummy->id(), this->id());
      return *m_dummy;
    }

    template<typename T>
    void
    sc_inout<T>::
    write(const T &val)
    {
      ::quiny::collector::portWrite(this->id(), val.id());      
    }

  }

}

#endif
