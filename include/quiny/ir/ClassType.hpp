// 2006-03-22, Thorsten Schubert, OFFIS

#ifndef QUINY_IR_CLASSTYPE_INCLUDED
#define QUINY_IR_CLASSTYPE_INCLUDED

#include <string>
#include "quiny/ir/Type.hpp"

namespace quiny
{

  namespace ir
  {

    class ClassType : public Type
    {
      public:

        ClassType();
      
        virtual
        ~ClassType();

        // Overriding Type::getName()
        virtual
        std::string
        getName() const;
                
        virtual
        void
        setName(const std::string &name);
        
      protected:
        std::string   m_name;
    };

  }

}

#endif
