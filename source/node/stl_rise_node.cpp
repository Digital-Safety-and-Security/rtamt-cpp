#include "stl_rise_node.hpp"

#include <visitor/stl_visitor.hpp>

#include <algorithm>
#include <limits>

using namespace visitor;
using namespace node;

// Initialize previous and current value
StlRiseNode::StlRiseNode(StlNode* child) {
  prev_in.time  = 0;
  prev_in.value = -std::numeric_limits<double>::infinity();
  this->addChild(child);
  initIOType();
  this->name = "rise(" + this->getChild(0)->getName() + ")";
}

void StlRiseNode::addNewInput(Sample sample) {
  in.time  = sample.time;
  in.value = sample.value;
}

Sample StlRiseNode::update() {
  Sample out;

  out.time  = in.time;
  out.value = in.value;

  out.value = std::min(in.value, -prev_in.value);

  prev_in.time  = in.time;
  prev_in.value = in.value;

  return out;
}

void StlRiseNode::accept(StlVisitor& v) {
  v.visit(this);
}

void StlRiseNode::reset() {
  prev_in.time  = 0;
  prev_in.value = -std::numeric_limits<double>::infinity();
}
