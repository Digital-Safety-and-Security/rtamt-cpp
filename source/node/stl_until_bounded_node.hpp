/*
 * File:   stl_until_bounded_node.h
 * Author: nickovic
 *
 * Created on June 18, 2020
 */

#ifndef STL_UNTIL_BOUNDED_NODE_H
#define STL_UNTIL_BOUNDED_NODE_H

#include <node/stl_node.hpp>
#include <visitor/stl_visitor.hpp>

#include <cstdint>

namespace node {

/**
 * @brief This class defines the Node for the
 * STL Bounded Until operation and implements its
 * monitoring algorithm.
 *
 */

class StlUntilBoundedNode : public StlNode {
private:
  /**
   * @brief Lower bound (until[begin,end])
   *
   */
  uint64_t _begin;
  /**
   * @brief upper bound (until[begin,end])
   *
   */
  uint64_t _end;

public:
  /**
   * @brief Constructor, sets the bounded interval [begin, end] and the child STL formula child.
   *
   * @param begin Lower bound (until[begin,end] phi)
   * @param end Upper bound (until[begin,end] phi)
   * @param left_child STL node representing the subformula phi of the formula phi until[begin,end] psi.
   * @param right_child STL node representing the subformula phi of the formula phi until[begin,end] psi.
   */
  StlUntilBoundedNode(uint64_t begin, uint64_t end, StlNode* left_child, StlNode* right_child);
  /**
   * @brief Throws StlNodeException - StlUntilBoundedNode does not admit the monitoring algorithm.
   *
   * @return node::Sample
   */
  Sample update() override;
  /**
   * @brief Throws StlNodeException - StlUntilBoundedNode does not admit adding inputs.
   *
   * @param msg p_msg:...
   */
  void addNewInput(Sample left, Sample right);
  /**
   * @brief Accepts STL Visitor and calls its visit function.
   *
   * @param v STL Visitor
   */
  void accept(visitor::StlVisitor& v) override;
  /**
   * @brief Returns the lower bound begin.
   *
   * @return uint64_t
   */
  uint64_t begin() { return _begin; }
  /**
   * @brief Returns the upper bound end.
   *
   * @return uint64_t
   */
  uint64_t end() { return _end; }

  ~StlUntilBoundedNode() override = default;

  /**
   * @brief Reset the monitor state of STL Bounded Until node.
   *
   */
  void reset() override {}
};

} // namespace node

#endif /* STL_UNTIL_BOUNDED_NODE_H */
