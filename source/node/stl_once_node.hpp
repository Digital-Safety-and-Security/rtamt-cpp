#ifndef STL_ONCE_NODE_H
#define STL_ONCE_NODE_H

#include <node/stl_node.hpp>
#include <node/stl_sample.hpp>
#include <visitor/stl_visitor.hpp>

#include <boost/circular_buffer.hpp>

namespace node {

/**
 * @brief This class defines the Node for the
 * STL Once operation and implements the monitoring algorithm
 * for computing it.
 *
 */

class StlOnceNode : public StlNode {
private:
  /**
   * @brief Current input sample.
   *
   */
  Sample in;
  /**
   * @brief Previous computed output sample.
   *
   */
  Sample prev_out;

public:
  /**
   * @brief Constructor that sets the child node
   *
   * @param child STL node representing the subformula phi of the formula once(phi).
   */
  explicit StlOnceNode(StlNode* child);
  /**
   * @brief Monitoring algorithm computing the once operation.
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

  ~StlOnceNode() override = default;

  /**
   * @brief Reset the monitor state of STL Once node.
   *
   */
  void reset() override;
};

} // namespace node

#endif /* STL_ONCE_NODE_H */
