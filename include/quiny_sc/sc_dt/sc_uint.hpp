// 2006-03-27, Thorsten Schubert, OFFIS

#ifndef QUINY_SC_SC_DT_SC_UINT_INCLUDED
#define QUINY_SC_SC_DT_SC_UINT_INCLUDED

#include "quiny_sc/sc_dt/sc_uint_base.hpp"

#include "quiny/collector/collector.hpp"
#include "quiny/collector/TypeHelper.hpp"

#include "quiny_sc/cpp_dt/ArithmeticOperators.hpp"
#include "quiny_sc/cpp_dt/RelationalOperators.hpp"

#include "quiny_sc/cpp_dt/Int.hpp"

namespace quiny_sc
{
  namespace sc_dt
  {

    template<int WIDTH>
    class sc_uint : public sc_uint_base,
                    //public ::quiny::collector::HasId,
                    public ::quiny::collector::TypeHelper<sc_uint<WIDTH> >,
                    public cpp_dt::ArithmeticOperators<sc_uint<WIDTH> >, 
                    public cpp_dt::RelationalOperators<sc_uint<WIDTH> >
    {
      public:

        sc_uint();
        sc_uint(const sc_uint<WIDTH> &);
        sc_uint(int);
        
        cpp_dt::Int 
        toInt() {return cpp_dt::Int();}
        operator cpp_dt::Int () {return toInt();}
    };
    
    // ===============================================================================================
    // IMPLEMENTATION
    // ===============================================================================================     
  
    template<int WIDTH>
    sc_uint<WIDTH>::
    sc_uint()
    {
    }

    template<int WIDTH>
    sc_uint<WIDTH>::
    sc_uint(const sc_uint<WIDTH> &val)
    {
//      ::quiny::collector::
//        hasType(m_id, *this);
//        
//      ::quiny::collector::
//        initialisation(this->id(), val.id());                          
    }

    template<int WIDTH>
    sc_uint<WIDTH>::
    sc_uint(int val)
    {
      ::quiny::collector::hasType(this->id(), *this);
      
      cpp_dt::Int i(val);
      ::quiny::collector::isInitialised(this->id(), i.id());
      
//      ::quiny::collector::
//        hasType(m_id, *this);
//        
//      cpp_dt::Int *tmp = new cpp_dt::Int(val, true);
//      
//      ::quiny::collector::
//        initialisation(this->id(), tmp->id());                          
    }
        
  }
}

#endif
