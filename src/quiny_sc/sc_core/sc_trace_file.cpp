// 2006-07-12, Thorsten Schubert, OFFIS

#include "quiny_sc/sc_core/sc_trace_file.hpp"

namespace quiny_sc
{

  namespace sc_core
  {

    sc_trace_file*
    sc_create_vcd_trace_file(const char *)
    { 
      return 0;
    }
    
    void
    sc_close_vcd_trace_file()
    {
    
    }
    
    void
    sc_write_comment(sc_trace_file *, const std::string &)
    {
    
    }

  }

}
