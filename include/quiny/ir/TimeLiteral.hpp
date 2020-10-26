// Thorsten Schubert, OFFIS

#ifndef QUINY_IR_TIME_LITERAL_INCLUDED
#define QUINY_IR_TIME_LITERAL_INCLUDED

#include "quiny/utils/utils.hpp"

namespace quiny
{

  namespace ir
  {

    // TODO: Derive TimeLiteral from Expression?
    
    class TimeLiteral
    {
      public:
        DEFINE_ACCEPT_METHOD(TimeLiteral)
      
        enum TimeUnit
        {
          FS = 0, 
          PS, 
          NS, 
          US, 
          MS, 
          SEC
        };
        
        TimeLiteral(double value, TimeUnit unit);
        
        virtual
        ~TimeLiteral();
        
        double
        getValue() const;
        
        void
        setValue(double value);
        
        TimeUnit
        getUnit() const;
        
        void
        setUnit(TimeUnit unit);

      protected:
        double    m_value;
        TimeUnit  m_unit;
        
    };
  }
}

#endif
