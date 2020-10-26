// 2006-03-22, Thorsten Schubert, OFFIS

#include "quiny/ir/ClassType.hpp"

namespace quiny
{

  namespace ir
  {
    
    ClassType::ClassType()
    : m_name("UNKNOWN")
    {
    }

    ClassType::~ClassType()
    {
    }

    std::string
    ClassType::
    getName() const
    {
      return m_name;
    }

    void
    ClassType::
    setName(const std::string &name)
    {
      m_name = name;
    }
    
  }

}

