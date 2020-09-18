#include "stl_subtraction_node.hpp"

#include <visitor/stl_visitor.hpp>

#include <algorithm>
#include <cmath>
#include <limits>

using namespace visitor;
using namespace node;

StlSubtractionNode::StlSubtractionNode(StlNode* left_child, StlNode* right_child) {
  this->addChild(left_child);
  this->addChild(right_child);
  initIOType();
  this->name = "(" + this->getChild(0)->getName() + ")-(" + this->getChild(1)->getName() + ")";
}

void StlSubtractionNode::addNewInput(Sample left, Sample right) {
  in.at(0).time  = left.time;
  in.at(0).value = left.value;

  in.at(1).time  = right.time;
  in.at(1).value = right.value;
}

Sample StlSubtractionNode::update() {
  Sample out;
  double val;

  val = in[0].value - in[1].value;

  out.time  = in[0].time;
  out.value = val;

  return out;
}

void StlSubtractionNode::accept(StlVisitor& v) {
  v.visit(this);
}
