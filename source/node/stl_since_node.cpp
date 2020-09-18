#include "stl_since_node.hpp"

#include <visitor/stl_visitor.hpp>

#include <algorithm>
#include <limits>

using namespace visitor;
using namespace node;

// Initialize previous and current value
StlSinceNode::StlSinceNode(StlNode* left_child, StlNode* right_child) {
  prev_out.time  = 0;
  prev_out.value = -std::numeric_limits<double>::infinity();
  this->addChild(left_child);
  this->addChild(right_child);
  initIOType();
  this->name = "(" + this->getChild(0)->getName() + ")since(" + this->getChild(1)->getName() + ")";
}

void StlSinceNode::addNewInput(Sample left, Sample right) {
  in.at(0).time  = left.time;
  in.at(0).value = left.value;

  in.at(1).time  = right.time;
  in.at(1).value = right.value;
}

Sample StlSinceNode::update() {
  Sample out;

  out.value = std::min(in[0].value, prev_out.value);
  out.value = std::max(out.value, in[1].value);
  out.time  = in[0].time;

  prev_out.time  = out.time;
  prev_out.value = out.value;

  return out;
}

void StlSinceNode::accept(StlVisitor& v) {
  v.visit(this);
}

void StlSinceNode::reset() {
  prev_out.time  = 0;
  prev_out.value = -std::numeric_limits<double>::infinity();
}
