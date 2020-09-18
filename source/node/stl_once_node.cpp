#include "stl_once_node.hpp"

#include <visitor/stl_visitor.hpp>

#include <algorithm>
#include <limits>

using namespace visitor;
using namespace node;

// Initialize previous and current value
StlOnceNode::StlOnceNode(StlNode* child) {
  prev_out.time  = 0;
  prev_out.value = -std::numeric_limits<double>::infinity();
  this->addChild(child);
  initIOType();
  this->name = "once(" + this->getChild(0)->getName() + ")";
}

void StlOnceNode::addNewInput(Sample sample) {
  in.time  = sample.time;
  in.value = sample.value;
}

Sample StlOnceNode::update() {
  Sample out;

  out.time  = in.time;
  out.value = std::max(in.value, prev_out.value);

  prev_out.time  = out.time;
  prev_out.value = out.value;

  return out;
}

void StlOnceNode::accept(StlVisitor& v) {
  v.visit(this);
}

void StlOnceNode::reset() {
  prev_out.time  = 0;
  prev_out.value = -std::numeric_limits<double>::infinity();
}
