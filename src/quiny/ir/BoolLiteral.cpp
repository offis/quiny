#include "quiny/ir/BoolLiteral.hpp"

namespace quiny
{

  namespace ir
  {
    BoolLiteral::
    BoolLiteral(bool value)
    : m_value(value)
    {
      
    }
    
    BoolLiteral::
    ~BoolLiteral()
    {
    }
    
    bool
    BoolLiteral::
    getValue() const
    {
      return m_value; 
    }
    
    void
    BoolLiteral::
    setValue(bool b)
    {
      m_value = b; 
    }
    
  }
}
