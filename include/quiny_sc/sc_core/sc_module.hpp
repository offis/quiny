// 2006-03-27, Thorsten Schubert, OFFIS

#ifndef QUINY_SC_SC_CORE_SC_MODULE_INCLUDED
#define QUINY_SC_SC_CORE_SC_MODULE_INCLUDED

#include "quiny_sc/sc_core/sc_object.hpp"
#include "quiny_sc/sc_core/sc_sensitive_d.hpp"

#include "quiny_sc/sc_core/sc_module_name.hpp"

#define SC_MODULE(name) struct name : public sc_module
#define SC_CTOR(moduleName) static std::string getClassName() { return #moduleName ;}\
                            moduleName(::quiny_sc::sc_core::sc_module_name_q< moduleName > name)  
                            
#define SC_METHOD(name) { ::quiny::collector::enteringScMethod( #name ); \
                          name();  \
                          ::quiny::collector::leavingScMethod(); \
                        }
#define SC_THREAD(name) { ::quiny::collector::enteringScThread( #name ); \
                          name();  \
                          ::quiny::collector::leavingScThread(); \
                        }
#define SC_CTHREAD(name, clkEdge)

namespace quiny_sc
{

  namespace sc_core
  {
    class sc_time;

    class sc_module : public sc_object
    {
      public:
      
        sc_module();
        explicit sc_module(const char *name);

        virtual
        ~sc_module();        
        
        // TODO: the int should be a cpp_dt::Int
        void 
        wait(int);
        
        void
        wait(const sc_time&);

        // TODO: Many wait variants are missing

      protected:
        sc_sensitive_d    sensitive;
    };

  }

}

#endif
