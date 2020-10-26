// 2006-03-22, Thorsten Schubert, OFFIS

#ifndef QUINY_IR_TYPE_INCLUDED
#define QUINY_IR_TYPE_INCLUDED

#include <string>
#include "quiny/utils/utils.hpp"

namespace quiny
{

  namespace ir
  {

    struct CVNess
    {
      bool  m_const;
      bool  m_volatile;

      CVNess(bool constNess=false, bool volatileNess=false);
      static CVNess NonConstNonVolatile;
    };
    
    
    // Abstract base class for all types
    class Type
    {
      public:     
      
        DEFINE_ACCEPT_METHOD(Type)
        
        Type(CVNess cvness=CVNess::NonConstNonVolatile);
            
        virtual
        ~Type();
                
        bool
        isConst() const;
        
        void
        setConst(bool isConst=true);
        
        bool
        isVolatile() const;
        
        void
        setVolatile(bool isVolatile=true);
        
        virtual
        std::string
        getName() const = 0;
        
      private:
        CVNess  m_cvness;
    };

  }

}

#endif
