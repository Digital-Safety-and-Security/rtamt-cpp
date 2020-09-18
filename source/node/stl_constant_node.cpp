#include "stl_constant_node.hpp"

#include <visitor/stl_visitor.hpp>

#include <algorithm>
#include <limits>

using namespace visitor;
using namespace node;

// Initialize previous and current value
StlConstantNode::StlConstantNode(double val) {
  this->val  = val;
  this->time = 0;
  this->name = std::to_string(val);
}

Sample StlConstantNode::update() {
  Sample out;

  out.time   = this->time;
  out.value  = this->val;
  this->time = this->time + 1;

  return out;
}

void StlConstantNode::accept(StlVisitor& v) {
  v.visit(this);
}

void StlConstantNode::reset() {
  this->time = 0;
}
