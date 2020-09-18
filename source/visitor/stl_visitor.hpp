#ifndef STL_VISITOR_H
#define STL_VISITOR_H

namespace node {
class StlAbsNode;
class StlAdditionNode;
class StlAlwaysBoundedNode;
class StlAlwaysNode;
class StlAndNode;
class StlCombinatorialBinaryNode;
class StlConstantNode;
class StlDivisionNode;
class StlEventuallyBoundedNode;
class StlEventuallyNode;
class StlFallNode;
class StlHistoricallyBoundedNode;
class StlHistoricallyNode;
class StlIffNode;
class StlImpliesNode;
class StlMultiplicationNode;
class StlNotNode;
class StlOnceBoundedNode;
class StlOnceNode;
class StlOrNode;
class StlPrecedesBoundedNode;
class StlPredicateNode;
class StlRiseNode;
class StlSinceBoundedNode;
class StlSinceNode;
class StlSubtractionNode;
class StlUntilBoundedNode;
class StlVariableNode;
class StlXorNode;
class StlNode;
} // namespace node

namespace visitor {

class StlVisitor {
public:
  virtual void visit(node::StlAbsNode* e)                 = 0;
  virtual void visit(node::StlAdditionNode* e)            = 0;
  virtual void visit(node::StlAlwaysBoundedNode* e)       = 0;
  virtual void visit(node::StlAlwaysNode* e)              = 0;
  virtual void visit(node::StlAndNode* e)                 = 0;
  virtual void visit(node::StlConstantNode* e)            = 0;
  virtual void visit(node::StlDivisionNode* e)            = 0;
  virtual void visit(node::StlEventuallyBoundedNode* e)   = 0;
  virtual void visit(node::StlEventuallyNode* e)          = 0;
  virtual void visit(node::StlFallNode* e)                = 0;
  virtual void visit(node::StlHistoricallyBoundedNode* e) = 0;
  virtual void visit(node::StlHistoricallyNode* e)        = 0;
  virtual void visit(node::StlIffNode* e)                 = 0;
  virtual void visit(node::StlImpliesNode* e)             = 0;
  virtual void visit(node::StlMultiplicationNode* e)      = 0;
  virtual void visit(node::StlNotNode* e)                 = 0;
  virtual void visit(node::StlOnceBoundedNode* e)         = 0;
  virtual void visit(node::StlOnceNode* e)                = 0;
  virtual void visit(node::StlOrNode* e)                  = 0;
  virtual void visit(node::StlPrecedesBoundedNode* e)     = 0;
  virtual void visit(node::StlPredicateNode* e)           = 0;
  virtual void visit(node::StlRiseNode* e)                = 0;
  virtual void visit(node::StlSinceBoundedNode* e)        = 0;
  virtual void visit(node::StlSinceNode* e)               = 0;
  virtual void visit(node::StlSubtractionNode* e)         = 0;
  virtual void visit(node::StlUntilBoundedNode* e)        = 0;
  virtual void visit(node::StlVariableNode* e)            = 0;
  virtual void visit(node::StlXorNode* e)                 = 0;
};

} // namespace visitor

#endif /* STL_VISITOR_H */
