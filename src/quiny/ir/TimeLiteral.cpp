// Thorsten Schubert, OFFIS

#include "quiny/ir/TimeLiteral.hpp"

namespace quiny
{
  namespace ir
  {
    TimeLiteral::
    TimeLiteral(double value, TimeUnit unit)
    : m_value(value)
    , m_unit(unit)
    {
    }
    
    TimeLiteral::
    ~TimeLiteral()
    {
    }
    
    double
    TimeLiteral::
    getValue() const
    {
      return m_value;
    }
    
    void
    TimeLiteral::
    setValue(double value)
    {
      m_value = value;
    }    
    
    TimeLiteral::TimeUnit
    TimeLiteral::
    getUnit() const
    {
      return m_unit; 
    }
    
    void
    TimeLiteral::
    setUnit(TimeUnit unit)
    {
      m_unit = unit;
    }
    
  } 
}
