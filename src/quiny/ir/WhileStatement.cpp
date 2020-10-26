// 2006-03-22, Thorsten Schubert, OFFIS

#include "quiny/ir/WhileStatement.hpp"
#include "quiny/ir/Expression.hpp"

namespace quiny
{

  namespace ir
  {

    WhileStatement::
    WhileStatement(utils::owner_ptr<Expression> condition,
                   utils::owner_ptr<Statement> body)
    : m_condition(condition)
    , m_body(body)
    {
    }
                   
    WhileStatement::~WhileStatement()
    {
      /* TODO */
    }
    
                    
    utils::observer_ptr<Expression>
    WhileStatement::
    getCondition() const
    {
      return m_condition;
    }
    
    void
    WhileStatement::
    setCondition(utils::owner_ptr<Expression> condition)
    {
      m_condition = condition;
    }
    
    utils::observer_ptr<Statement>
    WhileStatement::
    getBody() const
    {
      return m_body;
    }
    
    void
    WhileStatement::
    setBody(utils::owner_ptr<Statement> body)
    {
      m_body = body;
    }

  }
}
