#ifndef STL_CONSTANT_H
#define STL_CONSTANT_H

#include <node/stl_node.hpp>
#include <node/stl_sample.hpp>
#include <visitor/stl_visitor.hpp>

namespace node {

/**
 * @brief This class defines the Node for the
 * STL Constant operation and implements the monitoring algorithm
 * for computing it.
 *
 */

class StlConstantNode : public StlNode {
private:
  /**
   * @brief Constant value
   *
   */
  double val;
  /**
   * @brief Curent logical time.
   *
   */
  long time;

public:
  /**
   * @brief Constructor that sets the constant value
   *
   * @param val Constant value.
   */
  explicit StlConstantNode(double val);
  /**
   * @brief Monitoring algorithm computing the constant value
   *
   * @return node::Sample
   */
  Sample update() override;
  /**
   * @brief Accepts STL Visitor and calls its visit function.
   *
   * @param v STL Visitor
   */
  void accept(visitor::StlVisitor& v) override;
  /**
   * @brief Getter returning the constant value.
   *
   * @return double
   */
  double value() { return val; }

  ~StlConstantNode() override = default;

  /**
   * @brief Reset the internal state of STL Constant node.
   *
   */
  void reset() override;
};

} // namespace node

#endif /* STL_NOT_H */
