// 2006-03-23, Thorsten Schubert, OFFIS

#include "quiny/ir/CastExpression.hpp"
#include "quiny/ir/Type.hpp"

namespace quiny
{

  namespace ir
  {

    CastExpression::
    CastExpression(utils::owner_ptr<Type> destType,
                   utils::owner_ptr<Expression> expression)
    : UnaryOperation(expression)
    , m_destType(destType)
    {
      
    }
                   
    CastExpression::~CastExpression()
    {
      /* TODO */
    }

    utils::observer_ptr<Type>
    CastExpression::
    getDestType() const
    {
      return m_destType; 
    }
    
    void
    CastExpression::
    setDestType(utils::owner_ptr<Type> destType)
    {
      m_destType = destType; 
    }
    
    
  }


}

