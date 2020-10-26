// 2006-03-22, Thorsten Schubert, OFFIS

#include "quiny/ir/Statement.hpp"

namespace quiny
{

  namespace ir
  {

    Statement::
    Statement(utils::observer_ptr<Statement> parent)
    : m_parent(parent)
    {
      
    }
    
    Statement::~Statement()
    {
      /* TODO */
    }

    utils::observer_ptr<Statement>
    Statement::
    getParent() const
    {
      return m_parent;
    }

    void
    Statement::
    setParent(utils::observer_ptr<Statement> newParent)
    {
      m_parent = newParent;
    }
    
  }

}

