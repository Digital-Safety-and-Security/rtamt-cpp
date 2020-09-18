#include "stl_eventually_node.hpp"

#include <visitor/stl_visitor.hpp>

#include <algorithm>
#include <limits>

using namespace visitor;
using namespace node;

// Initialize previous and current value
StlEventuallyNode::StlEventuallyNode(StlNode* child) {
  prev_out.time  = 0;
  prev_out.value = -std::numeric_limits<double>::infinity();
  this->addChild(child);
  initIOType();
  this->name = "eventually(" + this->getChild(0)->getName() + ")";
}

void StlEventuallyNode::addNewInput(Sample sample) {
  in.time  = sample.time;
  in.value = sample.value;
}

Sample StlEventuallyNode::update() {
  Sample out;
  out.time  = in.time;
  out.value = in.value;

  out.value = std::max(in.value, prev_out.value);

  prev_out.time  = out.time;
  prev_out.value = out.value;

  return out;
}

void StlEventuallyNode::accept(StlVisitor& v) {
  v.visit(this);
}

void StlEventuallyNode::reset() {
  prev_out.time  = 0;
  prev_out.value = -std::numeric_limits<double>::infinity();
}
