// 2006-03-28, Thorsten Schubert, OFFIS

#ifndef QUINY_COLLECTOR_COLLECTOR_INCLUDED
#define QUINY_COLLECTOR_COLLECTOR_INCLUDED

#include <iosfwd>
#include <string>
#include "quiny/ir/BinaryOperation.hpp"
#include "quiny/ir/Process.hpp"
#include "quiny/ir/TimeLiteral.hpp"

#include "quiny/collector/SourcePos.hpp"


namespace quiny
{
  namespace collector
  {
    class TypeHelperBase;

    typedef unsigned int IDType;
    
    // Helper class for everything that needs an ID
    class HasId
    {
      public:
        HasId();
    
        IDType
        id() const;

      protected:
        IDType    m_id;
    };
    
    // Collector logging. NULL disables logging
    void 
    setLogStream(std::ostream *log);
    

    // We generate unique IDs here in order to track the objects.
    // This should be more reliable than using addresses, especially
    // for local variables and temporary objects
    IDType
    getNewId();

    void
    objectDeleted(IDType id);

    void
    hasType(IDType id,
            const TypeHelperBase &type);

    void    
    isIntegerLiteral(IDType id,
                     unsigned long long value);
                     
    void
    isBooleanLiteral(IDType id, bool value);

    void
    isInitialised(IDType dest, IDType source);

    void
    isBinaryOperationResult(IDType result, 
                            IDType lhs, 
                            ::quiny::ir::BinaryOperation::EnumValue op,
                            IDType rhs);

    // SystemC expressions
    void 
    isSignalRead(IDType val, IDType signal);
    
    void
    isPortRead(IDType val, IDType port);

    void
    isTimeLiteral(IDType id, double value, ::quiny::ir::TimeLiteral::TimeUnit);

    // Statements

    void
    ifBegin(IDType condition, const SourcePos& pos);
    
    void 
    thenEnd();
    
    void
    elseBegin();

    void
    elseEnd();
    
    void
    whileBegin(IDType condition);
    
    // TODO: Do we need some kind of ID here?
    void whileEnd();

    // SystemC Statements
    
    void
    signalWrite(IDType lhs, IDType rhs);
    
    void
    portWrite(IDType lhs, IDType rhs);
        
    
    // SystemC

    void 
    enteringScMain();
    
    void 
    leavingScMain();
        
    void
    signalCreated(IDType id, const std::string &name, const TypeHelperBase &type);

    void
    inputPortCreated(IDType id, const std::string &name, const TypeHelperBase &type);

    void
    outputPortCreated(IDType id, const std::string &name, const TypeHelperBase &type);   
                          
    void
    moduleCreated(IDType id);
    
    void
    moduleHasClassName(IDType id, const std::string &name);
    
    void 
    enteringModuleCtor(IDType id, const std::string &name);
    
    void
    leavingModuleCtor(IDType id);

    void
    portToInterfaceBinding(IDType portID, IDType interfaceID);
    
    void
    portToPortBinding(IDType targetID, IDType sourceID);
        
    void
    sensitivity(IDType portOrSignalID, ir::Process::Sensitivity::Edge edge);
    
    void 
    enteringScMethod(const std::string &name);                  
    
    // Processes cannot be nested, hence we know which process we are leaving    
    void 
    leavingScMethod();

    void
    enteringScThread(const std::string &name);
    
    void
    leavingScThread();
    
    void 
    wait(int);
    
    void
    waitTimeLiteral(IDType idTime);
    
    void
    start(IDType idTime);
    
    void
    trace(IDType idTarget);
    
  }

}

#endif
