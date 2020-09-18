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
#include <rtamt/stl_exception.hpp>
#include <rtamt/stl_specification.hpp>


using namespace node;
using namespace rtamt;


class StlNodeEvaluationTest : public ::testing::Test {
    protected:
        Sample sample_1_1;
        Sample sample_1_2;

        Sample sample_2_1;
        Sample sample_2_2;

        Sample sample_3_1;
        Sample sample_3_2;

        Sample sample_4_1;
        Sample sample_4_2;

        Sample sample_5_1;
        Sample sample_5_2;

        virtual void SetUp() {
            sample_1_1.time = 0;
            sample_1_2.time = 0;
            sample_1_1.value = 100;
            sample_1_2.value = 20;

            sample_2_1.time = 1;
            sample_2_2.time = 1;
            sample_2_1.value = -1;
            sample_2_2.value = -2;

            sample_3_1.time = 2;
            sample_3_2.time = 2;
            sample_3_1.value = -2;
            sample_3_2.value = 10;

            sample_4_1.time = 3;
            sample_4_2.time = 3;
            sample_4_1.value = 5;
            sample_4_2.value = 4;

            sample_5_1.time = 4;
            sample_5_2.time = 4;
            sample_5_1.value = -1;
            sample_5_2.value = -1;
        }
};


TEST_F (StlNodeEvaluationTest, constant) {
    double val = 5;
    StlConstantNode *node = new StlConstantNode(val);
    
    Sample out;
    
    out = node->update();
    EXPECT_EQ(0, out.time);
    EXPECT_EQ(5, out.value);
    
    out = node->update();
    EXPECT_EQ(1, out.time);
    EXPECT_EQ(5, out.value);
    
    delete node;
}

TEST_F (StlNodeEvaluationTest, variable) {
    const std::string name = "request"; 
    StlVariableNode *node = new StlVariableNode(name);
    
    Sample out;
    
    node->addNewInput(this->sample_1_1);
    out = node->update();
    EXPECT_EQ(0, out.time);
    EXPECT_EQ(100, out.value);
    
    node->addNewInput(this->sample_2_1);
    out = node->update();
    EXPECT_EQ(1, out.time);
    EXPECT_EQ(-1, out.value);
    
    node->addNewInput(this->sample_3_1);
    out = node->update();
    EXPECT_EQ(2, out.time);
    EXPECT_EQ(-2, out.value);
    
    node->addNewInput(this->sample_4_1);
    out = node->update();
    EXPECT_EQ(3, out.time);
    EXPECT_EQ(5, out.value);
    
    node->addNewInput(this->sample_5_1);
    out = node->update();
    EXPECT_EQ(4, out.time);
    EXPECT_EQ(-1, out.value);
    
    delete node;
}

TEST_F (StlNodeEvaluationTest, abs) {
    const std::string name = "request"; 
    StlVariableNode *var = new StlVariableNode(name);
    StlAbsNode *node = new StlAbsNode(var);
    
    Sample out;
    
    node->addNewInput(this->sample_1_1);
    out = node->update();
    EXPECT_EQ(0, out.time);
    EXPECT_EQ(100, out.value);
    
    node->addNewInput(this->sample_2_1);
    out = node->update();
    EXPECT_EQ(1, out.time);
    EXPECT_EQ(1, out.value);
    
    node->addNewInput(this->sample_3_1);
    out = node->update();
    EXPECT_EQ(2, out.time);
    EXPECT_EQ(2, out.value);
    
    node->addNewInput(this->sample_4_1);
    out = node->update();
    EXPECT_EQ(3, out.time);
    EXPECT_EQ(5, out.value);
    
    node->addNewInput(this->sample_5_1);
    out = node->update();
    EXPECT_EQ(4, out.time);
    EXPECT_EQ(1, out.value);
    
    delete node;
}

TEST_F (StlNodeEvaluationTest, addition) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlAdditionNode *node = new StlAdditionNode(var_1, var_2);
    
    Sample out;
    
    node->addNewInput(sample_1_1, sample_1_2);
    out = node->update();
    EXPECT_EQ(0, out.time);
    EXPECT_EQ(120, out.value);
    
    node->addNewInput(sample_2_1, sample_2_2);
    out = node->update();
    EXPECT_EQ(1, out.time);
    EXPECT_EQ(-3, out.value);
    
    node->addNewInput(sample_3_1, sample_3_2);
    out = node->update();
    EXPECT_EQ(2, out.time);
    EXPECT_EQ(8, out.value);
    
    node->addNewInput(sample_4_1, sample_4_2);
    out = node->update();
    EXPECT_EQ(3, out.time);
    EXPECT_EQ(9, out.value);
    
    node->addNewInput(sample_5_1, sample_5_2);
    out = node->update();
    EXPECT_EQ(4, out.time);
    EXPECT_EQ(-2, out.value);
    
    delete node;
}

TEST_F (StlNodeEvaluationTest, subtraction) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlSubtractionNode *node = new StlSubtractionNode(var_1, var_2);
    
    Sample out;
    
    node->addNewInput(sample_1_1, sample_1_2);
    out = node->update();
    EXPECT_EQ(0, out.time);
    EXPECT_EQ(80, out.value);
    
    node->addNewInput(sample_2_1, sample_2_2);
    out = node->update();
    EXPECT_EQ(1, out.time);
    EXPECT_EQ(1, out.value);
    
    node->addNewInput(sample_3_1, sample_3_2);
    out = node->update();
    EXPECT_EQ(2, out.time);
    EXPECT_EQ(-12, out.value);
    
    node->addNewInput(sample_4_1, sample_4_2);
    out = node->update();
    EXPECT_EQ(3, out.time);
    EXPECT_EQ(1, out.value);
    
    node->addNewInput(sample_5_1, sample_5_2);
    out = node->update();
    EXPECT_EQ(4, out.time);
    EXPECT_EQ(0, out.value);
    
    delete node;
}

TEST_F (StlNodeEvaluationTest, multiplication) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlMultiplicationNode *node = new StlMultiplicationNode(var_1, var_2);
    
    Sample out;
    
    node->addNewInput(sample_1_1, sample_1_2);
    out = node->update();
    EXPECT_EQ(0, out.time);
    EXPECT_EQ(2000, out.value);
    
    node->addNewInput(sample_2_1, sample_2_2);
    out = node->update();
    EXPECT_EQ(1, out.time);
    EXPECT_EQ(2, out.value);
    
    node->addNewInput(sample_3_1, sample_3_2);
    out = node->update();
    EXPECT_EQ(2, out.time);
    EXPECT_EQ(-20, out.value);
    
    node->addNewInput(sample_4_1, sample_4_2);
    out = node->update();
    EXPECT_EQ(3, out.time);
    EXPECT_EQ(20, out.value);
    
    node->addNewInput(sample_5_1, sample_5_2);
    out = node->update();
    EXPECT_EQ(4, out.time);
    EXPECT_EQ(1, out.value);
    
    delete node;
}

TEST_F (StlNodeEvaluationTest, division) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlDivisionNode *node = new StlDivisionNode(var_1, var_2);
    
    Sample out;
    
    node->addNewInput(sample_1_1, sample_1_2);
    out = node->update();
    EXPECT_EQ(0, out.time);
    EXPECT_EQ(100.0/20.0, out.value);
    
    node->addNewInput(sample_2_1, sample_2_2);
    out = node->update();
    EXPECT_EQ(1, out.time);
    EXPECT_EQ(-1.0/-2.0, out.value);
    
    node->addNewInput(sample_3_1, sample_3_2);
    out = node->update();
    EXPECT_EQ(2, out.time);
    EXPECT_EQ(-2.0/10.0, out.value);
    
    node->addNewInput(sample_4_1, sample_4_2);
    out = node->update();
    EXPECT_EQ(3, out.time);
    EXPECT_EQ(5.0/4.0, out.value);
    
    node->addNewInput(sample_5_1, sample_5_2);
    out = node->update();
    EXPECT_EQ(4, out.time);
    EXPECT_EQ(-1.0/-1.0, out.value);
    
    delete node;
}

TEST_F (StlNodeEvaluationTest, predicate_leq) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlPredicateNode *node = new StlPredicateNode(StlComparisonOperator::LEQ, var_1, var_2);
    
    Sample out;
    
    node->addNewInput(sample_1_1, sample_1_2);
    out = node->update();
    EXPECT_EQ(0, out.time);
    EXPECT_EQ(-80, out.value);
    
    node->addNewInput(sample_2_1, sample_2_2);
    out = node->update();
    EXPECT_EQ(1, out.time);
    EXPECT_EQ(-1, out.value);
    
    node->addNewInput(sample_3_1, sample_3_2);
    out = node->update();
    EXPECT_EQ(2, out.time);
    EXPECT_EQ(12, out.value);
    
    node->addNewInput(sample_4_1, sample_4_2);
    out = node->update();
    EXPECT_EQ(3, out.time);
    EXPECT_EQ(-1, out.value);
    
    node->addNewInput(sample_5_1, sample_5_2);
    out = node->update();
    EXPECT_EQ(4, out.time);
    EXPECT_EQ(0, out.value);
    
    delete node;
}

TEST_F (StlNodeEvaluationTest, predicate_leq_standard) {
    const std::string name_1 = "req";
    const std::string name_2 = "gnt";
    StlVariableNode *var_1 = new StlVariableNode(name_1, StlIOType::IN);
    StlVariableNode *var_2 = new StlVariableNode(name_2, StlIOType::OUT);
    StlPredicateNode *node = new StlPredicateNode(StlSemantics::STANDARD, StlComparisonOperator::LEQ, var_1, var_2);
    
    Sample out;
    
    node->addNewInput(sample_1_1, sample_1_2);
    out = node->update();
    EXPECT_EQ(0, out.time);
    EXPECT_EQ(-80, out.value);
    
    node->addNewInput(sample_2_1, sample_2_2);
    out = node->update();
    EXPECT_EQ(1, out.time);
    EXPECT_EQ(-1, out.value);
    
    node->addNewInput(sample_3_1, sample_3_2);
    out = node->update();
    EXPECT_EQ(2, out.time);
    EXPECT_EQ(12, out.value);
    
    node->addNewInput(sample_4_1, sample_4_2);
    out = node->update();
    EXPECT_EQ(3, out.time);
    EXPECT_EQ(-1, out.value);
    
    node->addNewInput(sample_5_1, sample_5_2);
    out = node->update();
    EXPECT_EQ(4, out.time);
    EXPECT_EQ(0, out.value);
    
    delete node;
}

TEST_F (StlNodeEvaluationTest, predicate_leq_in_vacuity) {
    const std::string name_1 = "req";
    const std::string name_2 = "gnt";
    StlVariableNode *var_1 = new StlVariableNode(name_1, StlIOType::OUT);
    StlVariableNode *var_2 = new StlVariableNode(name_2, StlIOType::OUT);
    StlPredicateNode *node = new StlPredicateNode(StlSemantics::IN_VACUITY, StlComparisonOperator::LEQ, var_1, var_2);
    
    Sample out;
    
    node->addNewInput(sample_1_1, sample_1_2);
    out = node->update();
    EXPECT_EQ(0, out.time);
    EXPECT_EQ(0, out.value);
    
    node->addNewInput(sample_2_1, sample_2_2);
    out = node->update();
    EXPECT_EQ(1, out.time);
    EXPECT_EQ(0, out.value);
    
    node->addNewInput(sample_3_1, sample_3_2);
    out = node->update();
    EXPECT_EQ(2, out.time);
    EXPECT_EQ(0, out.value);
    
    node->addNewInput(sample_4_1, sample_4_2);
    out = node->update();
    EXPECT_EQ(3, out.time);
    EXPECT_EQ(0, out.value);
    
    node->addNewInput(sample_5_1, sample_5_2);
    out = node->update();
    EXPECT_EQ(4, out.time);
    EXPECT_EQ(0, out.value);
    
    delete node;
}

TEST_F (StlNodeEvaluationTest, predicate_leq_in_robustness) {
    const std::string name_1 = "req";
    const std::string name_2 = "gnt";
    StlVariableNode *var_1 = new StlVariableNode(name_1, StlIOType::OUT);
    StlVariableNode *var_2 = new StlVariableNode(name_2, StlIOType::OUT);
    StlPredicateNode *node = new StlPredicateNode(StlSemantics::IN_ROBUSTNESS, StlComparisonOperator::LEQ, var_1, var_2);
    
    Sample out;
    
    node->addNewInput(sample_1_1, sample_1_2);
    out = node->update();
    EXPECT_EQ(0, out.time);
    EXPECT_EQ(-std::numeric_limits<double>::infinity(), out.value);
    
    node->addNewInput(sample_2_1, sample_2_2);
    out = node->update();
    EXPECT_EQ(1, out.time);
    EXPECT_EQ(-std::numeric_limits<double>::infinity(), out.value);
    
    node->addNewInput(sample_3_1, sample_3_2);
    out = node->update();
    EXPECT_EQ(2, out.time);
    EXPECT_EQ(std::numeric_limits<double>::infinity(), out.value);
    
    node->addNewInput(sample_4_1, sample_4_2);
    out = node->update();
    EXPECT_EQ(3, out.time);
    EXPECT_EQ(-std::numeric_limits<double>::infinity(), out.value);
    
    delete node;
}

TEST_F (StlNodeEvaluationTest, predicate_leq_out_robustness) {
    const std::string name_1 = "req";
    const std::string name_2 = "gnt";
    StlVariableNode *var_1 = new StlVariableNode(name_1, StlIOType::IN);
    StlVariableNode *var_2 = new StlVariableNode(name_2, StlIOType::IN);
    StlPredicateNode *node = new StlPredicateNode(StlSemantics::OUT_ROBUSTNESS, StlComparisonOperator::LEQ, var_1, var_2);
    
    Sample out;
    
    node->addNewInput(sample_1_1, sample_1_2);
    out = node->update();
    EXPECT_EQ(0, out.time);
    EXPECT_EQ(-std::numeric_limits<double>::infinity(), out.value);
    
    node->addNewInput(sample_2_1, sample_2_2);
    out = node->update();
    EXPECT_EQ(1, out.time);
    EXPECT_EQ(-std::numeric_limits<double>::infinity(), out.value);
    
    node->addNewInput(sample_3_1, sample_3_2);
    out = node->update();
    EXPECT_EQ(2, out.time);
    EXPECT_EQ(std::numeric_limits<double>::infinity(), out.value);
    
    node->addNewInput(sample_4_1, sample_4_2);
    out = node->update();
    EXPECT_EQ(3, out.time);
    EXPECT_EQ(-std::numeric_limits<double>::infinity(), out.value);
    
    delete node;
}

TEST_F (StlNodeEvaluationTest, predicate_leq_out_vacuity) {
    const std::string name_1 = "req";
    const std::string name_2 = "gnt";
    StlVariableNode *var_1 = new StlVariableNode(name_1, StlIOType::IN);
    StlVariableNode *var_2 = new StlVariableNode(name_2, StlIOType::IN);
    StlPredicateNode *node = new StlPredicateNode(StlSemantics::OUT_VACUITY, StlComparisonOperator::LEQ, var_1, var_2);
    
    Sample out;
    
    node->addNewInput(sample_1_1, sample_1_2);
    out = node->update();
    EXPECT_EQ(0, out.time);
    EXPECT_EQ(0, out.value);
    
    node->addNewInput(sample_2_1, sample_2_2);
    out = node->update();
    EXPECT_EQ(1, out.time);
    EXPECT_EQ(0, out.value);
    
    node->addNewInput(sample_3_1, sample_3_2);
    out = node->update();
    EXPECT_EQ(2, out.time);
    EXPECT_EQ(0, out.value);
    
    node->addNewInput(sample_4_1, sample_4_2);
    out = node->update();
    EXPECT_EQ(3, out.time);
    EXPECT_EQ(0, out.value);
    
    node->addNewInput(sample_5_1, sample_5_2);
    out = node->update();
    EXPECT_EQ(4, out.time);
    EXPECT_EQ(0, out.value);
    
    delete node;
}

TEST_F (StlNodeEvaluationTest, predicate_less) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlPredicateNode *node = new StlPredicateNode(StlComparisonOperator::LESS, var_1, var_2);
    
    Sample out;
    
    node->addNewInput(sample_1_1, sample_1_2);
    out = node->update();
    EXPECT_EQ(0, out.time);
    EXPECT_EQ(-80, out.value);
    
    node->addNewInput(sample_2_1, sample_2_2);
    out = node->update();
    EXPECT_EQ(1, out.time);
    EXPECT_EQ(-1, out.value);
    
    node->addNewInput(sample_3_1, sample_3_2);
    out = node->update();
    EXPECT_EQ(2, out.time);
    EXPECT_EQ(12, out.value);
    
    node->addNewInput(sample_4_1, sample_4_2);
    out = node->update();
    EXPECT_EQ(3, out.time);
    EXPECT_EQ(-1, out.value);
    
    node->addNewInput(sample_5_1, sample_5_2);
    out = node->update();
    EXPECT_EQ(4, out.time);
    EXPECT_EQ(0, out.value);
    
    delete node;
}

TEST_F (StlNodeEvaluationTest, predicate_geq) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlPredicateNode *node = new StlPredicateNode(StlComparisonOperator::GEQ, var_1, var_2);
    
    Sample out;
    
    node->addNewInput(sample_1_1, sample_1_2);
    out = node->update();
    EXPECT_EQ(0, out.time);
    EXPECT_EQ(80, out.value);
    
    node->addNewInput(sample_2_1, sample_2_2);
    out = node->update();
    EXPECT_EQ(1, out.time);
    EXPECT_EQ(1, out.value);
    
    node->addNewInput(sample_3_1, sample_3_2);
    out = node->update();
    EXPECT_EQ(2, out.time);
    EXPECT_EQ(-12, out.value);
    
    node->addNewInput(sample_4_1, sample_4_2);
    out = node->update();
    EXPECT_EQ(3, out.time);
    EXPECT_EQ(1, out.value);
    
    node->addNewInput(sample_5_1, sample_5_2);
    out = node->update();
    EXPECT_EQ(4, out.time);
    EXPECT_EQ(0, out.value);
    
    delete node;
}

TEST_F (StlNodeEvaluationTest, predicate_greater) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlPredicateNode *node = new StlPredicateNode(StlComparisonOperator::GREATER, var_1, var_2);
    
    Sample out;
    
    node->addNewInput(sample_1_1, sample_1_2);
    out = node->update();
    EXPECT_EQ(0, out.time);
    EXPECT_EQ(80, out.value);
    
    node->addNewInput(sample_2_1, sample_2_2);
    out = node->update();
    EXPECT_EQ(1, out.time);
    EXPECT_EQ(1, out.value);
    
    node->addNewInput(sample_3_1, sample_3_2);
    out = node->update();
    EXPECT_EQ(2, out.time);
    EXPECT_EQ(-12, out.value);
    
    node->addNewInput(sample_4_1, sample_4_2);
    out = node->update();
    EXPECT_EQ(3, out.time);
    EXPECT_EQ(1, out.value);
    
    node->addNewInput(sample_5_1, sample_5_2);
    out = node->update();
    EXPECT_EQ(4, out.time);
    EXPECT_EQ(0, out.value);
    
    delete node;
}

TEST_F (StlNodeEvaluationTest, predicate_eq) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlPredicateNode *node = new StlPredicateNode(StlComparisonOperator::EQUAL, var_1, var_2);
    
    Sample out;
    
    node->addNewInput(sample_1_1, sample_1_2);
    out = node->update();
    EXPECT_EQ(0, out.time);
    EXPECT_EQ(-80, out.value);
    
    node->addNewInput(sample_2_1, sample_2_2);
    out = node->update();
    EXPECT_EQ(1, out.time);
    EXPECT_EQ(-1, out.value);
    
    node->addNewInput(sample_3_1, sample_3_2);
    out = node->update();
    EXPECT_EQ(2, out.time);
    EXPECT_EQ(-12, out.value);
    
    node->addNewInput(sample_4_1, sample_4_2);
    out = node->update();
    EXPECT_EQ(3, out.time);
    EXPECT_EQ(-1, out.value);
    
    node->addNewInput(sample_5_1, sample_5_2);
    out = node->update();
    EXPECT_EQ(4, out.time);
    EXPECT_EQ(0, out.value);
    
    delete node;
}

TEST_F (StlNodeEvaluationTest, predicate_neq) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlPredicateNode *node = new StlPredicateNode(StlComparisonOperator::NEQ, var_1, var_2);
    
    Sample out;
    
    node->addNewInput(sample_1_1, sample_1_2);
    out = node->update();
    EXPECT_EQ(0, out.time);
    EXPECT_EQ(80, out.value);
    
    node->addNewInput(sample_2_1, sample_2_2);
    out = node->update();
    EXPECT_EQ(1, out.time);
    EXPECT_EQ(1, out.value);
    
    node->addNewInput(sample_3_1, sample_3_2);
    out = node->update();
    EXPECT_EQ(2, out.time);
    EXPECT_EQ(12, out.value);
    
    node->addNewInput(sample_4_1, sample_4_2);
    out = node->update();
    EXPECT_EQ(3, out.time);
    EXPECT_EQ(1, out.value);
    
    node->addNewInput(sample_5_1, sample_5_2);
    out = node->update();
    EXPECT_EQ(4, out.time);
    EXPECT_EQ(0, out.value);
    
    delete node;
}

TEST_F (StlNodeEvaluationTest, not) {
    const std::string name = "request"; 
    StlVariableNode *var = new StlVariableNode(name);
    StlNotNode *node = new StlNotNode(var);
    
    Sample out;
    
    node->addNewInput(this->sample_1_1);
    out = node->update();
    EXPECT_EQ(0, out.time);
    EXPECT_EQ(-100, out.value);
    
    node->addNewInput(this->sample_2_1);
    out = node->update();
    EXPECT_EQ(1, out.time);
    EXPECT_EQ(1, out.value);
    
    node->addNewInput(this->sample_3_1);
    out = node->update();
    EXPECT_EQ(2, out.time);
    EXPECT_EQ(2, out.value);
    
    node->addNewInput(this->sample_4_1);
    out = node->update();
    EXPECT_EQ(3, out.time);
    EXPECT_EQ(-5, out.value);
    
    node->addNewInput(this->sample_5_1);
    out = node->update();
    EXPECT_EQ(4, out.time);
    EXPECT_EQ(1, out.value);
    
    delete node;
}

TEST_F (StlNodeEvaluationTest, conjunction) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlAndNode *node = new StlAndNode(var_1, var_2);
    
    Sample out;
    
    node->addNewInput(sample_1_1, sample_1_2);
    out = node->update();
    EXPECT_EQ(0, out.time);
    EXPECT_EQ(20, out.value);
    
    node->addNewInput(sample_2_1, sample_2_2);
    out = node->update();
    EXPECT_EQ(1, out.time);
    EXPECT_EQ(-2, out.value);
    
    node->addNewInput(sample_3_1, sample_3_2);
    out = node->update();
    EXPECT_EQ(2, out.time);
    EXPECT_EQ(-2, out.value);
    
    node->addNewInput(sample_4_1, sample_4_2);
    out = node->update();
    EXPECT_EQ(3, out.time);
    EXPECT_EQ(4, out.value);
    
    node->addNewInput(sample_5_1, sample_5_2);
    out = node->update();
    EXPECT_EQ(4, out.time);
    EXPECT_EQ(-1, out.value);
    
    delete node;
}

TEST_F (StlNodeEvaluationTest, disjunction) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlOrNode *node = new StlOrNode(var_1, var_2);
    
    Sample out;
    
    node->addNewInput(sample_1_1, sample_1_2);
    out = node->update();
    EXPECT_EQ(0, out.time);
    EXPECT_EQ(100, out.value);
    
    node->addNewInput(sample_2_1, sample_2_2);
    out = node->update();
    EXPECT_EQ(1, out.time);
    EXPECT_EQ(-1, out.value);
    
    node->addNewInput(sample_3_1, sample_3_2);
    out = node->update();
    EXPECT_EQ(2, out.time);
    EXPECT_EQ(10, out.value);
    
    node->addNewInput(sample_4_1, sample_4_2);
    out = node->update();
    EXPECT_EQ(3, out.time);
    EXPECT_EQ(5, out.value);
    
    node->addNewInput(sample_5_1, sample_5_2);
    out = node->update();
    EXPECT_EQ(4, out.time);
    EXPECT_EQ(-1, out.value);
    
    delete node;
}

TEST_F (StlNodeEvaluationTest, implication) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlImpliesNode *node = new StlImpliesNode(var_1, var_2);
    
    Sample out;
    
    node->addNewInput(sample_1_1, sample_1_2);
    out = node->update();
    EXPECT_EQ(0, out.time);
    EXPECT_EQ(20, out.value);
    
    node->addNewInput(sample_2_1, sample_2_2);
    out = node->update();
    EXPECT_EQ(1, out.time);
    EXPECT_EQ(1, out.value);
    
    node->addNewInput(sample_3_1, sample_3_2);
    out = node->update();
    EXPECT_EQ(2, out.time);
    EXPECT_EQ(10, out.value);
    
    node->addNewInput(sample_4_1, sample_4_2);
    out = node->update();
    EXPECT_EQ(3, out.time);
    EXPECT_EQ(4, out.value);
    
    node->addNewInput(sample_5_1, sample_5_2);
    out = node->update();
    EXPECT_EQ(4, out.time);
    EXPECT_EQ(1, out.value);
    
    delete node;
}

TEST_F (StlNodeEvaluationTest, iff) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlIffNode *node = new StlIffNode(var_1, var_2);
    
    Sample out;
    
    node->addNewInput(sample_1_1, sample_1_2);
    out = node->update();
    EXPECT_EQ(0, out.time);
    EXPECT_EQ(-80, out.value);
    
    node->addNewInput(sample_2_1, sample_2_2);
    out = node->update();
    EXPECT_EQ(1, out.time);
    EXPECT_EQ(-1, out.value);
    
    node->addNewInput(sample_3_1, sample_3_2);
    out = node->update();
    EXPECT_EQ(2, out.time);
    EXPECT_EQ(-12, out.value);
    
    node->addNewInput(sample_4_1, sample_4_2);
    out = node->update();
    EXPECT_EQ(3, out.time);
    EXPECT_EQ(-1, out.value);
    
    node->addNewInput(sample_5_1, sample_5_2);
    out = node->update();
    EXPECT_EQ(4, out.time);
    EXPECT_EQ(0, out.value);
    
    delete node;
}

TEST_F (StlNodeEvaluationTest, xor) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlXorNode *node = new StlXorNode(var_1, var_2);
    
    Sample out;
    
    node->addNewInput(sample_1_1, sample_1_2);
    out = node->update();
    EXPECT_EQ(0, out.time);
    EXPECT_EQ(80, out.value);
    
    node->addNewInput(sample_2_1, sample_2_2);
    out = node->update();
    EXPECT_EQ(1, out.time);
    EXPECT_EQ(1, out.value);
    
    node->addNewInput(sample_3_1, sample_3_2);
    out = node->update();
    EXPECT_EQ(2, out.time);
    EXPECT_EQ(12, out.value);
    
    node->addNewInput(sample_4_1, sample_4_2);
    out = node->update();
    EXPECT_EQ(3, out.time);
    EXPECT_EQ(1, out.value);
    
    node->addNewInput(sample_5_1, sample_5_2);
    out = node->update();
    EXPECT_EQ(4, out.time);
    EXPECT_EQ(0, out.value);
    
    delete node;
}

TEST_F (StlNodeEvaluationTest, rise) {
    const std::string name = "request"; 
    StlVariableNode *var = new StlVariableNode(name);
    StlRiseNode *node = new StlRiseNode(var);
    
    Sample out;
    
    node->addNewInput(this->sample_1_1);
    out = node->update();
    EXPECT_EQ(0, out.time);
    EXPECT_EQ(100, out.value);
    
    node->addNewInput(this->sample_2_1);
    out = node->update();
    EXPECT_EQ(1, out.time);
    EXPECT_EQ(-100, out.value);
    
    node->addNewInput(this->sample_3_1);
    out = node->update();
    EXPECT_EQ(2, out.time);
    EXPECT_EQ(-2, out.value);
    
    node->addNewInput(this->sample_4_1);
    out = node->update();
    EXPECT_EQ(3, out.time);
    EXPECT_EQ(2, out.value);
    
    node->addNewInput(this->sample_5_1);
    out = node->update();
    EXPECT_EQ(4, out.time);
    EXPECT_EQ(-5, out.value);
    
    delete node;
}

TEST_F (StlNodeEvaluationTest, fall) {
    const std::string name = "request"; 
    StlVariableNode *var = new StlVariableNode(name);
    StlFallNode *node = new StlFallNode(var);
    
    Sample out;
    
    node->addNewInput(this->sample_1_1);
    out = node->update();
    EXPECT_EQ(0, out.time);
    EXPECT_EQ(-100, out.value);
    
    node->addNewInput(this->sample_2_1);
    out = node->update();
    EXPECT_EQ(1, out.time);
    EXPECT_EQ(1, out.value);
    
    node->addNewInput(this->sample_3_1);
    out = node->update();
    EXPECT_EQ(2, out.time);
    EXPECT_EQ(-1, out.value);
    
    node->addNewInput(this->sample_4_1);
    out = node->update();
    EXPECT_EQ(3, out.time);
    EXPECT_EQ(-5, out.value);
    
    node->addNewInput(this->sample_5_1);
    out = node->update();
    EXPECT_EQ(4, out.time);
    EXPECT_EQ(1, out.value);
    
    delete node;
}

TEST_F (StlNodeEvaluationTest, once) {
    const std::string name = "request"; 
    StlVariableNode *var = new StlVariableNode(name);
    StlOnceNode *node = new StlOnceNode(var);
    
    Sample out;
    
    node->addNewInput(this->sample_1_1);
    out = node->update();
    EXPECT_EQ(0, out.time);
    EXPECT_EQ(100, out.value);
    
    node->addNewInput(this->sample_2_1);
    out = node->update();
    EXPECT_EQ(1, out.time);
    EXPECT_EQ(100, out.value);
    
    node->addNewInput(this->sample_3_1);
    out = node->update();
    EXPECT_EQ(2, out.time);
    EXPECT_EQ(100, out.value);
    
    node->addNewInput(this->sample_4_1);
    out = node->update();
    EXPECT_EQ(3, out.time);
    EXPECT_EQ(100, out.value);
    
    node->addNewInput(this->sample_5_1);
    out = node->update();
    EXPECT_EQ(4, out.time);
    EXPECT_EQ(100, out.value);
    
    delete node;
}

TEST_F (StlNodeEvaluationTest, historically) {
    const std::string name = "request"; 
    StlVariableNode *var = new StlVariableNode(name);
    StlHistoricallyNode *node = new StlHistoricallyNode(var);
    
    Sample out;
    
    node->addNewInput(this->sample_1_1);
    out = node->update();
    EXPECT_EQ(0, out.time);
    EXPECT_EQ(100, out.value);
    
    node->addNewInput(this->sample_2_1);
    out = node->update();
    EXPECT_EQ(1, out.time);
    EXPECT_EQ(-1, out.value);
    
    node->addNewInput(this->sample_3_1);
    out = node->update();
    EXPECT_EQ(2, out.time);
    EXPECT_EQ(-2, out.value);
    
    node->addNewInput(this->sample_4_1);
    out = node->update();
    EXPECT_EQ(3, out.time);
    EXPECT_EQ(-2, out.value);
    
    node->addNewInput(this->sample_5_1);
    out = node->update();
    EXPECT_EQ(4, out.time);
    EXPECT_EQ(-2, out.value);
    
    delete node;
}

TEST_F (StlNodeEvaluationTest, eventually) {
    const std::string name = "request"; 
    StlVariableNode *var = new StlVariableNode(name);
    StlEventuallyNode *node = new StlEventuallyNode(var);
    
    Sample out;
    
    node->addNewInput(this->sample_1_1);
    out = node->update();
    EXPECT_EQ(0, out.time);
    EXPECT_EQ(100, out.value);
    
    node->addNewInput(this->sample_2_1);
    out = node->update();
    EXPECT_EQ(1, out.time);
    EXPECT_EQ(100, out.value);
    
    node->addNewInput(this->sample_3_1);
    out = node->update();
    EXPECT_EQ(2, out.time);
    EXPECT_EQ(100, out.value);
    
    node->addNewInput(this->sample_4_1);
    out = node->update();
    EXPECT_EQ(3, out.time);
    EXPECT_EQ(100, out.value);
    
    node->addNewInput(this->sample_5_1);
    out = node->update();
    EXPECT_EQ(4, out.time);
    EXPECT_EQ(100, out.value);
    
    delete node;
}

TEST_F (StlNodeEvaluationTest, always) {
    const std::string name = "request"; 
    StlVariableNode *var = new StlVariableNode(name);
    StlAlwaysNode *node = new StlAlwaysNode(var);
    
    Sample out;
    
    node->addNewInput(this->sample_1_1);
    out = node->update();
    EXPECT_EQ(0, out.time);
    EXPECT_EQ(100, out.value);
    
    node->addNewInput(this->sample_2_1);
    out = node->update();
    EXPECT_EQ(1, out.time);
    EXPECT_EQ(-1, out.value);
    
    node->addNewInput(this->sample_3_1);
    out = node->update();
    EXPECT_EQ(2, out.time);
    EXPECT_EQ(-2, out.value);
    
    node->addNewInput(this->sample_4_1);
    out = node->update();
    EXPECT_EQ(3, out.time);
    EXPECT_EQ(-2, out.value);
    
    node->addNewInput(this->sample_5_1);
    out = node->update();
    EXPECT_EQ(4, out.time);
    EXPECT_EQ(-2, out.value);
    
    delete node;
}

TEST_F (StlNodeEvaluationTest, since) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlSinceNode *node = new StlSinceNode(var_1, var_2);
    
    Sample out;
    
    node->addNewInput(sample_1_1, sample_1_2);
    out = node->update();
    EXPECT_EQ(0, out.time);
    EXPECT_EQ(20, out.value);
    
    node->addNewInput(sample_2_1, sample_2_2);
    out = node->update();
    EXPECT_EQ(1, out.time);
    EXPECT_EQ(-1, out.value);
    
    node->addNewInput(sample_3_1, sample_3_2);
    out = node->update();
    EXPECT_EQ(2, out.time);
    EXPECT_EQ(10, out.value);
    
    node->addNewInput(sample_4_1, sample_4_2);
    out = node->update();
    EXPECT_EQ(3, out.time);
    EXPECT_EQ(5, out.value);
    
    node->addNewInput(sample_5_1, sample_5_2);
    out = node->update();
    EXPECT_EQ(4, out.time);
    EXPECT_EQ(-1, out.value);
    
    delete node;
}

TEST_F (StlNodeEvaluationTest, once_bounded_0_1) {
    const std::string name = "request"; 
    StlVariableNode *var = new StlVariableNode(name);
    StlOnceBoundedNode *node = new StlOnceBoundedNode(0, 1, var, true);
    
    Sample out;
    
    node->addNewInput(this->sample_1_1);
    out = node->update();
    EXPECT_EQ(0, out.time);
    EXPECT_EQ(100, out.value);
    
    node->addNewInput(this->sample_2_1);
    out = node->update();
    EXPECT_EQ(1, out.time);
    EXPECT_EQ(100, out.value);
    
    node->addNewInput(this->sample_3_1);
    out = node->update();
    EXPECT_EQ(2, out.time);
    EXPECT_EQ(-1, out.value);
    
    node->addNewInput(this->sample_4_1);
    out = node->update();
    EXPECT_EQ(3, out.time);
    EXPECT_EQ(5, out.value);
    
    node->addNewInput(this->sample_5_1);
    out = node->update();
    EXPECT_EQ(4, out.time);
    EXPECT_EQ(5, out.value);
    
    delete node;
}

TEST_F (StlNodeEvaluationTest, historically_bounded_0_1) {
    const std::string name = "request"; 
    StlVariableNode *var = new StlVariableNode(name);
    StlHistoricallyBoundedNode *node = new StlHistoricallyBoundedNode(0, 1, var, true);
    
    Sample out;
    
    node->addNewInput(this->sample_1_1);
    out = node->update();
    EXPECT_EQ(0, out.time);
    EXPECT_EQ(100, out.value);
    
    node->addNewInput(this->sample_2_1);
    out = node->update();
    EXPECT_EQ(1, out.time);
    EXPECT_EQ(-1, out.value);
    
    node->addNewInput(this->sample_3_1);
    out = node->update();
    EXPECT_EQ(2, out.time);
    EXPECT_EQ(-2, out.value);
    
    node->addNewInput(this->sample_4_1);
    out = node->update();
    EXPECT_EQ(3, out.time);
    EXPECT_EQ(-2, out.value);
    
    node->addNewInput(this->sample_5_1);
    out = node->update();
    EXPECT_EQ(4, out.time);
    EXPECT_EQ(-1, out.value);
    
    delete node;
}

TEST_F (StlNodeEvaluationTest, eventually_bounded) {
    const std::string name = "request"; 
    StlVariableNode *var = new StlVariableNode(name);
    StlEventuallyBoundedNode *node = new StlEventuallyBoundedNode(4, 5, var);
            
    try {
        node->addNewInput(this->sample_1_1);
        node->update();
        FAIL() << "Expected StlNodeException and the execution succeeded";
    }
    catch(StlNodeException const & err) {
        SUCCEED() << err.what();
    }
    catch(...) {
        FAIL() << "Expected StlNodeException and the excution returned a different exception";
    }
    
    delete node;
}

TEST_F (StlNodeEvaluationTest, eventually_bounded_update_exception) {
    const std::string name = "request"; 
    StlVariableNode *var = new StlVariableNode(name);
    StlEventuallyBoundedNode *node = new StlEventuallyBoundedNode(4, 5, var);
            
    try {
        node->update();
        FAIL() << "Expected StlNodeException and the execution succeeded";
    }
    catch(StlNodeException const & err) {
        SUCCEED() << err.what();
    }
    catch(...) {
        FAIL() << "Expected StlNodeException and the excution returned a different exception";
    }
    
    delete node;
}

TEST_F (StlNodeEvaluationTest, always_bounded) {
    const std::string name = "request"; 
    StlVariableNode *var = new StlVariableNode(name);
    StlAlwaysBoundedNode *node = new StlAlwaysBoundedNode(0, 3, var);
        
    try {
        node->addNewInput(this->sample_1_1);
        node->update();
        FAIL() << "Expected StlNodeException and the execution succeeded";
    }
    catch(StlNodeException const & err) {
        SUCCEED() << err.what();
    }
    catch(...) {
        FAIL() << "Expected StlNodeException and the excution returned a different exception";
    }
    
    delete node;
}

TEST_F (StlNodeEvaluationTest, always_bounded_update_exception) {
    const std::string name = "request"; 
    StlVariableNode *var = new StlVariableNode(name);
    StlAlwaysBoundedNode *node = new StlAlwaysBoundedNode(0, 3, var);
        
    try {
        node->update();
        FAIL() << "Expected StlNodeException and the execution succeeded";
    }
    catch(StlNodeException const & err) {
        SUCCEED() << err.what();
    }
    catch(...) {
        FAIL() << "Expected StlNodeException and the excution returned a different exception";
    }
    
    delete node;
}

TEST_F (StlNodeEvaluationTest, since_bounded_0_1) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlSinceBoundedNode *node = new StlSinceBoundedNode(0, 1, var_1, var_2, true);
    
    Sample out;
    
    node->addNewInput(sample_1_1, sample_1_2);
    out = node->update();
    EXPECT_EQ(0, out.time);
    EXPECT_EQ(20, out.value);
    
    node->addNewInput(sample_2_1, sample_2_2);
    out = node->update();
    EXPECT_EQ(1, out.time);
    EXPECT_EQ(-1, out.value);
    
    node->addNewInput(sample_3_1, sample_3_2);
    out = node->update();
    EXPECT_EQ(2, out.time);
    EXPECT_EQ(10, out.value);
    
    node->addNewInput(sample_4_1, sample_4_2);
    out = node->update();
    EXPECT_EQ(3, out.time);
    EXPECT_EQ(5, out.value);
    
    node->addNewInput(sample_5_1, sample_5_2);
    out = node->update();
    EXPECT_EQ(4, out.time);
    EXPECT_EQ(-1, out.value);
    
    delete node;
}

TEST_F (StlNodeEvaluationTest, until_bounded) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlUntilBoundedNode *node = new StlUntilBoundedNode(1, 2, var_1, var_2);
    
    
    try {
        node->addNewInput(sample_1_1, sample_1_2);
        node->update();
        FAIL() << "Expected StlNodeException and the execution succeeded";
    }
    catch(StlNodeException const & err) {
        SUCCEED() << err.what();
    }
    catch(...) {
        FAIL() << "Expected StlNodeException and the excution returned a different exception";
    }
    
    delete node;
}

TEST_F (StlNodeEvaluationTest, until_bounded_update_exception) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlUntilBoundedNode *node = new StlUntilBoundedNode(1, 2, var_1, var_2);
    
    
    try {
        node->update();
        FAIL() << "Expected StlNodeException and the execution succeeded";
    }
    catch(StlNodeException const & err) {
        SUCCEED() << err.what();
    }
    catch(...) {
        FAIL() << "Expected StlNodeException and the excution returned a different exception";
    }
    
    delete node;
}

TEST_F (StlNodeEvaluationTest, precedes_bounded_0_1) {
    const std::string name_1 = "request"; 
    const std::string name_2 = "grant";
    StlVariableNode *var_1 = new StlVariableNode(name_1);
    StlVariableNode *var_2 = new StlVariableNode(name_2);
    StlPrecedesBoundedNode *node = new StlPrecedesBoundedNode(1, 2, var_1, var_2, true);
    
    Sample out;
    
    node->addNewInput(sample_1_1, sample_1_2);
    out = node->update();
    EXPECT_EQ(0, out.time);
    EXPECT_EQ(20, out.value);
    
    node->addNewInput(sample_2_1, sample_2_2);
    out = node->update();
    EXPECT_EQ(1, out.time);
    EXPECT_EQ(20, out.value);
    
    node->addNewInput(sample_3_1, sample_3_2);
    out = node->update();
    EXPECT_EQ(2, out.time);
    EXPECT_EQ(-1, out.value);
    
    node->addNewInput(sample_4_1, sample_4_2);
    out = node->update();
    EXPECT_EQ(3, out.time);
    EXPECT_EQ(-1, out.value);
    
    node->addNewInput(sample_5_1, sample_5_2);
    out = node->update();
    EXPECT_EQ(4, out.time);
    EXPECT_EQ(-2, out.value);
    
    delete node;
}
