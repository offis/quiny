// 2006-03-22, Thorsten Schubert, OFFIS

#ifndef QUINY_IR_PROCESS_INCLUDED
#define QUINY_IR_PROCESS_INCLUDED

#include <string>
#include "quiny/utils/utils.hpp"

namespace quiny
{

  namespace ir
  {
    class CompoundStatement;
    class PortChannelBase;
    
    class Process
    {
      public:
      
        enum EnumValue
        {
          ScMethod,
          ScCThread,
          ScThread
        };
      
      
        Process(const std::string &name,
                Process::EnumValue kind,
                utils::owner_ptr<CompoundStatement>  body);
      
        struct Sensitivity
        {
          utils::observer_ptr<PortChannelBase>  m_portOrChannel;
          
          enum Edge
          {
            PosEdge,
            NegEdge,
            AnyEdge
          } m_edge;
        };

        virtual
        ~Process();
        
        std::string
        getName() const;

        void
        addSensitivity(utils::owner_ptr<Sensitivity> sensitivity);

        utils::observer_iter<Sensitivity>
        getSensitivities() const;
        
        utils::observer_ptr<CompoundStatement>
        getBody() const;
                
      protected:
        std::string                           m_name;
        EnumValue                             m_kind;
        utils::owner_ptr<CompoundStatement>   m_body;
        utils::owner_ptr_list<Sensitivity>    m_sensitivityList;
    };

  }

}

#endif
