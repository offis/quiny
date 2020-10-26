// 2006-03-27, Thorsten Schubert, OFFIS

#ifndef QUINY_SC_SC_DT_SC_VALUE_BASE_D_INCLUDED
#define QUINY_SC_SC_DT_SC_VALUE_BASE_D_INCLUDED


namespace quiny_sc
{

  namespace sc_dt
  {

    class sc_value_base_d 
    //: public ::quiny::collector::TypeHelperBase
    {
      public:
        sc_value_base_d();
        
        virtual
        ~sc_value_base_d();

//         virtual
//         bool
//         isSystemCType() const;
// 
//         quiny::collector::IDType
//         id() const;

      protected:
//        quiny::collector::IDType  m_id;
      
    };

  }

}

#endif
