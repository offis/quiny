// 2006-03-28, Thorsten Schubert, OFFIS

#include "quiny/collector/collector.hpp"
#include "quiny/utils/utils.hpp"
#include "quiny/collector/TypeHelperBase.hpp"
#include "quiny/ir/ir.hpp"

#include <iostream>
#include <map>
#include <cassert>

#define COLLECTOR_LOG(msg) \
  if (g_state->m_logStream) \
  {\
    (*g_state->m_logStream) << "COLLECTOR: " << msg << std::endl;\
  }
//#define COLLECTOR_LOG(msg)

namespace quiny
{

  namespace collector
  {
    using utils::owner_ptr;
    using utils::owner_ptr_list;
    using utils::observer_ptr;
  
    using std::map;


    HasId::
    HasId() : m_id(getNewId()) 
    {
    }
    
    IDType
    HasId::
    id() const
    {
      return m_id;
    }
  
    namespace
    {
      struct node
      {
        node(IDType id);
      
        IDType                        m_id;
        owner_ptr<ir::Type>           m_Type;
        owner_ptr<ir::Expression>     m_exclusiveExpression;
        observer_ptr<ir::Module>      m_Module;
        observer_ptr<ir::Signal>      m_Signal;
        observer_ptr<ir::Port>        m_Port;
        owner_ptr<ir::TimeLiteral>    m_exclusiveTimeLiteral;
      };

      node::node(IDType id) : m_id(id) {}

      struct state
      {
        state();
        
        IDType                        m_id;
        std::ostream                 *m_logStream;
      
        owner_ptr<ir::Module>         m_rootModule;
        observer_ptr<ir::Module>      m_currentModule;
        observer_ptr<ir::Process>     m_currentProcess;
        observer_ptr<ir::CompoundStatement> m_activeCompoundStatement;
        observer_ptr<ir::IfStatement> m_lastThenTerminatedIf;
        owner_ptr<ir::SimulationCommands> m_simulationCommands;
      
        map<IDType, node* >           m_nodeMap;
      
        typedef map<IDType, node* >::iterator       mapIter;
        typedef map<IDType, node* >::const_iterator const_mapIter;
      
      } *g_state= new state();
      
      state::state() 
      : m_id(0) 
      , m_logStream(0)
      {
      }

      node *getNode(IDType id)
      {
        state::mapIter it = g_state->m_nodeMap.find(id);
        assert(it != g_state->m_nodeMap.end());

        node *n = it->second;

        return n;
      }
      
    }  

    // to be used by main only       
    utils::owner_ptr<ir::StructuralObject>
    getRootObject()
    {
      utils::owner_ptr<ir::StructuralObject> result(g_state->m_rootModule);
      return result; 
    }
    
    utils::owner_ptr<ir::SimulationCommands>
    getSimulationCommands()
    {
      utils::owner_ptr<ir::SimulationCommands> result(g_state->m_simulationCommands);
      return result;
    }    
    
    void 
    setLogStream(std::ostream *log)
    {
      g_state->m_logStream = log; 
    }

    
    IDType
    getNewId()
    {
      IDType newID = ++g_state->m_id;
      
      g_state->m_nodeMap[newID] = new node(newID);
      
      return newID;
    }

    void
    objectDeleted(IDType id)
    {
      COLLECTOR_LOG("Deleting object: " << id )
    }

    void
    hasType(IDType id,
            const TypeHelperBase &type)
    {
      COLLECTOR_LOG("Expression: " << id << " has type: " <<  type.getName() )

      getNode(id)->m_Type = owner_ptr<ir::Type> (type.getType());
    }

    void    
    isIntegerLiteral(IDType id,
                     unsigned long long val)
    {
      COLLECTOR_LOG("Expression " << id << " is an integer literal: " << val);

      owner_ptr<ir::Type> type(getNode(id)->m_Type);
      assert(type);
      owner_ptr<ir::SimpleType> simpleType(type.dyn_cast<ir::SimpleType>());
      assert(simpleType);
      
      owner_ptr<ir::IntLiteral> newLit(new ir::IntLiteral(val, simpleType));
      
      getNode(id)->m_exclusiveExpression = newLit;
//       
//       node *n = getNode(id);
//       COLLECTOR_LOG("Object " << id << " is an integer literal: " 
//                   << val
//                   << " of type :" << n->m_Type->getName())
    }
    
    void
    isBooleanLiteral(IDType id, bool value)
    {
       COLLECTOR_LOG("Expression " << id << " is a Boolean literal: " << value)
       
       owner_ptr<ir::BoolLiteral> newLit(new ir::BoolLiteral(value));
       getNode(id)->m_exclusiveExpression = newLit;
    }
    
    
    void
    isInitialised(IDType dest, IDType source)
    {
      COLLECTOR_LOG("Expression " << dest << " is initialised by expression " << source);    
      
      owner_ptr<ir::Type> destType = getNode(dest)->m_Type;
      owner_ptr<ir::Expression> exp = getNode(source)->m_exclusiveExpression;
      
      assert(destType);
      assert(exp);
      
      owner_ptr<ir::CastExpression> newExp(new ir::CastExpression(destType, exp));
      
      getNode(dest)->m_exclusiveExpression = newExp;
    }

    void
    isBinaryOperationResult(IDType result, 
                            IDType lhs, 
                            ::quiny::ir::BinaryOperation::EnumValue op,
                            IDType rhs)
    {
      COLLECTOR_LOG("Expression " << result << " is binOp " << op 
                  << " (" << lhs << "," << rhs << ")" );    

      owner_ptr<ir::Expression> expLhs(getNode(lhs)->m_exclusiveExpression),
                                expRhs(getNode(rhs)->m_exclusiveExpression);
                  
      // Shared expressions, i.e. variables which are referenced multiple times are not
      // supported yet.                  
      assert(expLhs);
      assert(expRhs);

      owner_ptr<ir::BinaryOperation> newBinOp(new ir::BinaryOperation(op, expLhs, expRhs));
      
      getNode(result)->m_exclusiveExpression = newBinOp;    
    }

    void 
    isSignalRead(IDType val, IDType signal)
    {
      COLLECTOR_LOG("Expression " << val << " is SignalRead from " << signal) 
      
      observer_ptr<ir::PortChannelBase> sourceSignal = getNode(signal)->m_Signal;
      
      assert(sourceSignal);
      
      owner_ptr<ir::PortChannelRead> newPcr(new ir::PortChannelRead(sourceSignal));
      getNode(val)->m_exclusiveExpression = newPcr;
      
    }

    void 
    isPortRead(IDType val, IDType port)
    {
      COLLECTOR_LOG("Expression " << val << " is PortRead from " << port) 
      
      observer_ptr<ir::PortChannelBase> sourcePort = getNode(port)->m_Port;
      
      assert(sourcePort);
      
      owner_ptr<ir::PortChannelRead> newPcr(new ir::PortChannelRead(sourcePort));
      getNode(val)->m_exclusiveExpression = newPcr;
    }
    
    void
    isTimeLiteral(IDType id, double value, ::quiny::ir::TimeLiteral::TimeUnit unit)
    {
      COLLECTOR_LOG("Expression " << id << " is time literal: " << value << ", " << unit) 
      
      owner_ptr<ir::TimeLiteral> newLit(new ir::TimeLiteral(value, unit));
      getNode(id)->m_exclusiveTimeLiteral = newLit;
    }
    
            
    void
    ifBegin(IDType cond, const SourcePos& pos)
    {
      COLLECTOR_LOG("If, cond == " << cond << " " << pos)
      
      assert(g_state->m_activeCompoundStatement);
      
      owner_ptr<ir::Expression> condExp = getNode(cond)->m_exclusiveExpression;
      assert(condExp);
      
      owner_ptr<ir::Statement> thenStmt(new ir::CompoundStatement);
      
      observer_ptr<ir::Statement> thenObs(thenStmt);
      owner_ptr<ir::Statement> newIf(new ir::IfStatement(condExp, thenStmt));
      
      newIf->setParent(g_state->m_activeCompoundStatement);
      thenObs->setParent(newIf);
      
      g_state->m_activeCompoundStatement->addStatement(newIf);
      g_state->m_activeCompoundStatement = thenObs;
      
    }
    
    void
    thenEnd()
    {
      COLLECTOR_LOG("thenEnd")
      
      observer_ptr<ir::IfStatement> ifStmt(
        g_state->m_activeCompoundStatement->getParent().dyn_cast<ir::IfStatement>());
        
      assert(ifStmt);
      
      g_state->m_lastThenTerminatedIf = ifStmt;
      
      observer_ptr<ir::CompoundStatement> ifParent(
        ifStmt->getParent().dyn_cast<ir::CompoundStatement>());
        
      assert(ifParent);
      
      g_state->m_activeCompoundStatement = ifParent;
    }
    
    void
    elseBegin()
    {
      COLLECTOR_LOG("elseBegin")
      
      assert(g_state->m_lastThenTerminatedIf);
      
      owner_ptr<ir::Statement> elseStmt(new ir::CompoundStatement);
      elseStmt->setParent(g_state->m_lastThenTerminatedIf);
      
      g_state->m_activeCompoundStatement = elseStmt;
      
      g_state->m_lastThenTerminatedIf->setElseStatement(elseStmt);
            
      
    }

    void
    elseEnd()
    {
      COLLECTOR_LOG("elseEnd")
      
      observer_ptr<ir::IfStatement> ifStmt(
        g_state->m_activeCompoundStatement->getParent().dyn_cast<ir::IfStatement>());
        
      assert(ifStmt);
      
      observer_ptr<ir::CompoundStatement> ifParent(
        ifStmt->getParent().dyn_cast<ir::CompoundStatement>());
        
      assert(ifParent);
      
      g_state->m_activeCompoundStatement = ifParent;
    }
    
    void
    enteringScMain()
    {
      COLLECTOR_LOG("Entering sc_main")
      
      assert(g_state->m_rootModule == 0);
      assert(g_state->m_currentModule == 0);
      assert(g_state->m_simulationCommands == 0);
      
      owner_ptr<ir::Module> newModule(new ir::Module("sc_main"));
      g_state->m_rootModule = newModule;
      g_state->m_currentModule = g_state->m_rootModule;
      
      owner_ptr<ir::SimulationCommands> simCmds(new ir::SimulationCommands);
      g_state->m_simulationCommands = simCmds;
    }

    void
    whileBegin(IDType cond)
    {
      COLLECTOR_LOG("While, cond == " << cond)
      
      assert(g_state->m_activeCompoundStatement);
      
      owner_ptr<ir::Expression> condExp = getNode(cond)->m_exclusiveExpression;
      assert(condExp);
      
      owner_ptr<ir::Statement> whileBody(new ir::CompoundStatement);
      
      observer_ptr<ir::Statement> whileBodyObs(whileBody);
      owner_ptr<ir::Statement> newWhile(new ir::WhileStatement(condExp, whileBody));
      
      newWhile->setParent(g_state->m_activeCompoundStatement);
      whileBodyObs->setParent(newWhile);
      
      g_state->m_activeCompoundStatement->addStatement(newWhile);
      g_state->m_activeCompoundStatement = whileBodyObs;
      
    }
    
    void
    whileEnd()
    {
      COLLECTOR_LOG("whileEnd")
      
      observer_ptr<ir::WhileStatement> whileStmt(
        g_state->m_activeCompoundStatement->getParent().dyn_cast<ir::WhileStatement>());
        
      assert(whileStmt);
      
      observer_ptr<ir::CompoundStatement> whileParent(
        whileStmt->getParent().dyn_cast<ir::CompoundStatement>());
        
      assert(whileParent);
      
      g_state->m_activeCompoundStatement = whileParent;
      
    }

    void
    signalWrite(IDType lhs, IDType rhs)
    {
      COLLECTOR_LOG("Signal write: " << lhs << " <= " << rhs) 
      
      assert(getNode(lhs)->m_Signal);
      assert(getNode(rhs)->m_exclusiveExpression);
      
      owner_ptr<ir::Statement> stmt(
        new ir::PortChannelWriteStatement(getNode(lhs)->m_Signal,
                                          getNode(rhs)->m_exclusiveExpression)
        );
      
      assert(g_state->m_activeCompoundStatement);
      g_state->m_activeCompoundStatement->addStatement(stmt);
    }
    
    void
    portWrite(IDType lhs, IDType rhs)
    {
      COLLECTOR_LOG("Port write: " << lhs << " <= " << rhs) 
      
      assert(getNode(lhs)->m_Port);
      assert(getNode(rhs)->m_exclusiveExpression);
      
      owner_ptr<ir::Statement> stmt(
        new ir::PortChannelWriteStatement(getNode(lhs)->m_Port,
                                          getNode(rhs)->m_exclusiveExpression)
        );
      
      assert(g_state->m_activeCompoundStatement);
      g_state->m_activeCompoundStatement->addStatement(stmt);
      
    }
            
    void 
    leavingScMain()
    {
      COLLECTOR_LOG("Leaving sc_main")
      
      // Check module stack consistency      
      //assert(g_state->m_moduleStack.size() == 1);
      assert(g_state->m_rootModule != 0);
      assert(g_state->m_rootModule == g_state->m_currentModule);
      assert(g_state->m_currentModule->basename() == "sc_main");
    }
    
        
    void
    signalCreated(IDType id, const std::string &name, const TypeHelperBase &type)
    {
      COLLECTOR_LOG("Signal created (" << id << "): " << name << ", type is " << type.getName() )

      owner_ptr<ir::Signal> newSig(new ir::Signal);
      getNode(id)->m_Signal = newSig;
      newSig->rename(name);
      owner_ptr<ir::Type> newSigsType(type.getType());
      newSig->setValueType(newSigsType);
      
      g_state->m_currentModule->addSignal(newSig);
//       
//       
//       COLLECTOR_LOG("Type is: " << newSigsType->getName())

    }

    
    // helper function
    void
    addPortToSignal(IDType id, const std::string &name, const TypeHelperBase &type, 
                    ir::PortToSignal::Direction direction)
    {
      owner_ptr<ir::PortToSignal> newPort(new ir::PortToSignal(direction));
      getNode(id)->m_Port = newPort;
      newPort->rename(name);
      owner_ptr<ir::Type> newPortsType(type.getType());
      newPort->setValueType(newPortsType);

      owner_ptr<ir::Port> tmp(newPort);      
      // Probably it is not a good idea to set the module as parent, because the
      // ports are stored in the ModuleType.
      tmp->setParent(g_state->m_currentModule);
      g_state->m_currentModule->getModuleType()->addPort(tmp);
    }
    
    void
    inputPortCreated(IDType id, const std::string &name, const TypeHelperBase &type)
    {
      COLLECTOR_LOG("Input Port created (" << id << "): " << name << ", type is " << type.getName() )

      addPortToSignal(id, name, type, ir::PortToSignal::IN);
    }

    void
    outputPortCreated(IDType id, const std::string &name, const TypeHelperBase &type)
    {
      COLLECTOR_LOG("Output Port created (" << id << "): " << name << ", type is " << type.getName() )
      addPortToSignal(id, name, type, ir::PortToSignal::OUT);
    }

            
    void
    moduleCreated(IDType id)
    {
      COLLECTOR_LOG("Module created (" << id << ")")
            
      
    }

    void
    moduleHasClassName(IDType id, const std::string &name)
    {
      COLLECTOR_LOG("Module has class name (" << id << "): " << name )
      
      getNode(id)->m_Module->getModuleType()->setName(name);
//      observer_ptr<ir::Module> currentTop(g_state->m_moduleStack.back());
//      owner_ptr<ir::Module> newModule(new ir::Module(name,currentTop));
    }
    
    
    void 
    enteringModuleCtor(IDType id, const std::string &name)
    {
       COLLECTOR_LOG("Entering module ctor (" << id << "): " << name )

       owner_ptr<ir::Module> newModule(new ir::Module(name, g_state->m_currentModule));
       observer_ptr<ir::Module> newModuleObs(newModule);
       g_state->m_currentModule->addSubModule(newModule);
       g_state->m_currentModule = newModuleObs;
       
       getNode(id)->m_Module = newModuleObs;
    }
    
    void
    leavingModuleCtor(IDType id)
    {
       COLLECTOR_LOG("Leaving module ctor (" << id << ")")           
       
       g_state->m_currentModule = g_state->m_currentModule->getParent();       
    }
    
    void
    portToInterfaceBinding(IDType portID, IDType interfaceID)
    {
      COLLECTOR_LOG("Port to interface binding: " << portID << " => " << interfaceID)
      
      observer_ptr<ir::Port> port(getNode(portID)->m_Port);
      observer_ptr<ir::Signal> signal(getNode(interfaceID)->m_Signal);
      
      assert(port);
      assert(signal);
      
      owner_ptr<ir::Module::Binding> newBind(new ir::Module::Binding);
      newBind->m_port = port;
      newBind->m_channelOrPort = signal;
      
      observer_ptr<ir::Module> parentModule(port->getParent().dyn_cast<ir::Module>());
      assert(parentModule);
      parentModule->addBinding(newBind);
    }
    
    void
    portToPortBinding(IDType targetID, IDType sourceID)
    {
      COLLECTOR_LOG("Port to port binding: " << targetID << " => " << sourceID)
      
      observer_ptr<ir::Port> targetPort(getNode(targetID)->m_Port),
                             sourcePort(getNode(sourceID)->m_Port);
      
      assert(targetPort);
      assert(sourcePort);
      
      owner_ptr<ir::Module::Binding> newBind(new ir::Module::Binding);
      newBind->m_port = targetPort;
      newBind->m_channelOrPort = sourcePort;
      
      observer_ptr<ir::Module> parentModule(targetPort->getParent().dyn_cast<ir::Module>());
      assert(parentModule);
      parentModule->addBinding(newBind);
    }
    
    observer_ptr<ir::PortChannelBase>
    getPortOrSignal(IDType portOrSignalID)
    {
      // The given ID must be *either* a port or a signal
      observer_ptr<ir::PortChannelBase> portOrSignal(getNode(portOrSignalID)->m_Port);
      
      if(!portOrSignal)
      {
        portOrSignal = getNode(portOrSignalID)->m_Signal;
      }
      else
      {
        assert(! getNode(portOrSignalID)->m_Signal);
      }
      
      assert(portOrSignal);

      return portOrSignal;      
    }
    
    void
    sensitivity(IDType portOrSignalID, ir::Process::Sensitivity::Edge edge)
    {
      COLLECTOR_LOG("Sensitivity " << portOrSignalID << ", edge: " << edge) 
      
      observer_ptr<ir::PortChannelBase> portOrSignal(getPortOrSignal(portOrSignalID));
      
      owner_ptr<ir::Process::Sensitivity> newSens(new ir::Process::Sensitivity);
      newSens->m_portOrChannel = portOrSignal;
      newSens->m_edge = edge;
      
      g_state->m_currentProcess->addSensitivity(newSens);
    }

    
    void
    signalWrite(IDType id)
    {
      COLLECTOR_LOG("Signal write");
    }
    
    static
    void
    createProcess(const std::string &name, ir::Process::EnumValue kind)
    {
      owner_ptr<ir::CompoundStatement> newCompound(new ir::CompoundStatement());      
      owner_ptr<ir::Process> newProcess(new ir::Process(name, kind, newCompound)); 

      g_state->m_currentProcess = newProcess;
      
      g_state->m_currentModule->addProcess(newProcess);      
      g_state->m_activeCompoundStatement = g_state->m_currentProcess->getBody();
    }
    
    void 
    enteringScMethod(const std::string &name)
    {
      COLLECTOR_LOG("Entering SC_METHOD " << name )
      createProcess(name, ir::Process::ScMethod);
    }
    
    void 
    leavingScMethod()
    {
      COLLECTOR_LOG("Leaving SC_METHOD")
      
    }
    
    void
    enteringScThread(const std::string &name)
    {
      COLLECTOR_LOG("Entering SC_THREAD " << name )
      createProcess(name, ir::Process::ScThread);
      
    }
    
    void
    leavingScThread()
    {
      COLLECTOR_LOG("Leaving SC_THREAD")
      
    }

    void 
    wait(int)
    {
      COLLECTOR_LOG("wait(int)")
      
    }
    
    void
    waitTimeLiteral(IDType idTime)
    {
      COLLECTOR_LOG("wait time literal " << idTime)
      
      owner_ptr<ir::TimeLiteral> timeLiteral = getNode(idTime)->m_exclusiveTimeLiteral;
      assert(timeLiteral);
      
      owner_ptr<ir::Statement> stmt(new ir::WaitStatement(timeLiteral));
      g_state->m_activeCompoundStatement->addStatement(stmt);
    }
    
    void
    start(IDType idTime)
    {
      COLLECTOR_LOG("start: " << idTime) 
      
      owner_ptr<ir::TimeLiteral> timeLiteral = getNode(idTime)->m_exclusiveTimeLiteral;
      assert(timeLiteral);
      
      owner_ptr<ir::SimulationCommand> newCmd(new ir::StartCommand(timeLiteral));
      
      g_state->m_simulationCommands->addCommand(newCmd);
    }
    
    void
    trace(IDType idTarget)
    {
      COLLECTOR_LOG("trace: " << idTarget)

      observer_ptr<ir::PortChannelBase> portOrSignal(getPortOrSignal(idTarget));
      
      owner_ptr<ir::SimulationCommand> newCmd(new ir::TraceCommand(portOrSignal));
      
      g_state->m_simulationCommands->addCommand(newCmd);
    }
        
  }
}

