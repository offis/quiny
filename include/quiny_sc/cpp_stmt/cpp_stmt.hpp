// 2006-09-09, Thorsten Schubert, OFFIS

#ifndef QUINY_SC_CPP_STMT_INCLUDED
#define QUINY_SC_CPP_STMT_INCLUDED

#include <string>

#include "quiny_sc/cpp_dt/Bool.hpp"
#include "quiny/collector/collector.hpp"

namespace quiny_sc
{

  namespace cpp_stmt
  {
    inline void If(cpp_dt::Bool b, const ::quiny::collector::SourcePos &sourcePos) 
    { ::quiny::collector::ifBegin(b.id(), sourcePos); }
    inline void ThenEnd()  { ::quiny::collector::thenEnd(); }
    inline void ElseBegin() { ::quiny::collector::elseBegin();}
    inline void ElseEnd()   { ::quiny::collector::elseEnd();}
    inline void While(cpp_dt::Bool b) {::quiny::collector::whileBegin(b.id()); }
    inline void WhileEnd()   { ::quiny::collector::whileEnd();}
    
    class BlockHelper
    {
      public:
      
        // Public helper flag
        bool  m_runOnce;
      
        enum EnumValue
        {
          BLOCK_IF,
          BLOCK_ELSE,
          BLOCK_WHILE 
        };
        
        BlockHelper(EnumValue kind, cpp_dt::Bool cond=cpp_dt::Bool(), 
                    ::quiny::collector::SourcePos sourcePos=::quiny::collector::SourcePos())
        : m_kind(kind)
        , m_runOnce(false)
        , m_sourcePos(sourcePos)
        {
          switch(m_kind)
          {
            case BLOCK_IF: 
              If(cond, m_sourcePos);
              break;
            case BLOCK_ELSE:
              ElseBegin();
              break;
            case BLOCK_WHILE:
              While(cond);
              break; 
          }
        }
        
        ~BlockHelper()
        {
          switch(m_kind)
          {
            case BLOCK_IF: 
              ThenEnd();
              break;
            case BLOCK_ELSE:
              ElseEnd();
              break;
            case BLOCK_WHILE:
              WhileEnd();
              break; 
          }
        }
                        
      protected:
        EnumValue   m_kind;
        ::quiny::collector::SourcePos m_sourcePos;
    };
  }
}

#endif
