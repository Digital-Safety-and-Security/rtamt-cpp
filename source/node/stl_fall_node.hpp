#ifndef STL_FALL_H
#define STL_FALL_H

#include <node/stl_node.hpp>
#include <node/stl_sample.hpp>
#include <visitor/stl_visitor.hpp>

namespace node {

/**
 * @brief This class defines the Node for the
 * STL Falling Edge operation and implements the monitoring algorithm
 * for computing it.
 *
 */

class StlFallNode : public StlNode {
private:
  /**
   * @brief Current input sample
   *
   */
  Sample in;
  /**
   * @brief Previous input sample
   *
   */
  Sample prev_in;

public:
  /**
   * @brief Constructor that sets the child node
   *
   * @param child STL node representing the subformula phi of the formula fall(phi).
   */
  explicit StlFallNode(StlNode* child);
  /**
   * @brief Monitoring algorithm computing the falling edge operation.
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

  ~StlFallNode() override = default;

  /**
   * @brief Reset the monitor state of STL Fall node.
   *
   */
  void reset() override;
};

} // namespace node

#endif /* STL_RISE_H */
