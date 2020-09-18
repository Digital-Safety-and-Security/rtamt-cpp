#ifndef STL_ABS_NODE_H
#define STL_ABS_NODE_H

#include <node/stl_node.hpp>
#include <node/stl_sample.hpp>
#include <visitor/stl_visitor.hpp>

namespace node {

/**
 * @brief This class defines the Node for the Absolute Value
 * STL operation and implements the monitoring algorithm
 * for computing it.
 *
 */

class StlAbsNode : public StlNode {
private:
  /**
   * @brief Current input sample
   *
   */
  Sample in;

public:
  /**
   * @brief Constructor that sets the child node
   *
   * @param child STL node representing the subformula phi of the formula abs(phi).
   */
  explicit StlAbsNode(StlNode* child);
  /**
   * @brief Monitoring algorithm computing the absolute value
   *
   * @return node::Sample
   */
  Sample update() override;

  /**
   * @brief Updated the input with a new input sample
   *
   * @param sample new input
   */
  void addNewInput(Sample sample);
  /**
   * @brief Accepts STL Visitor and calls its visit function.
   *
   * @param v STL Visitor
   */
  void accept(visitor::StlVisitor& v) override;

  /**
   * @brief Default and explitic descructor.
   *
   */
  ~StlAbsNode() override = default;

  /**
   * @brief Reset the monitor state of STL Absolute Value node.
   *
   */
  void reset() override {}
};

} // namespace node

#endif /* STL_ABS_NODE_H */
