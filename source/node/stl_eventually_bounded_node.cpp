#include "stl_eventually_bounded_node.hpp"

#include <rtamt/stl_exception.hpp>
#include <visitor/stl_visitor.hpp>

using namespace visitor;
using namespace node;
using namespace rtamt;

// Initialize previous and current value
StlEventuallyBoundedNode::StlEventuallyBoundedNode(uint64_t begin, uint64_t end, StlNode* child) {
  _begin = begin;
  _end   = end;
  initIOType();
  this->addChild(child);
  this->name =
      "eventually[" + std::to_string(begin) + "," + std::to_string(end) + "](" + this->getChild(0)->getName() + ")";
}

void StlEventuallyBoundedNode::addNewInput(Sample /*sample*/) {
  throw StlNodeException("Cannot add input to a bounded eventually node\n");
}

Sample StlEventuallyBoundedNode::update() {
  throw StlNodeException("Cannot make update in a bounded eventually node\n");
}

void StlEventuallyBoundedNode::accept(StlVisitor& v) {
  v.visit(this);
}
