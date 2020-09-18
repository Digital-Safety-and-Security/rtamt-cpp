#include "stl_always_node.hpp"

#include <visitor/stl_visitor.hpp>

#include <algorithm>
#include <limits>

using namespace visitor;
using namespace node;

// Initialize previous and current value
StlAlwaysNode::StlAlwaysNode(StlNode* child) {
  prev_out.time  = 0;
  prev_out.value = std::numeric_limits<double>::infinity();
  addChild(child);
  initIOType();
  name = "always(" + this->getChild(0)->getName() + ")";
}

void StlAlwaysNode::addNewInput(Sample sample) {
  in.time  = sample.time;
  in.value = sample.value;
}

Sample StlAlwaysNode::update() {
  Sample out;

  out.time  = in.time;
  out.value = in.value;

  out.value = std::min(in.value, prev_out.value);

  prev_out.time  = out.time;
  prev_out.value = out.value;

  return out;
}

void StlAlwaysNode::accept(StlVisitor& v) {
  v.visit(this);
}

void StlAlwaysNode::reset() {
  prev_out.time  = 0;
  prev_out.value = std::numeric_limits<double>::infinity();
}
