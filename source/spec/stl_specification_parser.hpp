#ifndef STL_SPECIFICATION_PARSER_H
#define STL_SPECIFICATION_PARSER_H

#include <node/stl_abs_node.hpp>
#include <node/stl_addition_node.hpp>
#include <node/stl_always_bounded_node.hpp>
#include <node/stl_always_node.hpp>
#include <node/stl_and_node.hpp>
#include <node/stl_combinatorial_binary_node.hpp>
#include <node/stl_constant_node.hpp>
#include <node/stl_division_node.hpp>
#include <node/stl_eventually_bounded_node.hpp>
#include <node/stl_eventually_node.hpp>
#include <node/stl_fall_node.hpp>
#include <node/stl_historically_bounded_node.hpp>
#include <node/stl_historically_node.hpp>
#include <node/stl_iff_node.hpp>
#include <node/stl_implies_node.hpp>
#include <node/stl_multiplication_node.hpp>
#include <node/stl_node.hpp>
#include <node/stl_not_node.hpp>
#include <node/stl_once_bounded_node.hpp>
#include <node/stl_once_node.hpp>
#include <node/stl_or_node.hpp>
#include <node/stl_precedes_bounded_node.hpp>
#include <node/stl_predicate_node.hpp>
#include <node/stl_rise_node.hpp>
#include <node/stl_since_bounded_node.hpp>
#include <node/stl_since_node.hpp>
#include <node/stl_subtraction_node.hpp>
#include <node/stl_until_bounded_node.hpp>
#include <node/stl_variable_node.hpp>
#include <node/stl_xor_node.hpp>
#include <rtamt/stl_specification.hpp>
#include <spec/stl_inner_specification.hpp>

#include <antlr4-runtime.h>
#include <grammar/StlParserBaseVisitor.h>

#include <boost/rational.hpp>

namespace spec {

/**
 * @brief Class that translates the STL ANTLR4 parse tree to an STL Specification object.
 *
 */
class StlSpecificationParser : public grammar::StlParserBaseVisitor {
private:
  const uint64_t s_unit  = 1000000000;
  const uint64_t ms_unit = 1000000;
  const uint64_t us_unit = 1000;
  const uint64_t ns_unit = 1;

  /**
   * @brief STL Inner Specification
   *
   */
  StlInnerSpecification* _spec;
  /**
   * @brief Pointer to the STL specification tree root
   *
   */
  node::StlNode* _root = {nullptr};

  struct interval {
    uint64_t begin{0};
    uint64_t end{0};
  };

  struct bound {
    boost::rational<uint64_t> value{0, 1};
    bool                      has_unit{false};
    rtamt::Unit               unit{rtamt::Unit::S};
  };

public:
  /**
   * @brief Constructor that passes the STL Inner Specification object to be populated
   *
   * @param spec
   */
  explicit StlSpecificationParser(StlInnerSpecification* spec) { _spec = spec; }

  /**
   * @brief Visit Specification rule
   *
   * @param ctx Context
   * @return antlrcpp::Any
   */
  antlrcpp::Any visitSpecification(grammar::StlParser::SpecificationContext* ctx) override;
  /**
   * @brief Visit Asserition rule
   *
   * @param ctx Context
   * @return antlrcpp::Any
   */
  antlrcpp::Any visitAssertion(grammar::StlParser::AssertionContext* ctx) override;

  /**exponents
   * @brief Visit Variable Declaration rule
   *
   * @param ctx Context
   * @return antlrcpp::Any
   */
  antlrcpp::Any visitDeclVariable(grammar::StlParser::DeclVariableContext* ctx) override;
  
  /**exponents
   * @brief Visit Constant Declaration rule
   *
   * @param ctx Context
   * @return antlrcpp::Any
   */
  antlrcpp::Any visitDeclConstant(grammar::StlParser::DeclConstantContext* ctx) override;

  /**
   * @brief Visit ExprLiteral (Constant) rule
   *
   * @param ctx Context
   * @return antlrcpp::Any
   */
  antlrcpp::Any visitExprLiteral(grammar::StlParser::ExprLiteralContext* ctx) override;

  /**
   * @brief Visit ExprId (Variable) rule
   *
   * @param ctx Context
   * @return antlrcpp::Any
   */
  antlrcpp::Any visitExprId(grammar::StlParser::ExprIdContext* ctx) override;

  /**
   * @brief Visit ExprAddition rule
   *
   * @param ctx Context
   * @return antlrcpp::Any
   */
  antlrcpp::Any visitExprAddition(grammar::StlParser::ExprAdditionContext* ctx) override;

  /**
   * @brief Visit ExprSubtraction rule
   *
   * @param ctx Context
   * @return antlrcpp::Any
   */
  antlrcpp::Any visitExprSubtraction(grammar::StlParser::ExprSubtractionContext* ctx) override;

  /**
   * @brief Visit ExprMultiplication rule
   *
   * @param ctx Context
   * @return antlrcpp::Any
   */
  antlrcpp::Any visitExprMultiplication(grammar::StlParser::ExprMultiplicationContext* ctx) override;

  /**
   * @brief Visit ExprDivision rule
   *
   * @param ctx Context
   * @return antlrcpp::Any
   */
  antlrcpp::Any visitExprDivision(grammar::StlParser::ExprDivisionContext* ctx) override;

  /**
   * @brief Visit IdCompInt (Predicate) rule
   *
   * @param ctx Context
   * @return antlrcpp::Any
   */
  antlrcpp::Any visitIdCompInt(grammar::StlParser::IdCompIntContext* ctx) override;

  /**
   * @brief Visit ExprAlwaysExpr (Bounded Always) rule
   *
   * @param ctx Context
   * @return antlrcpp::Any
   */
  antlrcpp::Any visitExprAlwaysExpr(grammar::StlParser::ExprAlwaysExprContext* ctx) override;

  /**
   * @brief Visit ExprEvExpr (Bounded Eventually) rule
   *
   * @param ctx Context
   * @return antlrcpp::Any
   */
  antlrcpp::Any visitExprEvExpr(grammar::StlParser::ExprEvExprContext* ctx) override;

  /**
   * @brief Visit ExprUntilExpr (Bounded Until) rule
   *
   * @param ctx Context
   * @return antlrcpp::Any
   */
  antlrcpp::Any visitExprUntilExpr(grammar::StlParser::ExprUntilExprContext* ctx) override;

  /**
   * @brief Visit ExprHistoricallyExpr ((Bounded) Historically) rule
   *
   * @param ctx Context
   * @return antlrcpp::Any
   */
  antlrcpp::Any visitExprHistExpr(grammar::StlParser::ExprHistExprContext* ctx) override;

  /**
   * @brief Visit ExprOnceExpr ((Bounded) Once) rule
   *
   * @param ctx Context
   * @return antlrcpp::Any
   */
  antlrcpp::Any visitExpreOnceExpr(grammar::StlParser::ExpreOnceExprContext* ctx) override;

  /**
   * @brief Visit ExprSinceExpr ((Bounded) Since) rule
   *
   * @param ctx Context
   * @return antlrcpp::Any
   */
  antlrcpp::Any visitExprSinceExpr(grammar::StlParser::ExprSinceExprContext* ctx) override;

  /**
   * @brief Visit ExprUntimedAlwaysExpr (Untimed Always) rule
   *
   * @param ctx Context
   * @return antlrcpp::Any
   */
  antlrcpp::Any visitExprUntimedAlwaysExpr(grammar::StlParser::ExprUntimedAlwaysExprContext* ctx) override;

  /**
   * @brief Visit ExprUntimedEvExpr (Untimed Eventually) rule
   *
   * @param ctx Context
   * @return antlrcpp::Any
   */
  antlrcpp::Any visitExprUntimedEvExpr(grammar::StlParser::ExprUntimedEvExprContext* ctx) override;

  /**
   * @brief Visit ExprNot (Not) rule
   *
   * @param ctx Context
   * @return antlrcpp::Any
   */
  antlrcpp::Any visitExprNot(grammar::StlParser::ExprNotContext* ctx) override;

  /**
   * @brief Visit ExprOrExpr rule
   *
   * @param ctx Context
   * @return antlrcpp::Any
   */
  antlrcpp::Any visitExprOrExpr(grammar::StlParser::ExprOrExprContext* ctx) override;

  /**
   * @brief Visit ExprAndExpr rule
   *
   * @param ctx Context
   * @return antlrcpp::Any
   */
  antlrcpp::Any visitExprAndExpr(grammar::StlParser::ExprAndExprContext* ctx) override;

  /**
   * @brief Visit ExprImpliesExpr rule
   *
   * @param ctx Context
   * @return antlrcpp::Any
   */
  antlrcpp::Any visitExprImpliesExpr(grammar::StlParser::ExprImpliesExprContext* ctx) override;

  /**
   * @brief Visit ExprIffExpr rule
   *
   * @param ctx Context
   * @return antlrcpp::Any
   */
  antlrcpp::Any visitExprIffExpr(grammar::StlParser::ExprIffExprContext* ctx) override;

  /**
   * @brief Visit ExprXorExpr rule
   *
   * @param ctx Context
   * @return antlrcpp::Any
   */
  antlrcpp::Any visitExprXorExpr(grammar::StlParser::ExprXorExprContext* ctx) override;

  /**
   * @brief Visit IntervalTimeLiteral rule
   *
   * @param ctx Context
   * @return antlrcpp::Any
   */
  antlrcpp::Any visitIntervalTimeLiteral(grammar::StlParser::IntervalTimeLiteralContext* ctx) override;

  /**
   * @brief Visit Interval rule
   *
   * @param ctx Context
   * @return antlrcpp::Any
   */
  antlrcpp::Any visitInterval(grammar::StlParser::IntervalContext* ctx) override;

  /**
   * @brief Visit ExprRise (Rise) rule
   *
   * @param ctx Context
   * @return antlrcpp::Any
   */
  antlrcpp::Any visitExprRise(grammar::StlParser::ExprRiseContext* ctx) override;

  /**
   * @brief Visit ExprFall (Fall) rule
   *
   * @param ctx Context
   * @return antlrcpp::Any
   */
  antlrcpp::Any visitExprFall(grammar::StlParser::ExprFallContext* ctx) override;

  /**
   * @brief Visit ExprAbs (Absolute Value) rule
   *
   * @param ctx Context
   * @return antlrcpp::Any
   */
  antlrcpp::Any visitExprAbs(grammar::StlParser::ExprAbsContext* ctx) override;

  static boost::rational<uint64_t> str_to_rational(const std::string& rational_str);

  static uint64_t ipow(uint64_t base, uint64_t exp);

  /**
   * @brief Return the STL Inner Specification
   *
   * @return spec::StlInnerSpecification
   */
  StlInnerSpecification* spec() { return _spec; }

  node::StlNode* root() { return _root; }
};

} // namespace spec

#endif // STL_SPECIFICATION_PARSER_H
