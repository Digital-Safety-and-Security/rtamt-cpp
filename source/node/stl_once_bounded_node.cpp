#include "stl_once_bounded_node.hpp"

#include <visitor/stl_visitor.hpp>

#include <algorithm>
#include <limits>

using namespace visitor;
using namespace node;

// Initialize previous and current value
StlOnceBoundedNode::StlOnceBoundedNode(uint64_t begin, uint64_t end, StlNode* child, bool init_monitor) {
  _begin = begin;
  _end   = end;
  this->addChild(child);
  initIOType();
  this->name = "once[" + std::to_string(begin) + "," + std::to_string(end) + "](" + this->getChild(0)->getName() + ")";

  if (init_monitor) {
    this->buffer = boost::circular_buffer<Sample>(end + 1);
    uint64_t i;
    for (i = 0; i <= end; i++) {
      Sample s;
      s.value = -std::numeric_limits<double>::infinity();
      this->buffer.push_back(s);
    }
  }
}

void StlOnceBoundedNode::addNewInput(Sample sample) {
  in.time  = sample.time;
  in.value = sample.value;

  this->buffer.push_back(in);
}

Sample StlOnceBoundedNode::update() {
  Sample out;

  out.time  = in.time;
  out.value = -std::numeric_limits<double>::infinity();
  uint64_t i;
  for (i = 0; i <= _end - _begin; i++) {
    out.value = std::max(out.value, buffer[i].value);
  }
  return out;
}

void StlOnceBoundedNode::accept(StlVisitor& v) {
  v.visit(this);
}

void StlOnceBoundedNode::reset() {
  uint64_t i;
  for (i = 0; i <= _end; i++) {
    Sample s;
    s.value = -std::numeric_limits<double>::infinity();
    this->buffer.push_back(s);
  }
}
