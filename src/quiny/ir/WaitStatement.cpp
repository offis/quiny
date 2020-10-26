// Thorsten Schubert, OFFIS

#include "quiny/ir/WaitStatement.hpp"
#include "quiny/ir/TimeLiteral.hpp"

namespace quiny
{
  namespace ir
  {
    WaitStatement::
    WaitStatement(utils::owner_ptr<TimeLiteral> timeLiteral)
    : m_timeLiteral(timeLiteral)
    {
    }
    
    WaitStatement::
    ~WaitStatement()
    {
    }
    
    utils::observer_ptr<TimeLiteral>
    WaitStatement::
    getTimeLiteral() const
    {
      return m_timeLiteral;
    }
    
    void
    WaitStatement::
    setTimeLiteral(utils::owner_ptr<TimeLiteral> timeLiteral)
    {
      m_timeLiteral = timeLiteral;
    }
    
  }
}
