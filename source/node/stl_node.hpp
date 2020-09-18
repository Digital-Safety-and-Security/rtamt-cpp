#ifndef STL_NODE_H
#define STL_NODE_H

#include <node/stl_sample.hpp>
#include <visitor/stl_visitor.hpp>

#include <cstdint>
#include <set>
#include <string>
#include <vector>

namespace node {

/**
 * @brief This abstract class defines (1) a common structure for
 * representing STL operators, (2) enables representing arbitrary
 * STL specifications as a parse tree, and (3) provides monitoring
 * (evaluation) algorithm for STL operators.
 *
 */
class StlNode {
public:
  /**
   * @brief STL Node constructor
   *
   */
  StlNode()               = default;
  StlNode(const StlNode&) = delete;
  StlNode(StlNode&&)      = delete;
  StlNode& operator=(const StlNode&) = delete;
  StlNode& operator=(StlNode&&) = delete;
  /**
   * @brief STL Node distructor
   *
   */
  virtual ~StlNode();
  /**
   * @brief Computes the monitoring evaluation (robustness degree) of a
   * specific operator in the current time step, based on the current
   * and past inputs. Pure virtual function that must be implemented by
   * all STL past operators.
   *
   * @return node::Sample
   */
  virtual Sample update() = 0;
  /**
   * @brief Returns the string containing textual representation
   * of the STL sub-formula represented by the node.
   *
   * @return std::string
   */
  std::string getName();
  /**
   * @brief Setter for the bounded horizon of the STl sub-formula
   * represented by the node.
   *
   * @param horizon Bounded horizon of the STL sub-formula represented
   * by the node.
   */
  void horizon(uint64_t horizon);
  /**
   * @brief Getter for the bounded horizon of the STl sub-formula
   * represented by the node.
   *
   * @return uint64_t
   */
  uint64_t horizon();
  /**
   * @brief Returns te pointer to the index-th child node
   *
   * @param index
   * @return node::StlNode*
   */
  StlNode* getChild(int index);

  /**
   * @brief Method that allows the STL node to accept a visitor of
   * type StlVisitor. Pure virtual function that is implemented
   * by concrete STL operator nodes.
   *
   * @param v STL visitor
   */
  virtual void accept(visitor::StlVisitor& v) = 0;

  /**
   * @brief Reset the internal state of the STL node.
   *
   */
  virtual void reset() = 0;

  std::set<std::string> in_vars() { return _in_vars; }

  std::set<std::string> out_vars() { return _out_vars; }

private:
  /**
   * @brief List of pointers to the chidren of the nodes.
   *
   */
  std::vector<StlNode*> children;
  /**
   * @brief Bounded horizon of the STL sub-formula represented by the node.
   *
   */
  uint64_t _horizon{0};

protected:
  /**
   * @brief Name of the STL sub-formula represented by the node.
   *
   */
  std::string name;

  std::set<std::string> _in_vars;
  std::set<std::string> _out_vars;

  /**
   * @brief Adds child to the list of the children to the node.
   *
   * @param child Pointer to the STL node to be added to the current node's children list.
   */
  void addChild(StlNode* child);

  void initIOType();
};

} // namespace node

#endif /* STL_NODE_H */
