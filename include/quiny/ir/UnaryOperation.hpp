// 2006-03-23, Thorsten Schubert, OFFIS

#ifndef QUINY_IR_UNARYOPERATION_INCLUDED
#define QUINY_IR_UNARYOPERATION_INCLUDED

#include "quiny/ir/OperationExpression.hpp"
#include "quiny/utils/utils.hpp"

namespace quiny
{

  namespace ir
  {
    class Expression;

    class UnaryOperation : public OperationExpression
    {
      public:
      
        UnaryOperation(utils::owner_ptr<Expression> expression);

        virtual
        ~UnaryOperation();
        
        utils::observer_ptr<Expression>
        getExpression() const;
        
        void
        setExpression(utils::owner_ptr<Expression> expression);
        
      protected:
        utils::owner_ptr<Expression>    m_expression;
    };

  }

}

#endif
