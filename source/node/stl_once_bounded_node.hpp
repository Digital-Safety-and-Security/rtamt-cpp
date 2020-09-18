#ifndef STL_ONCE_BOUNDED_NODE_H
#define STL_ONCE_BOUNDED_NODE_H

#include <node/stl_node.hpp>
#include <node/stl_sample.hpp>
#include <visitor/stl_visitor.hpp>

#include <cstdint>

#include <boost/circular_buffer.hpp>

namespace node {

/**
 * @brief This class defines the Node for the
 * STL Bounded Once operation and implements its
 * monitoring algorithm.
 *
 */

class StlOnceBoundedNode : public StlNode {
private:
  /**
   * @brief Lower bound (once[begin,end] phi)
   *
   */
  uint64_t _begin;
  /**
   * @brief Upper bound (once[begin,end] phi)
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
   * @param begin Lower bound (once[begin,end] phi)
   * @param end Upper bound (once[begin,end] phi)
   * @param child STL node representing the subformula phi of the formula once[begin,end] phi.
   */
  StlOnceBoundedNode(uint64_t begin, uint64_t end, StlNode* child, bool init_monitor = false);
  /**
   * @brief Monitoring algorithm computing the bounded once operation.
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

  ~StlOnceBoundedNode() override = default;

  /**
   * @brief Reset the monitor state of STL Bounded Once node.
   *
   */
  void reset() override;
};

} // namespace node

#endif /* STL_ONCE_BOUNDED_NODE_H */
