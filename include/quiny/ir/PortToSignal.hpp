// 2006-03-22, Thorsten Schubert, OFFIS

#ifndef QUINY_IR_PORTTOSIGNAL_INCLUDED
#define QUINY_IR_PORTTOSIGNAL_INCLUDED

#include "quiny/ir/Port.hpp"

namespace quiny
{

  namespace ir
  {
    class Type;

    // Represents sc_port<sc_signal_xyz_if<T> >, i.e. sc_in<T>, sc_out<T>, sc_inout<T>
    class PortToSignal : public Port
    {
      public:
      
        enum Direction
        {
          IN,
          OUT,
          INOUT
        };

        PortToSignal(Direction direction);

        virtual
        ~PortToSignal();
        
        Direction
        getDirection() const;
        
        void
        setDirection(Direction direction);
        
        utils::observer_ptr<Type>
        getValueType() const;
        
        void
        setValueType(utils::owner_ptr<Type> valueType);
                        
      protected:
        Direction   m_direction;
        utils::owner_ptr<Type>    m_valueType;
        
    };
  }
}

#endif
