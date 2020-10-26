// 2006-09-09, Thorsten Schubert, OFFIS

#ifndef QUINY_COLLECTOR_SOURCE_POS_INCLUDED
#define QUINY_COLLECTOR_SOURCE_POS_INCLUDED

#include <string>
#include <iosfwd>

namespace quiny
{
  namespace collector
  {
    struct SourcePos
    {
      SourcePos(int line=-1, const std::string &fileName="");
          
      int         m_line;
      std::string m_fileName;
      
      void
      print(std::ostream &os) const;
      
    };

    std::ostream&    
    operator << (std::ostream &os, const SourcePos pos);
  }    
}

#endif
