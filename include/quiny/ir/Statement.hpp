// 2006-03-22, Thorsten Schubert, OFFIS

#ifndef QUINY_IR_STATEMENT_INCLUDED
#define QUINY_IR_STATEMENT_INCLUDED

#include "quiny/utils/utils.hpp"

namespace quiny
{

  namespace ir
  {

    // A Statement may have a parent, i.e. another statement it is contained in. For example
    // the surrounding CompoundStatement or the If- of ForStatement for which 'this' is the body.
    class Statement
    {
      public:
      
        DEFINE_ACCEPT_METHOD(Statement)

      
        Statement(utils::observer_ptr<Statement> parent=0);
      
        virtual
        ~Statement();

        virtual
        utils::observer_ptr<Statement>
        getParent() const;
        
        virtual
        void
        setParent(utils::observer_ptr<Statement> newParent);
        
                
      protected:
        utils::observer_ptr<Statement>   m_parent;

    };

  }

}

#endif
