#ifndef STL_SINCE_BOUNDED_NODE_H
#define STL_SINCE_BOUNDED_NODE_H

#include <node/stl_node.hpp>
#include <node/stl_sample.hpp>
#include <visitor/stl_visitor.hpp>

#include <array>
#include <cstdint>

#include <boost/circular_buffer.hpp>

namespace node {

/**
 * @brief This class defines the Node for the
 * STL Bounded Since operation and implements its
 * monitoring algorithm.
 *
 */

class StlSinceBoundedNode : public StlNode {
private:
  /**
   * @brief Lower bound (since[begin,end] phi)
   *
   */
  uint64_t _begin;
  /**
   * @brief Lower bound (since[begin,end] phi)
   *
   */
  uint64_t _end;
  /**
   * @brief Current input sample
   *
   */
  Sample in;
  /**
   * @brief Arrays of two circular buffer containing end previous input samples from the left and right
   * children.
   *
   */
  std::array<boost::circular_buffer<Sample>, 2> buffer;

public:
  /**
   * @brief Constructor, sets the bounded interval [begin, end] and the child STL formula child.
   *
   * @param begin Lower bound (since[begin,end] phi)
   * @param end Upper bound (since[begin,end] phi)
   * @param left_child STL node representing the subformula phi of the formula phi since[begin,end] psi.
   * @param right_child STL node representing the subformula phi of the formula phi since[begin,end] psi.
   */
  StlSinceBoundedNode(uint64_t begin, uint64_t end, StlNode* left_child, StlNode* right_child,
                      bool init_monitor = false);
  /**
   * @brief Monitoring algorithm computing the bounded since operation.
   *
   * @return node::Sample
   */
  Sample update() override;
  /**
   * @brief Updates the input with new input samples (left and right).
   *
   * @param left left input sample.
   * @param right right input sample.
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

  ~StlSinceBoundedNode() override = default;

  /**
   * @brief Reset the monitor state of STL Bounded Since node.
   *
   */
  void reset() override;
};

} // namespace node

#endif /* STL_SINCE_BOUNDED_NODE_H */
