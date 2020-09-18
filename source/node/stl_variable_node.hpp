#ifndef STL_VARIABLE_H
#define STL_VARIABLE_H

#include <node/stl_node.hpp>
#include <node/stl_sample.hpp>
#include <rtamt/stl_specification.hpp>
#include <visitor/stl_visitor.hpp>

#include <string>

namespace node {

/**
 * @brief This class defines the Node for the
 * STL Variable and implements the monitoring algorithm
 * for computing it.
 *
 */
class StlVariableNode : public StlNode {
private:
  /**
   * @brief Current input sample
   *
   */
  Sample in;

  rtamt::StlIOType _io_type;

public:
  /**
   * @brief Constructor that sets the name of the variable
   *
   * @param name
   */
  explicit StlVariableNode(std::string name, rtamt::StlIOType io_type);

  /**
   * @brief Constructor that sets the name of the variable
   *
   * @param name
   */
  explicit StlVariableNode(std::string name);

  /**
   * @brief Updated the input with a new input sample
   *
   * @param sample new input
   */
  void addNewInput(Sample sample);
  /**
   * @brief Monitoring algorithm computing the variable
   *
   * @return node::Sample
   */
  Sample update() override;
  /**
   * @brief Accepts STL Visitor and calls its visit function.
   *
   * @param v STL Visitor
   */
  void accept(visitor::StlVisitor& v) override;

  ~StlVariableNode() override = default;

  /**
   * @brief Reset the internal state of STL Variable node.
   *
   */
  void reset() override {}

  rtamt::StlIOType io_type() { return _io_type; }
};

} // namespace node

#endif /* STL_VARIABLE_H */
