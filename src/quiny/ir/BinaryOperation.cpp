// 2006-03-23, Thorsten Schubert, OFFIS

#include "quiny/ir/BinaryOperation.hpp"

namespace quiny
{

  namespace ir
  {
    using utils::owner_ptr;
    using utils::observer_ptr;
  
    BinaryOperation::
    BinaryOperation(BinaryOperation::EnumValue op,
                    owner_ptr<Expression> lhs,
                    owner_ptr<Expression> rhs)
    : m_op(op),
      m_lhs(lhs),
      m_rhs(rhs)
    {
    
    }

    BinaryOperation::~BinaryOperation()
    {
      /* TODO */
    }

    BinaryOperation::EnumValue
    BinaryOperation::
    whichOperator() const
    {
      return m_op;
    }

    observer_ptr<Expression>
    BinaryOperation::
    getLhs() const
    {
      return m_lhs;
    }

    observer_ptr<Expression>
    BinaryOperation::
    getRhs() const
    {
      return m_rhs;
    }


  }


}

