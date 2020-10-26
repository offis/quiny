// 2006-03-22, Thorsten Schubert, OFFIS

#include "quiny/ir/SystemCType.hpp"
#include <string>
#include <sstream>

#include "quiny/utils/debug.hpp"

namespace quiny
{

  namespace ir
  {
    using std::string;
    using std::ostringstream;

    SystemCType::
    SystemCType(SystemCType::EnumValue type,
                unsigned int bitWidth,
                bool isSigned)
    : m_type(type),
      m_bitWidth(bitWidth),
      m_isSigned(isSigned)
    {
    
    }                

    unsigned int
    SystemCType::
    getBitWidth() const
    {
      return m_bitWidth;
    }

    bool
    SystemCType::
    isSigned() const
    {
      return m_isSigned;
    }
    
    SystemCType::
    ~SystemCType()
    {
      /* TODO */
    }
    
    std::string
    SystemCType::
    getName() const
    {
      ostringstream os;
      os << "<" << getBitWidth() << ">";
      
      string bwStr = os.str();
       
      switch(m_type)
      {        
        case SystemCType::SC_INT:
          if (isSigned()) 
          {
            return string("sc_int")+bwStr;
          }
          return string("sc_uint")+bwStr;

        case SystemCType::SC_BIG_INT:
          if (isSigned()) 
          {
            return string("sc_bigint")+bwStr;
          }
          return string("sc_biguint")+bwStr;
        case SystemCType::SC_BV:
          return string("sc_bv")+bwStr;
        case SystemCType::SC_LV:       
          return string("sc_lv")+bwStr;
          
        default:
          EXIT_WITH_ERROR("Unhandled case in switch statement");
      }
    }
  }
}
