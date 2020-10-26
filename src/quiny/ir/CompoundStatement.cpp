// 2006-03-22, Thorsten Schubert, OFFIS

#include "quiny/ir/CompoundStatement.hpp"

namespace quiny
{

  namespace ir
  {

    CompoundStatement::~CompoundStatement()
    {
      /* TODO */
    }

    void
    CompoundStatement::
    addStatement(utils::owner_ptr<Statement> statement)
    {
      m_body.push_back(statement); 
    }
    
    utils::observer_iter<Statement>
    CompoundStatement::
    getBody() const
    {
      return m_body.begin();
    }
    
    
  }


}

