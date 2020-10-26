// Thorsten Schubert, OFFIS

// Visitor pattern (see Gamma et al.)

#ifndef QUINY_UTILS_VISITOR_INCLUDED
#define QUINY_UTILS_VISITOR_INCLUDED

#include "quiny/utils/debug.hpp"

namespace quiny
{
  namespace ir
  {
    class ModuleType;
    class Module;
    class StructuralObject;
    class Type;
    class SimpleType;
    class SystemCType;
    class Signal;
    class Statement;
    class IfStatement;
    class CompoundStatement;
    class Expression;
    class BinaryOperation;
    class BoolLiteral;
    class PortChannelRead;
    class IntLiteral;
    class CastExpression;
    class PortChannelWriteStatement;
    class WhileStatement;
    class TimeLiteral;
    class WaitStatement;
    class SimulationCommand;
    class SimulationCommands;
    class StartCommand;
    class TraceCommand;
  }
  
  namespace utils
  {
    
    // To be used by the nodes that will be visited
    #define DEFINE_ACCEPT_METHOD(className) \
      virtual void \
      accept(utils::NodeVisitor &visitor) \
      {\
         visitor.visit##className(*this);\
      }

    // Helper for the definition of the vistor's method bodies
    #define VISIT_METHOD_DECLARATOR(className) \
      visit##className(ir::className &node)
          
    // Helper for the user-defined visitor class
    #define DECLARE_VISIT_METHOD(className) \
      virtual void \
      VISIT_METHOD_DECLARATOR(className);
        
    // Helper for an incomplete user-defined visitor class (or unused visit methods)
    #define DEFINE_DUMMY_VISIT_METHOD(className) \
      virtual void \
      VISIT_METHOD_DECLARATOR(className) \
      { \
        PRINT_WARNING("Visit-method for class " #className " is not defined.") \
      }
      
    // Helper for the Visitor base class
    #define DECLARE_PURE_VIRTUAL_VISIT_METHOD(className) \
      virtual void \
      VISIT_METHOD_DECLARATOR(className) = 0;
      
    class NodeVisitor
    {
      public:
        
        DECLARE_PURE_VIRTUAL_VISIT_METHOD(ModuleType)
        DECLARE_PURE_VIRTUAL_VISIT_METHOD(Module)
        DECLARE_PURE_VIRTUAL_VISIT_METHOD(StructuralObject)
        DECLARE_PURE_VIRTUAL_VISIT_METHOD(Type)
        DECLARE_PURE_VIRTUAL_VISIT_METHOD(SimpleType)
        DECLARE_PURE_VIRTUAL_VISIT_METHOD(SystemCType)
        DECLARE_PURE_VIRTUAL_VISIT_METHOD(Signal)        
        DECLARE_PURE_VIRTUAL_VISIT_METHOD(Statement)
        DECLARE_PURE_VIRTUAL_VISIT_METHOD(IfStatement)
        DECLARE_PURE_VIRTUAL_VISIT_METHOD(CompoundStatement)
        DECLARE_PURE_VIRTUAL_VISIT_METHOD(Expression)
        DECLARE_PURE_VIRTUAL_VISIT_METHOD(BinaryOperation)
        DECLARE_PURE_VIRTUAL_VISIT_METHOD(BoolLiteral)
        DECLARE_PURE_VIRTUAL_VISIT_METHOD(PortChannelRead)
        DECLARE_PURE_VIRTUAL_VISIT_METHOD(IntLiteral)
        DECLARE_PURE_VIRTUAL_VISIT_METHOD(CastExpression)
        DECLARE_PURE_VIRTUAL_VISIT_METHOD(PortChannelWriteStatement)
        DECLARE_PURE_VIRTUAL_VISIT_METHOD(WhileStatement)
        DECLARE_PURE_VIRTUAL_VISIT_METHOD(TimeLiteral)
        DECLARE_PURE_VIRTUAL_VISIT_METHOD(WaitStatement)
        DECLARE_PURE_VIRTUAL_VISIT_METHOD(SimulationCommand)
        DECLARE_PURE_VIRTUAL_VISIT_METHOD(SimulationCommands)
        DECLARE_PURE_VIRTUAL_VISIT_METHOD(StartCommand)
        DECLARE_PURE_VIRTUAL_VISIT_METHOD(TraceCommand)
        
    };
    
    #undef DECLARE_PURE_VIRTUAL_VISIT_METHOD 
  } 
}


#endif

