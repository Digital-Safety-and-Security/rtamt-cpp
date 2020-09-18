#include "stl_predicate_node.hpp"

#include <rtamt/stl_specification.hpp>
#include <visitor/stl_visitor.hpp>

#include <cmath>
#include <limits>
#include <string>

using namespace visitor;
using namespace node;
using namespace rtamt;

StlPredicateNode::StlPredicateNode(StlSemantics semantics, StlComparisonOperator op, StlNode* left_child,
                                   StlNode* right_child) {
  _op = op;
  this->addChild(left_child);
  this->addChild(right_child);
  initIOType();

  std::string op_name;

  switch (op) {
    case StlComparisonOperator::EQUAL:
      op_name = "==";
      break;
    case StlComparisonOperator::NEQ:
      op_name = "!=";
      break;
    case StlComparisonOperator::GEQ:
      op_name = ">=";
      break;
    case StlComparisonOperator::GREATER:
      op_name = ">";
      break;
    case StlComparisonOperator::LEQ:
      op_name = "<=";
      break;
    case StlComparisonOperator::LESS:
      op_name = "<";
      break;
  }

  this->name = "(" + this->getChild(0)->getName() + ")" + op_name + "(" + this->getChild(1)->getName() + ")";
  _semantics = semantics;
}

StlPredicateNode::StlPredicateNode(StlComparisonOperator op, StlNode* left_child, StlNode* right_child) :
    StlPredicateNode(StlSemantics::STANDARD, op, left_child, right_child) {}

void StlPredicateNode::addNewInput(Sample left, Sample right) {
  in.at(0).time  = left.time;
  in.at(0).value = left.value;

  in.at(1).time  = right.time;
  in.at(1).value = right.value;
}

void StlPredicateNode::accept(StlVisitor& v) {
  v.visit(this);
}

Sample StlPredicateNode::update() {
  Sample out;

  out.time = in[0].time;

  switch (_op) {
    case StlComparisonOperator::EQUAL:
      out.value = -std::abs(in[0].value - in[1].value);
      break;
    case StlComparisonOperator::NEQ:
      out.value = std::abs(in[0].value - in[1].value);
      break;
    case StlComparisonOperator::LEQ:
    case StlComparisonOperator::LESS:
      out.value = in[1].value - in[0].value;
      break;
    case StlComparisonOperator::GEQ:
    case StlComparisonOperator::GREATER:
      out.value = in[0].value - in[1].value;
      break;
  }

  if (_semantics == StlSemantics::OUT_ROBUSTNESS && _out_vars.empty()) {
    out.value = out.value * std::numeric_limits<double>::infinity();
  } else if (_semantics == StlSemantics::IN_VACUITY && _in_vars.empty()) {
    out.value = 0.0;
  } else if (_semantics == StlSemantics::IN_ROBUSTNESS && _in_vars.empty()) {
    out.value = out.value * std::numeric_limits<double>::infinity();
  } else if (_semantics == StlSemantics::OUT_VACUITY && _out_vars.empty()) {
    out.value = 0;
  }

  return out;
}
