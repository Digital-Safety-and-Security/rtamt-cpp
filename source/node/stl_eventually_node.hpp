#ifndef STL_EVENTUALLY_NODE_H
#define STL_EVENTUALLY_NODE_H

#include <node/stl_node.hpp>
#include <node/stl_sample.hpp>
#include <visitor/stl_visitor.hpp>

namespace node {

class StlEventuallyNode : public StlNode {
private:
  Sample in;
  Sample prev_out;

public:
  explicit StlEventuallyNode(StlNode* child);
  Sample update() override;
  void   addNewInput(Sample sample);
  void   accept(visitor::StlVisitor& v) override;

  ~StlEventuallyNode() override = default;

  /**
   * @brief Reset the monitor state of STL Eventually node.
   *
   */
  void reset() override;
};

} // namespace node

#endif /* STL_EVENTUALLY_NODE_H */
