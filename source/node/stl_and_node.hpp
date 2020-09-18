#ifndef STL_AND_NODE_H
#define STL_AND_NODE_H

#include <node/stl_combinatorial_binary_node.hpp>
#include <node/stl_operator_type.hpp>
#include <visitor/stl_visitor.hpp>

namespace node {

/**
 * @brief This class defines the Node for the
 * STL And operation and implements the monitoring algorithm
 * for computing it.
 *
 */
class StlAndNode : public StlCombinatorialBinaryNode {
public:
  /**
   * @brief Constructor that sets the child node
   *
   * @param left_child STL node representing the subformula phi of the formula phi and psi.
   * @param right_child STL node representing the subformula psi of the formula phi and psi.
   */
  StlAndNode(StlNode* left_child, StlNode* right_child) :
      StlCombinatorialBinaryNode(node::StlOperatorType::AND, left_child, right_child) {
    this->name = "(" + this->getChild(0)->getName() + ")and(" + this->getChild(1)->getName() + ")";
  }
  /**
   * @brief Accepts STL Visitor and calls its visit function.
   *
   * @param v STL Visitor
   */
  void accept(visitor::StlVisitor& v) override { v.visit(this); }

  ~StlAndNode() override = default;
};

} // namespace node

#endif /* STL_AND_NODE_H */
