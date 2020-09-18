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
#include <spec/stl_evaluation.hpp>
#include <rtamt/stl_exception.hpp>
#include <rtamt/stl_specification.hpp>


using namespace rtamt;
using namespace spec;
using namespace node;

class StlEvaluationTest : public ::testing::Test {
    protected:
        StlEvaluation *monitor = nullptr;
        
        Input input_1_1{"req", 100};
        Input input_1_2{"gnt", 20};

        Input input_2_1{"req", -1};
        Input input_2_2{"gnt", -2};

        Input input_3_1{"req", -2};
        Input input_3_2{"gnt", 10};

        Input input_4_1{"req", 5};
        Input input_4_2{"gnt", 4};

        Input input_5_1{"req", -1};
        Input input_5_2{"gnt", -1};
        
        std::vector<Input> single_input_1;
        std::vector<Input> single_input_2;
        std::vector<Input> single_input_3;
        std::vector<Input> single_input_4;
        std::vector<Input> single_input_5;
        
        std::vector<Input> double_input_1;
        std::vector<Input> double_input_2;
        std::vector<Input> double_input_3;
        std::vector<Input> double_input_4;
        std::vector<Input> double_input_5;

        virtual void SetUp() {
            single_input_1.push_back(input_1_1);
            double_input_1.push_back(input_1_1);
            double_input_1.push_back(input_1_2);

            single_input_2.push_back(input_2_1);
            double_input_2.push_back(input_2_1);
            double_input_2.push_back(input_2_2);

            single_input_3.push_back(input_3_1);
            double_input_3.push_back(input_3_1);
            double_input_3.push_back(input_3_2);

            single_input_4.push_back(input_4_1);
            double_input_4.push_back(input_4_1);
            double_input_4.push_back(input_4_2);

            single_input_5.push_back(input_5_1);
            double_input_5.push_back(input_5_1);
            double_input_5.push_back(input_5_2);
        }
};


TEST_F (StlEvaluationTest, constant) {
    double val = 5;
    StlConstantNode *node = new StlConstantNode(val);
    std::set<std::string> set {}; 
    std::map<std::string, rtamt::StlIOType> map {};
    StlEvaluation monitor(node, set, map);
    
    std::vector<Input> input_list = {};
    
    double out;
    out = monitor.update(0, input_list);
    
    EXPECT_EQ(5, out);
    
    delete node;
}

TEST_F (StlEvaluationTest, variable) {
    const std::string name{"req"};
    std::set<std::string> set {name}; 

    StlVariableNode *node = new StlVariableNode(name);
    std::map<std::string, rtamt::StlIOType> map {};
    StlEvaluation monitor(node, set, map);
    
    double out;
    
    out = monitor.update(0, single_input_1);
    EXPECT_EQ(100, out);
    
    out = monitor.update(1, single_input_2);
    EXPECT_EQ(-1, out);
    
    out = monitor.update(2, single_input_3);
    EXPECT_EQ(-2, out);
    
    out = monitor.update(3, single_input_4);
    EXPECT_EQ(5, out);
    
    out = monitor.update(4, single_input_5);
    EXPECT_EQ(-1, out);
    
    delete node;
}

TEST_F (StlEvaluationTest, abs) {
    const std::string name{"req"};
    std::set<std::string> set {name}; 

    StlVariableNode *tmp = new StlVariableNode(name);
    StlAbsNode *node = new StlAbsNode(tmp);
    
    std::map<std::string, rtamt::StlIOType> map {};
    StlEvaluation monitor(node, set, map);    
    
    double out;
    
    out = monitor.update(0, single_input_1);
    EXPECT_EQ(100, out);
    
    out = monitor.update(1, single_input_2);
    EXPECT_EQ(1, out);
    
    out = monitor.update(2, single_input_3);
    EXPECT_EQ(2, out);
    
    out = monitor.update(3, single_input_4);
    EXPECT_EQ(5, out);
    
    out = monitor.update(4, single_input_5);
    EXPECT_EQ(1, out);
    
    delete node;
}

TEST_F (StlEvaluationTest, addition) {
    const std::string name_1{"req"};
    const std::string name_2{"gnt"};
    std::set<std::string> set {name_1, name_2}; 

    StlVariableNode *tmp_1 = new StlVariableNode(name_1);
    StlVariableNode *tmp_2 = new StlVariableNode(name_2);
    StlAdditionNode *node = new StlAdditionNode(tmp_1, tmp_2);
    
    std::map<std::string, rtamt::StlIOType> map {};
    StlEvaluation monitor(node, set, map);
    
    double out;
    
    out = monitor.update(0, double_input_1);
    EXPECT_EQ(120, out);
    
    out = monitor.update(1, double_input_2);
    EXPECT_EQ(-3, out);
    
    out = monitor.update(2, double_input_3);
    EXPECT_EQ(8, out);
    
    out = monitor.update(3, double_input_4);
    EXPECT_EQ(9, out);
    
    out = monitor.update(4, double_input_5);
    EXPECT_EQ(-2, out);
    
    delete node;
}

TEST_F (StlEvaluationTest, subtraction) {
    const std::string name_1{"req"};
    const std::string name_2{"gnt"};
    std::set<std::string> set {name_1, name_2}; 

    StlVariableNode *tmp_1 = new StlVariableNode(name_1);
    StlVariableNode *tmp_2 = new StlVariableNode(name_2);
    StlSubtractionNode *node = new StlSubtractionNode(tmp_1, tmp_2);
    
    std::map<std::string, rtamt::StlIOType> map {};
    StlEvaluation monitor(node, set, map);    
    double out;
    
    out = monitor.update(0, double_input_1);
    EXPECT_EQ(80, out);
    
    out = monitor.update(1, double_input_2);
    EXPECT_EQ(1, out);
    
    out = monitor.update(2, double_input_3);
    EXPECT_EQ(-12, out);
    
    out = monitor.update(3, double_input_4);
    EXPECT_EQ(1, out);
    
    out = monitor.update(4, double_input_5);
    EXPECT_EQ(0, out);
    
    delete node;
}

TEST_F (StlEvaluationTest, multiplication) {
    const std::string name_1{"req"};
    const std::string name_2{"gnt"};
    std::set<std::string> set {name_1, name_2}; 

    StlVariableNode *tmp_1 = new StlVariableNode(name_1);
    StlVariableNode *tmp_2 = new StlVariableNode(name_2);
    StlMultiplicationNode *node = new StlMultiplicationNode(tmp_1, tmp_2);
    
    std::map<std::string, rtamt::StlIOType> map {};
    StlEvaluation monitor(node, set, map);
    
    double out;
    
    out = monitor.update(0, double_input_1);
    EXPECT_EQ(2000, out);
    
    out = monitor.update(1, double_input_2);
    EXPECT_EQ(2, out);
    
    out = monitor.update(2, double_input_3);
    EXPECT_EQ(-20, out);
    
    out = monitor.update(3, double_input_4);
    EXPECT_EQ(20, out);
    
    out = monitor.update(4, double_input_5);
    EXPECT_EQ(1, out);
    
    delete node;
}

TEST_F (StlEvaluationTest, division) {
    const std::string name_1{"req"};
    const std::string name_2{"gnt"};
    std::set<std::string> set {name_1, name_2}; 

    StlVariableNode *tmp_1 = new StlVariableNode(name_1);
    StlVariableNode *tmp_2 = new StlVariableNode(name_2);
    StlDivisionNode *node = new StlDivisionNode(tmp_1, tmp_2);
    
    std::map<std::string, rtamt::StlIOType> map {};
    StlEvaluation monitor(node, set, map);
    
    double out;
    
    out = monitor.update(0, double_input_1);
    EXPECT_EQ(100.0/20.0, out);
    
    out = monitor.update(1, double_input_2);
    EXPECT_EQ(-1.0/-2.0, out);
    
    out = monitor.update(2, double_input_3);
    EXPECT_EQ(-2.0/10.00, out);
    
    out = monitor.update(3, double_input_4);
    EXPECT_EQ(5.0/4.0, out);
    
    out = monitor.update(4, double_input_5);
    EXPECT_EQ(-1.0/-1.0, out);
    
    delete node;
}

TEST_F (StlEvaluationTest, predicate_leq) {
    const std::string name_1{"req"};
    const std::string name_2{"gnt"};
    std::set<std::string> set {name_1, name_2}; 

    StlVariableNode *tmp_1 = new StlVariableNode(name_1);
    StlVariableNode *tmp_2 = new StlVariableNode(name_2);
    StlPredicateNode *node = new StlPredicateNode(StlComparisonOperator::LEQ, tmp_1, tmp_2);    
    
    std::map<std::string, rtamt::StlIOType> map {};
    StlEvaluation monitor(node, set, map);
    
    double out;
    
    out = monitor.update(0, double_input_1);
    EXPECT_EQ(-80, out);
    
    out = monitor.update(1, double_input_2);
    EXPECT_EQ(-1, out);
    
    out = monitor.update(2, double_input_3);
    EXPECT_EQ(12, out);
    
    out = monitor.update(3, double_input_4);
    EXPECT_EQ(-1, out);
    
    out = monitor.update(4, double_input_5);
    EXPECT_EQ(0, out);
    
    delete node;
}

TEST_F (StlEvaluationTest, predicate_less) {
    const std::string name_1{"req"};
    const std::string name_2{"gnt"};
    std::set<std::string> set {name_1, name_2}; 

    StlVariableNode *tmp_1 = new StlVariableNode(name_1);
    StlVariableNode *tmp_2 = new StlVariableNode(name_2);
    StlPredicateNode *node = new StlPredicateNode(StlComparisonOperator::LESS, tmp_1, tmp_2);    
    
    std::map<std::string, rtamt::StlIOType> map {};
    StlEvaluation monitor(node, set, map);
    
    double out;
    
    out = monitor.update(0, double_input_1);
    EXPECT_EQ(-80, out);
    
    out = monitor.update(1, double_input_2);
    EXPECT_EQ(-1, out);
    
    out = monitor.update(2, double_input_3);
    EXPECT_EQ(12, out);
    
    out = monitor.update(3, double_input_4);
    EXPECT_EQ(-1, out);
    
    out = monitor.update(4, double_input_5);
    EXPECT_EQ(0, out);
    
    delete node;
}

TEST_F (StlEvaluationTest, predicate_geq) {
    const std::string name_1{"req"};
    const std::string name_2{"gnt"};
    std::set<std::string> set {name_1, name_2}; 

    StlVariableNode *tmp_1 = new StlVariableNode(name_1);
    StlVariableNode *tmp_2 = new StlVariableNode(name_2);
    StlPredicateNode *node = new StlPredicateNode(StlComparisonOperator::GEQ, tmp_1, tmp_2);    
    
    std::map<std::string, rtamt::StlIOType> map {};
    StlEvaluation monitor(node, set, map);
    
    double out;
    
    out = monitor.update(0, double_input_1);
    EXPECT_EQ(80, out);
    
    out = monitor.update(1, double_input_2);
    EXPECT_EQ(1, out);
    
    out = monitor.update(2, double_input_3);
    EXPECT_EQ(-12, out);
    
    out = monitor.update(3, double_input_4);
    EXPECT_EQ(1, out);
    
    out = monitor.update(4, double_input_5);
    EXPECT_EQ(0, out);
    
    delete node;
}

TEST_F (StlEvaluationTest, predicate_greater) {
    const std::string name_1{"req"};
    const std::string name_2{"gnt"};
    std::set<std::string> set {name_1, name_2}; 

    StlVariableNode *tmp_1 = new StlVariableNode(name_1);
    StlVariableNode *tmp_2 = new StlVariableNode(name_2);
    StlPredicateNode *node = new StlPredicateNode(StlComparisonOperator::GEQ, tmp_1, tmp_2);    
    
    std::map<std::string, rtamt::StlIOType> map {};
    StlEvaluation monitor(node, set, map);
    
    double out;
    
    out = monitor.update(0, double_input_1);
    EXPECT_EQ(80, out);
    
    out = monitor.update(1, double_input_2);
    EXPECT_EQ(1, out);
    
    out = monitor.update(2, double_input_3);
    EXPECT_EQ(-12, out);
    
    out = monitor.update(3, double_input_4);
    EXPECT_EQ(1, out);
    
    out = monitor.update(4, double_input_5);
    EXPECT_EQ(0, out);
    
    delete node;
}

TEST_F (StlEvaluationTest, predicate_eq) {
    const std::string name_1{"req"};
    const std::string name_2{"gnt"};
    std::set<std::string> set {name_1, name_2}; 

    StlVariableNode *tmp_1 = new StlVariableNode(name_1);
    StlVariableNode *tmp_2 = new StlVariableNode(name_2);
    StlPredicateNode *node = new StlPredicateNode(StlComparisonOperator::EQUAL, tmp_1, tmp_2);    
    
    std::map<std::string, rtamt::StlIOType> map {};
    StlEvaluation monitor(node, set, map);
    
    double out;
    
    out = monitor.update(0, double_input_1);
    EXPECT_EQ(-80, out);
    
    out = monitor.update(1, double_input_2);
    EXPECT_EQ(-1, out);
    
    out = monitor.update(2, double_input_3);
    EXPECT_EQ(-12, out);
    
    out = monitor.update(3, double_input_4);
    EXPECT_EQ(-1, out);
    
    out = monitor.update(4, double_input_5);
    EXPECT_EQ(0, out);
    
    delete node;
}

TEST_F (StlEvaluationTest, predicate_neq) {
    const std::string name_1{"req"};
    const std::string name_2{"gnt"};
    std::set<std::string> set {name_1, name_2}; 

    StlVariableNode *tmp_1 = new StlVariableNode(name_1);
    StlVariableNode *tmp_2 = new StlVariableNode(name_2);
    StlPredicateNode *node = new StlPredicateNode(StlComparisonOperator::NEQ, tmp_1, tmp_2);    
    
    std::map<std::string, rtamt::StlIOType> map {};
    StlEvaluation monitor(node, set, map);
    
    double out;
    
    out = monitor.update(0, double_input_1);
    EXPECT_EQ(80, out);
    
    out = monitor.update(1, double_input_2);
    EXPECT_EQ(1, out);
    
    out = monitor.update(2, double_input_3);
    EXPECT_EQ(12, out);
    
    out = monitor.update(3, double_input_4);
    EXPECT_EQ(1, out);
    
    out = monitor.update(4, double_input_5);
    EXPECT_EQ(0, out);
    
    delete node;
}

TEST_F (StlEvaluationTest, not) {
    const std::string name{"req"};
    std::set<std::string> set {name}; 

    StlVariableNode *tmp = new StlVariableNode(name);
    StlNotNode *node = new StlNotNode(tmp);
    
    std::map<std::string, rtamt::StlIOType> map {};
    StlEvaluation monitor(node, set, map);
    
    double out;
    
    out = monitor.update(0, single_input_1);
    EXPECT_EQ(-100, out);
    
    out = monitor.update(1, single_input_2);
    EXPECT_EQ(1, out);
    
    out = monitor.update(2, single_input_3);
    EXPECT_EQ(2, out);
    
    out = monitor.update(3, single_input_4);
    EXPECT_EQ(-5, out);
    
    out = monitor.update(4, single_input_5);
    EXPECT_EQ(1, out);
    
    delete node;
}

TEST_F (StlEvaluationTest, conjunction) {
    const std::string name_1{"req"};
    const std::string name_2{"gnt"};
    std::set<std::string> set {name_1, name_2}; 

    StlVariableNode *tmp_1 = new StlVariableNode(name_1);
    StlVariableNode *tmp_2 = new StlVariableNode(name_2);
    StlAndNode *node = new StlAndNode(tmp_1, tmp_2);    
    
    std::map<std::string, rtamt::StlIOType> map {};
    StlEvaluation monitor(node, set, map);
    
    double out;
    
    out = monitor.update(0, double_input_1);
    EXPECT_EQ(20, out);
    
    out = monitor.update(1, double_input_2);
    EXPECT_EQ(-2, out);
    
    out = monitor.update(2, double_input_3);
    EXPECT_EQ(-2, out);
    
    out = monitor.update(3, double_input_4);
    EXPECT_EQ(4, out);
    
    out = monitor.update(4, double_input_5);
    EXPECT_EQ(-1, out);
    
    delete node;
}

TEST_F (StlEvaluationTest, disjunction) {
    const std::string name_1{"req"};
    const std::string name_2{"gnt"};
    std::set<std::string> set {name_1, name_2}; 

    StlVariableNode *tmp_1 = new StlVariableNode(name_1);
    StlVariableNode *tmp_2 = new StlVariableNode(name_2);
    StlOrNode *node = new StlOrNode(tmp_1, tmp_2);    
    
    std::map<std::string, rtamt::StlIOType> map {};
    StlEvaluation monitor(node, set, map);
    
    double out;
    
    out = monitor.update(0, double_input_1);
    EXPECT_EQ(100, out);
    
    out = monitor.update(1, double_input_2);
    EXPECT_EQ(-1, out);
    
    out = monitor.update(2, double_input_3);
    EXPECT_EQ(10, out);
    
    out = monitor.update(3, double_input_4);
    EXPECT_EQ(5, out);
    
    out = monitor.update(4, double_input_5);
    EXPECT_EQ(-1, out);
    
    delete node;
}

TEST_F (StlEvaluationTest, implication) {
    const std::string name_1{"req"};
    const std::string name_2{"gnt"};
    std::set<std::string> set {name_1, name_2}; 

    StlVariableNode *tmp_1 = new StlVariableNode(name_1);
    StlVariableNode *tmp_2 = new StlVariableNode(name_2);
    StlImpliesNode *node = new StlImpliesNode(tmp_1, tmp_2);    
    
    std::map<std::string, rtamt::StlIOType> map {};
    StlEvaluation monitor(node, set, map);
    
    double out;
    
    out = monitor.update(0, double_input_1);
    EXPECT_EQ(20, out);
    
    out = monitor.update(1, double_input_2);
    EXPECT_EQ(1, out);
    
    out = monitor.update(2, double_input_3);
    EXPECT_EQ(10, out);
    
    out = monitor.update(3, double_input_4);
    EXPECT_EQ(4, out);
    
    out = monitor.update(4, double_input_5);
    EXPECT_EQ(1, out);
    
    delete node;
}

TEST_F (StlEvaluationTest, iff) {
    const std::string name_1{"req"};
    const std::string name_2{"gnt"};
    std::set<std::string> set {name_1, name_2}; 

    StlVariableNode *tmp_1 = new StlVariableNode(name_1);
    StlVariableNode *tmp_2 = new StlVariableNode(name_2);
    StlIffNode *node = new StlIffNode(tmp_1, tmp_2);    
    
    std::map<std::string, rtamt::StlIOType> map {};
    StlEvaluation monitor(node, set, map);
    
    double out;
    
    out = monitor.update(0, double_input_1);
    EXPECT_EQ(-80, out);
    
    out = monitor.update(1, double_input_2);
    EXPECT_EQ(-1, out);
    
    out = monitor.update(2, double_input_3);
    EXPECT_EQ(-12, out);
    
    out = monitor.update(3, double_input_4);
    EXPECT_EQ(-1, out);
    
    out = monitor.update(4, double_input_5);
    EXPECT_EQ(0, out);
    
    delete node;
}

TEST_F (StlEvaluationTest, xor) {
    const std::string name_1{"req"};
    const std::string name_2{"gnt"};
    std::set<std::string> set {name_1, name_2}; 

    StlVariableNode *tmp_1 = new StlVariableNode(name_1);
    StlVariableNode *tmp_2 = new StlVariableNode(name_2);
    StlXorNode *node = new StlXorNode(tmp_1, tmp_2);    
    
    std::map<std::string, rtamt::StlIOType> map {};
    StlEvaluation monitor(node, set, map);
    
    double out;
    
    out = monitor.update(0, double_input_1);
    EXPECT_EQ(80, out);
    
    out = monitor.update(1, double_input_2);
    EXPECT_EQ(1, out);
    
    out = monitor.update(2, double_input_3);
    EXPECT_EQ(12, out);
    
    out = monitor.update(3, double_input_4);
    EXPECT_EQ(1, out);
    
    out = monitor.update(4, double_input_5);
    EXPECT_EQ(0, out);
    
    delete node;
}

TEST_F (StlEvaluationTest, rise) {
    const std::string name{"req"};
    std::set<std::string> set {name}; 

    StlVariableNode *tmp = new StlVariableNode(name);
    StlRiseNode *node = new StlRiseNode(tmp);
    
    std::map<std::string, rtamt::StlIOType> map {};
    StlEvaluation monitor(node, set, map);
    
    double out;
    
    out = monitor.update(0, single_input_1);
    EXPECT_EQ(100, out);
    
    out = monitor.update(1, single_input_2);
    EXPECT_EQ(-100, out);
    
    out = monitor.update(2, single_input_3);
    EXPECT_EQ(-2, out);
    
    out = monitor.update(3, single_input_4);
    EXPECT_EQ(2, out);
    
    out = monitor.update(4, single_input_5);
    EXPECT_EQ(-5, out);
    
    delete node;
}

TEST_F (StlEvaluationTest, fall) {
    const std::string name{"req"};
    std::set<std::string> set {name}; 

    StlVariableNode *tmp = new StlVariableNode(name);
    StlFallNode *node = new StlFallNode(tmp);
    
    std::map<std::string, rtamt::StlIOType> map {};
    StlEvaluation monitor(node, set, map);
    
    double out;
    
    out = monitor.update(0, single_input_1);
    EXPECT_EQ(-100, out);
    
    out = monitor.update(1, single_input_2);
    EXPECT_EQ(1, out);
    
    out = monitor.update(2, single_input_3);
    EXPECT_EQ(-1, out);
    
    out = monitor.update(3, single_input_4);
    EXPECT_EQ(-5, out);
    
    out = monitor.update(4, single_input_5);
    EXPECT_EQ(1, out);
    
    delete node;
}

TEST_F (StlEvaluationTest, once) {
    const std::string name{"req"};
    std::set<std::string> set {name}; 

    StlVariableNode *tmp = new StlVariableNode(name);
    StlOnceNode *node = new StlOnceNode(tmp);
    
    std::map<std::string, rtamt::StlIOType> map {};
    StlEvaluation monitor(node, set, map);
    
    double out;
    
    out = monitor.update(0, single_input_1);
    EXPECT_EQ(100, out);
    
    out = monitor.update(1, single_input_2);
    EXPECT_EQ(100, out);
    
    out = monitor.update(2, single_input_3);
    EXPECT_EQ(100, out);
    
    out = monitor.update(3, single_input_4);
    EXPECT_EQ(100, out);
    
    out = monitor.update(4, single_input_5);
    EXPECT_EQ(100, out);
    
    delete node;
}

TEST_F (StlEvaluationTest, historically) {
    const std::string name{"req"};
    std::set<std::string> set {name}; 

    StlVariableNode *tmp = new StlVariableNode(name);
    StlHistoricallyNode *node = new StlHistoricallyNode(tmp);
    
    std::map<std::string, rtamt::StlIOType> map {};
    StlEvaluation monitor(node, set, map);
    
    double out;
    
    out = monitor.update(0, single_input_1);
    EXPECT_EQ(100, out);
    
    out = monitor.update(1, single_input_2);
    EXPECT_EQ(-1, out);
    
    out = monitor.update(2, single_input_3);
    EXPECT_EQ(-2, out);
    
    out = monitor.update(3, single_input_4);
    EXPECT_EQ(-2, out);
    
    out = monitor.update(4, single_input_5);
    EXPECT_EQ(-2, out);
    
    delete node;
}

TEST_F (StlEvaluationTest, eventually) {
    const std::string name{"req"};
    std::set<std::string> set {name}; 

    StlVariableNode *tmp = new StlVariableNode(name);
    StlEventuallyNode *node = new StlEventuallyNode(tmp);
    
    std::map<std::string, rtamt::StlIOType> map {};
    StlEvaluation monitor(node, set, map);
    
    double out;
    
    out = monitor.update(0, single_input_1);
    EXPECT_EQ(100, out);
    
    out = monitor.update(1, single_input_2);
    EXPECT_EQ(100, out);
    
    out = monitor.update(2, single_input_3);
    EXPECT_EQ(100, out);
    
    out = monitor.update(3, single_input_4);
    EXPECT_EQ(100, out);
    
    out = monitor.update(4, single_input_5);
    EXPECT_EQ(100, out);
    
    delete node;
}

TEST_F (StlEvaluationTest, always) {
    const std::string name{"req"};
    std::set<std::string> set {name}; 

    StlVariableNode *tmp = new StlVariableNode(name);
    StlAlwaysNode *node = new StlAlwaysNode(tmp);
    
    std::map<std::string, rtamt::StlIOType> map {};
    StlEvaluation monitor(node, set, map);
    
    double out;
    
    out = monitor.update(0, single_input_1);
    EXPECT_EQ(100, out);
    
    out = monitor.update(1, single_input_2);
    EXPECT_EQ(-1, out);
    
    out = monitor.update(2, single_input_3);
    EXPECT_EQ(-2, out);
    
    out = monitor.update(3, single_input_4);
    EXPECT_EQ(-2, out);
    
    out = monitor.update(4, single_input_5);
    EXPECT_EQ(-2, out);
    
    delete node;
}

TEST_F (StlEvaluationTest, since) {
    const std::string name_1{"req"};
    const std::string name_2{"gnt"};
    std::set<std::string> set {name_1, name_2}; 

    StlVariableNode *tmp_1 = new StlVariableNode(name_1);
    StlVariableNode *tmp_2 = new StlVariableNode(name_2);
    StlSinceNode *node = new StlSinceNode(tmp_1, tmp_2);    
    
    std::map<std::string, rtamt::StlIOType> map {};
    StlEvaluation monitor(node, set, map);
    
    double out;
    
    out = monitor.update(0, double_input_1);
    EXPECT_EQ(20, out);
    
    out = monitor.update(1, double_input_2);
    EXPECT_EQ(-1, out);
    
    out = monitor.update(2, double_input_3);
    EXPECT_EQ(10, out);
    
    out = monitor.update(3, double_input_4);
    EXPECT_EQ(5, out);
    
    out = monitor.update(4, double_input_5);
    EXPECT_EQ(-1, out);
    
    delete node;
}

TEST_F (StlEvaluationTest, once_bounded_0_1) {
    const std::string name{"req"};
    std::set<std::string> set {name}; 

    StlVariableNode *tmp = new StlVariableNode(name);
    StlOnceBoundedNode *node = new StlOnceBoundedNode(0, 1, tmp, true);
    
    std::map<std::string, rtamt::StlIOType> map {};
    StlEvaluation monitor(node, set, map);
    
    double out;
    
    out = monitor.update(0, single_input_1);
    EXPECT_EQ(100, out);
    
    out = monitor.update(1, single_input_2);
    EXPECT_EQ(100, out);
    
    out = monitor.update(2, single_input_3);
    EXPECT_EQ(-1, out);
    
    out = monitor.update(3, single_input_4);
    EXPECT_EQ(5, out);
    
    out = monitor.update(4, single_input_5);
    EXPECT_EQ(5, out);
    
    delete node;
}

TEST_F (StlEvaluationTest, historically_bounded_0_1) {
    const std::string name{"req"};
    std::set<std::string> set {name}; 

    StlVariableNode *tmp = new StlVariableNode(name);
    StlHistoricallyBoundedNode *node = new StlHistoricallyBoundedNode(0, 1, tmp, true);
    
    std::map<std::string, rtamt::StlIOType> map {};
    StlEvaluation monitor(node, set, map);
    
    double out;
    
    out = monitor.update(0, single_input_1);
    EXPECT_EQ(100, out);
    
    out = monitor.update(1, single_input_2);
    EXPECT_EQ(-1, out);
    
    out = monitor.update(2, single_input_3);
    EXPECT_EQ(-2, out);
    
    out = monitor.update(3, single_input_4);
    EXPECT_EQ(-2, out);
    
    out = monitor.update(4, single_input_5);
    EXPECT_EQ(-1, out);
    
    delete node;
}

TEST_F (StlEvaluationTest, eventually_bounded_0_1) {
    const std::string name{"req"};
    std::set<std::string> set {name}; 

    StlVariableNode *tmp = new StlVariableNode(name);
    StlEventuallyBoundedNode *node = new StlEventuallyBoundedNode(0, 1, tmp);
    
    std::map<std::string, rtamt::StlIOType> map {};
    StlEvaluation monitor(node, set, map);
    
    double out;
    
    try {
        out = monitor.update(0, single_input_1);
        delete node;
        FAIL() << "Expected StlNodeException and the execution succeeded";
    }
    catch(StlMonitorException const & err) {
        delete node;
        SUCCEED();
    }
    catch(...) {
        delete node;
        FAIL() << "Expected StlNodeException and the excution returned a different exception";
    }
}

TEST_F (StlEvaluationTest, always_bounded_0_1) {
    const std::string name{"req"};
    std::set<std::string> set {name}; 

    StlVariableNode *tmp = new StlVariableNode(name);
    StlAlwaysBoundedNode *node = new StlAlwaysBoundedNode(0, 1, tmp);
    
    std::map<std::string, rtamt::StlIOType> map {};
    StlEvaluation monitor(node, set, map);
    
    double out;
    
    try {
        out = monitor.update(0, single_input_1);
        delete node;
        FAIL() << "Expected StlNodeException and the execution succeeded";
    }
    catch(StlMonitorException const & err) {
        delete node;
        SUCCEED();
    }
    catch(...) {
        delete node;
        FAIL() << "Expected StlNodeException and the excution returned a different exception";
    }
}

TEST_F (StlEvaluationTest, until_bounded_0_1) {
    const std::string name_1{"req"};
    const std::string name_2{"gnt"};
    std::set<std::string> set {name_1, name_2}; 

    StlVariableNode *tmp_1 = new StlVariableNode(name_1);
    StlVariableNode *tmp_2 = new StlVariableNode(name_2);
    StlUntilBoundedNode *node = new StlUntilBoundedNode(0, 1, tmp_1, tmp_2);
    
    std::map<std::string, rtamt::StlIOType> map {};
    StlEvaluation monitor(node, set, map);
    
    double out;
    
    try {
        out = monitor.update(0, double_input_1);
        delete node;
        FAIL() << "Expected StlNodeException and the execution succeeded";
    }
    catch(StlMonitorException const & err) {
        delete node;
        SUCCEED();
    }
    catch(...) {
        delete node;
        FAIL() << "Expected StlNodeException and the excution returned a different exception";
    }
}

TEST_F (StlEvaluationTest, since_bounded_0_1) {
    const std::string name_1{"req"};
    const std::string name_2{"gnt"};
    std::set<std::string> set {name_1, name_2}; 

    StlVariableNode *tmp_1 = new StlVariableNode(name_1);
    StlVariableNode *tmp_2 = new StlVariableNode(name_2);
    StlSinceBoundedNode *node = new StlSinceBoundedNode(0, 1, tmp_1, tmp_2, true);    
    
    std::map<std::string, rtamt::StlIOType> map {};
    StlEvaluation monitor(node, set, map);
    
    double out;
    
    out = monitor.update(0, double_input_1);
    EXPECT_EQ(20, out);
    
    out = monitor.update(1, double_input_2);
    EXPECT_EQ(-1, out);
    
    out = monitor.update(2, double_input_3);
    EXPECT_EQ(10, out);
    
    out = monitor.update(3, double_input_4);
    EXPECT_EQ(5, out);
    
    out = monitor.update(4, double_input_5);
    EXPECT_EQ(-1, out);
    
    delete node;
}

TEST_F (StlEvaluationTest, precedes_bounded_1_2) {
    const std::string name_1{"req"};
    const std::string name_2{"gnt"};
    std::set<std::string> set {name_1, name_2}; 

    StlVariableNode *tmp_1 = new StlVariableNode(name_1);
    StlVariableNode *tmp_2 = new StlVariableNode(name_2);
    StlPrecedesBoundedNode *node = new StlPrecedesBoundedNode(1, 2, tmp_1, tmp_2, true);    
    
    std::map<std::string, rtamt::StlIOType> map {};
    StlEvaluation monitor(node, set, map);
    
    double out;
    
    out = monitor.update(0, double_input_1);
    EXPECT_EQ(20, out);
    
    out = monitor.update(1, double_input_2);
    EXPECT_EQ(20, out);
    
    out = monitor.update(2, double_input_3);
    EXPECT_EQ(-1, out);
    
    out = monitor.update(3, double_input_4);
    EXPECT_EQ(-1, out);
    
    out = monitor.update(4, double_input_5);
    EXPECT_EQ(-2, out);
    
    delete node;
}

TEST_F (StlEvaluationTest, wrong_var_name) {
    const std::string name{"req"};
    std::set<std::string> set {name}; 

    StlVariableNode *node = new StlVariableNode(name);
    
    std::map<std::string, rtamt::StlIOType> map {};
    StlEvaluation monitor(node, set, map);
    
    try {
        Input input = Input("rq", 1);
        monitor.update(0, {input});
        delete node;
        FAIL() << "Expected StlNodeException and the update succeeded";
    }
    catch(StlMonitorException const & err) {
        delete node;
        SUCCEED();
    }
    catch(...) {
        delete node;
        FAIL() << "Expected StlNodeException and the update returned a different exception";
    }
}

TEST_F (StlEvaluationTest, wrong_var_name_variable) {
    const std::string name{"req"};
    const std::string wrong_name{"rq"};
    std::set<std::string> set {name}; 

    StlVariableNode *node = new StlVariableNode(wrong_name);
    std::map<std::string, rtamt::StlIOType> map {};
    StlEvaluation monitor(node, set, map);
    
    try {
        node->accept(monitor);
        delete node;
        FAIL() << "Expected StlNodeException and the update succeeded";
    }
    catch(StlMonitorException const & err) {
        delete node;
        SUCCEED();
    }
    catch(...) {
        delete node;
        FAIL() << "Expected StlNodeException and the update returned a different exception";
    }
}
