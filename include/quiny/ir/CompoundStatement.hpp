// 2006-03-22, Thorsten Schubert, OFFIS

#ifndef QUINY_IR_COMPOUNDSTATEMENT_INCLUDED
#define QUINY_IR_COMPOUNDSTATEMENT_INCLUDED

#include "quiny/ir/Statement.hpp"
#include "quiny/utils/utils.hpp"

namespace quiny
{

  namespace ir
  {

    class CompoundStatement : public Statement
    {
      public:

        DEFINE_ACCEPT_METHOD(CompoundStatement)
        
        virtual
        ~CompoundStatement();
        
        void
        addStatement(utils::owner_ptr<Statement> statement);
        
        utils::observer_iter<Statement>
        getBody() const;
        
        
      protected:
        utils::owner_ptr_list<Statement>   m_body;
    };

  }

}

#endif
