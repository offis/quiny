#include "quiny/ir/IntLiteral.hpp"
#include "quiny/ir/SimpleType.hpp"

namespace quiny
{

  namespace ir
  {
    IntLiteral::
    IntLiteral(unsigned long long value, utils::owner_ptr<SimpleType> type)
    : m_value(value)
    , m_type(type)
    {
    }
    
    IntLiteral::
    ~IntLiteral()
    {
    }
    
    unsigned long long
    IntLiteral::
    getValue() const
    {
      return m_value; 
    }
    
    void
    IntLiteral::
    setValue(unsigned long long value)
    {
      m_value = value; 
    }
    
  }
}
