// 2006-03-27, Thorsten Schubert, OFFIS

#ifndef QUINY_SC_SC_CORE_SC_MODULE_NAME_INCLUDED
#define QUINY_SC_SC_CORE_SC_MODULE_NAME_INCLUDED

#include <string>

#include "quiny/collector/collector.hpp"

namespace quiny_sc
{

  namespace sc_core
  {
    class sc_module_name : public ::quiny::collector::HasId
    {
      public:
        sc_module_name(const char *);
        sc_module_name(const sc_module_name &);
        
        ~sc_module_name();
        
        operator const char*() const; 
        
      private:
        // Disabled
        sc_module_name();
        
        sc_module_name& 
        operator = (const sc_module_name&);

        std::string   m_name;
        
    };

    // Non-standard version which also determines the class name
    template<typename T>
    class sc_module_name_q : public sc_module_name
    {
      public:
        sc_module_name_q(const char *);
        sc_module_name_q(const sc_module_name_q &);
      
    };

    // ===============================================================================================
    // IMPLEMENTATION
    // ===============================================================================================     
    
    template<typename T>
    sc_module_name_q<T>::
    sc_module_name_q(const char *name)
    : sc_module_name(name)
    {
      ::quiny::collector::moduleHasClassName(this->id(), T::getClassName());
    }
    
    template<typename T>
    sc_module_name_q<T>::
    sc_module_name_q(const sc_module_name_q &name)
    : sc_module_name(name)
    {
      ::quiny::collector::moduleHasClassName(this->id(), T::getClassName());
    }
    
  }

}

#endif
