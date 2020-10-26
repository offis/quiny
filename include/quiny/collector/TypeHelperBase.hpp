// 2006-03-28, Thorsten Schubert, OFFIS

#ifndef QUINY_COLLECTOR_TYPEHELPERBASE_INCLUDED
#define QUINY_COLLECTOR_TYPEHELPERBASE_INCLUDED

#include <string>
#include "quiny/ir/SimpleType.hpp"
#include "quiny/ir/SystemCType.hpp"
#include "quiny/collector/collector.hpp"

namespace quiny
{
  namespace ir
  {
    class Type;
  }

  namespace collector
  {

    class TypeHelperBase
    {
      public:
      
        TypeHelperBase();
      
        virtual
        ~TypeHelperBase();
        
        // Will create a new object that must be destroyed by the caller
        ir::Type*
        getType() const;
        
        IDType
        id() const;
        
        // To be provided by the subclasses
                
        // only necessary for user-defined types
        virtual
        std::string
        getName() const;

        virtual
        bool
        isSimpleType() const;
        
        virtual
        ir::SimpleType::EnumValue
        whichSimpleType() const;
        
        virtual
        ir::CVNess
        getCVNess() const;
        
        virtual
        bool
        isSigned() const;
        
        virtual 
        bool
        isSystemCType() const;
        
        virtual
        ir::SystemCType::EnumValue
        whichSystemCType() const;

        virtual
        unsigned int
        getBitWidth() const;

      protected:        
      
        IDType    m_id;
    };

  }

}

#endif
