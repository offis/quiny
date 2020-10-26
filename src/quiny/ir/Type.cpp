// 2006-03-22, Thorsten Schubert, OFFIS

#include "quiny/ir/Type.hpp"

namespace quiny
{

  namespace ir
  {

    CVNess::
    CVNess(bool constNess, bool volatileNess)
    : m_const(constNess)
    , m_volatile(volatileNess)
    {
    }
    
    CVNess 
    CVNess::NonConstNonVolatile;
    
    
    
    Type::
    Type(CVNess cvness)
    : m_cvness(cvness)
    {
    
    }

    Type::~Type()
    {
      /* TODO */
    }

    bool
    Type::
    isConst() const
    {
      return m_cvness.m_const;
    }

    void
    Type::
    setConst(bool isConst)
    {
      m_cvness.m_const = isConst;
    }

    bool
    Type::
    isVolatile() const
    {
      return m_cvness.m_volatile;
    }

    void
    Type::
    setVolatile(bool isVolatile)
    {
      m_cvness.m_volatile = isVolatile;
    }

  }

}

