// 2006-03-22, Thorsten Schubert, OFFIS

#ifndef QUINY_IR_IFSTATEMENT_INCLUDED
#define QUINY_IR_IFSTATEMENT_INCLUDED

#include "quiny/ir/Statement.hpp"
#include "quiny/utils/utils.hpp"

namespace quiny
{

  namespace ir
  {
    class Expression;

    class IfStatement : public Statement
    {
      public:
        DEFINE_ACCEPT_METHOD(IfStatement)
      
        IfStatement(utils::owner_ptr<Expression> condition,
                    utils::owner_ptr<Statement> thenStatement=utils::owner_ptr<Statement>(0),
                    utils::owner_ptr<Statement> elseStatement=utils::owner_ptr<Statement>(0));

        virtual
        ~IfStatement();
        
        utils::observer_ptr<Expression>
        getCondition() const;
        
        void
        setCondition(utils::owner_ptr<Expression> condition);
        
        utils::observer_ptr<Statement>
        getThenStatement() const;
        
        void
        setThenStatement(utils::owner_ptr<Statement> thenStatement);
        
        utils::observer_ptr<Statement>
        getElseStatement() const;
        
        void
        setElseStatement(utils::owner_ptr<Statement> elseStatement);
        
        
      protected:
        utils::owner_ptr<Expression>    m_condition;
        utils::owner_ptr<Statement>     m_thenStatement,
                                        m_elseStatement;
    };

  }

}

#endif
