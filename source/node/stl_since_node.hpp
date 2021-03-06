#ifndef STL_SINCE_NODE_H
#define STL_SINCE_NODE_H

#include <node/stl_node.hpp>
#include <node/stl_sample.hpp>
#include <visitor/stl_visitor.hpp>

#include <array>

#include <boost/circular_buffer.hpp>

namespace node {

/**
 * @brief This class defines the Node for the
 * STL Since operation and implements the monitoring algorithm
 * for computing it.
 *
 */

class StlSinceNode : public StlNode {
private:
  /**
   * @brief Array of two input (left and right) samples
   *
   */
  std::array<Sample, 2> in;
  /**
   * @brief Previous computed output sample.
   *
   */
  Sample prev_out;

public:
  /**
   * @brief Constructor that sets the child node
   *
   * @param left_child STL node representing the subformula phi of the formula phi since psi.
   * @param right_child STL node representing the subformula psi of the formula phi since psi.
   */
  StlSinceNode(StlNode* left_child, StlNode* right_child);
  /**
   * @brief Monitoring algorithm computing the since operation.
   *
   * @return node::Sample
   */
  Sample update() override;
  /**
   * @brief Updates the input with new input samples (left and right).
   *
   * @param left left input sample.
   * @param right right input sample.
   */
  void addNewInput(Sample left, Sample right);
  /**
   * @brief Accepts STL Visitor and calls its visit function.
   *
   * @param v STL Visitor
   */
  void accept(visitor::StlVisitor& v) override;

  ~StlSinceNode() override = default;

  /**
   * @brief Reset the monitor state of STL Since node.
   *
   */
  void reset() override;
};

} // namespace node

#endif /* STL_SINCE_NODE_H */
