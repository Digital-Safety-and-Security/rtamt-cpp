#ifndef STL_COMBINATORIAL_BINARY_NODE_H
#define STL_COMBINATORIAL_BINARY_NODE_H

#include <node/stl_node.hpp>
#include <node/stl_operator_type.hpp>
#include <node/stl_sample.hpp>
#include <visitor/stl_visitor.hpp>

#include <array>

namespace node {

/**
 * @brief This abstract class defines the Node for the
 * all binary Boolean STL operation (and, or, implies, iff and xor) and
 * implements the monitoring algorithm
 * for computing it.
 *
 */

class StlCombinatorialBinaryNode : public StlNode {
protected:
  /**
   * @brief Type of the operator (and, or, impies, iff or xor)
   *
   */
  node::StlOperatorType type;
  /**
   * @brief Array of two input samples (left and right)
   *
   */
  std::array<Sample, 2> in;

public:
  /**
   * @brief Constructor, defines the operation type (and, or, impies, iff or xor) and
   * sets the children nodes.
   *
   * @param type Operator type (and, or, implies, iff or xor)
   * @param left_child STL Node representing the left child.
   * @param right_child STL Node representing the right child.
   */
  StlCombinatorialBinaryNode(node::StlOperatorType type, StlNode* left_child, StlNode* right_child);
  /**
   * @brief Generic monitoring algorithm computing binary Boolean operations
   * (for and, or, implies, iff and xor)
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

  ~StlCombinatorialBinaryNode() override = default;

  /**
   * @brief Reset the internal state of all Combinatorial Binary node.
   *
   */
  void reset() override {}
};

} // namespace node

#endif /* STL_COMBINATORIAL_BINARY_NODE_H */
