// 2006-03-22, Thorsten Schubert, OFFIS

#ifndef QUINY_IR_EXPRESSION_INCLUDED
#define QUINY_IR_EXPRESSION_INCLUDED

#include "quiny/utils/utils.hpp"

namespace quiny
{

  namespace ir
  {

    class Expression
    {
      public:
      
        DEFINE_ACCEPT_METHOD(Expression)


        virtual
        ~Expression();
    };

  }

}

#endif
