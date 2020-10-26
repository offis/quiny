// 2006-03-27, Thorsten Schubert, OFFIS

#ifndef QUINY_SC_SC_CORE_SC_OBJECT_INCLUDED
#define QUINY_SC_SC_CORE_SC_OBJECT_INCLUDED

#include <string>

#include "quiny/collector/collector.hpp"

namespace quiny_sc
{

  namespace sc_core
  {

    class sc_object : public virtual ::quiny::collector::HasId
    {
      public:

        virtual
        ~sc_object();
      
        const char* basename() const;
        
        // Internally used during the build-up phase, but freely available
        // when quiny_start is called
        void  *m_hook;
        
      protected:
        sc_object();
        explicit sc_object(const char *name);

        
      private:
        std::string   m_name;
    };

  }

}

#endif
