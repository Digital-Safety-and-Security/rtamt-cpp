#include "stl_always_bounded_node.hpp"

#include <rtamt/stl_exception.hpp>
#include <visitor/stl_visitor.hpp>

using namespace visitor;
using namespace node;
using namespace rtamt;

// Initialize previous and current value
StlAlwaysBoundedNode::StlAlwaysBoundedNode(uint64_t begin, uint64_t end, StlNode* child) {
  _begin = begin;
  _end   = end;
  addChild(child);
  initIOType();
  name = "always[" + std::to_string(_begin) + "," + std::to_string(_end) + "](" + this->getChild(0)->getName() + ")";
}

void StlAlwaysBoundedNode::addNewInput(Sample /*sample*/) {
  throw StlNodeException("Cannot add input to a bounded always node\n");
}

Sample StlAlwaysBoundedNode::update() {
  throw StlNodeException("Cannot make an update in a bounded always node\n");
}

void StlAlwaysBoundedNode::accept(StlVisitor& v) {
  v.visit(this);
}
