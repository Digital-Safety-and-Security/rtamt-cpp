#include "stl_combinatorial_binary_node.hpp"

#include <visitor/stl_visitor.hpp>

#include <algorithm>
#include <cmath>
#include <limits>

using namespace visitor;
using namespace node;

StlCombinatorialBinaryNode::StlCombinatorialBinaryNode(StlOperatorType type, StlNode* left_child,
                                                       StlNode* right_child) {
  this->type = type;
  this->addChild(left_child);
  this->addChild(right_child);
  initIOType();
}

void StlCombinatorialBinaryNode::addNewInput(Sample left, Sample right) {
  in.at(0).time  = left.time;
  in.at(0).value = left.value;

  in.at(1).time  = right.time;
  in.at(1).value = right.value;
}

Sample StlCombinatorialBinaryNode::update() {
  Sample out;
  double val{0.0};

  switch (type) {
    case StlOperatorType::AND:
      val = std::min(in[0].value, in[1].value);
      break;
    case StlOperatorType::OR:
      val = std::max(in[0].value, in[1].value);
      break;
    case StlOperatorType::IMPLIES:
      val = std::max(-in[0].value, in[1].value);
      break;
    case StlOperatorType::IFF:
      val = -std::abs(in[0].value - in[1].value);
      break;
    case StlOperatorType::XOR:
      val = std::abs(in[0].value - in[1].value);
      break;
  }

  out.time  = in[0].time;
  out.value = val;

  return out;
}
