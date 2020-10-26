// 2006-03-22, Thorsten Schubert, OFFIS

#ifndef QUINY_IR_SIGNAL_INCLUDED
#define QUINY_IR_SIGNAL_INCLUDED

#include "quiny/ir/PortChannelBase.hpp"
#include "quiny/utils/utils.hpp"

namespace quiny
{

  namespace ir
  {
    class Type;
    
    
    class Signal : public PortChannelBase
    {
      public:
      
        DEFINE_ACCEPT_METHOD(Signal)


        virtual
        ~Signal();
        
        utils::observer_ptr<Type>
        getValueType() const;
        
        void
        setValueType(utils::owner_ptr<Type> valueType);
        
      protected:
        utils::owner_ptr<Type>    m_valueType;
    };

  }

}

#endif
