#ifndef STL_PASTIFICATION_H
#define STL_PASTIFICATION_H

#include <visitor/stl_visitor.hpp>

#include <cstdint>

namespace spec {

/**
 * @brief This class translates bounded future STL formulas into an equisatisfiable past STL formula.
 *
 */
class StlPastification : public visitor::StlVisitor {
private:
  /**
   * @brief The variable _out is a pointer to the resulting past STL specification (and is
   * also used to store intermediate during the pastification of the bounded future STL
   * specification
   *
   */
  node::StlNode* _out = {nullptr};
  /**
   * @brief Auxiliary data structure to keep track of the horizon of the nodes.
   *
   */
  uint64_t _horizon{0};

public:
  /**
   * @brief Compute the translation of the bounded future STL specification to the
   * past STL specification
   *
   * @param root pointer to the input STL specification
   * @return node::StlNode*
   */
  node::StlNode* pastify(node::StlNode* root);
  /**
   * @brief Pastify the STL Absolute Value node
   *
   * @param e STL Absolute Value node
   */
  void visit(node::StlAbsNode* e) override;
  /**
   * @brief Pastify the STL Addition node
   *
   * @param e STL Addition node
   */
  void visit(node::StlAdditionNode* e) override;
  /**
   * @brief Pastify the STL Bounded Always node
   *
   * @param e STL Bounded Always node
   */
  void visit(node::StlAlwaysBoundedNode* e) override;
  /**
   * @brief Pastify the STL Always node
   *
   * @param e STL Always node
   */
  void visit(node::StlAlwaysNode* e) override;
  /**
   * @brief Pastify the STL And node
   *
   * @param e STL And node
   */
  void visit(node::StlAndNode* e) override;
  /**
   * @brief Pastify the STL Constant node
   *
   * @param e STL Constant node
   */
  void visit(node::StlConstantNode* e) override;
  /**
   * @brief Pastify the STL Division node
   *
   * @param e STL Division node
   */
  void visit(node::StlDivisionNode* e) override;
  /**
   * @brief Pastify the STL Bounded Eventually node
   *
   * @param e STL Bounded Eventually node
   */
  void visit(node::StlEventuallyBoundedNode* e) override;
  /**
   * @brief Pastify the STL Eventually node
   *
   * @param e STL Eventually node
   */
  void visit(node::StlEventuallyNode* e) override;
  /**
   * @brief Pastify the STL Fall node
   *
   * @param e STL Fall node
   */
  void visit(node::StlFallNode* e) override;
  /**
   * @brief Pastify the STL Bounded Historically node
   *
   * @param e STL Bounded Historically node
   */
  void visit(node::StlHistoricallyBoundedNode* e) override;
  /**
   * @brief Pastify the STL Historically node
   *
   * @param e STL Historically node
   */
  void visit(node::StlHistoricallyNode* e) override;
  /**
   * @brief Pastify the STL If and Only If (Iff) node
   *
   * @param e STL If and Only If (Iff) node
   */
  void visit(node::StlIffNode* e) override;
  /**
   * @brief Pastify the STL Implies node
   *
   * @param e STL Implies node
   */
  void visit(node::StlImpliesNode* e) override;
  /**
   * @brief Pastify the STL Multiplication node
   *
   * @param e STL Multiplication node
   */
  void visit(node::StlMultiplicationNode* e) override;
  /**
   * @brief Pastify the STL Not node
   *
   * @param e STL Not node
   */
  void visit(node::StlNotNode* e) override;
  /**
   * @brief Pastify the STL Bounded Once node
   *
   * @param e STL Bounded Once node
   */
  void visit(node::StlOnceBoundedNode* e) override;
  /**
   * @brief Pastify the STL Once node
   *
   * @param e STL Once node
   */
  void visit(node::StlOnceNode* e) override;
  /**
   * @brief Pastify the STL Or node
   *
   * @param e STL Or node
   */
  void visit(node::StlOrNode* e) override;
  /**
   * @brief Pastify the STL Bounded Precedes node
   *
   * @param e STL Bounded Precedes node
   */
  void visit(node::StlPrecedesBoundedNode* e) override;
  /**
   * @brief Pastify the STL Predicate node
   *
   * @param e STL Predicate node
   */
  void visit(node::StlPredicateNode* e) override;
  /**
   * @brief Pastify the STL Rise node
   *
   * @param e STL Rise node
   */
  void visit(node::StlRiseNode* e) override;
  /**
   * @brief Pastify the STL Bounded Since node
   *
   * @param e STL Bounded Since node
   */
  void visit(node::StlSinceBoundedNode* e) override;
  /**
   * @brief Pastify the STL Since node
   *
   * @param e STL Since node
   */
  void visit(node::StlSinceNode* e) override;
  /**
   * @brief Pastify the STL Subtraction node
   *
   * @param e STL Subtraction node
   */
  void visit(node::StlSubtractionNode* e) override;
  /**
   * @brief Pastify the STL Bounded Until node
   *
   * @param e STL Bounded Until node
   */
  void visit(node::StlUntilBoundedNode* e) override;
  /**
   * @brief Pastify the STL Variable node
   *
   * @param e STL Variable node
   */
  void visit(node::StlVariableNode* e) override;
  /**
   * @brief Pastify the STL Exclusive Or (Xor) node
   *
   * @param e STL Exclusive Or (Xor) node
   */
  void visit(node::StlXorNode* e) override;
};

} // namespace spec

#endif // STL_PASTIFICATION_H
