// 2006-09-09, Thorsten Schubert, OFFIS

#include "quiny/collector/SourcePos.hpp"
#include <iostream>

namespace quiny
{
  namespace collector
  {
    SourcePos::
    SourcePos(int line, const std::string &fileName)
    : m_line(line)
    , m_fileName(fileName)
    { 
      
    }
      
    void
    SourcePos::
    print(std::ostream &os) const
    {
      os << "[" << m_fileName << ":" << m_line << "]";      
    }
      
    std::ostream&
    operator << (std::ostream &os, const SourcePos pos)
    {
      pos.print(os);
      return os; 
    }

  }
}
