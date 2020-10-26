// 2006-03-23, Thorsten Schubert, OFFIS

#ifndef QUINY_IR_CASTEXPRESSION_INCLUDED
#define QUINY_IR_CASTEXPRESSION_INCLUDED

#include "quiny/ir/UnaryOperation.hpp"
#include "quiny/utils/utils.hpp"

namespace quiny
{

  namespace ir
  {
    class Type;

    class CastExpression : public UnaryOperation
    {
      public:
      
        DEFINE_ACCEPT_METHOD(CastExpression)
      
        CastExpression(utils::owner_ptr<Type> destType,
                       utils::owner_ptr<Expression> expression);

        virtual
        ~CastExpression();
        
        utils::observer_ptr<Type>
        getDestType() const;
        
        void
        setDestType(utils::owner_ptr<Type> destType);
        
      protected:
        utils::owner_ptr<Type>    m_destType;
    };

  }

}

#endif
