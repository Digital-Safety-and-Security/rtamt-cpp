#include "stl_variable_node.hpp"

#include <rtamt/stl_specification.hpp>
#include <visitor/stl_visitor.hpp>

#include <limits>
#include <string>
#include <utility>

using namespace visitor;
using namespace node;
using namespace rtamt;

// Initialize previous and current value

StlVariableNode::StlVariableNode(std::string name, StlIOType io_type) {
  this->name = std::move(name);
  _io_type   = io_type;
  switch (io_type) {
    case StlIOType::IN:
      _in_vars.insert(this->name);
      break;
    case StlIOType::OUT:
      _out_vars.insert(this->name);
      break;
    default:
      break;
  }
}

StlVariableNode::StlVariableNode(std::string name) : StlVariableNode(std::move(name), StlIOType::DEFAULT) {}

void StlVariableNode::addNewInput(Sample sample) {
  in.time  = sample.time;
  in.value = sample.value;
}

Sample StlVariableNode::update() {
  return this->in;
}

void StlVariableNode::accept(StlVisitor& v) {
  v.visit(this);
}
