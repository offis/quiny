// 2006-09-09, Thorsten Schubert, OFFIS

#ifndef QUINY_SC_CPP_DT_ARITHMETIC_OPERATORS_INCLUDED
#define QUINY_SC_CPP_DT_ARITHMETIC_OPERATORS_INCLUDED

#include "quiny/collector/collector.hpp"

namespace quiny_sc
{
  namespace cpp_dt
  {
   
    template<typename T>
    struct ArithmeticOperators
    {
      
      #define DEFINE_ARITHMETIC_OPERATOR( op, enumVal)\
      T \
      operator op (const T &b) const \
      { \
        T result;\
        \
        quiny::collector:: \
          hasType(result.id(), ::quiny::collector::TypeHelper<T> ()); \
        \
        quiny::collector:: \
          isBinaryOperationResult( result.id(), \
                                   static_cast<const T*>(this)->id(), \
                                   ::quiny::ir::BinaryOperation::enumVal, \
                                   b.id() ); \
        return result; \
      }
        
      DEFINE_ARITHMETIC_OPERATOR(+, Plus)
      DEFINE_ARITHMETIC_OPERATOR(-, Minus)
      DEFINE_ARITHMETIC_OPERATOR(*, Mult)
      DEFINE_ARITHMETIC_OPERATOR(/, Div)
      DEFINE_ARITHMETIC_OPERATOR(%, Mod)

      
      #undef DEFINE_ARITHMETIC_OPERATOR
    };
  }
}

#endif
