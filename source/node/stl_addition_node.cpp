#include "stl_addition_node.hpp"

#include <visitor/stl_visitor.hpp>

#include <algorithm>
#include <cmath>
#include <limits>

using namespace visitor;
using namespace node;

StlAdditionNode::StlAdditionNode(StlNode* left_child, StlNode* right_child) {
  addChild(left_child);
  addChild(right_child);
  initIOType();

  name = "(" + getChild(0)->getName() + ")+(" + getChild(1)->getName() + ")";
}

void StlAdditionNode::addNewInput(Sample left, Sample right) {
  in.at(0).time  = left.time;
  in.at(0).value = left.value;

  in.at(1).time  = right.time;
  in.at(1).value = right.value;
}

Sample StlAdditionNode::update() {
  Sample out;
  double val;

  val = in[0].value + in[1].value;

  out.time  = in[0].time;
  out.value = val;

  return out;
}

void StlAdditionNode::accept(StlVisitor& v) {
  v.visit(this);
}
