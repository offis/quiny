// 2006-03-22, Thorsten Schubert, OFFIS

#ifndef QUINY_IR_STRUCTURALOBJECT_INCLUDED
#define QUINY_IR_STRUCTURALOBJECT_INCLUDED

#include <string>
#include "quiny/utils/utils.hpp"

namespace quiny
{

  namespace ir
  {

    // StructuralObjects represent objects of the design hierarchy, e.g.
    // (potentially) named instances of modules, ports and signals        
    class StructuralObject
    {
      public:
      
        // TODO: add a reference to the Type of this instance
      
        DEFINE_ACCEPT_METHOD(StructuralObject)
        
        StructuralObject( const std::string &name="", 
                          utils::observer_ptr<StructuralObject> parent=0);

        virtual
        ~StructuralObject();
        
        virtual
        std::string
        name() const;
        
        virtual
        void
        rename(const std::string &newName);
        
        virtual
        std::string
        basename() const;
        
        virtual
        utils::observer_ptr<StructuralObject>
        getParent() const;
        
        virtual
        void
        setParent(utils::observer_ptr<StructuralObject> newParent);
        
      protected:
      
        std::string   m_name;
        
        utils::observer_ptr<StructuralObject>   m_parent;
    };

  }

}

#endif
