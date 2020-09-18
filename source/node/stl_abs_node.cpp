#include "stl_abs_node.hpp"

#include <visitor/stl_visitor.hpp>

#include <algorithm>
#include <cstdlib>
#include <limits>
#include <string>

using namespace node;
using namespace visitor;

// Initialize previous and current value
StlAbsNode::StlAbsNode(StlNode* child) {
  addChild(child);
  initIOType();
  name = "abs(" + this->getChild(0)->getName() + ")";
}

void StlAbsNode::addNewInput(Sample sample) {
  in.time  = sample.time;
  in.value = sample.value;
}

Sample StlAbsNode::update() {
  Sample out;

  out.time  = in.time;
  out.value = std::abs(in.value);

  return out;
}

void StlAbsNode::accept(StlVisitor& v) {
  v.visit(this);
}
