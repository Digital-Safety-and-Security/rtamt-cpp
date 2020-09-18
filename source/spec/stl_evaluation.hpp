#ifndef STL_EVALUATION_H
#define STL_EVALUATION_H

#include <node/stl_sample.hpp>
#include <rtamt/stl_specification.hpp>
#include <visitor/stl_visitor.hpp>

#include <map>
#include <queue>
#include <set>
#include <string>

namespace spec {

/**
 * @brief This class is used to evaluate (monitor) an STL specification. It is initialized with the pointer to the parse
 * tree of the specification and a set of strings containing all the names of free variables appearing in the
 * specification.
 */
class StlEvaluation : public visitor::StlVisitor {
private:
  /**
   * @brief map of (variable name, current sample) pairs
   *
   */
  std::map<std::string, node::Sample> _var_value_map;

  std::set<std::string> _in_vars;
  std::set<std::string> _out_vars;
  /**
   * @brief pointer to the STL specification
   *
   */
  node::StlNode* _root;

  /**
   * @brief output result (in form of a sample)
   *
   */
  node::Sample _out;

public:
  /**
   * @brief Constructs the STL Evaluation class and initializes it with the pointer to the STL specification parse tree
   * and a set of free variable names appearing in the specification.
   *
   * @param root STL specification parse tree
   * @param vars set of names (strings) of free variables appearing in the STL specification
   */
  StlEvaluation(node::StlNode* root, const std::set<std::string>& vars,
                const std::map<std::string, rtamt::StlIOType>& var_io_type_map);
  /**
   * @brief Evaluates STL Absolute Value node
   *
   * @param e STL Absolute Value node
   */
  void visit(node::StlAbsNode* e) override;
  /**
   * @brief Evaluates STL Addition node
   *
   * @param e STL Addition node
   */
  void visit(node::StlAdditionNode* e) override;
  /**
   * @brief Evaluates STL Bounded Always node
   *
   * @param e STL Bounded Always node
   */
  void visit(node::StlAlwaysBoundedNode* e) override;
  /**
   * @brief Evaluates STL Always node
   *
   * @param e STL Always node
   */
  void visit(node::StlAlwaysNode* e) override;
  /**
   * @brief Evaluates STL And node
   *
   * @param e STL And node
   */
  void visit(node::StlAndNode* e) override;
  /**
   * @brief Evaluates STL Constant node
   *
   * @param e STL Constant node
   */
  void visit(node::StlConstantNode* e) override;
  /**
   * @brief Evaluates STL Division node
   *
   * @param e STL Division node
   */
  void visit(node::StlDivisionNode* e) override;
  /**
   * @brief Evaluates STL Bounded Eventually node
   *
   * @param e STL Bounded Eventually node
   */
  void visit(node::StlEventuallyBoundedNode* e) override;
  /**
   * @brief Evaluates STL Eventually node
   *
   * @param e STL Eventually node
   */
  void visit(node::StlEventuallyNode* e) override;
  /**
   * @brief Evaluates STL Fall node
   *
   * @param e STL Fall node
   */
  void visit(node::StlFallNode* e) override;
  /**
   * @brief Evaluates STL Bounded Historically node
   *
   * @param e STL Bounded Historically node
   */
  void visit(node::StlHistoricallyBoundedNode* e) override;
  /**
   * @brief Evaluates STL Historically node
   *
   * @param e STL Historically node
   */
  void visit(node::StlHistoricallyNode* e) override;
  /**
   * @brief Evaluates STL If and Only If (Iff) node
   *
   * @param e STL If and Only If (Iff) node
   */
  void visit(node::StlIffNode* e) override;
  /**
   * @brief Evaluates STL Implies node
   *
   * @param e STL Implies node
   */
  void visit(node::StlImpliesNode* e) override;
  /**
   * @brief Evaluates STL Multiplication node
   *
   * @param e STL Multiplication node
   */
  void visit(node::StlMultiplicationNode* e) override;
  /**
   * @brief Evaluates STL Not node
   *
   * @param e STL Not node
   */
  void visit(node::StlNotNode* e) override;
  /**
   * @brief Evaluates STL Bounded Once node
   *
   * @param e STL Bounded Once node
   */
  void visit(node::StlOnceBoundedNode* e) override;
  /**
   * @brief Evaluates STL Once node
   *
   * @param e STL Once node
   */
  void visit(node::StlOnceNode* e) override;
  /**
   * @brief Evaluates STL Or node
   *
   * @param e STL Or node
   */
  void visit(node::StlOrNode* e) override;
  /**
   * @brief Evaluates STL Bounded Precedes node
   *
   * @param e STL Bounded Precedes node
   */
  void visit(node::StlPrecedesBoundedNode* e) override;
  /**
   * @brief Evaluates STL Predicate node
   *
   * @param e STL Predicate node
   */
  void visit(node::StlPredicateNode* e) override;
  /**
   * @brief Evaluates STL Rise node
   *
   * @param e STL Rise node
   */
  void visit(node::StlRiseNode* e) override;
  /**
   * @brief Evaluates STL Bounded Since node
   *
   * @param e STL Bounded Since node
   */
  void visit(node::StlSinceBoundedNode* e) override;
  /**
   * @brief Evaluates STL Since node
   *
   * @param e STL Since node
   */
  void visit(node::StlSinceNode* e) override;
  /**
   * @brief Evaluates STL Subtraction node
   *
   * @param e STL Subtraction node
   */
  void visit(node::StlSubtractionNode* e) override;
  /**
   * @brief Evaluates STL Bounded Until node
   *
   * @param e STL Bounded Until node
   */
  void visit(node::StlUntilBoundedNode* e) override;
  /**
   * @brief Evaluates STL Variable node
   *
   * @param e STL Variable node
   */
  void visit(node::StlVariableNode* e) override;
  /**
   * @brief Evaluates STL Exclusive Or (Xor) node
   *
   * @param e STL Exclusive Or (Xor) node
   */
  void visit(node::StlXorNode* e) override;
  /**
   * @brief Return the update (monitoring, evaluation) result of the STL specification at the given logical time
   * and with respect to the given inputs.
   *
   * @param time Current logical time
   * @param inputs A vector of Input (name, value) inputs
   * @return double
   */
  double update(uint64_t time, const std::vector<rtamt::Input>& inputs);
};
} // namespace spec

#endif // STL_EVALUATION_H
