// 2006-03-22, Thorsten Schubert, OFFIS

#include "quiny/ir/IfStatement.hpp"
#include "quiny/ir/Expression.hpp"

namespace quiny
{

  namespace ir
  {
    IfStatement::
    IfStatement(utils::owner_ptr<Expression> condition,
                utils::owner_ptr<Statement> thenStatement,
                utils::owner_ptr<Statement> elseStatement)
    : m_condition(condition)
    , m_thenStatement(thenStatement)
    , m_elseStatement(elseStatement)
    {
      
    }
    
    
    IfStatement::~IfStatement()
    {
      /* TODO */
    }


    utils::observer_ptr<Expression>
    IfStatement::
    getCondition() const
    {
      return m_condition; 
    }
    
    void
    IfStatement::
    setCondition(utils::owner_ptr<Expression> condition)
    {
      m_condition = condition;
    }

    utils::observer_ptr<Statement>
    IfStatement::
    getThenStatement() const
    {
      return m_thenStatement; 
    }
    
    void
    IfStatement::
    setThenStatement(utils::owner_ptr<Statement> thenStatement)
    {     
      m_thenStatement = thenStatement; 
    }
    
    utils::observer_ptr<Statement>
    IfStatement::
    getElseStatement() const
    {
      return m_elseStatement; 
    }
    
    void
    IfStatement::
    setElseStatement(utils::owner_ptr<Statement> elseStatement)
    {
      m_elseStatement = elseStatement;      
    }
        
  }

}

