// 2006-03-27, Thorsten Schubert, OFFIS

#include "quiny_sc/sc_core/sc_module_name.hpp"
#include "quiny/utils/utils.hpp"

namespace quiny_sc
{

  namespace sc_core
  {
  
    sc_module_name::
    sc_module_name(const char *name)
    : m_name(name)
    {
      ::quiny::collector::enteringModuleCtor(id(), m_name);
    }
    
    sc_module_name::
    sc_module_name(const sc_module_name &src)
    : m_name(src.m_name)
    {
      ::quiny::collector::enteringModuleCtor(id(), m_name);
    }

    sc_module_name::
    ~sc_module_name()
    {
      ::quiny::collector::leavingModuleCtor(id());
    }
    
    sc_module_name::
    operator const char*() const
    {
      return m_name.c_str();
    }

    // Disabled
    sc_module_name::
    sc_module_name()
    {
      THIS_IS_DEAD_CODE
    }
    
    sc_module_name& 
    sc_module_name::
    operator = (const sc_module_name&)
    {
      THIS_IS_DEAD_CODE
      return *this;
    }


  }


}

