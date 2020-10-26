// 2006-03-22, Thorsten Schubert, OFFIS

#include "quiny/ir/PortToSignal.hpp"
#include "quiny/ir/Type.hpp"

namespace quiny
{

  namespace ir
  {

    PortToSignal::
    PortToSignal(Direction direction)
    : m_direction(direction)
    {
      
    }

    PortToSignal::~PortToSignal()
    {
      /* TODO */
    }


    PortToSignal::Direction
    PortToSignal::
    getDirection() const
    {
      return m_direction; 
    }
    
    void
    PortToSignal::
    setDirection(Direction direction)
    {
      m_direction = direction; 
    }
    
    utils::observer_ptr<Type>
    PortToSignal::
    getValueType() const
    {
      return m_valueType;
    }

    void
    PortToSignal::
    setValueType(utils::owner_ptr<Type> valueType)
    {
      m_valueType = valueType;
    }
    
  }
}
