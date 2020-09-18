#ifndef STL_PREDICATE_NODE_H
#define STL_PREDICATE_NODE_H

#include <node/stl_comp_op.hpp>
#include <node/stl_node.hpp>
#include <node/stl_sample.hpp>
#include <rtamt/stl_specification.hpp>
#include <visitor/stl_visitor.hpp>

#include <array>

namespace node {

/**
 * @brief This class defines the Node for the
 * STL Predicate operation and implements the monitoring algorithm
 * for computing it.
 *
 */

class StlPredicateNode : public StlNode {
private:
  /**
   * @brief Comparison operation (LEQ, GEQ, GREATER, LESS, EQUAL, NEQ)
   *
   */
  StlComparisonOperator _op;

  rtamt::StlSemantics _semantics;
  /**
   * @brief Array of two input (left and right) samples
   *
   */
  std::array<Sample, 2> in;

public:
  /**
   * @brief Constructor, defines the comparison operation (LEQ; GEQ, LESS, GREATER, EQUAL or NEQ) and
   * sets the children nodes.
   *
   * @param op Comparison operation (LEQ; GEQ, LESS, GREATER, EQUAL or NEQ)
   * @param left_child STL Node representing the left child.
   * @param right_child STL Node representing the right child.
   */
  StlPredicateNode(rtamt::StlSemantics semantics, StlComparisonOperator op, StlNode* left_child, StlNode* right_child);
  /**
   * @brief Constructor, defines the comparison operation (LEQ; GEQ, LESS, GREATER, EQUAL or NEQ) and
   * sets the children nodes.
   *
   * @param op Comparison operation (LEQ; GEQ, LESS, GREATER, EQUAL or NEQ)
   * @param left_child STL Node representing the left child.
   * @param right_child STL Node representing the right child.
   */
  StlPredicateNode(StlComparisonOperator op, StlNode* left_child, StlNode* right_child);
  /**
   * @brief Monitoring algorithm computing the predicate
   *
   * @return node::Sample
   */
  Sample update() override;
  /**
   * @brief Updated the input with a new input sample
   *
   * @param sample new input
   */
  void addNewInput(Sample left, Sample right);
  /**
   * @brief Accepts STL Visitor and calls its visit function.
   *
   * @param v STL Visitor
   */
  void accept(visitor::StlVisitor& v) override;

  /**
   * @brief Getter returning the comparison operation.
   *
   * @return StlComparisonOperator
   */
  StlComparisonOperator op() { return _op; }

  ~StlPredicateNode() override = default;

  /**
   * @brief Reset the internal state of STL Predicate node.
   *
   */
  void reset() override {}

  /**
   * @brief Get the semantics used for computing robustness of the predicate.
   *
   * @return rtamt::StlSemantics
   */
  rtamt::StlSemantics semantics() { return _semantics; }
};

} // namespace node

#endif /* STL_PREDICATE_NODE_H */
