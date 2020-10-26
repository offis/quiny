// 2006-09-09, Thorsten Schubert, OFFIS

#ifndef QUINY_SC_CPP_DT_BOOL_INCLUDED
#define QUINY_SC_CPP_DT_BOOL_INCLUDED

#include "quiny/collector/collector.hpp"
#include "quiny/collector/TypeHelper.hpp"


namespace quiny_sc
{
  namespace cpp_dt
  {
    class BoolClass : public ::quiny::collector::HasId
    {
	    public: 
	      BoolClass() {}
	      BoolClass(bool b) 
	      {
  	      ::quiny::collector::isBooleanLiteral(this->id(), b);
  	    }

//         quiny::collector::IDType
//         id() const
//         { return m_id; }

        BoolClass 
        operator == (BoolClass b) const 
        { 
          BoolClass result;          
          
          quiny::collector::
            isBinaryOperationResult( result.id(),
                                     this->id(),
                                     ::quiny::ir::BinaryOperation::Equal,
                                     b.id() );
          return result;
        }

      private:        
//        quiny::collector::IDType  m_id;
            
    };

    // TODO: Switch between bool and BoolClass depending on intrusive/non-intrusive mode
    typedef BoolClass Bool;
    
  }
}

namespace quiny
{

  namespace collector
  {

    template<>
    class TypeHelper<quiny_sc::cpp_dt::BoolClass> : public ::quiny::collector::TypeHelper<bool>
    {
    };
  }
}


#endif
