// 2006-03-28, Thorsten Schubert, OFFIS

#include "quiny/collector/TypeHelperBase.hpp"

#include "quiny/ir/SimpleType.hpp"
#include "quiny/ir/SystemCType.hpp"
#include "quiny/utils/debug.hpp"

namespace quiny
{

  namespace collector
  {
  
    TypeHelperBase::
    TypeHelperBase() 
    : m_id(getNewId())
    {
    
    }

    TypeHelperBase::
    ~TypeHelperBase()
    {
      /* TODO */
    }


    ir::Type*
    TypeHelperBase::
    getType() const
    {
      if (isSimpleType())
      {
        return new ir::SimpleType(whichSimpleType(), isSigned(), getCVNess());
      }
      else if (isSystemCType())
      {
        return new ir::SystemCType(whichSystemCType(), getBitWidth(), isSigned());
      }
      
      NOT_YET_FULLY_IMPLMENETED
    }

    IDType
    TypeHelperBase::
    id() const
    {
      return m_id;
    }

    std::string
    TypeHelperBase::
    getName() const
    {
      return "UNKOWN";
    }

    bool
    TypeHelperBase::
    isSimpleType() const
    {
      return false;
    }
    
    ir::SimpleType::EnumValue
    TypeHelperBase::
    whichSimpleType() const
    {
      return ir::SimpleType::Void;
    }

    ir::CVNess
    TypeHelperBase::
    getCVNess() const
    {
      return ir::CVNess::NonConstNonVolatile;
    }

    bool
    TypeHelperBase::
    isSigned() const
    {
      return false;
    }
    
    bool
    TypeHelperBase::
    isSystemCType() const
    {
      return false;
    }

    ir::SystemCType::EnumValue
    TypeHelperBase::
    whichSystemCType() const
    {
      PRINT_ERROR("illegal call of whichSystemCType()");
      return ir::SystemCType::SC_INT;
    }

    unsigned int
    TypeHelperBase::
    getBitWidth() const
    {
      PRINT_ERROR("illegal call of getBitWidth()");
      return 0;
    }


  }


}

