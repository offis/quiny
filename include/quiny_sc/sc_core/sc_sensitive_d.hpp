// 2006-03-27, Thorsten Schubert, OFFIS

#ifndef QUINY_SC_SC_CORE_SC_SENSITIVE_D_INCLUDED
#define QUINY_SC_SC_CORE_SC_SENSITIVE_D_INCLUDED

namespace quiny_sc
{

  namespace sc_core
  { 
    class sc_event;
    class sc_interface;
    class sc_port_base;   
    class sc_event_finder;   

    class sc_sensitive_d
    {
      public:

        sc_sensitive_d&
        operator << (const sc_event &);
      
        sc_sensitive_d&
        operator << (const sc_interface &);
        
        sc_sensitive_d&
        operator << (const sc_port_base &);
      
        sc_sensitive_d&
        operator << (sc_event_finder &);
      
    };

  }

}

#endif
