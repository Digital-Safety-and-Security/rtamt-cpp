#ifndef STL_EVENTUALLY_BOUNDED_NODE_H
#define STL_EVENTUALLY_BOUNDED_NODE_H

#include <node/stl_node.hpp>
#include <visitor/stl_visitor.hpp>

#include <cstdint>

namespace node {

/**
 * @brief This class defines the Node for the
 * STL Bounded Eventually operation.
 *
 */
class StlEventuallyBoundedNode : public StlNode {
private:
  /**
   * @brief Lower bound (eventually[begin,end] phi)
   *
   */
  uint64_t _begin;
  /**
   * @brief Upper bound (eventually[begin,end] phi)
   *
   */
  uint64_t _end;

public:
  /**
   * @brief Constructor, sets the bounded interval [begin, end] and the child STL formula child.
   *
   * @param begin Lower bound (eventually[begin,end] phi)
   * @param end Upper bound (eventually[begin,end] phi)
   * @param child STL node representing the subformula phi of the formula eventually[begin,end] phi.
   */
  StlEventuallyBoundedNode(uint64_t begin, uint64_t end, StlNode* child);
  /**
   * @brief Throws StlNodeException - StlEventuallyBoundedNode does not admit the monitoring algorithm.
   *
   * @return node::Sample
   */
  Sample update() override;
  /**
   * @brief Throws StlNodeException - StlEventuallyBoundedNode does not admit adding inputs.
   *
   * @param msg p_msg:...
   */
  void addNewInput(Sample msg);
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

  ~StlEventuallyBoundedNode() override = default;

  /**
   * @brief Reset the monitor state of STL Bounded Precedes node.
   *
   */
  void reset() override{};
};

} // namespace node

#endif /* STL_EVENTUALLY_BOUNDED_NODE_H */
