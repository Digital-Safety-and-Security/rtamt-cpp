#include "node/stl_until_bounded_node.hpp"

#include <rtamt/stl_exception.hpp>
#include <visitor/stl_visitor.hpp>

using namespace visitor;
using namespace node;
using namespace rtamt;

// Initialize previous and current value
StlUntilBoundedNode::StlUntilBoundedNode(uint64_t begin, uint64_t end, StlNode* left_child, StlNode* right_child) {
  _begin = begin;
  _end   = end;
  this->addChild(left_child);
  this->addChild(right_child);
  initIOType();
  this->name = "(" + this->getChild(0)->getName() + ")until[" + std::to_string(begin) + "," + std::to_string(end) +
               "](" + this->getChild(1)->getName() + ")";
}

void StlUntilBoundedNode::addNewInput(Sample /*left*/, Sample /*right*/) {
  throw StlNodeException("Cannot add input to a bounded until node\n");
}

Sample StlUntilBoundedNode::update() {
  throw StlNodeException("Cannot make an update in a bounded until node\n");
}

void StlUntilBoundedNode::accept(StlVisitor& v) {
  v.visit(this);
}
