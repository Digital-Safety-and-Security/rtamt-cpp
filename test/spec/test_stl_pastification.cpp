#include <string>
#include <limits>
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
#include <node/stl_sample.hpp>
#include <spec/stl_pastification.hpp>
#include <rtamt/stl_specification.hpp>


using namespace rtamt;
using namespace spec;
using namespace node;

class StlPastificationTest : public ::testing::Test {
    protected:
        StlPastification pastification;

};


TEST_F (StlPastificationTest, constant) {
    double val = 5;
    StlConstantNode *node = new StlConstantNode(val);
    
    node->horizon(0);
    StlNode *out = pastification.pastify(node);
    std::string computed = out->getName();
    const std::string expected = std::to_string(val);
    
    EXPECT_EQ(expected, computed);
    
    delete out;
    
    node->horizon(5);
    out = pastification.pastify(node);
    computed = out->getName();
    
    EXPECT_EQ(expected, computed);
    
    delete node;
    delete out;
    
}

TEST_F (StlPastificationTest, variable) {
    const std::string name{"req"};
    std::set<std::string> set {name}; 

    StlVariableNode *node = new StlVariableNode(name);
    
    node->horizon(0);
    StlNode *out = pastification.pastify(node);
    std::string computed = out->getName();
    const std::string expected_1 = "req";
    
    EXPECT_EQ(expected_1, computed);
    
    delete out;
    
    node->horizon(5);
    out = pastification.pastify(node);
    computed = out->getName();
    const std::string expected_2 = "once[5,5](req)";
    
    EXPECT_EQ(expected_2, computed);
    
    delete node;
    delete out;
}

TEST_F (StlPastificationTest, abs) {
    const std::string name{"req"};
    std::set<std::string> set {name}; 

    StlVariableNode *tmp = new StlVariableNode(name);
    StlAbsNode *node = new StlAbsNode(tmp);
    
    node->horizon(0);
    StlNode *out = pastification.pastify(node);
    std::string computed = out->getName();
    const std::string expected_1 = "abs(req)";
    
    EXPECT_EQ(expected_1, computed);
    
    delete out;
    
    tmp->horizon(5);
    node->horizon(5);
    out = pastification.pastify(node);
    computed = out->getName();
    const std::string expected_2 = "abs(once[5,5](req))";
    
    EXPECT_EQ(expected_2, computed);
    
    delete node;
    delete out;
}

TEST_F (StlPastificationTest, addition) {
    const std::string name_1{"req"};
    const std::string name_2{"gnt"};
    std::set<std::string> set {name_1, name_2}; 

    StlVariableNode *tmp_1 = new StlVariableNode(name_1);
    StlVariableNode *tmp_2 = new StlVariableNode(name_2);
    StlAdditionNode *node = new StlAdditionNode(tmp_1, tmp_2);
        
    node->horizon(0);
    StlNode *out = pastification.pastify(node);
    std::string computed = out->getName();
    const std::string expected_1 = "(req)+(gnt)";
    
    EXPECT_EQ(expected_1, computed);
    
    delete out;
    delete node;
}

TEST_F (StlPastificationTest, subtraction) {
    const std::string name_1{"req"};
    const std::string name_2{"gnt"};
    std::set<std::string> set {name_1, name_2}; 

    StlVariableNode *tmp_1 = new StlVariableNode(name_1);
    StlVariableNode *tmp_2 = new StlVariableNode(name_2);
    StlSubtractionNode *node = new StlSubtractionNode(tmp_1, tmp_2);
    
    node->horizon(0);
    StlNode *out = pastification.pastify(node);
    std::string computed = out->getName();
    const std::string expected_1 = "(req)-(gnt)";
    
    EXPECT_EQ(expected_1, computed);
    
    delete out;
    delete node;
    
}

TEST_F (StlPastificationTest, multiplication) {
    const std::string name_1{"req"};
    const std::string name_2{"gnt"};
    std::set<std::string> set {name_1, name_2}; 

    StlVariableNode *tmp_1 = new StlVariableNode(name_1);
    StlVariableNode *tmp_2 = new StlVariableNode(name_2);
    StlMultiplicationNode *node = new StlMultiplicationNode(tmp_1, tmp_2);
    
    node->horizon(0);
    StlNode *out = pastification.pastify(node);
    std::string computed = out->getName();
    const std::string expected_1 = "(req)*(gnt)";
    
    EXPECT_EQ(expected_1, computed);
    
    delete out;
    delete node;
}

TEST_F (StlPastificationTest, division) {
    const std::string name_1{"req"};
    const std::string name_2{"gnt"};
    std::set<std::string> set {name_1, name_2}; 

    StlVariableNode *tmp_1 = new StlVariableNode(name_1);
    StlVariableNode *tmp_2 = new StlVariableNode(name_2);
    StlDivisionNode *node = new StlDivisionNode(tmp_1, tmp_2);
    
    node->horizon(0);
    StlNode *out = pastification.pastify(node);
    std::string computed = out->getName();
    const std::string expected_1 = "(req)/(gnt)";
    
    EXPECT_EQ(expected_1, computed);
    
    delete out;
    delete node;
}

TEST_F (StlPastificationTest, predicate_leq) {
    const std::string name_1{"req"};
    const std::string name_2{"gnt"};
    std::set<std::string> set {name_1, name_2}; 

    StlVariableNode *tmp_1 = new StlVariableNode(name_1);
    StlVariableNode *tmp_2 = new StlVariableNode(name_2);
    StlPredicateNode *node = new StlPredicateNode(StlComparisonOperator::LEQ, tmp_1, tmp_2);

    node->horizon(0);
    StlNode *out = pastification.pastify(node);
    std::string computed = out->getName();
    const std::string expected_1 = "(req)<=(gnt)";
    
    EXPECT_EQ(expected_1, computed);
    
    delete out;
    
    node->horizon(5);
    out = pastification.pastify(node);
    computed = out->getName();
    const std::string expected_2 = "(once[5,5](req))<=(once[5,5](gnt))";
    
    EXPECT_EQ(expected_2, computed);
    
    delete node;
    delete out;
}

TEST_F (StlPastificationTest, predicate_less) {
    const std::string name_1{"req"};
    const std::string name_2{"gnt"};
    std::set<std::string> set {name_1, name_2}; 

    StlVariableNode *tmp_1 = new StlVariableNode(name_1);
    StlVariableNode *tmp_2 = new StlVariableNode(name_2);
    StlPredicateNode *node = new StlPredicateNode(StlComparisonOperator::LESS, tmp_1, tmp_2);   
    
    node->horizon(0);
    StlNode *out = pastification.pastify(node);
    std::string computed = out->getName();
    const std::string expected_1 = "(req)<(gnt)";
    
    EXPECT_EQ(expected_1, computed);
    
    delete out;
    delete node;
}

TEST_F (StlPastificationTest, predicate_geq) {
    const std::string name_1{"req"};
    const std::string name_2{"gnt"};
    std::set<std::string> set {name_1, name_2}; 

    StlVariableNode *tmp_1 = new StlVariableNode(name_1);
    StlVariableNode *tmp_2 = new StlVariableNode(name_2);
    StlPredicateNode *node = new StlPredicateNode(StlComparisonOperator::GEQ, tmp_1, tmp_2);    
    
    node->horizon(0);
    StlNode *out = pastification.pastify(node);
    std::string computed = out->getName();
    const std::string expected_1 = "(req)>=(gnt)";
    
    EXPECT_EQ(expected_1, computed);
    
    delete out;
    delete node;
    
}

TEST_F (StlPastificationTest, predicate_greater) {
    const std::string name_1{"req"};
    const std::string name_2{"gnt"};
    std::set<std::string> set {name_1, name_2}; 

    StlVariableNode *tmp_1 = new StlVariableNode(name_1);
    StlVariableNode *tmp_2 = new StlVariableNode(name_2);
    StlPredicateNode *node = new StlPredicateNode(StlComparisonOperator::GREATER, tmp_1, tmp_2);    
    
    node->horizon(0);
    StlNode *out = pastification.pastify(node);
    std::string computed = out->getName();
    const std::string expected_1 = "(req)>(gnt)";
    
    EXPECT_EQ(expected_1, computed);
    
    delete out;
    delete node;
    
}

TEST_F (StlPastificationTest, predicate_eq) {
    const std::string name_1{"req"};
    const std::string name_2{"gnt"};
    std::set<std::string> set {name_1, name_2}; 

    StlVariableNode *tmp_1 = new StlVariableNode(name_1);
    StlVariableNode *tmp_2 = new StlVariableNode(name_2);
    StlPredicateNode *node = new StlPredicateNode(StlComparisonOperator::EQUAL, tmp_1, tmp_2);    
    
    node->horizon(0);
    StlNode *out = pastification.pastify(node);
    std::string computed = out->getName();
    const std::string expected_1 = "(req)==(gnt)";
    
    EXPECT_EQ(expected_1, computed);
    
    delete out;
    delete node;
    
}

TEST_F (StlPastificationTest, predicate_neq) {
    const std::string name_1{"req"};
    const std::string name_2{"gnt"};
    std::set<std::string> set {name_1, name_2}; 

    StlVariableNode *tmp_1 = new StlVariableNode(name_1);
    StlVariableNode *tmp_2 = new StlVariableNode(name_2);
    StlPredicateNode *node = new StlPredicateNode(StlComparisonOperator::NEQ, tmp_1, tmp_2);    
    
    node->horizon(0);
    StlNode *out = pastification.pastify(node);
    std::string computed = out->getName();
    const std::string expected_1 = "(req)!=(gnt)";
    
    EXPECT_EQ(expected_1, computed);
    
    delete out;
    delete node;
    
}

TEST_F (StlPastificationTest, not) {
    const std::string name{"req"};
    std::set<std::string> set {name}; 

    StlVariableNode *tmp = new StlVariableNode(name);
    StlNotNode *node = new StlNotNode(tmp);
    
    node->horizon(0);
    StlNode *out = pastification.pastify(node);
    std::string computed = out->getName();
    const std::string expected_1 = "not(req)";
    
    EXPECT_EQ(expected_1, computed);
    
    delete out;
    delete node;
    
}

TEST_F (StlPastificationTest, conjunction) {
    const std::string name_1{"req"};
    const std::string name_2{"gnt"};
    std::set<std::string> set {name_1, name_2}; 

    StlVariableNode *tmp_1 = new StlVariableNode(name_1);
    StlVariableNode *tmp_2 = new StlVariableNode(name_2);
    StlAndNode *node = new StlAndNode(tmp_1, tmp_2);    
    
    node->horizon(0);
    StlNode *out = pastification.pastify(node);
    std::string computed = out->getName();
    const std::string expected_1 = "(req)and(gnt)";
    
    EXPECT_EQ(expected_1, computed);
    
    delete out;
    delete node;
}

TEST_F (StlPastificationTest, disjunction) {
    const std::string name_1{"req"};
    const std::string name_2{"gnt"};
    std::set<std::string> set {name_1, name_2}; 

    StlVariableNode *tmp_1 = new StlVariableNode(name_1);
    StlVariableNode *tmp_2 = new StlVariableNode(name_2);
    StlOrNode *node = new StlOrNode(tmp_1, tmp_2);    
    
    node->horizon(0);
    StlNode *out = pastification.pastify(node);
    std::string computed = out->getName();
    const std::string expected_1 = "(req)or(gnt)";
    
    EXPECT_EQ(expected_1, computed);
    
    delete out;
    delete node;
}

TEST_F (StlPastificationTest, implication) {
    const std::string name_1{"req"};
    const std::string name_2{"gnt"};
    std::set<std::string> set {name_1, name_2}; 

    StlVariableNode *tmp_1 = new StlVariableNode(name_1);
    StlVariableNode *tmp_2 = new StlVariableNode(name_2);
    StlImpliesNode *node = new StlImpliesNode(tmp_1, tmp_2);   
    
    node->horizon(0);
    StlNode *out = pastification.pastify(node);
    std::string computed = out->getName();
    const std::string expected_1 = "(req)->(gnt)";
    
    EXPECT_EQ(expected_1, computed);
    
    delete out;
    delete node;
    
}

TEST_F (StlPastificationTest, iff) {
    const std::string name_1{"req"};
    const std::string name_2{"gnt"};
    std::set<std::string> set {name_1, name_2}; 

    StlVariableNode *tmp_1 = new StlVariableNode(name_1);
    StlVariableNode *tmp_2 = new StlVariableNode(name_2);
    StlIffNode *node = new StlIffNode(tmp_1, tmp_2);    
    
    node->horizon(0);
    StlNode *out = pastification.pastify(node);
    std::string computed = out->getName();
    const std::string expected_1 = "(req)iff(gnt)";
    
    EXPECT_EQ(expected_1, computed);
    
    delete out;
    delete node;
    
}

TEST_F (StlPastificationTest, xor) {
    const std::string name_1{"req"};
    const std::string name_2{"gnt"};
    std::set<std::string> set {name_1, name_2}; 

    StlVariableNode *tmp_1 = new StlVariableNode(name_1);
    StlVariableNode *tmp_2 = new StlVariableNode(name_2);
    StlXorNode *node = new StlXorNode(tmp_1, tmp_2);    
    
    node->horizon(0);
    StlNode *out = pastification.pastify(node);
    std::string computed = out->getName();
    const std::string expected_1 = "(req)xor(gnt)";
    
    EXPECT_EQ(expected_1, computed);
    
    delete out;
    delete node;
    
}

TEST_F (StlPastificationTest, rise) {
    const std::string name{"req"};
    std::set<std::string> set {name}; 

    StlVariableNode *tmp = new StlVariableNode(name);
    StlRiseNode *node = new StlRiseNode(tmp);
    
    node->horizon(0);
    StlNode *out = pastification.pastify(node);
    std::string computed = out->getName();
    const std::string expected_1 = "rise(req)";
    
    EXPECT_EQ(expected_1, computed);
    
    delete out;
    delete node;
    
}

TEST_F (StlPastificationTest, fall) {
    const std::string name{"req"};
    std::set<std::string> set {name}; 

    StlVariableNode *tmp = new StlVariableNode(name);
    StlFallNode *node = new StlFallNode(tmp);
    
    node->horizon(0);
    StlNode *out = pastification.pastify(node);
    std::string computed = out->getName();
    const std::string expected_1 = "fall(req)";
    
    EXPECT_EQ(expected_1, computed);
    
    delete out;
    delete node;
}

TEST_F (StlPastificationTest, once) {
    const std::string name{"req"};
    std::set<std::string> set {name}; 

    StlVariableNode *tmp = new StlVariableNode(name);
    StlOnceNode *node = new StlOnceNode(tmp);
    
    node->horizon(0);
    StlNode *out = pastification.pastify(node);
    std::string computed = out->getName();
    const std::string expected_1 = "once(req)";
    
    EXPECT_EQ(expected_1, computed);
    
    delete out;
    
    node->horizon(5);
    out = pastification.pastify(node);
    computed = out->getName();
    const std::string expected_2 = "once(once[5,5](req))";
    
    EXPECT_EQ(expected_2, computed);
    
    delete node;
    delete out;
    
}

TEST_F (StlPastificationTest, historically) {
    const std::string name{"req"};
    std::set<std::string> set {name}; 

    StlVariableNode *tmp = new StlVariableNode(name);
    StlHistoricallyNode *node = new StlHistoricallyNode(tmp);
    
    node->horizon(0);
    StlNode *out = pastification.pastify(node);
    std::string computed = out->getName();
    const std::string expected_1 = "historically(req)";
    
    EXPECT_EQ(expected_1, computed);
    
    delete out;
    
    node->horizon(5);
    out = pastification.pastify(node);
    computed = out->getName();
    const std::string expected_2 = "historically(once[5,5](req))";
    
    EXPECT_EQ(expected_2, computed);
    
    delete node;
    delete out;
}

TEST_F (StlPastificationTest, eventually) {
    const std::string name{"req"};
    std::set<std::string> set {name}; 

    StlVariableNode *tmp = new StlVariableNode(name);
    StlEventuallyNode *node = new StlEventuallyNode(tmp);
    
    node->horizon(0);
    StlNode *out = pastification.pastify(node);
    std::string computed = out->getName();
    const std::string expected_1 = "eventually(req)";
    
    EXPECT_EQ(expected_1, computed);
    
    delete out;
    delete node;
}

TEST_F (StlPastificationTest, always) {
    const std::string name{"req"};
    std::set<std::string> set {name}; 

    StlVariableNode *tmp = new StlVariableNode(name);
    StlAlwaysNode *node = new StlAlwaysNode(tmp);
    
    node->horizon(0);
    StlNode *out = pastification.pastify(node);
    std::string computed = out->getName();
    const std::string expected_1 = "always(req)";
    
    EXPECT_EQ(expected_1, computed);
    
    delete out;
    delete node;
}

TEST_F (StlPastificationTest, since) {
    const std::string name_1{"req"};
    const std::string name_2{"gnt"};
    std::set<std::string> set {name_1, name_2}; 

    StlVariableNode *tmp_1 = new StlVariableNode(name_1);
    StlVariableNode *tmp_2 = new StlVariableNode(name_2);
    StlSinceNode *node = new StlSinceNode(tmp_1, tmp_2);    
    
    node->horizon(0);
    StlNode *out = pastification.pastify(node);
    std::string computed = out->getName();
    const std::string expected_1 = "(req)since(gnt)";
    
    EXPECT_EQ(expected_1, computed);
    
    delete out;
    
    node->horizon(5);
    out = pastification.pastify(node);
    computed = out->getName();
    const std::string expected_2 = "(once[5,5](req))since(once[5,5](gnt))";
    
    EXPECT_EQ(expected_2, computed);
    
    delete node;
    delete out;
}

TEST_F (StlPastificationTest, once_bounded_0_1) {
    const std::string name{"req"};
    std::set<std::string> set {name}; 

    StlVariableNode *tmp = new StlVariableNode(name);
    StlOnceBoundedNode *node = new StlOnceBoundedNode(0, 1, tmp);
    
    node->horizon(0);
    StlNode *out = pastification.pastify(node);
    std::string computed = out->getName();
    const std::string expected_1 = "once[0,1](req)";
    
    EXPECT_EQ(expected_1, computed);
    
    delete out;
    
    node->horizon(5);
    out = pastification.pastify(node);
    computed = out->getName();
    const std::string expected_2 = "once[0,1](once[5,5](req))";
    
    EXPECT_EQ(expected_2, computed);
    
    delete node;
    delete out;
    
    
}

TEST_F (StlPastificationTest, historically_bounded_0_1) {
    const std::string name{"req"};
    std::set<std::string> set {name}; 

    StlVariableNode *tmp = new StlVariableNode(name);
    StlHistoricallyBoundedNode *node = new StlHistoricallyBoundedNode(0, 1, tmp);
    
    node->horizon(0);
    StlNode *out = pastification.pastify(node);
    std::string computed = out->getName();
    const std::string expected_1 = "historically[0,1](req)";
    
    EXPECT_EQ(expected_1, computed);
    
    delete out;
    
    
    node->horizon(5);
    out = pastification.pastify(node);
    computed = out->getName();
    const std::string expected_2 = "historically[0,1](once[5,5](req))";
    
    EXPECT_EQ(expected_2, computed);
    
    delete node;
    delete out;
    
}

TEST_F (StlPastificationTest, eventually_bounded_0_1) {
    const std::string name{"req"};
    std::set<std::string> set {name}; 

    StlVariableNode *tmp = new StlVariableNode(name);
    StlEventuallyBoundedNode *node = new StlEventuallyBoundedNode(0, 1, tmp);
    
    node->horizon(1);
    StlNode *out = pastification.pastify(node);
    std::string computed = out->getName();
    const std::string expected_1 = "once[0,1](req)";
    
    EXPECT_EQ(expected_1, computed);
    
    delete out;
    
    node->horizon(5);
    out = pastification.pastify(node);
    computed = out->getName();
    const std::string expected_2 = "once[0,1](once[4,4](req))";
    
    EXPECT_EQ(expected_2, computed);
    
    delete node;
    delete out;
    
}

TEST_F (StlPastificationTest, always_bounded_0_1) {
    const std::string name{"req"};
    std::set<std::string> set {name}; 

    StlVariableNode *tmp = new StlVariableNode(name);
    StlAlwaysBoundedNode *node = new StlAlwaysBoundedNode(0, 1, tmp);
    
    node->horizon(1);
    StlNode *out = pastification.pastify(node);
    std::string computed = out->getName();
    const std::string expected_1 = "historically[0,1](req)";
    
    EXPECT_EQ(expected_1, computed);
    
    delete out;
    
    node->horizon(5);
    out = pastification.pastify(node);
    computed = out->getName();
    const std::string expected_2 = "historically[0,1](once[4,4](req))";
    
    EXPECT_EQ(expected_2, computed);
    
    delete node;
    delete out;
}

TEST_F (StlPastificationTest, until_bounded_0_1) {
    const std::string name_1{"req"};
    const std::string name_2{"gnt"};
    std::set<std::string> set {name_1, name_2}; 

    StlVariableNode *tmp_1 = new StlVariableNode(name_1);
    StlVariableNode *tmp_2 = new StlVariableNode(name_2);
    StlUntilBoundedNode *node = new StlUntilBoundedNode(0, 1, tmp_1, tmp_2);
    
    node->horizon(1);
    StlNode *out = pastification.pastify(node);
    std::string computed = out->getName();
    const std::string expected_1 = "(req)precedes[0,1](gnt)";
    
    EXPECT_EQ(expected_1, computed);
    
    delete out;
    
    node->horizon(5);
    out = pastification.pastify(node);
    computed = out->getName();
    const std::string expected_2 = "(once[4,4](req))precedes[0,1](once[4,4](gnt))";
    
    EXPECT_EQ(expected_2, computed);
    
    delete node;
    delete out;
}

TEST_F (StlPastificationTest, since_bounded_0_1) {
    const std::string name_1{"req"};
    const std::string name_2{"gnt"};
    std::set<std::string> set {name_1, name_2}; 

    StlVariableNode *tmp_1 = new StlVariableNode(name_1);
    StlVariableNode *tmp_2 = new StlVariableNode(name_2);
    StlSinceBoundedNode *node = new StlSinceBoundedNode(0, 1, tmp_1, tmp_2);    
    
    node->horizon(0);
    StlNode *out = pastification.pastify(node);
    std::string computed = out->getName();
    const std::string expected_1 = "(req)since[0,1](gnt)";
    
    EXPECT_EQ(expected_1, computed);
    
    delete out;
    delete node;
}
    

TEST_F (StlPastificationTest, precedes_bounded_1_2) {
    const std::string name_1{"req"};
    const std::string name_2{"gnt"};
    std::set<std::string> set {name_1, name_2}; 

    StlVariableNode *tmp_1 = new StlVariableNode(name_1);
    StlVariableNode *tmp_2 = new StlVariableNode(name_2);
    StlPrecedesBoundedNode *node = new StlPrecedesBoundedNode(1, 2, tmp_1, tmp_2);    
    
    node->horizon(0);
    StlNode *out = pastification.pastify(node);
    std::string computed = out->getName();
    const std::string expected_1 = "(req)precedes[1,2](gnt)";
    
    EXPECT_EQ(expected_1, computed);
    
    delete out;
    delete node;
}

TEST_F (StlPastificationTest, past_complex_1) {
    const std::string name_1{"req"};
    const std::string name_2{"gnt"};
    std::set<std::string> set {name_1, name_2}; 

    StlVariableNode *tmp_1 = new StlVariableNode(name_1);
    StlVariableNode *tmp_2 = new StlVariableNode(name_2);
    StlRiseNode *rise = new StlRiseNode(tmp_1);
    StlHistoricallyNode *hist = new StlHistoricallyNode(tmp_2);
    StlOnceBoundedNode *once = new StlOnceBoundedNode(1, 2, hist);
    StlSinceBoundedNode *node = new StlSinceBoundedNode(2, 6, rise, once);    
    
    node->horizon(0);
    StlNode *out = pastification.pastify(node);
    std::string computed = out->getName();
    const std::string expected_1 = "(rise(req))since[2,6](once[1,2](historically(gnt)))";
    
    EXPECT_EQ(expected_1, computed);
    
    delete out;
    delete node;
}

TEST_F (StlPastificationTest, past_complex_2) {
    const std::string name_1{"req"};
    const std::string name_2{"gnt"};
    std::set<std::string> set {name_1, name_2}; 

    StlVariableNode *tmp_1 = new StlVariableNode(name_1);
    StlVariableNode *tmp_2 = new StlVariableNode(name_2);
    StlRiseNode *rise = new StlRiseNode(tmp_1);
    StlHistoricallyNode *hist = new StlHistoricallyNode(tmp_2);
    StlOnceBoundedNode *once = new StlOnceBoundedNode(1, 2, hist);
    StlSinceBoundedNode *since = new StlSinceBoundedNode(2, 6, rise, once);
    StlAlwaysNode *node = new StlAlwaysNode(since);    
    
    node->horizon(0);
    StlNode *out = pastification.pastify(node);
    std::string computed = out->getName();
    const std::string expected_1 = "always((rise(req))since[2,6](once[1,2](historically(gnt))))";
    
    EXPECT_EQ(expected_1, computed);
    
    delete out;
    delete node;
}

TEST_F (StlPastificationTest, bounded_future_complex_1) {
    const std::string name_1{"req"};
    const std::string name_2{"gnt"};
    std::set<std::string> set {name_1, name_2}; 

    StlVariableNode *tmp_1 = new StlVariableNode(name_1);
    StlVariableNode *tmp_2 = new StlVariableNode(name_2);
    StlConstantNode *cnt_1 = new StlConstantNode(3);
    StlConstantNode *cnt_2 = new StlConstantNode(3);
    StlPredicateNode *pd_1 = new StlPredicateNode(StlComparisonOperator::GEQ, tmp_1, cnt_1);
    StlPredicateNode *pd_2 = new StlPredicateNode(StlComparisonOperator::GEQ, tmp_2, cnt_2);
    
    StlRiseNode *rise = new StlRiseNode(pd_1);
    
    
    StlAlwaysBoundedNode *alw = new StlAlwaysBoundedNode(3, 4, pd_2);
    StlEventuallyBoundedNode *ev = new StlEventuallyBoundedNode(1, 2, alw);
    StlImpliesNode *imp = new StlImpliesNode(rise, ev);
    StlAlwaysNode *node = new StlAlwaysNode(imp);    
    
    node->horizon(6);
    StlNode *out = pastification.pastify(node);
    std::string computed = out->getName();
    const std::string expected_1 = "always((rise((once[6,6](req))>=(3.000000)))->(once[0,1](historically[0,1]((gnt)>=(3.000000)))))";
    
    EXPECT_EQ(expected_1, computed);
    
    delete out;
    delete node;
}

TEST_F (StlPastificationTest, bounded_future_complex_2) {
    const std::string name_1{"req"};
    const std::string name_2{"gnt"};
    const std::string name_3{"ack"};
    std::set<std::string> set {name_1, name_2, name_3}; 

    StlVariableNode *tmp_1 = new StlVariableNode(name_1);
    StlVariableNode *tmp_2 = new StlVariableNode(name_2);
    StlVariableNode *tmp_3 = new StlVariableNode(name_3);
    
    StlUntilBoundedNode *until = new StlUntilBoundedNode(1, 2, tmp_1, tmp_2);
    StlEventuallyBoundedNode *ev = new StlEventuallyBoundedNode(0, 6, tmp_3);
    StlImpliesNode *imp = new StlImpliesNode(until, ev);
    
    imp->horizon(6);
    
    StlNode *out = pastification.pastify(imp);
    std::string computed = out->getName();
    const std::string expected_1 = "((once[4,4](req))precedes[1,2](once[4,4](gnt)))->(once[0,6](ack))";
    
    EXPECT_EQ(expected_1, computed);
    
    delete out;
    delete imp;
}

TEST_F (StlPastificationTest, mixed_complex_1) {
    const std::string name_1{"req"};
    const std::string name_2{"gnt"};
    std::set<std::string> set {name_1, name_2}; 

    StlVariableNode *tmp_1 = new StlVariableNode(name_1);
    StlVariableNode *tmp_2 = new StlVariableNode(name_2);
    
    StlEventuallyBoundedNode *ev_1 = new StlEventuallyBoundedNode(5, 6, tmp_1);
    StlOnceBoundedNode *once = new StlOnceBoundedNode(1, 2, tmp_2);
    StlEventuallyBoundedNode *ev_2 = new StlEventuallyBoundedNode(3, 3, once);
    StlImpliesNode *imp = new StlImpliesNode(ev_1, ev_2);
    
    imp->horizon(6);
    
    StlNode *out = pastification.pastify(imp);
    std::string computed = out->getName();
    const std::string expected_1 = "(once[0,1](req))->(once[1,2](once[3,3](gnt)))";
    
    EXPECT_EQ(expected_1, computed);
    
    delete out;
    delete imp;
}

TEST_F (StlPastificationTest, mixed_complex_2) {
    const std::string name_1{"req"};
    const std::string name_2{"gnt"};
    std::set<std::string> set {name_1, name_2}; 

    StlVariableNode *tmp_1 = new StlVariableNode(name_1);
    StlVariableNode *tmp_2 = new StlVariableNode(name_2);
    
    StlEventuallyBoundedNode *ev_1 = new StlEventuallyBoundedNode(5, 6, tmp_1);
    StlOnceBoundedNode *once = new StlOnceBoundedNode(1, 2, tmp_2);
    StlAlwaysBoundedNode *alw = new StlAlwaysBoundedNode(3, 3, once);
    StlImpliesNode *imp = new StlImpliesNode(ev_1, alw);
    
    imp->horizon(6);
    
    StlNode *out = pastification.pastify(imp);
    std::string computed = out->getName();
    const std::string expected_1 = "(once[0,1](req))->(once[1,2](once[3,3](gnt)))";
    
    EXPECT_EQ(expected_1, computed);
    
    delete out;
    delete imp;
}

