// Thorsten Schubert, OFFIS

#ifndef QUINY_IR_PORT_CHANNEL_WRITE_STATEMENT_INCLUDED
#define QUINY_IR_PORT_CHANNEL_WRITE_STATEMENT_INCLUDED

#include "quiny/ir/Statement.hpp"

namespace quiny
{

  namespace ir
  {
    class PortChannelBase;
    class Expression;

    class PortChannelWriteStatement : public Statement
    {
      public:
      
        DEFINE_ACCEPT_METHOD(PortChannelWriteStatement)
        
        PortChannelWriteStatement(utils::observer_ptr<PortChannelBase> source,
                                  utils::owner_ptr<Expression> expression);
        
        virtual
        ~PortChannelWriteStatement();

        utils::observer_ptr<PortChannelBase>
        getSource() const;
        
        void
        setSource(utils::observer_ptr<PortChannelBase> source);

        utils::observer_ptr<Expression>
        getExpression() const;
        
        void
        setExpression(utils::owner_ptr<Expression> expression);
                        
      protected:
        utils::observer_ptr<PortChannelBase>    m_source;
        utils::owner_ptr<Expression>    m_expression;
        
    };
  }
}

#endif
