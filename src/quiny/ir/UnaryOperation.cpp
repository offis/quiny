// 2006-03-23, Thorsten Schubert, OFFIS

#include "quiny/ir/UnaryOperation.hpp"

namespace quiny
{

  namespace ir
  {

    UnaryOperation::
    UnaryOperation(utils::owner_ptr<Expression> expression)
    : m_expression(expression)
    {
      
    }
    
    UnaryOperation::~UnaryOperation()
    {
      /* TODO */
    }

    
    utils::observer_ptr<Expression>
    UnaryOperation::
    getExpression() const
    {
      return m_expression; 
    }
    
    void
    UnaryOperation::
    setExpression(utils::owner_ptr<Expression> expression)
    {
      m_expression = expression; 
    }
    
    
  }


}

