// 2006-03-23, Thorsten Schubert, OFFIS

#ifndef QUINY_IR_BINARYOPERATION_INCLUDED
#define QUINY_IR_BINARYOPERATION_INCLUDED

#include "quiny/ir/OperationExpression.hpp"
#include "quiny/utils/utils.hpp"

namespace quiny
{

  namespace ir
  {

    class BinaryOperation : public OperationExpression
    {
      public:
      
        DEFINE_ACCEPT_METHOD(BinaryOperation)

        enum EnumValue
        {
          Plus,
          Minus,
          Mult,
          Div,
          Mod,
          Less,
          LessEqual,
          Greater,
          GraterEqual,
          Equal,
          NotEqual
        };     
            
        BinaryOperation(BinaryOperation::EnumValue op,
                        utils::owner_ptr<Expression> lhs,
                        utils::owner_ptr<Expression> rhs);

        virtual
        ~BinaryOperation();
        
        
        BinaryOperation::EnumValue
        whichOperator() const;
        
        utils::observer_ptr<Expression>
        getLhs() const;
        
        utils::observer_ptr<Expression>
        getRhs() const;
        
        
      protected:
        BinaryOperation::EnumValue         m_op;
      
        utils::owner_ptr<Expression>       m_lhs,
                                           m_rhs;
    };

  }

}

#endif
