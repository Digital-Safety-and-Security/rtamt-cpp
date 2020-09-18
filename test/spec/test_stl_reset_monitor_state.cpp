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
#include <spec/stl_reset_monitor_state.hpp>
#include <rtamt/stl_specification.hpp>


using namespace node;
using namespace spec;
using namespace rtamt;

TEST (TestResetMonitorState, constant) {
    double val = 5;
    
    StlConstantNode *node = new StlConstantNode(val);
    
    Sample computed;
    StlResetMonitorState reset;
    
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 5);
    
    computed = node->update();
    EXPECT_EQ(computed.time, 1);
    EXPECT_EQ(computed.value, 5);
    
    node->accept(reset);
    
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 5);
    
    delete node;
}

TEST (TestResetMonitorState, variable) {
    const std::string name = "request"; 
    StlVariableNode *node = new StlVariableNode(name);
    
    Sample computed;
    StlResetMonitorState reset;
    
    node->addNewInput(Sample(0,5));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 5);
    
    node->addNewInput(Sample(1,2));
    computed = node->update();
    EXPECT_EQ(computed.time, 1);
    EXPECT_EQ(computed.value, 2);
    
    node->accept(reset);
    
    node->addNewInput(Sample(0,3));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 3);
    
    delete node;
}

TEST (TestResetMonitorState, abs) {
    const std::string name = "request"; 
    StlVariableNode *var = new StlVariableNode(name);
    StlAbsNode *node = new StlAbsNode(var);
    
    Sample computed;
    StlResetMonitorState reset;
    
    node->addNewInput(Sample(0,5));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 5);
    
    node->addNewInput(Sample(1,2));
    computed = node->update();
    EXPECT_EQ(computed.time, 1);
    EXPECT_EQ(computed.value, 2);
    
    node->accept(reset);
    
    node->addNewInput(Sample(0,3));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 3);
    
    delete node;
}

TEST (TestResetMonitorState, addition) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlAdditionNode *node = new StlAdditionNode(var_1, var_2);
    
    Sample computed;
    StlResetMonitorState reset;
    
    node->addNewInput(Sample(0,5), Sample(0,-2));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 3);
    
    node->addNewInput(Sample(1,2), Sample(1, 0.5));
    computed = node->update();
    EXPECT_EQ(computed.time, 1);
    EXPECT_EQ(computed.value, 2.5);
    
    node->accept(reset);
    
    node->addNewInput(Sample(0,3), Sample(0,3));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 6);
    
    delete node;
}

TEST (TestResetMonitorState, subtraction) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlSubtractionNode *node = new StlSubtractionNode(var_1, var_2);
    
    Sample computed;
    StlResetMonitorState reset;
    
    node->addNewInput(Sample(0,5), Sample(0,-2));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 7);
    
    node->addNewInput(Sample(1,2), Sample(1, 0.5));
    computed = node->update();
    EXPECT_EQ(computed.time, 1);
    EXPECT_EQ(computed.value, 1.5);
    
    node->accept(reset);
    
    node->addNewInput(Sample(0,3), Sample(0,3));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 0);
    
    delete node;
}

TEST (TestResetMonitorState, multiplication) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlMultiplicationNode *node = new StlMultiplicationNode(var_1, var_2);
    
    Sample computed;
    StlResetMonitorState reset;
    
    node->addNewInput(Sample(0,5), Sample(0,-2));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, -10);
    
    node->addNewInput(Sample(1,2), Sample(1, 0.5));
    computed = node->update();
    EXPECT_EQ(computed.time, 1);
    EXPECT_EQ(computed.value, 1);
    
    node->accept(reset);
    
    node->addNewInput(Sample(0,3), Sample(0,3));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 9);
    
    delete node;
}

TEST (TestResetMonitorState, division) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlDivisionNode *node = new StlDivisionNode(var_1, var_2);
    
    Sample computed;
    StlResetMonitorState reset;
    
    node->addNewInput(Sample(0,5), Sample(0,-2));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 5/-2.0);
    
    node->addNewInput(Sample(1,2), Sample(1, 0.5));
    computed = node->update();
    EXPECT_EQ(computed.time, 1);
    EXPECT_EQ(computed.value, 2/0.5);
    
    node->accept(reset);
    
    node->addNewInput(Sample(0,3), Sample(0,3));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 3/3);
    
    delete node;
}

TEST (TestResetMonitorState, predicate_leq) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlPredicateNode *node = new StlPredicateNode(StlComparisonOperator::LEQ, var_1, var_2);
    
    Sample computed;
    StlResetMonitorState reset;
    
    node->addNewInput(Sample(0,5), Sample(0,-2));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, -7);
    
    node->addNewInput(Sample(1,2), Sample(1, 0.5));
    computed = node->update();
    EXPECT_EQ(computed.time, 1);
    EXPECT_EQ(computed.value, -1.5);
    
    node->accept(reset);
    
    node->addNewInput(Sample(0,3), Sample(0,3));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 0);
    
    delete node;
}

TEST (TestResetMonitorState, predicate_less) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlPredicateNode *node = new StlPredicateNode(StlComparisonOperator::LESS, var_1, var_2);
    
    Sample computed;
    StlResetMonitorState reset;
    
    node->addNewInput(Sample(0,5), Sample(0,-2));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, -7);
    
    node->addNewInput(Sample(1,2), Sample(1, 0.5));
    computed = node->update();
    EXPECT_EQ(computed.time, 1);
    EXPECT_EQ(computed.value, -1.5);
    
    node->accept(reset);
    
    node->addNewInput(Sample(0,3), Sample(0,3));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 0);
    
    delete node;
}

TEST (TestResetMonitorState, predicate_geq) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlPredicateNode *node = new StlPredicateNode(StlComparisonOperator::GEQ, var_1, var_2);
    
    Sample computed;
    StlResetMonitorState reset;
    
    node->addNewInput(Sample(0,5), Sample(0,-2));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 7);
    
    node->addNewInput(Sample(1,2), Sample(1, 0.5));
    computed = node->update();
    EXPECT_EQ(computed.time, 1);
    EXPECT_EQ(computed.value, 1.5);
    
    node->accept(reset);
    
    node->addNewInput(Sample(0,3), Sample(0,3));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 0);
    
    delete node;
}

TEST (TestResetMonitorState, predicate_greater) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlPredicateNode *node = new StlPredicateNode(StlComparisonOperator::GREATER, var_1, var_2);
    
    Sample computed;
    StlResetMonitorState reset;
    
    node->addNewInput(Sample(0,5), Sample(0,-2));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 7);
    
    node->addNewInput(Sample(1,2), Sample(1, 0.5));
    computed = node->update();
    EXPECT_EQ(computed.time, 1);
    EXPECT_EQ(computed.value, 1.5);
    
    node->accept(reset);
    
    node->addNewInput(Sample(0,3), Sample(0,3));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 0);
    
    delete node;
}

TEST (TestResetMonitorState, predicate_eq) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlPredicateNode *node = new StlPredicateNode(StlComparisonOperator::EQUAL, var_1, var_2);
    
    Sample computed;
    StlResetMonitorState reset;
    
    node->addNewInput(Sample(0,5), Sample(0,-2));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, -7);
    
    node->addNewInput(Sample(1,2), Sample(1, 0.5));
    computed = node->update();
    EXPECT_EQ(computed.time, 1);
    EXPECT_EQ(computed.value, -1.5);
    
    node->accept(reset);
    
    node->addNewInput(Sample(0,3), Sample(0,3));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 0);
    
    delete node;
}

TEST (TestResetMonitorState, predicate_neq) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlPredicateNode *node = new StlPredicateNode(StlComparisonOperator::NEQ, var_1, var_2);
    
    Sample computed;
    StlResetMonitorState reset;
    
    node->addNewInput(Sample(0,5), Sample(0,-2));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 7);
    
    node->addNewInput(Sample(1,2), Sample(1, 0.5));
    computed = node->update();
    EXPECT_EQ(computed.time, 1);
    EXPECT_EQ(computed.value, 1.5);
    
    node->accept(reset);
    
    node->addNewInput(Sample(0,3), Sample(0,3));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 0);
    
    delete node;
}

TEST (TestResetMonitorState, not) {
    const std::string name = "request"; 
    StlVariableNode *var = new StlVariableNode(name);
    StlNotNode *node = new StlNotNode(var);
    
    Sample computed;
    StlResetMonitorState reset;
    
    node->addNewInput(Sample(0,5));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, -5);
    
    node->addNewInput(Sample(1,2));
    computed = node->update();
    EXPECT_EQ(computed.time, 1);
    EXPECT_EQ(computed.value, -2);
    
    node->accept(reset);
    
    node->addNewInput(Sample(0,3));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, -3);
    
    delete node;
}

TEST (TestResetMonitorState, conjunction) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlAndNode *node = new StlAndNode(var_1, var_2);
    
    Sample computed;
    StlResetMonitorState reset;
    
    node->addNewInput(Sample(0,5), Sample(0,-2));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, -2);
    
    node->addNewInput(Sample(1,2), Sample(1, 0.5));
    computed = node->update();
    EXPECT_EQ(computed.time, 1);
    EXPECT_EQ(computed.value, 0.5);
    
    node->accept(reset);
    
    node->addNewInput(Sample(0,3), Sample(0,3));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 3);
    
    delete node;
}

TEST (TestResetMonitorState, disjunction) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlOrNode *node = new StlOrNode(var_1, var_2);
    
    Sample computed;
    StlResetMonitorState reset;
    
    node->addNewInput(Sample(0,5), Sample(0,-2));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 5);
    
    node->addNewInput(Sample(1,2), Sample(1, 0.5));
    computed = node->update();
    EXPECT_EQ(computed.time, 1);
    EXPECT_EQ(computed.value, 2);
    
    node->accept(reset);
    
    node->addNewInput(Sample(0,3), Sample(0,3));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 3);
    
    delete node;
}

TEST (TestResetMonitorState, implication) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlImpliesNode *node = new StlImpliesNode(var_1, var_2);
    
    Sample computed;
    StlResetMonitorState reset;
    
    node->addNewInput(Sample(0,5), Sample(0,-2));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, -2);
    
    node->addNewInput(Sample(1,2), Sample(1, 0.5));
    computed = node->update();
    EXPECT_EQ(computed.time, 1);
    EXPECT_EQ(computed.value, 0.5);
    
    node->accept(reset);
    
    node->addNewInput(Sample(0,3), Sample(0,3));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 3);
    
    delete node;
}

TEST (TestResetMonitorState, iff) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlIffNode *node = new StlIffNode(var_1, var_2);
    
    Sample computed;
    StlResetMonitorState reset;
    
    node->addNewInput(Sample(0,5), Sample(0,-2));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, -7);
    
    node->addNewInput(Sample(1,2), Sample(1, 0.5));
    computed = node->update();
    EXPECT_EQ(computed.time, 1);
    EXPECT_EQ(computed.value, -1.5);
    
    node->accept(reset);
    
    node->addNewInput(Sample(0,3), Sample(0,3));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 0);
    
    delete node;
}

TEST (TestResetMonitorState, xor) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlXorNode *node = new StlXorNode(var_1, var_2);
    
    Sample computed;
    StlResetMonitorState reset;
    
    node->addNewInput(Sample(0,5), Sample(0,-2));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 7);
    
    node->addNewInput(Sample(1,2), Sample(1, 0.5));
    computed = node->update();
    EXPECT_EQ(computed.time, 1);
    EXPECT_EQ(computed.value, 1.5);
    
    node->accept(reset);
    
    node->addNewInput(Sample(0,3), Sample(0,3));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 0);
    
    delete node;
}

TEST (TestResetMonitorState, rise) {
    const std::string name = "request"; 
    StlVariableNode *var = new StlVariableNode(name);
    StlRiseNode *node = new StlRiseNode(var);
    
    Sample computed;
    StlResetMonitorState reset;
    
    node->addNewInput(Sample(0,5));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 5);
    
    node->addNewInput(Sample(1,2));
    computed = node->update();
    EXPECT_EQ(computed.time, 1);
    EXPECT_EQ(computed.value, -5);
    
    node->accept(reset);
    
    node->addNewInput(Sample(0,3));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 3);
    
    delete node;
}

TEST (TestResetMonitorState, fall) {
    const std::string name = "request"; 
    StlVariableNode *var = new StlVariableNode(name);
    StlFallNode *node = new StlFallNode(var);
    
    Sample computed;
    StlResetMonitorState reset;
    
    node->addNewInput(Sample(0,5));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, -5);
    
    node->addNewInput(Sample(1,2));
    computed = node->update();
    EXPECT_EQ(computed.time, 1);
    EXPECT_EQ(computed.value, -2);
    
    node->accept(reset);
    
    node->addNewInput(Sample(0,-3));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 3);
    
    delete node;
}

TEST (TestResetMonitorState, once) {
    const std::string name = "request"; 
    StlVariableNode *var = new StlVariableNode(name);
    StlOnceNode *node = new StlOnceNode(var);
    
    Sample computed;
    StlResetMonitorState reset;
    
    node->addNewInput(Sample(0,10));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 10);
    
    node->addNewInput(Sample(1,2));
    computed = node->update();
    EXPECT_EQ(computed.time, 1);
    EXPECT_EQ(computed.value, 10);
    
    node->accept(reset);
    
    node->addNewInput(Sample(0,3));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 3);
    
    delete node;
}

TEST (TestResetMonitorState, historically) {
    const std::string name = "request"; 
    StlVariableNode *var = new StlVariableNode(name);
    StlHistoricallyNode *node = new StlHistoricallyNode(var);
    
    Sample computed;
    StlResetMonitorState reset;
    
    node->addNewInput(Sample(0,2));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 2);
    
    node->addNewInput(Sample(1,5));
    computed = node->update();
    EXPECT_EQ(computed.time, 1);
    EXPECT_EQ(computed.value, 2);
    
    node->accept(reset);
    
    node->addNewInput(Sample(0,3));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 3);
    
    delete node;
}

TEST (TestResetMonitorState, eventually) {
    const std::string name = "request"; 
    StlVariableNode *var = new StlVariableNode(name);
    StlEventuallyNode *node = new StlEventuallyNode(var);
    
    Sample computed;
    StlResetMonitorState reset;
    
    node->addNewInput(Sample(0,10));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 10);
    
    node->addNewInput(Sample(1,2));
    computed = node->update();
    EXPECT_EQ(computed.time, 1);
    EXPECT_EQ(computed.value, 10);
    
    node->accept(reset);
    
    node->addNewInput(Sample(0,3));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 3);
    
    delete node;
}

TEST (TestResetMonitorState, always) {
    const std::string name = "request"; 
    StlVariableNode *var = new StlVariableNode(name);
    StlAlwaysNode *node = new StlAlwaysNode(var);
    
    Sample computed;
    StlResetMonitorState reset;
    
    node->addNewInput(Sample(0,2));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 2);
    
    node->addNewInput(Sample(1,5));
    computed = node->update();
    EXPECT_EQ(computed.time, 1);
    EXPECT_EQ(computed.value, 2);
    
    node->accept(reset);
    
    node->addNewInput(Sample(0,3));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 3);
    
    delete node;
}

TEST (TestResetMonitorState, since) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlSinceNode *node = new StlSinceNode(var_1, var_2);
    
    Sample computed;
    StlResetMonitorState reset;
    
    node->addNewInput(Sample(0,3), Sample(0,3));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 3);
    
    node->addNewInput(Sample(1,3), Sample(1, 3));
    computed = node->update();
    EXPECT_EQ(computed.time, 1);
    EXPECT_EQ(computed.value, 3);
    
    node->accept(reset);
    
    node->addNewInput(Sample(0,4), Sample(0,4));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 4);
    
    delete node;
}

TEST (TestResetMonitorState, once_bounded) {
    const std::string name = "request"; 
    StlVariableNode *var = new StlVariableNode(name);
    StlOnceBoundedNode *node = new StlOnceBoundedNode(0, 1, var, true);
    
    Sample computed;
    StlResetMonitorState reset;
    
    node->addNewInput(Sample(0,3));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 3);
    
    node->addNewInput(Sample(1,3));
    computed = node->update();
    EXPECT_EQ(computed.time, 1);
    EXPECT_EQ(computed.value, 3);
    
    node->accept(reset);
    
    node->addNewInput(Sample(0,2));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 2);
    
    delete node;
}

TEST (TestResetMonitorState, historically_bounded) {
    const std::string name = "request"; 
    StlVariableNode *var = new StlVariableNode(name);
    StlHistoricallyBoundedNode *node = new StlHistoricallyBoundedNode(0, 3, var, true);
    
    Sample computed;
    StlResetMonitorState reset;
    
    node->addNewInput(Sample(0,3));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 3);
    
    node->addNewInput(Sample(1,3));
    computed = node->update();
    EXPECT_EQ(computed.time, 1);
    EXPECT_EQ(computed.value, 3);
    
    node->accept(reset);
    
    node->addNewInput(Sample(0,4));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 4);
    
    delete node;
}

TEST (TestResetMonitorState, eventually_bounded) {
    const std::string name = "request"; 
    StlVariableNode *var = new StlVariableNode(name);
    StlEventuallyBoundedNode *node = new StlEventuallyBoundedNode(4, 5, var);
    
    StlResetMonitorState reset;
    
    node->accept(reset);
    delete node;
}

TEST (TestResetMonitorState, always_bounded) {
    const std::string name = "request"; 
    StlVariableNode *var = new StlVariableNode(name);
    StlAlwaysBoundedNode *node = new StlAlwaysBoundedNode(0, 3, var);
    
    StlResetMonitorState reset;
    
    node->accept(reset);
    delete node;
}

TEST (TestResetMonitorState, since_bounded) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlSinceBoundedNode *node = new StlSinceBoundedNode(0, 5, var_1, var_2, true);
    
    Sample computed;
    StlResetMonitorState reset;
    
    node->addNewInput(Sample(0,3), Sample(0,3));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 3);
    
    node->addNewInput(Sample(1,3), Sample(1, 3));
    computed = node->update();
    EXPECT_EQ(computed.time, 1);
    EXPECT_EQ(computed.value, 3);
    
    node->accept(reset);
    
    node->addNewInput(Sample(0,4), Sample(0,4));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 4);
    
    delete node;
}

TEST (TestResetMonitorState, until_bounded) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlUntilBoundedNode *node = new StlUntilBoundedNode(1, 2, var_1, var_2);
    
    StlResetMonitorState reset;
    
    node->accept(reset);
    delete node;
}

TEST (TestResetMonitorState, precedes_bounded) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlPrecedesBoundedNode *node = new StlPrecedesBoundedNode(0, 1, var_1, var_2, true);
    
    Sample computed;
    StlResetMonitorState reset;
    
    node->addNewInput(Sample(0,3), Sample(0,3));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 3);
    
    node->addNewInput(Sample(1,3), Sample(1, 3));
    computed = node->update();
    EXPECT_EQ(computed.time, 1);
    EXPECT_EQ(computed.value, 3);
    
    node->accept(reset);
    
    node->addNewInput(Sample(0,4), Sample(0,4));
    computed = node->update();
    EXPECT_EQ(computed.time, 0);
    EXPECT_EQ(computed.value, 4);
    
    delete node;
}

