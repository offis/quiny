// 2006-07-12, Thorsten Schubert, OFFIS

#ifndef QUINY_SC_SC_CORE_SC_TRACEFILE_INCLUDED
#define QUINY_SC_SC_CORE_SC_TRACEFILE_INCLUDED

#include "quiny_sc/sc_core/sc_time.hpp"
#include "quiny/collector/collector.hpp"
#include <string>

namespace quiny_sc
{

  namespace sc_core
  {
    class sc_trace_file
    {
      public:
        virtual 
        void
        set_time_unit(double, sc_time_unit) = 0;
    };
    
    sc_trace_file*
    sc_create_vcd_trace_file(const char *);
    
    void
    sc_close_vcd_trace_file();
    
    void
    sc_write_comment(sc_trace_file *, const std::string &);
    
    // Not standard compliant
    template<typename T>
    void
    sc_trace(sc_trace_file*, const T&, const std::string &);
    
    // ===============================================================================================
    // IMPLEMENTATION
    // ===============================================================================================     
    
    template<typename T>
    void
    sc_trace(sc_trace_file*, const T &obj, const std::string &)
    {
      ::quiny::collector::trace(obj.id());
    }
    
  }
}

#endif
