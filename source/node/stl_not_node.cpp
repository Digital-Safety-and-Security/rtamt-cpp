#include "stl_not_node.hpp"

#include <visitor/stl_visitor.hpp>

#include <algorithm>
#include <limits>

using namespace visitor;
using namespace node;

// Initialize previous and current value
StlNotNode::StlNotNode(StlNode* child) {
  this->addChild(child);
  initIOType();
  this->name = "not(" + this->getChild(0)->getName() + ")";
}

void StlNotNode::addNewInput(Sample sample) {
  in.time  = sample.time;
  in.value = sample.value;
}

Sample StlNotNode::update() {
  Sample out;

  out.time  = in.time;
  out.value = -in.value;

  return out;
}

void StlNotNode::accept(StlVisitor& v) {
  v.visit(this);
}
