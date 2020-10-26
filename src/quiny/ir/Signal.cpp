// 2006-03-22, Thorsten Schubert, OFFIS

#include "quiny/ir/Signal.hpp"
#include "quiny/ir/Type.hpp"

namespace quiny
{

  namespace ir
  {

    Signal::~Signal()
    {
      /* TODO */
    }


    utils::observer_ptr<Type>
    Signal::
    getValueType() const
    {
      return m_valueType;
    }

    void
    Signal::
    setValueType(utils::owner_ptr<Type> valueType)
    {
      m_valueType = valueType;
    }

  }

}

