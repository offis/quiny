// 2006-03-22, Thorsten Schubert, OFFIS

#ifndef QUINY_IR_WHILESTATEMENT_INCLUDED
#define QUINY_IR_WHILESTATEMENT_INCLUDED

#include "quiny/ir/Statement.hpp"

namespace quiny
{

  namespace ir
  {
    class Expression;

    class WhileStatement : public Statement
    {
      public:

        DEFINE_ACCEPT_METHOD(WhileStatement)
      
        WhileStatement(utils::owner_ptr<Expression> condition,
                       utils::owner_ptr<Statement> body=utils::owner_ptr<Statement>(0));
                    
        virtual
        ~WhileStatement();
        
        utils::observer_ptr<Expression>
        getCondition() const;
        
        void
        setCondition(utils::owner_ptr<Expression> condition);
        
        utils::observer_ptr<Statement>
        getBody() const;
        
        void
        setBody(utils::owner_ptr<Statement> body);
        
      protected:
        utils::owner_ptr<Expression>    m_condition;
        utils::owner_ptr<Statement>     m_body;
        
    };

  }

}

#endif
