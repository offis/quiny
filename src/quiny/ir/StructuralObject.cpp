// 2006-03-22, Thorsten Schubert, OFFIS

#include "quiny/ir/StructuralObject.hpp"

namespace quiny
{

  namespace ir
  {

    StructuralObject::
    StructuralObject( const std::string &name, 
                      utils::observer_ptr<StructuralObject> parent)
    : m_name(name)
    , m_parent(parent)
    {
    
    }

    StructuralObject::~StructuralObject()
    {
      /* TODO */
    }


    std::string
    StructuralObject::
    name() const
    {
      if (m_parent)
      {
        return m_parent->name() + "/" + m_name;
      }
      return m_name;
    }
    
    void
    StructuralObject::
    rename(const std::string &newName)
    {
      m_name = newName;
    }

    std::string
    StructuralObject::
    basename() const
    {
      return m_name;
    }

    utils::observer_ptr<StructuralObject>
    StructuralObject::
    getParent() const
    {
      return m_parent;
    }

    void
    StructuralObject::
    setParent(utils::observer_ptr<StructuralObject> newParent)
    {
      m_parent = newParent;
    }

  }

}

