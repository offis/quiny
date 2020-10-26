// Thorsten Schubert, OFFIS

#ifndef QUINY_IR_WAIT_STATEMENT_INCLUDED
#define QUINY_IR_WAIT_STATEMENT_INCLUDED

#include "quiny/ir/Statement.hpp"
#include "quiny/utils/utils.hpp"

namespace quiny
{

  namespace ir
  {
    class TimeLiteral;
    
    // Note: WaitStatement is currently limited to fixed-duration waits given by TimeLiterals
    
    class WaitStatement : public Statement
    {
      public:
        DEFINE_ACCEPT_METHOD(WaitStatement)
        
        WaitStatement(utils::owner_ptr<TimeLiteral> timeLiteral);
        
        virtual 
        ~WaitStatement();
        
        utils::observer_ptr<TimeLiteral>
        getTimeLiteral() const;
        
        void
        setTimeLiteral(utils::owner_ptr<TimeLiteral> timeLiteral);

      protected:
        utils::owner_ptr<TimeLiteral>   m_timeLiteral;                
    };
  }
}

#endif
