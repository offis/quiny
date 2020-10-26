// 2006-03-22, Thorsten Schubert, OFFIS

#include "quiny/ir/Process.hpp"
#include "quiny/ir/CompoundStatement.hpp"

namespace quiny
{

  namespace ir
  {
    Process::
    Process(const std::string &name,
            EnumValue kind,
            utils::owner_ptr<CompoundStatement>  body)
    : m_name(name)
    , m_kind(kind)
    , m_body(body)
    {
      
    }

                
    Process::~Process()
    {
      /* TODO */
    }

    std::string
    Process::
    getName() const
    {
      return m_name; 
    }
    
    void
    Process::
    addSensitivity(utils::owner_ptr<Sensitivity> sensitivity)
    {
      m_sensitivityList.push_back(sensitivity); 
    }

    utils::observer_iter<Process::Sensitivity>
    Process::
    getSensitivities() const
    {
      return m_sensitivityList.begin();
    }

    utils::observer_ptr<CompoundStatement>
    Process::
    getBody() const
    {
      return m_body;
    }
    
        
  }

}

