#include "stl_reset_monitor_state.hpp"

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

using namespace node;
using namespace spec;

void StlResetMonitorState::visit(StlAbsNode* e) {
  e->getChild(0)->accept(*this);
  e->reset();
}

void StlResetMonitorState::visit(StlAdditionNode* e) {
  e->getChild(0)->accept(*this);
  e->getChild(1)->accept(*this);
  e->reset();
}

void StlResetMonitorState::visit(StlAlwaysBoundedNode* e) {
  e->getChild(0)->accept(*this);
  e->reset();
}

void StlResetMonitorState::visit(StlAlwaysNode* e) {
  e->getChild(0)->accept(*this);
  e->reset();
}

void StlResetMonitorState::visit(StlAndNode* e) {
  e->getChild(0)->accept(*this);
  e->getChild(1)->accept(*this);
  e->reset();
}

void StlResetMonitorState::visit(StlConstantNode* e) {
  e->reset();
}

void StlResetMonitorState::visit(StlDivisionNode* e) {
  e->getChild(0)->accept(*this);
  e->getChild(1)->accept(*this);
  e->reset();
}

void StlResetMonitorState::visit(StlEventuallyBoundedNode* e) {
  e->getChild(0)->accept(*this);
  e->reset();
}

void StlResetMonitorState::visit(StlEventuallyNode* e) {
  e->getChild(0)->accept(*this);
  e->reset();
}

void StlResetMonitorState::visit(StlFallNode* e) {
  e->getChild(0)->accept(*this);
  e->reset();
}

void StlResetMonitorState::visit(StlHistoricallyBoundedNode* e) {
  e->getChild(0)->accept(*this);
  e->reset();
}

void StlResetMonitorState::visit(StlHistoricallyNode* e) {
  e->getChild(0)->accept(*this);
  e->reset();
}

void StlResetMonitorState::visit(StlIffNode* e) {
  e->getChild(0)->accept(*this);
  e->getChild(1)->accept(*this);
  e->reset();
}

void StlResetMonitorState::visit(StlImpliesNode* e) {
  e->getChild(0)->accept(*this);
  e->getChild(1)->accept(*this);
  e->reset();
}

void StlResetMonitorState::visit(StlMultiplicationNode* e) {
  e->getChild(0)->accept(*this);
  e->getChild(1)->accept(*this);
  e->reset();
}

void StlResetMonitorState::visit(StlNotNode* e) {
  e->getChild(0)->accept(*this);
  e->reset();
}

void StlResetMonitorState::visit(StlOnceBoundedNode* e) {
  e->getChild(0)->accept(*this);
  e->reset();
}

void StlResetMonitorState::visit(StlOnceNode* e) {
  e->getChild(0)->accept(*this);
  e->reset();
}

void StlResetMonitorState::visit(StlOrNode* e) {
  e->getChild(0)->accept(*this);
  e->getChild(1)->accept(*this);
  e->reset();
}

void StlResetMonitorState::visit(StlPrecedesBoundedNode* e) {
  e->getChild(0)->accept(*this);
  e->getChild(1)->accept(*this);
  e->reset();
}

void StlResetMonitorState::visit(StlPredicateNode* e) {
  e->getChild(0)->accept(*this);
  e->getChild(1)->accept(*this);
  e->reset();
}

void StlResetMonitorState::visit(StlRiseNode* e) {
  e->getChild(0)->accept(*this);
  e->reset();
}

void StlResetMonitorState::visit(StlSinceBoundedNode* e) {
  e->getChild(0)->accept(*this);
  e->getChild(1)->accept(*this);
  e->reset();
}

void StlResetMonitorState::visit(StlSinceNode* e) {
  e->getChild(0)->accept(*this);
  e->getChild(1)->accept(*this);
  e->reset();
}

void StlResetMonitorState::visit(StlSubtractionNode* e) {
  e->getChild(0)->accept(*this);
  e->getChild(1)->accept(*this);
  e->reset();
}

void StlResetMonitorState::visit(StlUntilBoundedNode* e) {
  e->getChild(0)->accept(*this);
  e->getChild(1)->accept(*this);
  e->reset();
}

void StlResetMonitorState::visit(StlVariableNode* e) {
  e->reset();
}

void StlResetMonitorState::visit(StlXorNode* e) {
  e->getChild(0)->accept(*this);
  e->getChild(1)->accept(*this);
  e->reset();
}
