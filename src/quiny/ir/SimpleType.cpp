// 2006-03-22, Thorsten Schubert, OFFIS

#include "quiny/ir/SimpleType.hpp"

namespace quiny
{

  namespace ir
  {

    using namespace std;

    bool
    SimpleType::
    isSignable(SimpleType::EnumValue typ)
    {
      switch (typ)
      {
        case SChar : return true;
        case Short : return true;
        case Int : return true;
        case Long : return true;
        default : return false;
      }
      
      return false;
    }
    
    
    SimpleType::
    SimpleType(SimpleType::EnumValue t, 
               bool isSigned,
               CVNess cvness) 
    : Type(cvness)
    , m_type(t)
    , m_signed(isSigned)
    {
    
    }

    SimpleType::~SimpleType()
    {
      /* TODO */
    }
    
    std::string
    SimpleType::
    getName() const
    {
      string cvString;

      if (isConst())
      {
        cvString = "const";
        
        if (isVolatile())
        {
          cvString += " volatile";
        }
      }
      else if (isVolatile())
      {
        cvString = "volatile";
      }

      
      string signedNess;
      if (ir::SimpleType::isSignable(m_type))
      {
        if (!isSigned())
        {
          signedNess = "unsigned";
        }
        // prefix the "signable" char with signed if necessary
        else if (m_type == SimpleType::SChar)        
        {
          signedNess = "signed";
        }        
      }

      string baseType;

      switch (m_type)
      {
        case SimpleType::Void : baseType = "void"; break;
        case SimpleType::Bool : baseType = "bool"; break;
        case SimpleType::Char : baseType = "char"; break;
        case SimpleType::SChar : baseType = "char"; break;
        case SimpleType::Short : baseType = "short"; break;
        case SimpleType::Int : baseType = "int"; break;
        case SimpleType::Long : baseType = "long"; break;
        case SimpleType::LongLong : baseType = "long long"; break;
        case SimpleType::Float : baseType = "float"; break;
        case SimpleType::Double : baseType = "double"; break;
        case SimpleType::LongDouble : baseType = "long double"; break;
        case SimpleType::WChar : baseType = "wchar_t"; break;
      }
      
      if (!cvString.empty())
      {
        cvString += " ";
      }
      
      if (!signedNess.empty())
      {
        signedNess += " ";
      }
      
      return cvString + signedNess + baseType;
    }

    bool
    SimpleType::
    isSigned() const
    {
      return m_signed;
    }

    SimpleType::EnumValue
    SimpleType::
    whichSimpleType() const
    {
      return m_type; 
    }
    
  }
}

