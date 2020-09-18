#ifndef STL_IFF_NODE_H
#define STL_IFF_NODE_H

#include <node/stl_combinatorial_binary_node.hpp>
#include <node/stl_operator_type.hpp>
#include <visitor/stl_visitor.hpp>

namespace node {

/**
 * @brief This class defines the Node for the
 * STL Iff operation and implements the monitoring algorithm
 * for computing it.
 *
 */

class StlIffNode : public StlCombinatorialBinaryNode {
public:
  /**
   * @brief Constructor that sets the child node
   *
   * @param left_child STL node representing the subformula phi of the formula phi iff psi.
   * @param right_child STL node representing the subformula psi of the formula phi iff psi.
   */
  StlIffNode(StlNode* left_child, StlNode* right_child) :
      StlCombinatorialBinaryNode(node::StlOperatorType::IFF, left_child, right_child) {
    this->name = "(" + this->getChild(0)->getName() + ")iff(" + this->getChild(1)->getName() + ")";
  }
  /**
   * @brief Accepts STL Visitor and calls its visit function.
   *
   * @param v STL Visitor
   */
  void accept(visitor::StlVisitor& v) override { v.visit(this); }

  ~StlIffNode() override = default;
};

} // namespace node

#endif /* STL_IFF_NODE_H */
