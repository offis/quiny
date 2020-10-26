#include "quiny/ir/PortChannelWriteStatement.hpp"
#include "quiny/ir/PortChannelBase.hpp"
#include "quiny/ir/Expression.hpp"


namespace quiny
{

  namespace ir
  {
            
    PortChannelWriteStatement::
    PortChannelWriteStatement(utils::observer_ptr<PortChannelBase> source,
                              utils::owner_ptr<Expression> expression)
    : m_source(source)
    , m_expression(expression)
    {

    }
                            
    PortChannelWriteStatement::
    ~PortChannelWriteStatement()
    {
      
    }

    
    void
    PortChannelWriteStatement::
    setSource(utils::observer_ptr<PortChannelBase> source)
    {
      m_source = source; 
    }
    
    utils::observer_ptr<PortChannelBase>
    PortChannelWriteStatement::
    getSource() const
    {
      return m_source; 
    }
    
    utils::observer_ptr<Expression>
    PortChannelWriteStatement::
    getExpression() const
    {
      return m_expression;
    }
    
    void
    PortChannelWriteStatement::
    setExpression(utils::owner_ptr<Expression> expression)
    {
      m_expression = expression; 
    }
    
  }
}
