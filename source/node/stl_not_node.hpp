#ifndef STL_NOT_H
#define STL_NOT_H

#include <node/stl_node.hpp>
#include <node/stl_sample.hpp>
#include <visitor/stl_visitor.hpp>

namespace node {

/**
 * @brief This class defines the Node for the
 * STL Not operation and implements the monitoring algorithm
 * for computing it.
 *
 */

class StlNotNode : public StlNode {
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
   * @param child STL node representing the subformula phi of the formula not(phi).
   */
  explicit StlNotNode(StlNode* child);
  /**
   * @brief Monitoring algorithm computing the negation
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

  ~StlNotNode() override = default;

  /**
   * @brief Reset the internal state of STL Not node.
   *
   */
  void reset() override {}
};

} // namespace node

#endif /* STL_NOT_H */
