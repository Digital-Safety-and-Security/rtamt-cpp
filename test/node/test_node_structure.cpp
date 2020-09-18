#include <string>
#include <gtest/gtest.h>
#include <node/stl_constant_node.hpp>
#include <node/stl_variable_node.hpp>
#include <node/stl_abs_node.hpp>
#include <node/stl_addition_node.hpp>
#include <node/stl_always_bounded_node.hpp>
#include <node/stl_always_node.hpp>
#include <node/stl_and_node.hpp>
#include <node/stl_division_node.hpp>
#include <node/stl_eventually_bounded_node.hpp>
#include <node/stl_eventually_node.hpp>
#include <node/stl_fall_node.hpp>
#include <node/stl_historically_bounded_node.hpp>
#include <node/stl_historically_node.hpp>
#include <node/stl_iff_node.hpp>
#include <node/stl_implies_node.hpp>
#include <node/stl_multiplication_node.hpp>
#include <node/stl_not_node.hpp>
#include <node/stl_once_bounded_node.hpp>
#include <node/stl_once_node.hpp>
#include <node/stl_or_node.hpp>
#include <node/stl_precedes_bounded_node.hpp>
#include <node/stl_predicate_node.hpp>
#include <node/stl_rise_node.hpp>
#include <node/stl_since_bounded_node.hpp>
#include <node/stl_since_node.hpp>
#include <node/stl_subtraction_node.hpp>
#include <node/stl_until_bounded_node.hpp>
#include <node/stl_xor_node.hpp>
#include <node/stl_comp_op.hpp>


using namespace node;

TEST (stl_node_structure, constant) {
    double val = 5;
    StlConstantNode *node = new StlConstantNode(val);
    EXPECT_EQ(std::to_string(val), node->getName());
    delete node;
}

TEST (stl_node_structure, variable) {
    const std::string name = "request"; 
    StlVariableNode *node = new StlVariableNode(name);
    EXPECT_EQ(name, node->getName());
    delete node;
}

TEST (stl_node_structure, abs) {
    const std::string name = "request"; 
    StlVariableNode *var = new StlVariableNode(name);
    StlAbsNode *node = new StlAbsNode(var);
    
    const std::string expected = "abs(request)";
    
    EXPECT_EQ(expected, node->getName());
    delete node;
}

TEST (stl_node_structure, addition) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlAdditionNode *node = new StlAdditionNode(var_1, var_2);
    
    const std::string expected = "(request)+(grant)";
    
    EXPECT_EQ(expected, node->getName());
    delete node;
}

TEST (stl_node_structure, subtraction) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlSubtractionNode *node = new StlSubtractionNode(var_1, var_2);
    
    const std::string expected = "(request)-(grant)";
    
    EXPECT_EQ(expected, node->getName());
    delete node;
}

TEST (stl_node_structure, multiplication) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlMultiplicationNode *node = new StlMultiplicationNode(var_1, var_2);
    
    const std::string expected = "(request)*(grant)";
    
    EXPECT_EQ(expected, node->getName());
    delete node;
}

TEST (stl_node_structure, division) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlDivisionNode *node = new StlDivisionNode(var_1, var_2);
    
    const std::string expected = "(request)/(grant)";
    
    EXPECT_EQ(expected, node->getName());
    delete node;
}

TEST (stl_node_structure, predicate_leq) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlPredicateNode *node = new StlPredicateNode(StlComparisonOperator::LEQ, var_1, var_2);
    
    const std::string expected = "(request)<=(grant)";
    
    EXPECT_EQ(expected, node->getName());
    delete node;
}

TEST (stl_node_structure, predicate_less) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlPredicateNode *node = new StlPredicateNode(StlComparisonOperator::LESS, var_1, var_2);
    
    const std::string expected = "(request)<(grant)";
    
    EXPECT_EQ(expected, node->getName());
    delete node;
}

TEST (stl_node_structure, predicate_geq) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlPredicateNode *node = new StlPredicateNode(StlComparisonOperator::GEQ, var_1, var_2);
    
    const std::string expected = "(request)>=(grant)";
    
    EXPECT_EQ(expected, node->getName());
    delete node;
}

TEST (stl_node_structure, predicate_greater) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlPredicateNode *node = new StlPredicateNode(StlComparisonOperator::GREATER, var_1, var_2);
    
    const std::string expected = "(request)>(grant)";
    
    EXPECT_EQ(expected, node->getName());
    delete node;
}

TEST (stl_node_structure, predicate_eq) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlPredicateNode *node = new StlPredicateNode(StlComparisonOperator::EQUAL, var_1, var_2);
    
    const std::string expected = "(request)==(grant)";
    
    EXPECT_EQ(expected, node->getName());
    delete node;
}

TEST (stl_node_structure, predicate_neq) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlPredicateNode *node = new StlPredicateNode(StlComparisonOperator::NEQ, var_1, var_2);
    
    const std::string expected = "(request)!=(grant)";
    
    EXPECT_EQ(expected, node->getName());
    delete node;
}

TEST (stl_node_structure, not) {
    const std::string name = "request"; 
    StlVariableNode *var = new StlVariableNode(name);
    StlNotNode *node = new StlNotNode(var);
    
    const std::string expected = "not(request)";
    
    EXPECT_EQ(expected, node->getName());
    delete node;
}

TEST (stl_node_structure, conjunction) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlAndNode *node = new StlAndNode(var_1, var_2);
    
    const std::string expected = "(request)and(grant)";
    
    EXPECT_EQ(expected, node->getName());
    delete node;
}

TEST (stl_node_structure, disjunction) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlOrNode *node = new StlOrNode(var_1, var_2);
    
    const std::string expected = "(request)or(grant)";
    
    EXPECT_EQ(expected, node->getName());
    delete node;
}

TEST (stl_node_structure, implication) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlImpliesNode *node = new StlImpliesNode(var_1, var_2);
    
    const std::string expected = "(request)->(grant)";
    
    EXPECT_EQ(expected, node->getName());
    delete node;
}

TEST (stl_node_structure, iff) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlIffNode *node = new StlIffNode(var_1, var_2);
    
    const std::string expected = "(request)iff(grant)";
    
    EXPECT_EQ(expected, node->getName());
    delete node;
}

TEST (stl_node_structure, xor) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlXorNode *node = new StlXorNode(var_1, var_2);
    
    const std::string expected = "(request)xor(grant)";
    
    EXPECT_EQ(expected, node->getName());
    delete node;
}

TEST (stl_node_structure, rise) {
    const std::string name = "request"; 
    StlVariableNode *var = new StlVariableNode(name);
    StlRiseNode *node = new StlRiseNode(var);
    
    const std::string expected = "rise(request)";
    
    EXPECT_EQ(expected, node->getName());
    delete node;
}

TEST (stl_node_structure, fall) {
    const std::string name = "request"; 
    StlVariableNode *var = new StlVariableNode(name);
    StlFallNode *node = new StlFallNode(var);
    
    const std::string expected = "fall(request)";
    
    EXPECT_EQ(expected, node->getName());
    delete node;
}

TEST (stl_node_structure, once) {
    const std::string name = "request"; 
    StlVariableNode *var = new StlVariableNode(name);
    StlOnceNode *node = new StlOnceNode(var);
    
    const std::string expected = "once(request)";
    
    EXPECT_EQ(expected, node->getName());
    delete node;
}

TEST (stl_node_structure, historically) {
    const std::string name = "request"; 
    StlVariableNode *var = new StlVariableNode(name);
    StlHistoricallyNode *node = new StlHistoricallyNode(var);
    
    const std::string expected = "historically(request)";
    
    EXPECT_EQ(expected, node->getName());
    delete node;
}

TEST (stl_node_structure, eventually) {
    const std::string name = "request"; 
    StlVariableNode *var = new StlVariableNode(name);
    StlEventuallyNode *node = new StlEventuallyNode(var);
    
    const std::string expected = "eventually(request)";
    
    EXPECT_EQ(expected, node->getName());
    delete node;
}

TEST (stl_node_structure, always) {
    const std::string name = "request"; 
    StlVariableNode *var = new StlVariableNode(name);
    StlAlwaysNode *node = new StlAlwaysNode(var);
    
    const std::string expected = "always(request)";
    
    EXPECT_EQ(expected, node->getName());
    delete node;
}

TEST (stl_node_structure, since) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlSinceNode *node = new StlSinceNode(var_1, var_2);
    
    const std::string expected = "(request)since(grant)";
    
    EXPECT_EQ(expected, node->getName());
    delete node;
}

TEST (stl_node_structure, once_bounded) {
    const std::string name = "request"; 
    StlVariableNode *var = new StlVariableNode(name);
    StlOnceBoundedNode *node = new StlOnceBoundedNode(1, 2, var);
    
    const std::string expected = "once[1,2](request)";
    
    EXPECT_EQ(expected, node->getName());
    delete node;
}

TEST (stl_node_structure, historically_bounded) {
    const std::string name = "request"; 
    StlVariableNode *var = new StlVariableNode(name);
    StlHistoricallyBoundedNode *node = new StlHistoricallyBoundedNode(0, 3, var);
    
    const std::string expected = "historically[0,3](request)";
    
    EXPECT_EQ(expected, node->getName());
    delete node;
}

TEST (stl_node_structure, eventually_bounded) {
    const std::string name = "request"; 
    StlVariableNode *var = new StlVariableNode(name);
    StlEventuallyBoundedNode *node = new StlEventuallyBoundedNode(4, 5, var);
    
    const std::string expected = "eventually[4,5](request)";
    
    EXPECT_EQ(expected, node->getName());
    delete node;
}

TEST (stl_node_structure, always_bounded) {
    const std::string name = "request"; 
    StlVariableNode *var = new StlVariableNode(name);
    StlAlwaysBoundedNode *node = new StlAlwaysBoundedNode(0, 3, var);
    
    const std::string expected = "always[0,3](request)";
    
    EXPECT_EQ(expected, node->getName());
    delete node;
}

TEST (stl_node_structure, since_bounded) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlSinceBoundedNode *node = new StlSinceBoundedNode(1, 2, var_1, var_2);
    
    const std::string expected = "(request)since[1,2](grant)";
    
    EXPECT_EQ(expected, node->getName());
    delete node;
}

TEST (stl_node_structure, until_bounded) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlUntilBoundedNode *node = new StlUntilBoundedNode(1, 2, var_1, var_2);
    
    const std::string expected = "(request)until[1,2](grant)";
    
    EXPECT_EQ(expected, node->getName());
    delete node;
}

TEST (stl_node_structure, precedes_bounded) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlPrecedesBoundedNode *node = new StlPrecedesBoundedNode(1, 2, var_1, var_2);
    
    const std::string expected = "(request)precedes[1,2](grant)";
    
    EXPECT_EQ(expected, node->getName());
    delete node;
}
