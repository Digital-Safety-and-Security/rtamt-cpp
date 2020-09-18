#include "stl_evaluation.hpp"

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
#include <node/stl_sample.hpp>
#include <node/stl_since_bounded_node.hpp>
#include <node/stl_since_node.hpp>
#include <node/stl_subtraction_node.hpp>
#include <node/stl_until_bounded_node.hpp>
#include <node/stl_variable_node.hpp>
#include <node/stl_xor_node.hpp>
#include <rtamt/stl_exception.hpp>

using namespace node;
using namespace spec;
using namespace rtamt;

StlEvaluation::StlEvaluation(node::StlNode* root, const std::set<std::string>& vars,
                             const std::map<std::string, rtamt::StlIOType>& var_io_type_map) {
  _root = root;

  for (const auto& var : vars) {
    _var_value_map.insert(std::make_pair(var, Sample()));
  }

  for (auto const& x : var_io_type_map) {
    switch (x.second) {
      case StlIOType::IN:
        _in_vars.insert(x.first);
        break;
      case StlIOType::OUT:
        _out_vars.insert(x.first);
        break;
      default:
        break;
    }
  }
}

double StlEvaluation::update(uint64_t time, const std::vector<rtamt::Input>& inputs) {
  for (const auto& input : inputs) {
    auto var = _var_value_map.find(input.name);
    if (var == _var_value_map.end()) {
      throw StlMonitorException("Variable could not be found.");
    }
    Sample& in = var->second;
    in.time    = time;
    in.value   = input.value;
  }
  _root->accept(*this);
  Sample out = _out;
  return out.value;
}

void StlEvaluation::visit(StlAbsNode* e) {
  e->getChild(0)->accept(*this);
  Sample in = _out;
  e->addNewInput(in);
  _out = e->update();
}

void StlEvaluation::visit(StlAdditionNode* e) {
  e->getChild(0)->accept(*this);
  Sample in_1 = _out;
  e->getChild(1)->accept(*this);
  Sample in_2 = _out;
  e->addNewInput(in_1, in_2);
  _out = e->update();
}

void StlEvaluation::visit(StlAlwaysBoundedNode* /*e*/) {
  throw StlMonitorException("Bounded future operators should not be directly monitored.");
}

void StlEvaluation::visit(StlAlwaysNode* e) {
  e->getChild(0)->accept(*this);
  Sample in = _out;
  e->addNewInput(in);
  _out = e->update();
}

void StlEvaluation::visit(StlAndNode* e) {
  e->getChild(0)->accept(*this);
  Sample in_1 = _out;
  e->getChild(1)->accept(*this);
  Sample in_2 = _out;
  e->addNewInput(in_1, in_2);
  _out = e->update();
}

void StlEvaluation::visit(StlConstantNode* e) {
  _out = e->update();
}

void StlEvaluation::visit(StlDivisionNode* e) {
  e->getChild(0)->accept(*this);
  Sample in_1 = _out;
  e->getChild(1)->accept(*this);
  Sample in_2 = _out;
  e->addNewInput(in_1, in_2);
  _out = e->update();
}

void StlEvaluation::visit(StlEventuallyBoundedNode* /*e*/) {
  throw StlMonitorException("Bounded future operators should not be directly monitored.");
}

void StlEvaluation::visit(StlEventuallyNode* e) {
  e->getChild(0)->accept(*this);
  Sample in = _out;
  e->addNewInput(in);
  _out = e->update();
}

void StlEvaluation::visit(StlFallNode* e) {
  e->getChild(0)->accept(*this);
  Sample in = _out;
  e->addNewInput(in);
  _out = e->update();
}

void StlEvaluation::visit(StlHistoricallyBoundedNode* e) {
  e->getChild(0)->accept(*this);
  Sample in = _out;
  e->addNewInput(in);
  _out = e->update();
}

void StlEvaluation::visit(StlHistoricallyNode* e) {
  e->getChild(0)->accept(*this);
  Sample in = _out;
  e->addNewInput(in);
  _out = e->update();
}

void StlEvaluation::visit(StlIffNode* e) {
  e->getChild(0)->accept(*this);
  Sample in_1 = _out;
  e->getChild(1)->accept(*this);
  Sample in_2 = _out;
  e->addNewInput(in_1, in_2);
  _out = e->update();
}

void StlEvaluation::visit(StlImpliesNode* e) {
  e->getChild(0)->accept(*this);
  Sample in_1 = _out;
  e->getChild(1)->accept(*this);
  Sample in_2 = _out;
  e->addNewInput(in_1, in_2);
  _out = e->update();
}

void StlEvaluation::visit(StlMultiplicationNode* e) {
  e->getChild(0)->accept(*this);
  Sample in_1 = _out;
  e->getChild(1)->accept(*this);
  Sample in_2 = _out;
  e->addNewInput(in_1, in_2);
  _out = e->update();
}

void StlEvaluation::visit(StlNotNode* e) {
  e->getChild(0)->accept(*this);
  Sample in = _out;
  e->addNewInput(in);
  _out = e->update();
}

void StlEvaluation::visit(StlOnceBoundedNode* e) {
  e->getChild(0)->accept(*this);
  Sample in = _out;
  e->addNewInput(in);
  _out = e->update();
}

void StlEvaluation::visit(StlOnceNode* e) {
  e->getChild(0)->accept(*this);
  Sample in = _out;
  e->addNewInput(in);
  _out = e->update();
}

void StlEvaluation::visit(StlOrNode* e) {
  e->getChild(0)->accept(*this);
  Sample in_1 = _out;
  e->getChild(1)->accept(*this);
  Sample in_2 = _out;
  e->addNewInput(in_1, in_2);
  _out = e->update();
}

void StlEvaluation::visit(StlPrecedesBoundedNode* e) {
  e->getChild(0)->accept(*this);
  Sample in_1 = _out;
  e->getChild(1)->accept(*this);
  Sample in_2 = _out;
  e->addNewInput(in_1, in_2);
  _out = e->update();
}

void StlEvaluation::visit(StlPredicateNode* e) {
  e->getChild(0)->accept(*this);
  Sample in_1 = _out;
  e->getChild(1)->accept(*this);
  Sample in_2 = _out;
  e->addNewInput(in_1, in_2);
  _out = e->update();
}

void StlEvaluation::visit(StlRiseNode* e) {
  e->getChild(0)->accept(*this);
  Sample in = _out;
  e->addNewInput(in);
  _out = e->update();
}

void StlEvaluation::visit(StlSinceBoundedNode* e) {
  e->getChild(0)->accept(*this);
  Sample in_1 = _out;
  e->getChild(1)->accept(*this);
  Sample in_2 = _out;
  e->addNewInput(in_1, in_2);
  _out = e->update();
}

void StlEvaluation::visit(StlSinceNode* e) {
  e->getChild(0)->accept(*this);
  Sample in_1 = _out;
  e->getChild(1)->accept(*this);
  Sample in_2 = _out;
  e->addNewInput(in_1, in_2);
  _out = e->update();
}

void StlEvaluation::visit(StlSubtractionNode* e) {
  e->getChild(0)->accept(*this);
  Sample in_1 = _out;
  e->getChild(1)->accept(*this);
  Sample in_2 = _out;
  e->addNewInput(in_1, in_2);
  _out = e->update();
}

void StlEvaluation::visit(StlUntilBoundedNode* /*e*/) {
  throw StlMonitorException("Bounded future operators should not be directly monitored.");
}

void StlEvaluation::visit(StlVariableNode* e) {
  std::string name = e->getName();
  auto        var  = _var_value_map.find(name);
  if (var == _var_value_map.end()) {
    throw StlMonitorException("Variable could not be found.");
  }
  Sample& in = var->second;
  e->addNewInput(in);
  _out = e->update();
}

void StlEvaluation::visit(StlXorNode* e) {
  e->getChild(0)->accept(*this);
  Sample in_1 = _out;
  e->getChild(1)->accept(*this);
  Sample in_2 = _out;
  e->addNewInput(in_1, in_2);
  _out = e->update();
}
