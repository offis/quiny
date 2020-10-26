#include "Visitor.hpp"

#include "quiny/ir/ir.hpp"

#include <iostream>
#include <string>
#include <cassert>

namespace vhdlgen
{
  using namespace std;
  using namespace quiny::ir;
  
  using utils::owner_ptr;
  using utils::owner_ptr_list;
  using utils::observer_ptr;
  using utils::observer_iter;
  
  
  ostream *g_genOut = &cout;
  
  ostream &genOut()
  {
    return *g_genOut; 
  }

    
  // Quick-Hack
  Visitor *g_vhdlGenerator=0;
  
  // Helper class for the generation of nicely indented code
  class Indentation
  {
    public:
      
      Indentation() : m_level(0) {}
      
      int m_level;
      
      void operator ++ () { ++m_level; }
      void operator -- () { if (m_level>0) --m_level; }
  
      std::string getPrefix() 
      { 
        std::string tmp;
        
        for (int i=0; i<m_level; ++i) tmp += "  ";
        return tmp;
      }
  
  } indentation;  
  
  void
  Visitor::
  setOutputStream(std::ostream *output)
  {
    g_genOut = output; 
  }
  
  ostream& lineBegin() 
  {
    genOut() << indentation.getPrefix();
    return genOut();
  }
  
  void genLibraryUsage()
  {
    genOut()
      <<   "LIBRARY ieee;"
         "\nUSE ieee.std_logic_1164.all;"
         "\nUSE ieee.std_logic_unsigned.all;"
         "\nUSE ieee.std_logic_arith.all;"
         "\n"
      << endl;
  }

  string
  genDirection(PortToSignal::Direction direction)
  {
     switch(direction)
     {
        case PortToSignal::IN   : return "IN";
        case PortToSignal::OUT  : return "OUT";
        case PortToSignal::INOUT: return "INOUT";
        default : 
          EXIT_WITH_ERROR("Illegal direction.")       
     }
     
     // Dead code
     return "";
  }  
  
  void genPortList(observer_iter<Port> it)
  {
    if (!it)
    {
       return; 
    }
    
    lineBegin() << "PORT (\n";
    ++indentation;
    for (; it; ++it)
    while(it)
    {
      observer_ptr<PortToSignal> pts((*it).dyn_cast<PortToSignal>());
      
      lineBegin() << it->basename() << " : " 
        << genDirection(pts->getDirection())
        << " ";
      
      pts->getValueType()->accept(*g_vhdlGenerator);
        
      ++it;
      if (it)
      {
        genOut() << ";";
      }
      genOut() << endl;
    }
    
    --indentation;
    lineBegin() << ");" << endl;
    
  }
  
  void genEntity(const string &name, observer_iter<Port> it)
  {
    genOut() << "ENTITY " << name << " IS" << endl; 
    ++indentation;
    genPortList(it);
    --indentation;    
    genOut() << "END " << name << ";" << endl;
  }
  
  void genComponent(const string &name, observer_iter<Port> it)
  {
    lineBegin() << "COMPONENT " << name << endl; 
    ++indentation;
    genPortList(it);
    --indentation;    
    lineBegin() << "END COMPONENT;" << endl;
  }

  string
  genEntityName(const Module& node)
  {
    return node.getModuleType()->getName() + "_" + node.basename() + "_entity";    
  }
  
  void genBinding(const Module::Binding &binding)
  {
    lineBegin() << binding.m_port->basename() << " => " 
                << binding.m_channelOrPort->basename();
  }
  
  void
  genInstantiation(const Module &node)
  {
    const string instanceName = "inst_" + genEntityName(node);

    lineBegin() << instanceName << " : "  << genEntityName(node) << "\n";
    ++indentation;
    lineBegin() << "PORT MAP(";
    
    ++indentation;
    
    observer_iter<Module::Binding> itBind = node.getBindings();
    assert(itBind);
    while(itBind)
    {
      genOut() << endl;
      genBinding(**itBind);
     
      ++itBind;
      if(itBind)
      {        
        genOut() << ",";
      } 
    }            
    genOut() << endl;
    --indentation;
    lineBegin() << ");" << endl;
    --indentation;
  }

  void
  genSensitivityList(observer_iter<Process::Sensitivity> itSens)
  {
    if (!itSens)
    {
      genOut() << endl;
      return ; 
    }  
    
    genOut() << "(";
    while(itSens)
    {
      genOut() << itSens->m_portOrChannel->basename();
      ++itSens; 
      if (itSens)
      {
        genOut() << ", ";
      }
    }
    genOut() << ")" << endl;
  }
      
  void
  genProcessBody(observer_ptr<CompoundStatement> body, observer_iter<Process::Sensitivity> itSens,
                 const string &name)
  {
    bool genEventTest=false;
    
    lineBegin() << "BEGIN\n";
    ++indentation;
    
    if (itSens && itSens->m_edge != Process::Sensitivity::AnyEdge)
    {
      genEventTest = true; 
    }
    
    if (genEventTest)
    {
      lineBegin() << "IF " << itSens->m_portOrChannel->basename() << "'EVENT AND "
                  << itSens->m_portOrChannel->basename() << " = "
                  << (itSens->m_edge == Process::Sensitivity::PosEdge ? "TRUE"
                                                                      : "FALSE")
                  << " THEN\n";
      ++indentation;
    }
    
    body->accept(*g_vhdlGenerator);
    
    if (genEventTest)
    {
      --indentation;
      lineBegin() << "END IF;\n" ;
    }
    
    --indentation;
    lineBegin() << "END PROCESS " << name << ";" << endl;
  }
        
        
        

  
  void
  Visitor::
  VISIT_METHOD_DECLARATOR(Module)
  {
    g_vhdlGenerator = this;
    
    genLibraryUsage();

    const string entityName=genEntityName(node);    
    
    genEntity(entityName, node.getModuleType()->getPorts());
    
    genOut() << "\nARCHITECTURE behaviour OF " << entityName << " IS" << endl;
    ++indentation;    
    // Components
    for (observer_iter<Module> itSub=node.getSubModules(); itSub; ++itSub)
    {
      genComponent(genEntityName(**itSub), itSub->getModuleType()->getPorts());
    }           
    
    // Signals
    for (observer_iter<Signal> itSig=node.getSignals(); itSig; ++itSig)
    {
      itSig->accept(*this);
    }    
    --indentation;
    lineBegin() << "BEGIN\n" << endl;
    ++indentation;
    for (observer_iter<Module> itSub=node.getSubModules(); itSub; ++itSub)
    {
      genInstantiation(**itSub);
    }               
    
    // Processes
    for (observer_iter<Process> itPro=node.getProcesses(); itPro; ++itPro)
    {
      lineBegin() << itPro->getName() << " : PROCESS";
      genSensitivityList(itPro->getSensitivities());
      genProcessBody(itPro->getBody(), itPro->getSensitivities(), itPro->getName());
      genOut() << endl;
    }
    
    
    --indentation;
    genOut() << "END behaviour;"
              "\n"
           << endl;
           
    for (observer_iter<Module> itSub=node.getSubModules(); itSub; ++itSub)
    {
      itSub->accept(*this);
    }           
  }
  
  void
  Visitor::
  VISIT_METHOD_DECLARATOR(SimpleType)
  {
      // Quite incomplete
      // TODO: handle signedness
      
      string vhdlType;

      switch (node.whichSimpleType())
      {
        case SimpleType::Bool   : vhdlType = "BOOLEAN"; break;
        case SimpleType::Char   : vhdlType = "CHARACTER"; break;
        case SimpleType::Int    : vhdlType = "INTEGER"; break;
        case SimpleType::Double : vhdlType = "REAL"; break;
        default:
          NOT_YET_FULLY_IMPLMENETED
      }
     
      genOut() << vhdlType;
  }
  
  void
  Visitor::
  VISIT_METHOD_DECLARATOR(SystemCType)
  {
    genOut() << "STD_LOGIC_VECTOR(" << node.getBitWidth()-1 << " DOWNTO 0)";
  }  
  
  void
  Visitor::
  VISIT_METHOD_DECLARATOR(Signal)
  {
    lineBegin() << "SIGNAL " << node.basename() << " : ";
    node.getValueType()->accept(*g_vhdlGenerator);
    genOut() << ";" << endl;
  }  
  
  void
  Visitor::
  VISIT_METHOD_DECLARATOR(IfStatement)
  {
    lineBegin() << "IF ";
    node.getCondition()->accept(*this);
    genOut() << " THEN\n";
    ++indentation;
    assert(node.getThenStatement());
    node.getThenStatement()->accept(*this);
    --indentation;
    
    observer_ptr<Statement> elseStmt = node.getElseStatement();
    if(elseStmt)
    {
      lineBegin() << "ELSE\n";
      ++indentation;
      elseStmt->accept(*this);
      --indentation; 
    }
    
    lineBegin() << "END IF;" << endl;
  } 
  
  void
  Visitor::
  VISIT_METHOD_DECLARATOR(CompoundStatement)
  {
    for(observer_iter<Statement> itStmt=node.getBody(); itStmt; ++itStmt)
    {
       itStmt->accept(*g_vhdlGenerator);
    }
  }  
  
  void
  Visitor::
  VISIT_METHOD_DECLARATOR(BinaryOperation)
  {
    genOut() << "(";
    node.getLhs()->accept(*this);
    
    switch(node.whichOperator())
    {
      case BinaryOperation::Plus: 
        genOut() << "+";
        break;
      case BinaryOperation::Minus:
        genOut() << "-";
        break;
      case BinaryOperation::Mult:
        genOut() << "*";
        break;
//      case BinaryOperation::Div: break;
//      case BinaryOperation::Mod: break;
      case BinaryOperation::Less:
        genOut() << "<";
        break;
      case BinaryOperation::LessEqual:
        genOut() << "<=";
        break;
      case BinaryOperation::Greater:
        genOut() << ">";
        break;
      case BinaryOperation::GraterEqual:
        genOut() << ">=";
        break;
      case BinaryOperation::Equal:
        genOut() << "=";
        break;
      case BinaryOperation::NotEqual:
        genOut() << "/=";
        break;
        
      default:
        NOT_YET_FULLY_IMPLMENETED
    }
    
    node.getRhs()->accept(*this);
    genOut() << ")";
  }   
  
  void
  Visitor::
  VISIT_METHOD_DECLARATOR(BoolLiteral)
  {
    genOut() << (node.getValue() ? "TRUE" : "FALSE");
  }
    
  void
  Visitor::
  VISIT_METHOD_DECLARATOR(PortChannelRead)
  {
    genOut() << node.getSource()->basename();
  }

  void
  Visitor::
  VISIT_METHOD_DECLARATOR(IntLiteral)
  {
    genOut() << node.getValue();
  }
    
  void
  Visitor::
  VISIT_METHOD_DECLARATOR(CastExpression)
  {
    // Limitation: only integer literals can be cast to 
    // sc_uint (which result in bitvectors)
    assert(node.getExpression().dyn_cast<IntLiteral>());
    
    observer_ptr<SystemCType> destType(
      node.getDestType().dyn_cast<SystemCType>());
      
    assert(destType);
    
    genOut() << "CONV_STD_LOGIC_VECTOR(";
    node.getExpression()->accept(*this);
    genOut() << ", " << destType->getBitWidth() << ")";
  }

  void
  Visitor::
  VISIT_METHOD_DECLARATOR(PortChannelWriteStatement)
  {
    lineBegin() << node.getSource()->basename() << " <= ";
    node.getExpression()->accept(*this);
    genOut() << ";\n";
  }

  void
  Visitor::
  VISIT_METHOD_DECLARATOR(WhileStatement)
  {
    lineBegin() << "WHILE ";
    node.getCondition()->accept(*this);
    genOut() << " LOOP\n";
    ++indentation;
    node.getBody()->accept(*this);
    --indentation;
    lineBegin() << "END LOOP;" << endl;
  }      
  
  void
  Visitor::
  VISIT_METHOD_DECLARATOR(TimeLiteral)
  {
    genOut() << node.getValue() << " ";
    switch (node.getUnit())
    {
      case TimeLiteral::FS:  
        genOut() << "fs";
        break;
      case TimeLiteral::PS:  
        genOut() << "ps";
        break;
      case TimeLiteral::NS:  
        genOut() << "ns";
        break;
      case TimeLiteral::US:  
        genOut() << "us";
        break;
      case TimeLiteral::MS:  
        genOut() << "ms";
        break;
      case TimeLiteral::SEC: 
        genOut() << "sec";
        break;        
      default:
        THIS_IS_DEAD_CODE
    }
  }

  void
  Visitor::
  VISIT_METHOD_DECLARATOR(WaitStatement)
  {
    lineBegin() << "WAIT FOR ";
    node.getTimeLiteral()->accept(*this);
    genOut() << ";" << endl;
  }  

  void
  Visitor::
  VISIT_METHOD_DECLARATOR(SimulationCommands)
  {
    for(observer_iter<SimulationCommand> itCmd=node.getCommands(); itCmd; ++itCmd)
    {
      itCmd->accept(*this); 
    }
  }  
  void
  Visitor::
  VISIT_METHOD_DECLARATOR(StartCommand)
  {
    genOut() << "run ";
    node.getDuration()->accept(*this);        
    genOut() << endl;
  }  
  
  void
  Visitor::
  VISIT_METHOD_DECLARATOR(TraceCommand)
  {
    genOut() << "add wave " << node.getTarget()->basename() << endl;
  }  
      
}
