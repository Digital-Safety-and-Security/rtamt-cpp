#include "stl_precedes_bounded_node.hpp"

#include <visitor/stl_visitor.hpp>

#include <algorithm>
#include <limits>

using namespace visitor;
using namespace node;

// Initialize previous and current value
StlPrecedesBoundedNode::StlPrecedesBoundedNode(uint64_t begin, uint64_t end, StlNode* left_child, StlNode* right_child,
                                               bool init_monitor) {
  _begin = begin;
  _end   = end;
  this->addChild(left_child);
  this->addChild(right_child);
  initIOType();

  this->name = "(" + this->getChild(0)->getName() + ")precedes[" + std::to_string(begin) + "," + std::to_string(end) +
               "](" + this->getChild(1)->getName() + ")";

  if (init_monitor) {
    this->buffer[0] = boost::circular_buffer<Sample>(end + 1);
    this->buffer[1] = boost::circular_buffer<Sample>(end + 1);
    uint64_t i;
    for (i = 0; i <= _end; i++) {
      Sample s_left;
      Sample s_right;
      s_left.value  = std::numeric_limits<double>::infinity();
      s_right.value = -std::numeric_limits<double>::infinity();
      this->buffer[0].push_back(s_left);
      this->buffer[1].push_back(s_right);
    }
  }
}

void StlPrecedesBoundedNode::addNewInput(Sample left, Sample right) {
  in.time  = left.time;
  in.value = left.value;
  this->buffer.at(0).push_back(in);

  in.time  = right.time;
  in.value = right.value;
  this->buffer.at(1).push_back(in);
}

Sample StlPrecedesBoundedNode::update() {
  Sample out;

  out.time  = in.time;
  out.value = -std::numeric_limits<double>::infinity();
  uint64_t i;
  for (i = _begin; i <= _end; i++) {
    Sample left;
    Sample right;
    right.value = buffer[1][i].value;
    left.value  = std::numeric_limits<double>::infinity();
    uint64_t j;
    for (j = 0; j < i; j++) {
      left.value = std::min(left.value, buffer[0][j].value);
    }
    out.value = std::max(out.value, std::min(left.value, right.value));
  }
  return out;
}

void StlPrecedesBoundedNode::accept(StlVisitor& v) {
  v.visit(this);
}

void StlPrecedesBoundedNode::reset() {
  uint64_t i;
  for (i = 0; i <= _end; i++) {
    Sample s_left;
    Sample s_right;
    s_left.value  = std::numeric_limits<double>::infinity();
    s_right.value = -std::numeric_limits<double>::infinity();
    this->buffer[0].push_back(s_left);
    this->buffer[1].push_back(s_right);
  }
}
