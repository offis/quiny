// 2006-03-27, Thorsten Schubert, OFFIS

#ifndef QUINY_SC_SC_CORE_SC_SIGNAL_INCLUDED
#define QUINY_SC_SC_CORE_SC_SIGNAL_INCLUDED

#include "quiny_sc/sc_core/sc_signal_inout_if.hpp"
#include "quiny_sc/sc_core/sc_prim_channel.hpp"

#include "quiny/collector/collector.hpp"
#include "quiny/collector/TypeHelper.hpp"

namespace quiny_sc
{

  namespace sc_core
  {
    template<typename T>
    class sc_signal : public sc_signal_inout_if<T>, 
                      public sc_prim_channel
    {
      public:

        sc_signal();
        explicit sc_signal(const char *name);       
        
        virtual
        ~sc_signal();
        
        virtual
        const T&
        read() const;
        
        virtual
        void
        write (const T&);
        
      private:
        mutable T   *m_dummy;
        
//        ::quiny::collector::TypeHelper<T>   m_typeHelper;
    };

    // ===============================================================================================
    // IMPLEMENTATION
    // ===============================================================================================     

    template<typename T>    
    sc_signal<T>::
    sc_signal()
    : m_dummy(0)
    {
//      ::quiny::collector::signalCreated(this, m_typeHelper);
    }
    
    template<typename T>    
    sc_signal<T>::
    sc_signal(const char *name)
    : sc_prim_channel(name)
    , m_dummy(0)
    {
      ::quiny::collector::TypeHelper<T>   m_typeHelper;
      ::quiny::collector::signalCreated(id(), basename(), m_typeHelper);
    }
    
    template<typename T>    
    sc_signal<T>::
    ~sc_signal()
    {
      /* TODO */
    }

    template<typename T>    
    const T&
    sc_signal<T>::
    read() const
    {
      delete m_dummy;
      m_dummy = new T();
      ::quiny::collector::isSignalRead(m_dummy->id(), this->id());
      return *m_dummy;  
    }

    template<typename T>    
    void
    sc_signal<T>::
    write (const T& val)
    {
      ::quiny::collector::signalWrite(this->id(), val.id());
    }

  }

}

#endif
