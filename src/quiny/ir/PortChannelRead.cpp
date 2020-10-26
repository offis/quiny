#include "quiny/ir/PortChannelRead.hpp"

namespace quiny
{

  namespace ir
  {
    PortChannelRead::
    PortChannelRead(utils::observer_ptr<PortChannelRead> source)
    : m_source(source)
    {
      
    }
    
    PortChannelRead::
    ~PortChannelRead()
    {
    }
    
  
    utils::observer_ptr<PortChannelBase>
    PortChannelRead::
    getSource() const
    {
      return m_source; 
    }
    
    void
    PortChannelRead::
    setSource(utils::observer_ptr<PortChannelBase> source)
    {
      m_source = source;
    }
    
  }
}
