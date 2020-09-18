#ifndef STL_HISTORICALLY_BOUNDED_NODE_H
#define STL_HISTORICALLY_BOUNDED_NODE_H

#include <node/stl_node.hpp>
#include <node/stl_sample.hpp>
#include <visitor/stl_visitor.hpp>

#include <boost/circular_buffer.hpp>

namespace node {

/**
 * @brief This class defines the Node for the
 * STL Bounded Historically operation and implements its
 * monitoring algorithm.
 *
 */

class StlHistoricallyBoundedNode : public StlNode {
private:
  /**
   * @brief Lower bound (historically[begin,end] phi)
   *
   */
  uint64_t _begin;
  /**
   * @brief Upper bound (historically[begin,end] phi)
   *
   */
  uint64_t _end;
  /**
   * @brief Current input sample
   *
   */
  Sample in;
  /**
   * @brief Circular buffer containing end previous input samples.
   *
   */
  boost::circular_buffer<Sample> buffer;

public:
  /**
   * @brief Constructor, sets the bounded interval [begin, end] and the child STL formula child.
   *
   * @param begin Lower bound (historically[begin,end] phi)
   * @param end Upper bound (historically[begin,end] phi)
   * @param child STL node representing the subformula phi of the formula historically[begin,end] phi.
   */
  StlHistoricallyBoundedNode(uint64_t begin, uint64_t end, StlNode* child, bool init_monitor = false);
  /**
   * @brief Monitoring algorithm computing the bounded historically operation.
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

  ~StlHistoricallyBoundedNode() override = default;

  /**
   * @brief Reset the monitor state of STL Bounded Historically node.
   *
   */
  void reset() override;
};

} // namespace node

#endif /* STL_HISTORICALLY_BOUNDED_NODE_H */
