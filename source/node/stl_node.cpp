#include "stl_node.hpp"

#include <set>
#include <string>

using namespace node;

StlNode::~StlNode() {
  for (StlNode* c : children) {
    delete c;
  }
}

void StlNode::addChild(StlNode* child) {
  this->children.push_back(child);
}

std::string StlNode::getName() {
  return this->name;
}

StlNode* StlNode::getChild(int index) {
  return this->children.at(index);
}

void StlNode::horizon(uint64_t horizon) {
  _horizon = horizon;
}

uint64_t StlNode::horizon() {
  return _horizon;
}

void StlNode::initIOType() {
  for (auto const& child : children) {
    std::set<std::string> in_var_child  = child->in_vars();
    std::set<std::string> out_var_child = child->out_vars();
    _in_vars.insert(in_var_child.begin(), in_var_child.end());
    _out_vars.insert(out_var_child.begin(), out_var_child.end());
  }
}
