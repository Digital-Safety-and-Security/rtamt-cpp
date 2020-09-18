#ifndef STL_RESET_MONITOR_STATE_H
#define STL_RESET_MONITOR_STATE_H

#include <node/stl_sample.hpp>
#include <rtamt/stl_specification.hpp>
#include <visitor/stl_visitor.hpp>

#include <map>
#include <queue>
#include <set>
#include <string>

namespace spec {

/**
 * @brief This class is used to reset the monitoring state of an existing STL specification.
 */
class StlResetMonitorState : public visitor::StlVisitor {
public:
  /**
   * @brief Reset the state of the STL Absolute Value node
   *
   * @param e STL Absolute Value node
   */
  void visit(node::StlAbsNode* e) override;
  /**
   * @brief Reset the state of the STL Addition node
   *
   * @param e STL Addition node
   */
  void visit(node::StlAdditionNode* e) override;
  /**
   * @brief Reset the state of the STL Bounded Always node
   *
   * @param e STL Bounded Always node
   */
  void visit(node::StlAlwaysBoundedNode* e) override;
  /**
   * @brief Reset the state of the STL Always node
   *
   * @param e STL Always node
   */
  void visit(node::StlAlwaysNode* e) override;
  /**
   * @brief Reset the state of the STL And node
   *
   * @param e STL And node
   */
  void visit(node::StlAndNode* e) override;
  /**
   * @brief Reset the state of the STL Constant node
   *
   * @param e STL Constant node
   */
  void visit(node::StlConstantNode* e) override;
  /**
   * @brief Reset the state of the STL Division node
   *
   * @param e STL Division node
   */
  void visit(node::StlDivisionNode* e) override;
  /**
   * @brief Reset the state of the STL Bounded Eventually node
   *
   * @param e STL Bounded Eventually node
   */
  void visit(node::StlEventuallyBoundedNode* e) override;
  /**
   * @brief Reset the state of the STL Eventually node
   *
   * @param e STL Eventually node
   */
  void visit(node::StlEventuallyNode* e) override;
  /**
   * @brief Reset the state of the STL Fall node
   *
   * @param e STL Fall node
   */
  void visit(node::StlFallNode* e) override;
  /**
   * @brief Reset the state of the STL Bounded Historically node
   *
   * @param e STL Bounded Historically node
   */
  void visit(node::StlHistoricallyBoundedNode* e) override;
  /**
   * @brief Reset the state of the STL Historically node
   *
   * @param e STL Historically node
   */
  void visit(node::StlHistoricallyNode* e) override;
  /**
   * @brief Reset the state of the STL If and Only If (Iff) node
   *
   * @param e STL If and Only If (Iff) node
   */
  void visit(node::StlIffNode* e) override;
  /**
   * @brief Reset the state of the STL Implies node
   *
   * @param e STL Implies node
   */
  void visit(node::StlImpliesNode* e) override;
  /**
   * @brief Reset the state of the STL Multiplication node
   *
   * @param e STL Multiplication node
   */
  void visit(node::StlMultiplicationNode* e) override;
  /**
   * @brief Reset the state of the STL Not node
   *
   * @param e STL Not node
   */
  void visit(node::StlNotNode* e) override;
  /**
   * @brief Reset the state of the STL Bounded Once node
   *
   * @param e STL Bounded Once node
   */
  void visit(node::StlOnceBoundedNode* e) override;
  /**
   * @brief Reset the state of the STL Once node
   *
   * @param e STL Once node
   */
  void visit(node::StlOnceNode* e) override;
  /**
   * @brief Reset the state of the STL Or node
   *
   * @param e STL Or node
   */
  void visit(node::StlOrNode* e) override;
  /**
   * @brief Reset the state of the STL Bounded Precedes node
   *
   * @param e STL Bounded Precedes node
   */
  void visit(node::StlPrecedesBoundedNode* e) override;
  /**
   * @brief Reset the state of the STL Predicate node
   *
   * @param e STL Predicate node
   */
  void visit(node::StlPredicateNode* e) override;
  /**
   * @brief Reset the state of the STL Rise node
   *
   * @param e STL Rise node
   */
  void visit(node::StlRiseNode* e) override;
  /**
   * @brief Reset the state of the STL Bounded Since node
   *
   * @param e STL Bounded Since node
   */
  void visit(node::StlSinceBoundedNode* e) override;
  /**
   * @brief Reset the state of the STL Since node
   *
   * @param e STL Since node
   */
  void visit(node::StlSinceNode* e) override;
  /**
   * @brief Reset the state of the STL Subtraction node
   *
   * @param e STL Subtraction node
   */
  void visit(node::StlSubtractionNode* e) override;
  /**
   * @brief Reset the state of the STL Bounded Until node
   *
   * @param e STL Bounded Until node
   */
  void visit(node::StlUntilBoundedNode* e) override;
  /**
   * @brief Reset the state of the STL Variable node
   *
   * @param e STL Variable node
   */
  void visit(node::StlVariableNode* e) override;
  /**
   * @brief Reset the state of the STL Exclusive Or (Xor) node
   *
   * @param e STL Exclusive Or (Xor) node
   */
  void visit(node::StlXorNode* e) override;
};
} // namespace spec

#endif // STL_RESET_MONITOR_STATE_H
