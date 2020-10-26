// 2006-09-09, Thorsten Schubert, OFFIS

#ifndef QUINY_SC_CPP_DT_RELATIONAL_OPERATORS_INCLUDED
#define QUINY_SC_CPP_DT_RELATIONAL_OPERATORS_INCLUDED

#include "quiny_sc/cpp_dt/Bool.hpp"
#include "quiny/collector/collector.hpp"


namespace quiny_sc
{
  namespace cpp_dt
  {
    template<typename T>
    struct RelationalOperators
    {
      Bool
      operator < (const T &b) const 
      {
        Bool result;
        
        ::quiny::collector::TypeHelper<T> tmp;
        
        quiny::collector::
          hasType(result.id(), tmp  );
        
        quiny::collector::
          isBinaryOperationResult( result.id(),
                                   static_cast<const T*>(this)->id(),
                                   ::quiny::ir::BinaryOperation::Less,
                                   b.id() );
        return result;
      }

    };
   
  }
}

#endif
