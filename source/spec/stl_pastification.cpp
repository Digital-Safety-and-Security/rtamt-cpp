#include "stl_pastification.hpp"

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

StlNode* StlPastification::pastify(StlNode* root) {
  _horizon = root->horizon();
  root->accept(*this);
  return _out;
}

void StlPastification::visit(StlAbsNode* e) {
  e->getChild(0)->accept(*this);
  StlNode*    child = _out;
  StlAbsNode* node  = new StlAbsNode(child);
  _out              = node;
}

void StlPastification::visit(StlAdditionNode* e) {
  uint64_t tmp_horizon = _horizon;
  e->getChild(0)->accept(*this);
  StlNode* left_child = _out;
  _horizon            = tmp_horizon;
  e->getChild(1)->accept(*this);
  StlNode* right_child = _out;
  e->getChild(0)->horizon(e->horizon());
  e->getChild(1)->horizon(e->horizon());
  StlAdditionNode* node = new StlAdditionNode(left_child, right_child);
  _out                  = node;
}

void StlPastification::visit(StlAlwaysBoundedNode* e) {
  _horizon = _horizon - e->end();
  e->getChild(0)->accept(*this);
  StlNode* child = _out;
  uint64_t begin = 0;
  uint64_t end   = e->end() - e->begin();
  if (end > 0) {
    StlHistoricallyBoundedNode* node = new StlHistoricallyBoundedNode(begin, end, child, true);
    _out                             = node;
  } else {
    _out = child;
  }
}

void StlPastification::visit(StlAlwaysNode* e) {
  e->getChild(0)->accept(*this);
  StlNode*       child = _out;
  StlAlwaysNode* node  = new StlAlwaysNode(child);
  _out                 = node;
}

void StlPastification::visit(StlAndNode* e) {
  uint64_t tmp_horizon = _horizon;
  e->getChild(0)->accept(*this);
  StlNode* left_child = _out;
  _horizon            = tmp_horizon;
  e->getChild(1)->accept(*this);
  StlNode*    right_child = _out;
  StlAndNode* node        = new StlAndNode(left_child, right_child);
  _out                    = node;
}

void StlPastification::visit(StlConstantNode* e) {
  StlConstantNode* node = new StlConstantNode(e->value());
  _out                  = node;
}

void StlPastification::visit(StlDivisionNode* e) {
  uint64_t tmp_horizon = _horizon;
  e->getChild(0)->accept(*this);
  StlNode* left_child = _out;
  _horizon            = tmp_horizon;
  e->getChild(1)->accept(*this);
  StlNode*         right_child = _out;
  StlDivisionNode* node        = new StlDivisionNode(left_child, right_child);
  _out                         = node;
}

void StlPastification::visit(StlEventuallyBoundedNode* e) {
  _horizon = _horizon - e->end();
  e->getChild(0)->accept(*this);
  StlNode* child = _out;
  uint64_t begin = 0;
  uint64_t end   = e->end() - e->begin();
  if (end > 0) {
    StlOnceBoundedNode* node = new StlOnceBoundedNode(begin, end, child, true);
    _out                     = node;
  } else {
    _out = child;
  }
}

void StlPastification::visit(StlEventuallyNode* e) {
  e->getChild(0)->accept(*this);
  StlNode*           child = _out;
  StlEventuallyNode* node  = new StlEventuallyNode(child);
  _out                     = node;
}

void StlPastification::visit(StlFallNode* e) {
  e->getChild(0)->accept(*this);
  StlNode*     child = _out;
  StlFallNode* node  = new StlFallNode(child);
  _out               = node;
}

void StlPastification::visit(StlHistoricallyBoundedNode* e) {
  e->getChild(0)->accept(*this);
  StlNode*                    child = _out;
  StlHistoricallyBoundedNode* node  = new StlHistoricallyBoundedNode(e->begin(), e->end(), child, true);
  _out                              = node;
}

void StlPastification::visit(StlHistoricallyNode* e) {
  e->getChild(0)->accept(*this);
  StlNode* child = _out;
  StlNode* node  = new StlHistoricallyNode(child);
  _out           = node;
}

void StlPastification::visit(StlIffNode* e) {
  uint64_t tmp_horizon = _horizon;
  e->getChild(0)->accept(*this);
  StlNode* left_child = _out;
  _horizon            = tmp_horizon;
  e->getChild(1)->accept(*this);
  StlNode*    right_child = _out;
  StlIffNode* node        = new StlIffNode(left_child, right_child);
  _out                    = node;
}

void StlPastification::visit(StlImpliesNode* e) {
  uint64_t tmp_horizon = _horizon;
  e->getChild(0)->accept(*this);
  StlNode* left_child = _out;
  _horizon            = tmp_horizon;
  e->getChild(1)->accept(*this);
  StlNode*        right_child = _out;
  StlImpliesNode* node        = new StlImpliesNode(left_child, right_child);
  _out                        = node;
}

void StlPastification::visit(StlMultiplicationNode* e) {
  uint64_t tmp_horizon = _horizon;
  e->getChild(0)->accept(*this);
  StlNode* left_child = _out;
  _horizon            = tmp_horizon;
  e->getChild(1)->accept(*this);
  StlNode*               right_child = _out;
  StlMultiplicationNode* node        = new StlMultiplicationNode(left_child, right_child);
  _out                               = node;
}

void StlPastification::visit(StlNotNode* e) {
  e->getChild(0)->accept(*this);
  StlNode*    child = _out;
  StlNotNode* node  = new StlNotNode(child);
  _out              = node;
}

void StlPastification::visit(StlOnceBoundedNode* e) {
  e->getChild(0)->accept(*this);
  StlNode*            child = _out;
  StlOnceBoundedNode* node  = new StlOnceBoundedNode(e->begin(), e->end(), child, true);
  _out                      = node;
}

void StlPastification::visit(StlOnceNode* e) {
  e->getChild(0)->accept(*this);
  StlNode* child = _out;
  StlNode* node  = new StlOnceNode(child);
  _out           = node;
}

void StlPastification::visit(StlOrNode* e) {
  uint64_t tmp_horizon = _horizon;
  e->getChild(0)->accept(*this);
  StlNode* left_child = _out;
  _horizon            = tmp_horizon;
  e->getChild(1)->accept(*this);
  StlNode*   right_child = _out;
  StlOrNode* node        = new StlOrNode(left_child, right_child);
  _out                   = node;
}

void StlPastification::visit(StlPrecedesBoundedNode* e) {
  uint64_t tmp_horizon = _horizon;
  e->getChild(0)->accept(*this);
  StlNode* left_child = _out;
  _horizon            = tmp_horizon;
  e->getChild(1)->accept(*this);
  StlNode*                right_child = _out;
  StlPrecedesBoundedNode* node        = new StlPrecedesBoundedNode(e->begin(), e->end(), left_child, right_child, true);
  _out                                = node;
}

void StlPastification::visit(StlPredicateNode* e) {
  uint64_t tmp_horizon = _horizon;
  e->getChild(0)->accept(*this);
  StlNode* left_child = _out;
  _horizon            = tmp_horizon;
  e->getChild(1)->accept(*this);
  StlNode* right_child = _out;
  StlNode* node        = new StlPredicateNode(e->semantics(), e->op(), left_child, right_child);
  _out                 = node;
}

void StlPastification::visit(StlRiseNode* e) {
  e->getChild(0)->accept(*this);
  StlNode*     child = _out;
  StlRiseNode* node  = new StlRiseNode(child);
  _out               = node;
}

void StlPastification::visit(StlSinceBoundedNode* e) {
  uint64_t tmp_horizon = _horizon;
  e->getChild(0)->accept(*this);
  StlNode* left_child = _out;
  _horizon            = tmp_horizon;
  e->getChild(1)->accept(*this);
  StlNode*             right_child = _out;
  StlSinceBoundedNode* node        = new StlSinceBoundedNode(e->begin(), e->end(), left_child, right_child, true);
  _out                             = node;
}

void StlPastification::visit(StlSinceNode* e) {
  uint64_t tmp_horizon = _horizon;
  e->getChild(0)->accept(*this);
  StlNode* left_child = _out;
  _horizon            = tmp_horizon;
  e->getChild(1)->accept(*this);
  StlNode* right_child = _out;

  StlNode* node = new StlSinceNode(left_child, right_child);

  _out = node;
}

void StlPastification::visit(StlSubtractionNode* e) {
  uint64_t tmp_horizon = _horizon;
  e->getChild(0)->accept(*this);
  StlNode* left_child = _out;
  _horizon            = tmp_horizon;
  e->getChild(1)->accept(*this);
  StlNode* right_child = _out;

  StlSubtractionNode* node = new StlSubtractionNode(left_child, right_child);
  _out                     = node;
}

void StlPastification::visit(StlUntilBoundedNode* e) {
  _horizon             = _horizon - e->end();
  uint64_t tmp_horizon = _horizon;
  e->getChild(0)->accept(*this);
  StlNode* left_child = _out;
  _horizon            = tmp_horizon;
  e->getChild(1)->accept(*this);
  StlNode* right_child = _out;

  uint64_t begin = e->begin();
  uint64_t end   = e->end();

  StlPrecedesBoundedNode* node = new StlPrecedesBoundedNode(begin, end, left_child, right_child, true);

  _out = node;
}

void StlPastification::visit(StlVariableNode* e) {
  StlNode* node = new StlVariableNode(e->getName(), e->io_type());

  if (_horizon > 0) {
    node = new StlOnceBoundedNode(_horizon, _horizon, node, true);
  }

  _out = node;
}

void StlPastification::visit(StlXorNode* e) {
  uint64_t tmp_horizon = _horizon;
  e->getChild(0)->accept(*this);
  StlNode* left_child = _out;
  _horizon            = tmp_horizon;
  e->getChild(1)->accept(*this);
  StlNode* right_child = _out;

  StlXorNode* node = new StlXorNode(left_child, right_child);

  _out = node;
}
