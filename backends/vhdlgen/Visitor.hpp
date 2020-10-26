// Thorsten Schubert, OFFIS

#ifndef BACKEND_VHDL_GEN_VISITOR_INCLUDED
#define BACKEND_VHDL_GEN_VISITOR_INCLUDED

#include "quiny/utils/utils.hpp"
#include "quiny/ir/ir.hpp"

#include <iosfwd>

namespace vhdlgen
{
  using namespace quiny;
  
  class Visitor : public utils::NodeVisitor
  {
    public:
    
      void
      setOutputStream(std::ostream *output);
    
      DECLARE_VISIT_METHOD(Module)
      DEFINE_DUMMY_VISIT_METHOD(ModuleType)
      DEFINE_DUMMY_VISIT_METHOD(StructuralObject)
      
      // Visiting a type will print its name
      DEFINE_DUMMY_VISIT_METHOD(Type)
      DECLARE_VISIT_METHOD(SimpleType)
      DECLARE_VISIT_METHOD(SystemCType)      
      
      DECLARE_VISIT_METHOD(Signal)
      
      DEFINE_DUMMY_VISIT_METHOD(Statement)
      DECLARE_VISIT_METHOD(IfStatement)      
      // A compound statement will result in a list of statements of its body
      // (without any begin/end)
      DECLARE_VISIT_METHOD(CompoundStatement)
      DEFINE_DUMMY_VISIT_METHOD(Expression)
      DECLARE_VISIT_METHOD(BinaryOperation)
      DECLARE_VISIT_METHOD(BoolLiteral)
      DECLARE_VISIT_METHOD(PortChannelRead)
      DECLARE_VISIT_METHOD(IntLiteral)
      DECLARE_VISIT_METHOD(CastExpression)
      DECLARE_VISIT_METHOD(PortChannelWriteStatement)
      DECLARE_VISIT_METHOD(WhileStatement)
      DECLARE_VISIT_METHOD(TimeLiteral)
      DECLARE_VISIT_METHOD(WaitStatement)
      DEFINE_DUMMY_VISIT_METHOD(SimulationCommand)
      DECLARE_VISIT_METHOD(SimulationCommands)
      DECLARE_VISIT_METHOD(StartCommand)
      DECLARE_VISIT_METHOD(TraceCommand)
      
  };
}

#endif

