#include "stl_specification_parser.hpp"

#include <node/stl_comp_op.hpp>
#include <rtamt/stl_exception.hpp>
#include <rtamt/stl_specification.hpp>
#include <spec/stl_specification_parser.hpp>

#include <cmath>
#include <cstring>
#include <regex>

#include <boost/rational.hpp>

using namespace spec;
using namespace grammar;
using namespace rtamt;
using namespace node;

antlrcpp::Any StlSpecificationParser::visitSpecification(StlParser::SpecificationContext* ctx) {
  _spec->name(ctx->Identifier()->getText());
  antlrcpp::Any returnVal = visitChildren(ctx);
  return returnVal;
}

antlrcpp::Any StlSpecificationParser::visitAssertion(StlParser::AssertionContext* ctx) {
  std::string rob_var = ctx->Identifier()->getText();
  _spec->rob_var(rob_var);

  antlrcpp::Any returnVal = visit(ctx->topExpression());
  return returnVal;
}

antlrcpp::Any StlSpecificationParser::visitDeclVariable(StlParser::DeclVariableContext* ctx) {
  StlIOType     io_type   = StlIOType::DEFAULT;
  antlrcpp::Any returnVal = visitChildren(ctx);

  StlParser::VariableDeclarationContext* varDeclCtx = ctx->variableDeclaration();

  std::string var_name = varDeclCtx->Identifier()->getText();

  if (varDeclCtx->ioType() != nullptr) {
    std::string io_type_str(varDeclCtx->ioType()->getText());
    std::string in_str("input");
    std::string out_str("output");
    if (io_type_str == in_str) {
      io_type = StlIOType::IN;
    } else if (io_type_str == out_str) {
      io_type = StlIOType::OUT;
    }
  }

  if (varDeclCtx->domainType()->getText() != "float") {
    throw StlParseException("Only float variables supported in this version.");
  }

  _spec->declare_var(var_name, rtamt::Type::FLOAT);
  _spec->var_io_type(var_name, io_type);

  return returnVal;
}

antlrcpp::Any StlSpecificationParser::visitDeclConstant(StlParser::DeclConstantContext* ctx) {
  antlrcpp::Any returnVal = visitChildren(ctx);

  StlParser::ConstantDeclarationContext* constantDeclCtx = ctx->constantDeclaration();

  std::string const_name = constantDeclCtx->Identifier()->getText();

  if (constantDeclCtx->domainType()->getText() != "float") {
    throw StlParseException("Only float variables supported in this version.");
  }
  
  std::string value = constantDeclCtx->literal()->getText();

  _spec->declare_const(const_name, rtamt::Type::FLOAT, value);
  
  return returnVal;
}

antlrcpp::Any StlSpecificationParser::visitExprLiteral(grammar::StlParser::ExprLiteralContext* ctx) {
  antlrcpp::Any    returnVal = visitChildren(ctx);
  double           value     = std::stod(ctx->literal()->getText());
  StlConstantNode* node      = new StlConstantNode(value);
  _root                      = node;
  return returnVal;
}

antlrcpp::Any StlSpecificationParser::visitExprId(grammar::StlParser::ExprIdContext* ctx) {
  antlrcpp::Any    returnVal   = visitChildren(ctx);
  std::string      name        = ctx->getText();
  StlNode * node               = nullptr;
  if (_spec->is_var(name)) {
    node                       = new StlVariableNode(name, _spec->var_io_type(name));
  } else {
    double value               = std::stod(_spec->const_value(name));
    node                       = new StlConstantNode(value);
  }
  _root                        = node;
  return returnVal;
}

antlrcpp::Any StlSpecificationParser::visitExprAddition(grammar::StlParser::ExprAdditionContext* ctx) {
  antlrcpp::Any returnVal;
  visit(ctx->real_expression(0));
  StlNode* left_child = _root;

  visit(ctx->real_expression(1));
  StlNode* right_child = _root;

  StlAdditionNode* node = new StlAdditionNode(left_child, right_child);

  uint64_t horizon_left_child  = left_child->horizon();
  uint64_t horizon_right_child = right_child->horizon();
  node->horizon(std::max(horizon_left_child, horizon_right_child));

  _root = node;

  return returnVal;
}

antlrcpp::Any StlSpecificationParser::visitExprSubtraction(grammar::StlParser::ExprSubtractionContext* ctx) {
  antlrcpp::Any returnVal;
  visit(ctx->real_expression(0));
  StlNode* left_child = _root;

  visit(ctx->real_expression(1));
  StlNode* right_child = _root;

  StlSubtractionNode* node = new StlSubtractionNode(left_child, right_child);

  uint64_t horizon_left_child  = left_child->horizon();
  uint64_t horizon_right_child = right_child->horizon();
  node->horizon(std::max(horizon_left_child, horizon_right_child));

  _root = node;

  return returnVal;
}

antlrcpp::Any StlSpecificationParser::visitExprMultiplication(grammar::StlParser::ExprMultiplicationContext* ctx) {
  antlrcpp::Any returnVal;
  visit(ctx->real_expression(0));
  StlNode* left_child = _root;

  visit(ctx->real_expression(1));
  StlNode* right_child = _root;

  StlMultiplicationNode* node = new StlMultiplicationNode(left_child, right_child);

  uint64_t horizon_left_child  = left_child->horizon();
  uint64_t horizon_right_child = right_child->horizon();
  node->horizon(std::max(horizon_left_child, horizon_right_child));

  _root = node;

  return returnVal;
}

antlrcpp::Any StlSpecificationParser::visitExprDivision(grammar::StlParser::ExprDivisionContext* ctx) {
  antlrcpp::Any returnVal;
  visit(ctx->real_expression(0));
  StlNode* left_child = _root;

  visit(ctx->real_expression(1));
  StlNode* right_child = _root;

  StlDivisionNode* node = new StlDivisionNode(left_child, right_child);

  uint64_t horizon_left_child  = left_child->horizon();
  uint64_t horizon_right_child = right_child->horizon();
  node->horizon(std::max(horizon_left_child, horizon_right_child));

  _root = node;

  return returnVal;
}

antlrcpp::Any StlSpecificationParser::visitIdCompInt(grammar::StlParser::IdCompIntContext* ctx) {
  antlrcpp::Any returnVal;
  visit(ctx->expression(0));
  StlNode* left_child = _root;

  visit(ctx->expression(1));
  StlNode* right_child = _root;

  std::string op_str = ctx->comparisonOp()->getText();

  StlComparisonOperator op = StlComparisonOperator::GEQ;

  if (op_str == "<=") {
    op = StlComparisonOperator::LEQ;
  } else if (op_str == "<") {
    op = StlComparisonOperator::LESS;
  } else if (op_str == ">=") {
    op = StlComparisonOperator::GEQ;
  } else if (op_str == ">") {
    op = StlComparisonOperator::GREATER;
  } else if (op_str == "==") {
    op = StlComparisonOperator::EQUAL;
  } else if (op_str == "!==") {
    op = StlComparisonOperator::NEQ;
  }

  StlPredicateNode* node = new StlPredicateNode(_spec->semantics(), op, left_child, right_child);

  uint64_t horizon_left_child  = left_child->horizon();
  uint64_t horizon_right_child = right_child->horizon();
  node->horizon(std::max(horizon_left_child, horizon_right_child));

  _root = node;

  return returnVal;
}

antlrcpp::Any StlSpecificationParser::visitExprAlwaysExpr(grammar::StlParser::ExprAlwaysExprContext* ctx) {
  antlrcpp::Any returnVal;
  visit(ctx->expression());
  StlNode* child = _root;

  try {
    interval              itv  = visit(ctx->interval());
    StlAlwaysBoundedNode* node = new StlAlwaysBoundedNode(itv.begin, itv.end, child);

    uint64_t horizon_child = child->horizon();
    node->horizon(horizon_child + itv.end);

    _root = node;
  } catch (std::exception& e) {
    delete child;
    throw StlParseException(e.what());
  }

  return returnVal;
}

antlrcpp::Any StlSpecificationParser::visitExprEvExpr(grammar::StlParser::ExprEvExprContext* ctx) {
  antlrcpp::Any returnVal;
  visit(ctx->expression());
  StlNode* child = _root;

  try {
    interval                  itv  = visit(ctx->interval());
    StlEventuallyBoundedNode* node = new StlEventuallyBoundedNode(itv.begin, itv.end, child);

    uint64_t horizon_child = child->horizon();
    node->horizon(horizon_child + itv.end);

    _root = node;
  } catch (std::exception& e) {
    delete child;
    throw StlParseException(e.what());
  }

  return returnVal;
}

antlrcpp::Any StlSpecificationParser::visitExprUntilExpr(grammar::StlParser::ExprUntilExprContext* ctx) {
  antlrcpp::Any returnVal;
  visit(ctx->expression(0));
  StlNode* left_child = _root;
  visit(ctx->expression(1));
  StlNode* right_child = _root;

  try {
    interval             itv  = visit(ctx->interval());
    StlUntilBoundedNode* node = new StlUntilBoundedNode(itv.begin, itv.end, left_child, right_child);

    uint64_t horizon_left_child  = left_child->horizon();
    uint64_t horizon_right_child = right_child->horizon();
    node->horizon(std::max(horizon_left_child, horizon_right_child) + itv.end);
    _root = node;
  } catch (std::exception& e) {
    delete left_child;
    delete right_child;
    throw StlParseException(e.what());
  }

  return returnVal;
}

antlrcpp::Any StlSpecificationParser::visitExprHistExpr(grammar::StlParser::ExprHistExprContext* ctx) {
  antlrcpp::Any returnVal;
  visit(ctx->expression());
  StlNode* child = _root;

  StlNode* node;
  if (ctx->interval() != nullptr) {
    try {
      interval itv = visit(ctx->interval());
      node         = new StlHistoricallyBoundedNode(itv.begin, itv.end, child);
    } catch (std::exception& e) {
      delete child;
      throw StlParseException(e.what());
    }
  } else {
    node = new StlHistoricallyNode(child);
  }

  uint64_t horizon_child = child->horizon();
  node->horizon(horizon_child);

  _root = node;

  return returnVal;
}

antlrcpp::Any StlSpecificationParser::visitExpreOnceExpr(grammar::StlParser::ExpreOnceExprContext* ctx) {
  antlrcpp::Any returnVal;
  visit(ctx->expression());
  StlNode* child = _root;

  StlNode* node;
  if (ctx->interval() != nullptr) {
    try {
      interval itv = visit(ctx->interval());
      node         = new StlOnceBoundedNode(itv.begin, itv.end, child);
    } catch (std::exception& e) {
      delete child;
      throw StlParseException(e.what());
    }
  } else {
    node = new StlOnceNode(child);
  }

  uint64_t horizon_child = child->horizon();
  node->horizon(horizon_child);

  _root = node;

  return returnVal;
}

antlrcpp::Any StlSpecificationParser::visitExprSinceExpr(grammar::StlParser::ExprSinceExprContext* ctx) {
  antlrcpp::Any returnVal;
  visit(ctx->expression(0));
  StlNode* left_child = _root;
  visit(ctx->expression(1));
  StlNode* right_child = _root;

  StlNode* node;
  if (ctx->interval() != nullptr) {
    try {
      interval itv = visit(ctx->interval());
      node         = new StlSinceBoundedNode(itv.begin, itv.end, left_child, right_child);
    } catch (std::exception& e) {
      delete left_child;
      delete right_child;
      throw StlParseException(e.what());
    }
  } else {
    node = new StlSinceNode(left_child, right_child);
  }
  uint64_t horizon_left_child  = left_child->horizon();
  uint64_t horizon_right_child = right_child->horizon();
  node->horizon(std::max(horizon_left_child, horizon_right_child));

  _root = node;

  return returnVal;
}

antlrcpp::Any
StlSpecificationParser::visitExprUntimedAlwaysExpr(grammar::StlParser::ExprUntimedAlwaysExprContext* ctx) {
  antlrcpp::Any returnVal;
  visit(ctx->expression());
  StlNode* child = _root;

  StlAlwaysNode* node = new StlAlwaysNode(child);

  uint64_t horizon_child = child->horizon();
  node->horizon(horizon_child);

  _root = node;

  return returnVal;
}

antlrcpp::Any StlSpecificationParser::visitExprUntimedEvExpr(grammar::StlParser::ExprUntimedEvExprContext* ctx) {
  antlrcpp::Any returnVal;
  visit(ctx->expression());
  StlNode* child = _root;

  StlEventuallyNode* node = new StlEventuallyNode(child);

  uint64_t horizon_child = child->horizon();
  node->horizon(horizon_child);

  _root = node;

  return returnVal;
}

antlrcpp::Any StlSpecificationParser::visitExprNot(grammar::StlParser::ExprNotContext* ctx) {
  antlrcpp::Any returnVal;
  visit(ctx->expression());
  StlNode* child = _root;

  StlNotNode* node = new StlNotNode(child);

  uint64_t horizon_child = child->horizon();
  node->horizon(horizon_child);

  _root = node;

  return returnVal;
}

antlrcpp::Any StlSpecificationParser::visitExprOrExpr(grammar::StlParser::ExprOrExprContext* ctx) {
  antlrcpp::Any returnVal;
  visit(ctx->expression(0));
  StlNode* left_child = _root;
  visit(ctx->expression(1));
  StlNode* right_child = _root;

  StlOrNode* node = new StlOrNode(left_child, right_child);

  uint64_t horizon_left_child  = left_child->horizon();
  uint64_t horizon_right_child = right_child->horizon();
  node->horizon(std::max(horizon_left_child, horizon_right_child));

  _root = node;

  return returnVal;
}

antlrcpp::Any StlSpecificationParser::visitExprAndExpr(grammar::StlParser::ExprAndExprContext* ctx) {
  antlrcpp::Any returnVal;
  visit(ctx->expression(0));
  StlNode* left_child = _root;
  visit(ctx->expression(1));
  StlNode* right_child = _root;

  StlAndNode* node = new StlAndNode(left_child, right_child);

  uint64_t horizon_left_child  = left_child->horizon();
  uint64_t horizon_right_child = right_child->horizon();
  node->horizon(std::max(horizon_left_child, horizon_right_child));

  _root = node;

  return returnVal;
}

antlrcpp::Any StlSpecificationParser::visitExprImpliesExpr(grammar::StlParser::ExprImpliesExprContext* ctx) {
  antlrcpp::Any returnVal;
  visit(ctx->expression(0));
  StlNode* left_child = _root;
  visit(ctx->expression(1));
  StlNode* right_child = _root;

  StlImpliesNode* node = new StlImpliesNode(left_child, right_child);

  uint64_t horizon_left_child  = left_child->horizon();
  uint64_t horizon_right_child = right_child->horizon();
  node->horizon(std::max(horizon_left_child, horizon_right_child));

  _root = node;

  return returnVal;
}

antlrcpp::Any StlSpecificationParser::visitExprIffExpr(grammar::StlParser::ExprIffExprContext* ctx) {
  antlrcpp::Any returnVal;
  visit(ctx->expression(0));
  StlNode* left_child = _root;
  visit(ctx->expression(1));
  StlNode* right_child = _root;

  StlIffNode* node = new StlIffNode(left_child, right_child);

  uint64_t horizon_left_child  = left_child->horizon();
  uint64_t horizon_right_child = right_child->horizon();
  node->horizon(std::max(horizon_left_child, horizon_right_child));

  _root = node;

  return returnVal;
}

antlrcpp::Any StlSpecificationParser::visitExprXorExpr(grammar::StlParser::ExprXorExprContext* ctx) {
  antlrcpp::Any returnVal;
  visit(ctx->expression(0));
  StlNode* left_child = _root;
  visit(ctx->expression(1));
  StlNode* right_child = _root;

  StlXorNode* node = new StlXorNode(left_child, right_child);

  uint64_t horizon_left_child  = left_child->horizon();
  uint64_t horizon_right_child = right_child->horizon();
  node->horizon(std::max(horizon_left_child, horizon_right_child));

  _root = node;

  return returnVal;
}

antlrcpp::Any StlSpecificationParser::visitExprRise(grammar::StlParser::ExprRiseContext* ctx) {
  antlrcpp::Any returnVal;
  visit(ctx->expression());
  StlNode* child = _root;

  StlRiseNode* node = new StlRiseNode(child);

  uint64_t horizon_child = child->horizon();
  node->horizon(horizon_child);

  _root = node;

  return returnVal;
}

antlrcpp::Any StlSpecificationParser::visitExprFall(grammar::StlParser::ExprFallContext* ctx) {
  antlrcpp::Any returnVal;
  visit(ctx->expression());
  StlNode* child = _root;

  StlFallNode* node = new StlFallNode(child);

  uint64_t horizon_child = child->horizon();
  node->horizon(horizon_child);

  _root = node;

  return returnVal;
}

antlrcpp::Any StlSpecificationParser::visitExprAbs(grammar::StlParser::ExprAbsContext* ctx) {
  antlrcpp::Any returnVal;
  visit(ctx->real_expression());
  StlNode* child = _root;

  StlAbsNode* node = new StlAbsNode(child);
  _root            = node;

  return returnVal;
}

antlrcpp::Any StlSpecificationParser::visitIntervalTimeLiteral(grammar::StlParser::IntervalTimeLiteralContext* ctx) {
  boost::rational<uint64_t> value = str_to_rational(ctx->literal()->getText());

  bound b;
  b.value    = value;
  b.has_unit = false;
  b.unit     = Unit::S;

  std::map<std::string, Unit> m{std::make_pair("s", Unit::S), std::make_pair("ms", Unit::MS),
                                std::make_pair("us", Unit::US), std::make_pair("ns", Unit::NS)};

  if (ctx->unit() != nullptr) {
    b.has_unit           = true;
    std::string unit_str = ctx->unit()->getText();
    b.unit               = m[unit_str];
  }

  antlrcpp::Any returnVal = b;

  return returnVal;
}

antlrcpp::Any StlSpecificationParser::visitConstantTimeLiteral(grammar::StlParser::ConstantTimeLiteralContext* ctx) {
  std::string const_name = ctx->Identifier()->getText();
  boost::rational<uint64_t> value = str_to_rational(_spec->const_value(const_name));

  bound b;
  b.value    = value;
  b.has_unit = false;
  b.unit     = Unit::S;

  std::map<std::string, Unit> m{std::make_pair("s", Unit::S), std::make_pair("ms", Unit::MS),
                                std::make_pair("us", Unit::US), std::make_pair("ns", Unit::NS)};

  if (ctx->unit() != nullptr) {
    b.has_unit           = true;
    std::string unit_str = ctx->unit()->getText();
    b.unit               = m[unit_str];
  }

  antlrcpp::Any returnVal = b;

  return returnVal;
}

antlrcpp::Any StlSpecificationParser::visitInterval(grammar::StlParser::IntervalContext* ctx) {
  bound b_begin = visit(ctx->intervalTime(0));
  bound b_end   = visit(ctx->intervalTime(1));

  if (b_begin.has_unit && !b_end.has_unit) {
    throw StlParseException(
        "Temporal operator has lower bound with a specified and upper bound with unspecified unit.");
  }

  if (!b_begin.has_unit && b_end.has_unit) {
    b_begin.unit = b_end.unit;
  }

  std::map<Unit, uint64_t> u{std::make_pair(Unit::S, s_unit), std::make_pair(Unit::MS, ms_unit),
                             std::make_pair(Unit::US, us_unit), std::make_pair(Unit::NS, ns_unit)};

  if (!b_begin.has_unit) {
    b_begin.unit = _spec->default_unit();
  }
  if (!b_end.has_unit) {
    b_end.unit = _spec->default_unit();
  }

  b_begin.value = b_begin.value * u[b_begin.unit];
  b_end.value   = b_end.value * u[b_end.unit];

  if (b_begin.value.numerator() % (b_begin.value.denominator() * _spec->sampling_period()) != 0) {
    std::stringstream ss("The bound ");
    ss << ctx->intervalTime(0)->getText() << " is not divisible by the sampling period " << _spec->sampling_period();
    throw StlParseException(ss.str());
  }

  if (b_end.value.numerator() % (b_end.value.denominator() * _spec->sampling_period()) != 0) {
    std::stringstream ss("The bound ");
    ss << ctx->intervalTime(1)->getText() << " is not divisible by the sampling period " << _spec->sampling_period();
    throw StlParseException(ss.str());
  }

  uint64_t begin = b_begin.value.numerator() / (b_begin.value.denominator() * _spec->sampling_period());
  uint64_t end   = b_end.value.numerator() / (b_end.value.denominator() * _spec->sampling_period());

  if (begin > end) {
    std::stringstream ss("Temporal operator has bound ");
    ss << "[" << begin << ", " << end << "], where the lower bound " << begin;
    ss << " is greater than the upper bound " << end << ".\n";
    throw StlParseException(ss.str());
  }

  interval      itv{begin, end};
  antlrcpp::Any returnVal = itv;

  return returnVal;
}

boost::rational<uint64_t> StlSpecificationParser::str_to_rational(const std::string& str) {
  const uint64_t ten = 10;

  uint64_t nominator   = 0;
  uint64_t denominator = 1;
  int64_t  exponent    = 0;

  uint64_t number_of_denominator_chars = 0;

  // The string can have at most 3 parts:
  // 1) A number before the dot
  // 2) A number after the dot
  // 3) an exponent
  // Examples:
  // 10
  // 12.23
  // .34
  // 10e5
  // 1.33E-5
  // .5e3
  std::string number_str;
  std::string number_before_dot_str;
  std::string number_after_dot_str;
  std::string exponent_str;

  // Check if the string contains an exponent or not
  std::regex                 reg_e("[eE]");
  std::sregex_token_iterator iter_e(str.begin(), str.end(), reg_e, -1);
  std::sregex_token_iterator end_e;
  std::vector<std::string>   tokens_exponent(iter_e, end_e);

  if (tokens_exponent.size() > 2) {
    std::stringstream ss("The bound ");
    ss << str << " contains more than one exponent [eE] delimiters - unexpected format.\n";
    throw StlParseException(ss.str());
  }

  if (tokens_exponent.size() == 2) {
    // Translate the exponent string to integer
    exponent_str = tokens_exponent.at(1);
    std::istringstream iss_e(exponent_str);
    iss_e >> exponent;
  }

  number_str = tokens_exponent.at(0);

  // Check is number contains dot (.)
  std::regex                 reg_pt("[.]");
  std::sregex_token_iterator iter_pt(number_str.begin(), number_str.end(), reg_pt, -1);
  std::sregex_token_iterator end_pt;

  std::vector<std::string> number_tokens(iter_pt, end_pt);

  if (number_tokens.size() > 2) {
    std::stringstream ss("The bound ");
    ss << str << " does not contain a single . (dot) - unexpected format.\n";
    throw StlParseException(ss.str());
  }

  if (number_tokens.size() == 2) {
    number_after_dot_str        = number_tokens.at(1);
    number_of_denominator_chars = number_after_dot_str.size();
    std::istringstream iss_a(number_after_dot_str);
    iss_a >> nominator;
    denominator = ipow(ten, number_of_denominator_chars);
  }

  number_before_dot_str = number_tokens.at(0);
  if (!number_before_dot_str.empty()) {
    uint64_t           temp;
    std::istringstream iss_b(number_before_dot_str);
    iss_b >> temp;
    nominator = temp * denominator + nominator;
  }

  if (exponent >= 0) {
    nominator *= ipow(ten, exponent);
  } else {
    denominator *= ipow(ten, labs(exponent));
  }

  boost::rational<uint64_t> out(nominator, denominator);

  return out;
}

uint64_t StlSpecificationParser::ipow(uint64_t base, uint64_t exp) {
  uint64_t result = 1U;
  for (;;) {
    if ((exp & 1U) != 0U) {
      result *= base;
    }
    exp >>= 1U;
    if (exp == 0U) {
      break;
    }
    base *= base;
  }

  return result;
}
