#ifndef STL_ALWAYS_NODE_H
#define STL_ALWAYS_NODE_H

#include <node/stl_node.hpp>
#include <node/stl_sample.hpp>
#include <visitor/stl_visitor.hpp>

namespace node {

/**
 * @brief This class defines the Node for the Always
 * STL operation and implements the monitoring algorithm
 * for computing it.
 *
 */

class StlAlwaysNode : public StlNode {
private:
  /**
   * @brief Current input sample.
   *
   */
  Sample in;
  /**
   * @brief Computed output sample from the previous step
   *
   */
  Sample prev_out;

public:
  /**
   * @brief Constructor that sets the child node
   *
   * @param child STL node representing the subformula phi of the formula always(phi).
   */
  explicit StlAlwaysNode(StlNode* child);
  /**
   * @brief Monitoring algorithm computing the always operator.
   * Note: always adopts non standard semantics.
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

  ~StlAlwaysNode() override = default;

  /**
   * @brief Reset the monitor state of STL Always node.
   *
   */
  void reset() override;
};

} // namespace node

#endif /* STL_ALWAYS_NODE_H */
