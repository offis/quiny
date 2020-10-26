// 2006-09-09, Thorsten Schubert, OFFIS

#ifndef QUINY_SC_CPP_DT_INT_INCLUDED
#define QUINY_SC_CPP_DT_INT_INCLUDED


#include "quiny/collector/collector.hpp"
#include "quiny/collector/TypeHelper.hpp"

#include "quiny_sc/cpp_dt/ArithmeticOperators.hpp"
#include "quiny_sc/cpp_dt/RelationalOperators.hpp"

namespace quiny_sc
{
  namespace cpp_dt
  {

    class Int : public ::quiny::collector::TypeHelper<int>,
                public ArithmeticOperators<Int>,
                public RelationalOperators<Int>
    {
      public:
        Int() {}
        Int(const Int&) {}
        Int(int val, bool isLiteral=true) 
        {
          ::quiny::collector::hasType(this->id(), *this);
          
          if (isLiteral)
          {
            ::quiny::collector::isIntegerLiteral(this->id(), val /*, *this */ /*quiny::collector::TypeHelper<int> ()*/ );
          }
        }
        Int(short);
        Int(char);

//         quiny::collector::IDType
//         id() const
//         { return m_id; }

      private:        
//         quiny::collector::IDType  m_id;
    };

  }
}

#endif
