#include <string>
#include <limits>
#include <gtest/gtest.h>
#include <rtamt/stl_specification.hpp>
#include <rtamt/stl_exception.hpp>
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


using namespace rtamt;
using namespace std;
using namespace spec;
using namespace node;


using In = rtamt::Input;

class StlSpecificationTest : public ::testing::Test {
    protected:
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


TEST_F (StlSpecificationTest, example) {
    StlSpecification spec;
    
    spec.name("STL Example specification");
    
    ASSERT_EQ(spec.name(), "STL Example specification");
    
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("gnt", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.var_type("out", rtamt::Type::FLOAT);
    spec.var_io_type("req", StlIOType::IN);
    spec.var_io_type("gnt", StlIOType::OUT);
    spec.semantics(StlSemantics::STANDARD);
    spec.sampling_period(1, Unit::S);
    spec.sampling_period(1, Unit::S, 0.1);
    spec.spec("out = req<=2 and gnt>=3");
    
    ASSERT_EQ(spec.spec(), "out = req<=2 and gnt>=3");
    ASSERT_EQ(spec.var_type("req"), rtamt::Type::FLOAT);
    ASSERT_EQ(spec.semantics(), StlSemantics::STANDARD);
    ASSERT_EQ(spec.sampling_period(), 1000000000);
    ASSERT_EQ(spec.var_io_type("req"), StlIOType::IN);
    ASSERT_EQ(spec.sampling_tolerance(), 0.1);
    
    try {
      spec.parse();
      double computed;
      computed = spec.update(0, {In("req", 2.2), In("gnt", 1)});
      ASSERT_EQ(computed, -2.0);
      
      computed = spec.update(1.2, {In("req", 4.2), In("gnt", -3.7)});
      ASSERT_EQ(computed, -6.7);
      ASSERT_EQ(spec.sampling_violation_counter(), 1);
      
      spec.reset();
      
      computed = spec.update(1, {In("req", 4.2), In("gnt", -3.7)});
      ASSERT_EQ(computed, -6.7);
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    } 
}

TEST_F (StlSpecificationTest, wrong_sampling_tolerance) {
    StlSpecification spec;
    
    try {
        spec.sampling_period(5, Unit::MS, 1.2);
        FAIL() << "Calling sampling_period with sampling tolerance not in [0,1] should throw a StlSpecificationException";
    } catch (StlSpecificationException &e) {
        std::cout << e.what();
        SUCCEED();
    } catch (...) {
        FAIL() << "I expected StlSpecficationException";
    }
}

TEST_F (StlSpecificationTest, constant) {
    StlSpecification spec;
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = 5");
    
    try {
      spec.parse();
      
      double out;
      out = spec.update(0, {});
    
      EXPECT_EQ(5, out);
      
      out = spec.update(1, {});
    
      EXPECT_EQ(5, out);
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    } 
}

TEST_F (StlSpecificationTest, variable) {
    StlSpecification spec;
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = req");
    
    try {
      spec.parse();
      
      double out;
    
      out = spec.update(0, single_input_1);
      EXPECT_EQ(100, out);
    
      out = spec.update(1, single_input_2);
      EXPECT_EQ(-1, out);
    
      out = spec.update(2, single_input_3);
      EXPECT_EQ(-2, out);
    
      out = spec.update(3, single_input_4);
      EXPECT_EQ(5, out);
    
      out = spec.update(4, single_input_5);
      EXPECT_EQ(-1, out);
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    } 
}

TEST_F (StlSpecificationTest, abs) {
    StlSpecification spec;
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = abs(req)");
    
    try {
      spec.parse();
      
      double out;
    
      out = spec.update(0, single_input_1);
      EXPECT_EQ(100, out);
    
      out = spec.update(1, single_input_2);
      EXPECT_EQ(1, out);
    
      out = spec.update(2, single_input_3);
      EXPECT_EQ(2, out);
    
      out = spec.update(3, single_input_4);
      EXPECT_EQ(5, out);
    
      out = spec.update(4, single_input_5);
      EXPECT_EQ(1, out);
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    } 
}

TEST_F (StlSpecificationTest, addition) {
    StlSpecification spec;
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("gnt", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = req + gnt");
    
    try {
      spec.parse();
      
      double out;
    
      out = spec.update(0, double_input_1);
      EXPECT_EQ(120, out);
    
      out = spec.update(1, double_input_2);
      EXPECT_EQ(-3, out);
    
      out = spec.update(2, double_input_3);
      EXPECT_EQ(8, out);
    
      out = spec.update(3, double_input_4);
      EXPECT_EQ(9, out);
    
      out = spec.update(4, double_input_5);
      EXPECT_EQ(-2, out);
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    } 
}

TEST_F (StlSpecificationTest, subtraction) {
    StlSpecification spec;
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("gnt", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = req - gnt");
    
    try {
      spec.parse();
      
      double out;
    
      out = spec.update(0, double_input_1);
      EXPECT_EQ(80, out);
    
      out = spec.update(1, double_input_2);
      EXPECT_EQ(1, out);
    
      out = spec.update(2, double_input_3);
      EXPECT_EQ(-12, out);
    
      out = spec.update(3, double_input_4);
      EXPECT_EQ(1, out);
    
      out = spec.update(4, double_input_5);
      EXPECT_EQ(0, out);
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    } 
}

TEST_F (StlSpecificationTest, multiplication) {
    StlSpecification spec;
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("gnt", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = req * gnt");
    
    try {
      spec.parse();
      
      double out;
    
      out = spec.update(0, double_input_1);
      EXPECT_EQ(2000, out);
    
      out = spec.update(1, double_input_2);
      EXPECT_EQ(2, out);
    
      out = spec.update(2, double_input_3);
      EXPECT_EQ(-20, out);
    
      out = spec.update(3, double_input_4);
      EXPECT_EQ(20, out);
    
      out = spec.update(4, double_input_5);
      EXPECT_EQ(1, out);
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    } 
}

TEST_F (StlSpecificationTest, division) {
    StlSpecification spec;
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("gnt", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = req / gnt");
    
    try {
      spec.parse();
      
      double out;
    
      out = spec.update(0, double_input_1);
      EXPECT_EQ(100.0/20.0, out);
    
      out = spec.update(1, double_input_2);
      EXPECT_EQ(-1.0/-2.0, out);
    
      out = spec.update(2, double_input_3);
      EXPECT_EQ(-2.0/10.00, out);
    
      out = spec.update(3, double_input_4);
      EXPECT_EQ(5.0/4.0, out);
    
      out = spec.update(4, double_input_5);
      EXPECT_EQ(-1.0/-1.0, out);
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    } 
}

TEST_F (StlSpecificationTest, predicate_leq) {
    StlSpecification spec;
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("gnt", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = req <= gnt");
    
    try {
      spec.parse();
      
      double out;
    
      out = spec.update(0, double_input_1);
      EXPECT_EQ(-80, out);
    
      out = spec.update(1, double_input_2);
      EXPECT_EQ(-1, out);
    
      out = spec.update(2, double_input_3);
      EXPECT_EQ(12, out);
    
      out = spec.update(3, double_input_4);
      EXPECT_EQ(-1, out);
    
      out = spec.update(4, double_input_5);
      EXPECT_EQ(0, out);
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    } 
}

TEST_F (StlSpecificationTest, predicate_less) {
    StlSpecification spec;
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("gnt", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = req < gnt");
    
    try {
      spec.parse();
      
      double out;
    
      out = spec.update(0, double_input_1);
      EXPECT_EQ(-80, out);
    
      out = spec.update(1, double_input_2);
      EXPECT_EQ(-1, out);
    
      out = spec.update(2, double_input_3);
      EXPECT_EQ(12, out);
    
      out = spec.update(3, double_input_4);
      EXPECT_EQ(-1, out);
    
      out = spec.update(4, double_input_5);
      EXPECT_EQ(0, out);
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    } 
}

TEST_F (StlSpecificationTest, predicate_geq) {
    StlSpecification spec;
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("gnt", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = req >= gnt");
    
    try {
      spec.parse();
      
      double out;
    
      out = spec.update(0, double_input_1);
      EXPECT_EQ(80, out);
    
      out = spec.update(1, double_input_2);
      EXPECT_EQ(1, out);
    
      out = spec.update(2, double_input_3);
      EXPECT_EQ(-12, out);
    
      out = spec.update(3, double_input_4);
      EXPECT_EQ(1, out);
    
      out = spec.update(4, double_input_5);
      EXPECT_EQ(0, out);
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    } 
}

TEST_F (StlSpecificationTest, predicate_greater) {
    StlSpecification spec;
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("gnt", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = req > gnt");
    
    try {
      spec.parse();
      
      double out;
    
      out = spec.update(0, double_input_1);
      EXPECT_EQ(80, out);
    
      out = spec.update(1, double_input_2);
      EXPECT_EQ(1, out);
    
      out = spec.update(2, double_input_3);
      EXPECT_EQ(-12, out);
    
      out = spec.update(3, double_input_4);
      EXPECT_EQ(1, out);
    
      out = spec.update(4, double_input_5);
      EXPECT_EQ(0, out);
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    } 
}

TEST_F (StlSpecificationTest, predicate_neq) {
    StlSpecification spec;
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("gnt", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = req !== gnt");
    
    try {
      spec.parse();
      
      double out;
    
      out = spec.update(0, double_input_1);
      EXPECT_EQ(80, out);
    
      out = spec.update(1, double_input_2);
      EXPECT_EQ(1, out);
    
      out = spec.update(2, double_input_3);
      EXPECT_EQ(12, out);
    
      out = spec.update(3, double_input_4);
      EXPECT_EQ(1, out);
    
      out = spec.update(4, double_input_5);
      EXPECT_EQ(0, out);
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    } 
}

TEST_F (StlSpecificationTest, predicate_eq) {
    StlSpecification spec;
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("gnt", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = req == gnt");
    
    try {
      spec.parse();
      
      double out;
    
      out = spec.update(0, double_input_1);
      EXPECT_EQ(-80, out);
    
      out = spec.update(1, double_input_2);
      EXPECT_EQ(-1, out);
    
      out = spec.update(2, double_input_3);
      EXPECT_EQ(-12, out);
    
      out = spec.update(3, double_input_4);
      EXPECT_EQ(-1, out);
    
      out = spec.update(4, double_input_5);
      EXPECT_EQ(0, out);
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    } 
}

TEST_F (StlSpecificationTest, not) {
    StlSpecification spec;
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = not req");
    
    try {
      spec.parse();
      
      double out;
    
      out = spec.update(0, single_input_1);
      EXPECT_EQ(-100, out);
    
      out = spec.update(1, single_input_2);
      EXPECT_EQ(1, out);
    
      out = spec.update(2, single_input_3);
      EXPECT_EQ(2, out);
    
      out = spec.update(3, single_input_4);
      EXPECT_EQ(-5, out);
    
      out = spec.update(4, single_input_5);
      EXPECT_EQ(1, out);
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    } 
}

TEST_F (StlSpecificationTest, conjunction) {
    StlSpecification spec;
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("gnt", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = req and gnt");
    
    try {
      spec.parse();
      
      double out;
    
      out = spec.update(0, double_input_1);
      EXPECT_EQ(20, out);
     
      out = spec.update(1, double_input_2);
      EXPECT_EQ(-2, out);
    
      out = spec.update(2, double_input_3);
      EXPECT_EQ(-2, out);
    
      out = spec.update(3, double_input_4);
      EXPECT_EQ(4, out);
    
      out = spec.update(4, double_input_5);
      EXPECT_EQ(-1, out);
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    } 
}

TEST_F (StlSpecificationTest, disjunction) {
    StlSpecification spec;
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("gnt", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = req or gnt");
    
    try {
      spec.parse();
      
      double out;
    
      out = spec.update(0, double_input_1);
      EXPECT_EQ(100, out);
    
      out = spec.update(1, double_input_2);
      EXPECT_EQ(-1, out);
    
      out = spec.update(2, double_input_3);
      EXPECT_EQ(10, out);
    
      out = spec.update(3, double_input_4);
      EXPECT_EQ(5, out);
    
      out = spec.update(4, double_input_5);
      EXPECT_EQ(-1, out);
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    } 
}

TEST_F (StlSpecificationTest, implies) {
    StlSpecification spec;
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("gnt", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = req -> gnt");
    
    try {
      spec.parse();
      
      double out;
    
      out = spec.update(0, double_input_1);
      EXPECT_EQ(20, out);
    
      out = spec.update(1, double_input_2);
      EXPECT_EQ(1, out);
    
      out = spec.update(2, double_input_3);
      EXPECT_EQ(10, out);
    
      out = spec.update(3, double_input_4);
      EXPECT_EQ(4, out);
    
      out = spec.update(4, double_input_5);
      EXPECT_EQ(1, out);
    } catch ( StlException &e ) {
      FAIL() << e.what();
    } 
}

TEST_F (StlSpecificationTest, iff) {
    StlSpecification spec;
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("gnt", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = req <-> gnt");
    
    try {
      spec.parse();
      
      double out;
    
      out = spec.update(0, double_input_1);
      EXPECT_EQ(-80, out);
    
      out = spec.update(1, double_input_2);
      EXPECT_EQ(-1, out);
    
      out = spec.update(2, double_input_3);
      EXPECT_EQ(-12, out);
    
      out = spec.update(3, double_input_4);
      EXPECT_EQ(-1, out);
    
      out = spec.update(4, double_input_5);
      EXPECT_EQ(0, out);
    } catch ( StlException &e ) {
      FAIL() << e.what();
    } 
}

TEST_F (StlSpecificationTest, xor) {
    StlSpecification spec;
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("gnt", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = req xor gnt");
    
    try {
      spec.parse();
      
      double out;
    
      out = spec.update(0, double_input_1);
      EXPECT_EQ(80, out);
    
      out = spec.update(1, double_input_2);
      EXPECT_EQ(1, out);
    
      out = spec.update(2, double_input_3);
      EXPECT_EQ(12, out);
    
      out = spec.update(3, double_input_4);
      EXPECT_EQ(1, out);
    
      out = spec.update(4, double_input_5);
      EXPECT_EQ(0, out);
    } catch ( StlException &e ) {
      FAIL() << e.what();
    } 
}

TEST_F (StlSpecificationTest, rise) {
    StlSpecification spec;
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = rise(req)");
    
    try {
      spec.parse();
      
      double out;
    
      out = spec.update(0, single_input_1);
      EXPECT_EQ(100, out);
    
      out = spec.update(1, single_input_2);
      EXPECT_EQ(-100, out);
    
      out = spec.update(2, single_input_3);
      EXPECT_EQ(-2, out);
    
      out = spec.update(3, single_input_4);
      EXPECT_EQ(2, out);
    
      out = spec.update(4, single_input_5);
      EXPECT_EQ(-5, out);
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    } 
}

TEST_F (StlSpecificationTest, fall) {
    StlSpecification spec;
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = fall(req)");
    
    try {
      spec.parse();
      
      double out;
    
      out = spec.update(0, single_input_1);
      EXPECT_EQ(-100, out);
    
      out = spec.update(1, single_input_2);
      EXPECT_EQ(1, out);
    
      out = spec.update(2, single_input_3);
      EXPECT_EQ(-1, out);
    
      out = spec.update(3, single_input_4);
      EXPECT_EQ(-5, out);
    
      out = spec.update(4, single_input_5);
      EXPECT_EQ(1, out);
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    } 
}

TEST_F (StlSpecificationTest, once) {
    StlSpecification spec;
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = once req");
    
    try {
      spec.parse();
      
      double out;
    
      out = spec.update(0, single_input_1);
      EXPECT_EQ(100, out);
    
      out = spec.update(1, single_input_2);
      EXPECT_EQ(100, out);
    
      out = spec.update(2, single_input_3);
      EXPECT_EQ(100, out);
    
      out = spec.update(3, single_input_4);
      EXPECT_EQ(100, out);
    
      out = spec.update(4, single_input_5);
      EXPECT_EQ(100, out);
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    } 
}

TEST_F (StlSpecificationTest, historically) {
    StlSpecification spec;
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = historically req");
    
    try {
      spec.parse();
      
      double out;
    
      out = spec.update(0, single_input_1);
      EXPECT_EQ(100, out);
    
      out = spec.update(1, single_input_2);
      EXPECT_EQ(-1, out);
    
      out = spec.update(2, single_input_3);
      EXPECT_EQ(-2, out);
    
      out = spec.update(3, single_input_4);
      EXPECT_EQ(-2, out);
    
      out = spec.update(4, single_input_5);
      EXPECT_EQ(-2, out);
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    } 
}

TEST_F (StlSpecificationTest, eventually) {
    StlSpecification spec;
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = eventually req");
    
    try {
      spec.parse();
      
      double out;
    
      out = spec.update(0, single_input_1);
      EXPECT_EQ(100, out);
    
      out = spec.update(1, single_input_2);
      EXPECT_EQ(100, out);
    
      out = spec.update(2, single_input_3);
      EXPECT_EQ(100, out);
    
      out = spec.update(3, single_input_4);
      EXPECT_EQ(100, out);
    
      out = spec.update(4, single_input_5);
      EXPECT_EQ(100, out);
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    } 
}

TEST_F (StlSpecificationTest, always) {
    StlSpecification spec;
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = always req");
    
    try {
      spec.parse();
      
      double out;
    
      out = spec.update(0, single_input_1);
      EXPECT_EQ(100, out);
    
      out = spec.update(1, single_input_2);
      EXPECT_EQ(-1, out);
    
      out = spec.update(2, single_input_3);
      EXPECT_EQ(-2, out);
    
      out = spec.update(3, single_input_4);
      EXPECT_EQ(-2, out);
    
      out = spec.update(4, single_input_5);
      EXPECT_EQ(-2, out);
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    } 
}

TEST_F (StlSpecificationTest, since) {
    StlSpecification spec;
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("gnt", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = req since gnt");
    
    try {
      spec.parse();
      
      double out;
    
      out = spec.update(0, double_input_1);
      EXPECT_EQ(20, out);
    
      out = spec.update(1, double_input_2);
      EXPECT_EQ(-1, out);
    
      out = spec.update(2, double_input_3);
      EXPECT_EQ(10, out);
    
      out = spec.update(3, double_input_4);
      EXPECT_EQ(5, out);
    
      out = spec.update(4, double_input_5);
      EXPECT_EQ(-1, out);
    } catch ( StlException &e ) {
      FAIL() << e.what();
    } 
}

TEST_F (StlSpecificationTest, once_bounded_0_1) {
    StlSpecification spec;
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = once[0:1] req");
    
    try {
      spec.parse();
      
      double out;
    
      out = spec.update(0, single_input_1);
      EXPECT_EQ(100, out);
    
      out = spec.update(1, single_input_2);
      EXPECT_EQ(100, out);
    
      out = spec.update(2, single_input_3);
      EXPECT_EQ(-1, out);
    
      out = spec.update(3, single_input_4);
      EXPECT_EQ(5, out);
    
      out = spec.update(4, single_input_5);
      EXPECT_EQ(5, out);
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    } 
}

TEST_F (StlSpecificationTest, historically_bounded_0_1) {
    StlSpecification spec;
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = historically[0:1] req");
    
    try {
      spec.parse();
      
      double out;
    
      out = spec.update(0, single_input_1);
      EXPECT_EQ(100, out);
    
      out = spec.update(1, single_input_2);
      EXPECT_EQ(-1, out);
    
      out = spec.update(2, single_input_3);
      EXPECT_EQ(-2, out);
    
      out = spec.update(3, single_input_4);
      EXPECT_EQ(-2, out);
    
      out = spec.update(4, single_input_5);
      EXPECT_EQ(-1, out);
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    } 
}

TEST_F (StlSpecificationTest, eventually_bounded_0_1) {
    StlSpecification spec;
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = eventually[0:1] req");
    
    try {
      spec.parse();
      
      double out;
    
      out = spec.update(0, single_input_1);
      EXPECT_EQ(100, out);
    
      out = spec.update(1, single_input_2);
      EXPECT_EQ(100, out);
    
      out = spec.update(2, single_input_3);
      EXPECT_EQ(-1, out);
    
      out = spec.update(3, single_input_4);
      EXPECT_EQ(5, out);
    
      out = spec.update(4, single_input_5);
      EXPECT_EQ(5, out);
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    } 
}

TEST_F (StlSpecificationTest, always_bounded_0_1) {
    StlSpecification spec;
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = always[0:1] req");
    
    try {
      spec.parse();
      
      double out;
    
      out = spec.update(0, single_input_1);
      EXPECT_EQ(100, out);
    
      out = spec.update(1, single_input_2);
      EXPECT_EQ(-1, out);
    
      out = spec.update(2, single_input_3);
      EXPECT_EQ(-2, out);
    
      out = spec.update(3, single_input_4);
      EXPECT_EQ(-2, out);
    
      out = spec.update(4, single_input_5);
      EXPECT_EQ(-1, out);
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    } 
}

TEST_F (StlSpecificationTest, since_bounded_0_1) {
    StlSpecification spec;
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("gnt", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = req since[0:1] gnt");
    
    try {
      spec.parse();
      
      double out;
    
      out = spec.update(0, double_input_1);
      EXPECT_EQ(20, out);
    
      out = spec.update(1, double_input_2);
      EXPECT_EQ(-1, out);
    
      out = spec.update(2, double_input_3);
      EXPECT_EQ(10, out);
    
      out = spec.update(3, double_input_4);
      EXPECT_EQ(5, out);
    
      out = spec.update(4, double_input_5);
      EXPECT_EQ(-1, out);
    } catch ( StlException &e ) {
      FAIL() << e.what();
    } 
}

TEST_F (StlSpecificationTest, until_bounded_0_1) {
    StlSpecification spec;
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("gnt", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = req until[0:1] gnt");
    
    try {
      spec.parse();
      
      double out;
    
      out = spec.update(0, double_input_1);
      EXPECT_EQ(20, out);
    
      out = spec.update(1, double_input_2);
      EXPECT_EQ(20, out);
    
      out = spec.update(2, double_input_3);
      EXPECT_EQ(-1, out);
    
      out = spec.update(3, double_input_4);
      EXPECT_EQ(10, out);
    
      out = spec.update(4, double_input_5);
      EXPECT_EQ(4, out);
    } catch ( StlException &e ) {
      FAIL() << e.what();
    } 
}

TEST_F (StlSpecificationTest, wrong_declare_name_after_lock) {
    StlSpecification spec;
    
    spec.name("Name");
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("gnt", rtamt::Type::FLOAT);
    spec.var_io_type("req", StlIOType::OUT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = req until[0:1] gnt");
    try {
      spec.parse();
      spec.name("New name");
      FAIL() << "Expected StlInvalidOperationException\n";
    } catch ( StlInvalidOperationException &e ) {
      SUCCEED() << e.what();
    } catch (...) {
      FAIL() << "Expected StlInvalidOperationException\n";
    }
}

TEST_F (StlSpecificationTest, wrong_semantics_after_lock) {
    StlSpecification spec;
    
    spec.name("Name");
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("gnt", rtamt::Type::FLOAT);
    spec.var_io_type("req", StlIOType::OUT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = req until[0:1] gnt");
    try {
      spec.parse();
      spec.semantics(StlSemantics::OUT_ROBUSTNESS);
      FAIL() << "Expected StlInvalidOperationException\n";
    } catch ( StlInvalidOperationException &e ) {
      SUCCEED() << e.what();
    } catch (...) {
      FAIL() << "Expected StlInvalidOperationException\n";
    }
}

TEST_F (StlSpecificationTest, wrong_parse_after_lock) {
    StlSpecification spec;
    
    spec.name("Name");
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("gnt", rtamt::Type::FLOAT);
    spec.var_io_type("req", StlIOType::OUT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = req until[0:1] gnt");
    try {
      spec.parse();
      spec.parse();
      FAIL() << "Expected StlInvalidOperationException\n";
    } catch ( StlInvalidOperationException &e ) {
      SUCCEED() << e.what();
    } catch (...) {
      FAIL() << "Expected StlInvalidOperationException\n";
    }
}

TEST_F (StlSpecificationTest, wrong_declare_var_after_lock) {
    StlSpecification spec;
    
    spec.name("Name");
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("gnt", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = req until[0:1] gnt");
    try {
      spec.parse();
      spec.declare_var("ack", rtamt::Type::FLOAT);
      FAIL() << "Expected StlInvalidOperationException\n";
    } catch ( StlInvalidOperationException &e ) {
      SUCCEED() << e.what();
    } catch (...) {
      FAIL() << "Expected StlInvalidOperationException\n";
    }
}

TEST_F (StlSpecificationTest, wrong_change_var_type_after_lock) {
    StlSpecification spec;
    
    spec.name("Name");
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("gnt", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = req until[0:1] gnt");
    try {
      spec.parse();
      spec.var_type("req", rtamt::Type::FLOAT);
      FAIL() << "Expected StlInvalidOperationException\n";
    } catch ( StlInvalidOperationException &e ) {
      SUCCEED() << e.what();
    } catch (...) {
      FAIL() << "Expected StlInvalidOperationException\n";
    }
}

TEST_F (StlSpecificationTest, wrong_change_io_type_after_lock) {
    StlSpecification spec;
    
    spec.name("Name");
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("gnt", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = req until[0:1] gnt");
    try {
      spec.parse();
      spec.var_io_type("req", StlIOType::OUT);
      FAIL() << "Expected StlInvalidOperationException\n";
    } catch ( StlInvalidOperationException &e ) {
      SUCCEED() << e.what();
    } catch (...) {
      FAIL() << "Expected StlInvalidOperationException\n";
    }
}

TEST_F (StlSpecificationTest, wrong_change_var_type_undefined_var) {
    StlSpecification spec;
    
    try {
      spec.var_type("req", rtamt::Type::FLOAT);
      FAIL() << "Expected StlInvalidOperationException\n";
    } catch ( StlInvalidOperationException &e ) {
      SUCCEED() << e.what();
    } catch (...) {
      FAIL() << "Expected StlInvalidOperationException\n";
    }
}

TEST_F (StlSpecificationTest, wrong_change_var_io_type_undefined_var) {
    StlSpecification spec;
    
    try {
      spec.var_io_type("req", StlIOType::IN);
      FAIL() << "Expected StlInvalidOperationException\n";
    } catch ( StlInvalidOperationException &e ) {
      SUCCEED() << e.what();
    } catch (...) {
      FAIL() << "Expected StlInvalidOperationException\n";
    }
}

TEST_F (StlSpecificationTest, wrong_change_spec_from_file_after_lock) {
    StlSpecification spec;
    
    spec.name("Name");
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("gnt", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = req until[0:1] gnt");
    try {
      spec.parse();
      spec.spec_from_file("../test/stl-inputs/always_bounded_pass.stl");
      FAIL() << "Expected StlInvalidOperationException\n";
    } catch ( StlInvalidOperationException &e ) {
      SUCCEED() << e.what();
    } catch (...) {
      FAIL() << "Expected StlInvalidOperationException\n";
    }
}

TEST_F (StlSpecificationTest, wrong_change_sampling_period_after_lock_1) {
    StlSpecification spec;
    
    spec.name("Name");
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("gnt", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = req until[0:1] gnt");
    try {
      spec.parse();
      spec.sampling_period(1, Unit::MS);
      FAIL() << "Expected StlInvalidOperationException\n";
    } catch ( StlInvalidOperationException &e ) {
      SUCCEED() << e.what();
    } catch (...) {
      FAIL() << "Expected StlInvalidOperationException\n";
    }
}

TEST_F (StlSpecificationTest, wrong_change_sampling_period_after_lock_2) {
    StlSpecification spec;
    
    spec.name("Name");
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("gnt", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = req until[0:1] gnt");
    try {
      spec.parse();
      spec.sampling_period(1, Unit::MS, 0.1);
      FAIL() << "Expected StlInvalidOperationException\n";
    } catch ( StlInvalidOperationException &e ) {
      SUCCEED() << e.what();
    } catch (...) {
      FAIL() << "Expected StlInvalidOperationException\n";
    }
}

TEST_F (StlSpecificationTest, wrong_change_default_unit_after_lock) {
    StlSpecification spec;
    
    spec.name("Name");
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("gnt", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = req until[0:1] gnt");
    try {
      spec.parse();
      spec.default_unit(Unit::MS);
      FAIL() << "Expected StlInvalidOperationException\n";
    } catch ( StlInvalidOperationException &e ) {
      SUCCEED() << e.what();
    } catch (...) {
      FAIL() << "Expected StlInvalidOperationException\n";
    }
}

TEST_F (StlSpecificationTest, wrong_update_before_parse) {
    StlSpecification spec;
    
    spec.name("Name");
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("gnt", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = req until[0:1] gnt");
    try {
      spec.update(0,{});
    } catch ( StlMonitorException &e ) {
      SUCCEED() << e.what();
    } catch (...) {
      FAIL() << "Expected StlMonitorOperation\n";
    }
}

TEST_F (StlSpecificationTest, wrong_declare_var_twice) {
    StlSpecification spec;
    
    try {
      spec.name("Name");
      spec.declare_var("req", rtamt::Type::FLOAT);
      spec.declare_var("req", rtamt::Type::FLOAT);
      FAIL() << "Expected StlInvalidOperationException\n";
    } catch ( StlInvalidOperationException &e ) {
      SUCCEED() << e.what();
    } catch (...) {
      FAIL() << "Expected StlInvalidOperationException\n";
    }
}

TEST_F (StlSpecificationTest, wrong_declare_var_not_float) {
    StlSpecification spec;
    
    try {
      spec.name("Name");
      spec.spec("float req\n int gnt\n float out\n out = req until[0ms:1ms] gnt");
      spec.parse();
      FAIL() << "Succeded but expected StlParseException\n";
    } catch ( StlParseException &e ) {
      SUCCEED() << e.what();
    } catch (...) {
      FAIL() << "Failed but expected StlParseException\n";
    }
}

TEST_F (StlSpecificationTest, spec_with_both_time_units) {
    StlSpecification spec;
    
    spec.name("Name");
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("gnt", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = req until[0 s:1 s] gnt");
    try {
      spec.parse();
      SUCCEED();
    } catch (std::exception e) {
      std::cout << e.what();
      FAIL() << "Did not expect an exception\n";
    }
}

TEST_F (StlSpecificationTest, spec_with_right_time_unit) {
    StlSpecification spec;
    
    spec.name("Name");
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("gnt", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = req until[0:1s] gnt");
    try {
      spec.parse();
      SUCCEED();
    } catch (...) {
      FAIL() << "Did not expect an exception\n";
    }
}

TEST_F (StlSpecificationTest, wrong_spec_with_left_time_unit) {
    StlSpecification spec;
    
    spec.name("Name");
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("gnt", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = req until[0ms:1] gnt");
    try {
      spec.parse();
      FAIL() << "Expected StlParseException\n";
    } catch (StlParseException &e) {
      SUCCEED();
    } catch (...) {
      FAIL() << "Expected StlParseException\n";
    }
}

TEST_F (StlSpecificationTest, wrong_spec_with_left_time_unit_once) {
    StlSpecification spec;
    
    spec.name("Name");
    spec.declare_var("gnt", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = once[0ms:1] gnt");
    try {
      spec.parse();
      FAIL() << "Expected StlParseException\n";
    } catch (StlParseException &e) {
      SUCCEED();
    } catch (...) {
      FAIL() << "Expected StlParseException\n";
    }
}

TEST_F (StlSpecificationTest, wrong_spec_begin_bigger_than_end) {
    StlSpecification spec;
    
    spec.name("Name");
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("gnt", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = req until[10:5] gnt");
    try {
      spec.parse();
      FAIL() << "Expected StlParseException\n";
    } catch (StlParseException &e) {
      SUCCEED();
    } catch (...) {
      FAIL() << "Expected StlParseException\n";
    }
}

TEST_F (StlSpecificationTest, wrong_spec_begin_not_divisible_by_sampling_period) {
    StlSpecification spec;
    
    spec.name("Name");
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("gnt", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.sampling_period(2, Unit::MS);
    spec.spec("out = req until[3ms:10ms] gnt");
    try {
      spec.parse();
      FAIL() << "Expected StlParseException\n";
    } catch (StlParseException &e) {
      SUCCEED();
    } catch (...) {
      FAIL() << "Expected StlParseException\n";
    }
}

TEST_F (StlSpecificationTest, wrong_spec_always_begin_not_divisible_by_sampling_period) {
    StlSpecification spec;
    
    spec.name("Name");
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.sampling_period(2, Unit::MS);
    spec.spec("out = always[3ms:10ms] req");
    try {
      spec.parse();
      FAIL() << "Expected StlParseException\n";
    } catch (StlParseException &e) {
      SUCCEED();
    } catch (...) {
      FAIL() << "Expected StlParseException\n";
    }
}


TEST_F (StlSpecificationTest, wrong_spec_eventually_begin_not_divisible_by_sampling_period) {
    StlSpecification spec;
    
    spec.name("Name");
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.sampling_period(2, Unit::MS);
    spec.spec("out = eventually[3ms:10ms] req");
    try {
      spec.parse();
      FAIL() << "Expected StlParseException\n";
    } catch (StlParseException &e) {
      SUCCEED();
    } catch (...) {
      FAIL() << "Expected StlParseException\n";
    }
}

TEST_F (StlSpecificationTest, wrong_spec_historically_begin_not_divisible_by_sampling_period) {
    StlSpecification spec;
    
    spec.name("Name");
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.sampling_period(2, Unit::MS);
    spec.spec("out = historically[3ms:10ms] req");
    try {
      spec.parse();
      FAIL() << "Expected StlParseException\n";
    } catch (StlParseException &e) {
      SUCCEED();
    } catch (...) {
      FAIL() << "Expected StlParseException\n";
    }
}

TEST_F (StlSpecificationTest, wrong_spec_once_begin_not_divisible_by_sampling_period) {
    StlSpecification spec;
    
    spec.name("Name");
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.sampling_period(2, Unit::MS);
    spec.spec("out = once[3ms:10ms] req");
    try {
      spec.parse();
      FAIL() << "Expected StlParseException\n";
    } catch (StlParseException &e) {
      SUCCEED();
    } catch (...) {
      FAIL() << "Expected StlParseException\n";
    }
}

TEST_F (StlSpecificationTest, wrong_spec_end_not_divisible_by_sampling_period) {
    StlSpecification spec;
    
    spec.name("Name");
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("gnt", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.var_io_type("gnt", StlIOType::OUT);
    spec.sampling_period(2, Unit::MS);
    spec.spec("out = req until[2ms:9ms] gnt");
    try {
      spec.parse();
      FAIL() << "Expected StlParseException\n";
    } catch (StlParseException &e) {
      SUCCEED();
    } catch (...) {
      FAIL() << "Expected StlParseException\n";
    }
}

TEST_F (StlSpecificationTest, wrong_spec_since_end_not_divisible_by_sampling_period) {
    StlSpecification spec;
    
    spec.name("Name");
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("gnt", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.var_io_type("gnt", StlIOType::OUT);
    spec.sampling_period(2, Unit::MS);
    spec.spec("out = req since[2ms:9ms] gnt");
    try {
      spec.parse();
      FAIL() << "Expected StlParseException\n";
    } catch (StlParseException &e) {
      SUCCEED();
    } catch (...) {
      FAIL() << "Expected StlParseException\n";
    }
}

TEST_F (StlSpecificationTest, wrong_spec_from_file_with_constant) {
    StlSpecification spec;
    spec.spec("output float req\nconst float bla = 5\nout = req");
    
    try {
      spec.parse();
      FAIL() << "Succeded parsing, but was expecting an exception";
    } catch (StlParseException &e) {
      SUCCEED();
    } catch (...) {
      FAIL() << "Did not expect an exception\n";
    }
}

TEST_F (StlSpecificationTest, default_unit_default_sampling_unit_perfect_samples) {
    StlSpecification spec;
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = rise(req)");
    
    try {
      spec.parse();
      
      double out;
    
      out = spec.update(0, single_input_1);
      out = spec.update(1, single_input_2);
      out = spec.update(2, single_input_3);
      out = spec.update(3, single_input_4);
      out = spec.update(4, single_input_5);
      
      ASSERT_EQ(spec.sampling_violation_counter(), 0);
    } catch ( StlException &e ) {
      FAIL() << e.what();
    } 
}

TEST_F (StlSpecificationTest, unit_ms_sampling_unit_ms_perfect_samples) {
    StlSpecification spec;
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = rise(req)");
    spec.default_unit(Unit::MS);
    spec.sampling_period(1, Unit::MS);
    
    ASSERT_EQ(spec.default_unit(), Unit::MS);
    
    try {
      spec.parse();
      
      double out;
    
      out = spec.update(0, single_input_1);
      out = spec.update(1, single_input_2);
      out = spec.update(2, single_input_3);
      out = spec.update(3, single_input_4);
      out = spec.update(4, single_input_5);
      
      ASSERT_EQ(spec.sampling_violation_counter(), 0);
    } catch ( StlException &e ) {
      FAIL() << e.what();
    } 
}

TEST_F (StlSpecificationTest, default_unit_default_sampling_unit_almost_perfect_samples) {
    StlSpecification spec;
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = rise(req)");
    
    try {
      spec.parse();
      
      double out;
    
      out = spec.update(0, single_input_1);
      out = spec.update(1.05, single_input_2);
      out = spec.update(1.99, single_input_3);
      out = spec.update(3.01, single_input_4);
      out = spec.update(4.09, single_input_5);
      
      ASSERT_EQ(spec.sampling_violation_counter(), 0);
    } catch ( StlException &e ) {
      FAIL() << e.what();
    } 
}

TEST_F (StlSpecificationTest, default_unit_default_sampling_unit_wrong_samples) {
    StlSpecification spec;
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = rise(req)");
    
    try {
      spec.parse();
      
      double out;
    
      out = spec.update(0, single_input_1);
      out = spec.update(1.11, single_input_2);
      out = spec.update(1.99, single_input_3);
      out = spec.update(3.38, single_input_4);
      out = spec.update(4.39, single_input_5);
      
      ASSERT_EQ(spec.sampling_violation_counter(), 3);
    } catch ( StlException &e ) {
      FAIL() << e.what();
    } 
}

TEST_F (StlSpecificationTest, default_unit_default_sampling_unit_greater_tolerance_ok_samples) {
    StlSpecification spec;
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = rise(req)");
    spec.sampling_period(1, Unit::S, 0.5);
    
    try {
      spec.parse();
      
      double out;
    
      out = spec.update(0, single_input_1);
      out = spec.update(1.11, single_input_2);
      out = spec.update(1.99, single_input_3);
      out = spec.update(3.38, single_input_4);
      out = spec.update(4.39, single_input_5);
      
      ASSERT_EQ(spec.sampling_violation_counter(), 0);
    } catch ( StlException &e ) {
      FAIL() << e.what();
    } 
}

TEST_F (StlSpecificationTest, default_unit_sampling_unit_ms_almost_perfect_samples) {
    StlSpecification spec;
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = rise(req)");
    spec.sampling_period(1, Unit::MS);
    
    try {
      spec.parse();
      
      double out;
    
      out = spec.update(0, single_input_1);
      out = spec.update(0.001, single_input_2);
      out = spec.update(0.002, single_input_3);
      out = spec.update(0.003, single_input_4);
      out = spec.update(0.004, single_input_5);
      
      ASSERT_EQ(spec.sampling_violation_counter(), 0);
    } catch ( StlException &e ) {
      FAIL() << e.what();
    } 
}

TEST_F (StlSpecificationTest, default_unit_sampling_unit_ms_wrong_samples) {
    StlSpecification spec;
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = rise(req)");
    spec.default_unit(Unit::MS);
    
    try {
      spec.parse();
      
      double out;
    
      out = spec.update(0, single_input_1);
      out = spec.update(1.05, single_input_2);
      out = spec.update(1.99, single_input_3);
      out = spec.update(3.01, single_input_4);
      out = spec.update(4.09, single_input_5);
      
      ASSERT_EQ(spec.sampling_violation_counter(), 4);
    } catch ( StlException &e ) {
      FAIL() << e.what();
    } 
}

TEST_F (StlSpecificationTest, spec_from_file) {
    StlSpecification spec;
    spec.spec_from_file("../test/stl-inputs/always_bounded_pass.stl");
    
    try {
      spec.parse();
      SUCCEED();
    } catch (...) {
      FAIL() << "Did not expect an exception\n";
    }
}

TEST_F (StlSpecificationTest, wrong_file_spec_from_file) {
    StlSpecification spec;
    spec.spec_from_file("../test/stl-inputs/not_existing_file.stl");
    
    try {
      spec.parse();
      FAIL();
    } catch (StlParseException &e) {
      SUCCEED() << e.what();
    } catch (...) {
      FAIL();
    }
}

TEST_F (StlSpecificationTest, high_req_high_gnt_standard) {
    StlSpecification spec;
    
    spec.declare_var("req", Type::FLOAT);
    spec.declare_var("gnt", Type::FLOAT);
    spec.declare_var("out", Type::FLOAT);
    
    spec.var_io_type("req", StlIOType::IN);
    spec.var_io_type("gnt", StlIOType::OUT);
    
    spec.default_unit(Unit::MS);
    spec.sampling_period(10, Unit::MS, 0.1);
    
    spec.semantics(StlSemantics::STANDARD);
    
    spec.spec("out = (req >= 3) -> (eventually[0:50ms](gnt >= 3))");
    
    spec.parse();
    
    double out;
    
    out = spec.update(0, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(10, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(20, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(30, {In("req", 6.0), In("gnt", 0.0)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(40, {In("req", 6.0), In("gnt", 0.0)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(50, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, 3.0);
    
    out = spec.update(60, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, 3.0);
    
    out = spec.update(70, {In("req", 0.0), In("gnt", 6.0)});
    ASSERT_EQ(out, 3.0);
    
    out = spec.update(80, {In("req", 0.0), In("gnt", 6.0)});
    ASSERT_EQ(out, 3.0);
    
    out = spec.update(90, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, 3.0);
    
    out = spec.update(100, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, 3.0);
    
    out = spec.update(110, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, 3.0);
    
    spec.reset();
    
    out = spec.update(0, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(10, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(20, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(30, {In("req", 6.0), In("gnt", 0.0)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(40, {In("req", 6.0), In("gnt", 0.0)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(50, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, 3.0);
    
    out = spec.update(60, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, 3.0);
    
    out = spec.update(70, {In("req", 0.0), In("gnt", 2.0)});
    ASSERT_EQ(out, 3.0);
    
    out = spec.update(80, {In("req", 0.0), In("gnt", 2.0)});
    ASSERT_EQ(out, -1.0);
    
    out = spec.update(90, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, -1.0);
    
    out = spec.update(100, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, 3.0);
    
    out = spec.update(110, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, 3.0);
    
    spec.reset();
    
    out = spec.update(0, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(10, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(20, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(30, {In("req", 1.0), In("gnt", 0.0)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(40, {In("req", 1.0), In("gnt", 0.0)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(50, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, 3.0);
    
    out = spec.update(60, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, 3.0);
    
    out = spec.update(70, {In("req", 0.0), In("gnt", 2.0)});
    ASSERT_EQ(out, 3.0);
    
    out = spec.update(80, {In("req", 0.0), In("gnt", 2.0)});
    ASSERT_EQ(out, 2.0);
    
    out = spec.update(90, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, 2.0);
    
    out = spec.update(100, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, 3.0);
    
    out = spec.update(110, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, 3.0);
    
    spec.reset();
    
    out = spec.update(0, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(10, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(20, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(30, {In("req", 2.5), In("gnt", 0.0)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(40, {In("req", 2.5), In("gnt", 0.0)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(50, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, 3.0);
    
    out = spec.update(60, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, 3.0);
    
    out = spec.update(70, {In("req", 0.0), In("gnt", 2.0)});
    ASSERT_EQ(out, 3.0);
    
    out = spec.update(80, {In("req", 0.0), In("gnt", 2.0)});
    ASSERT_EQ(out, 0.5);
    
    out = spec.update(90, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, 0.5);
    
    out = spec.update(100, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, 3.0);
    
    out = spec.update(110, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, 3.0);
}

TEST_F (StlSpecificationTest, complex_random_spec_1) {
    StlSpecification spec;
    
    spec.declare_var("req", Type::FLOAT);
    spec.declare_var("gnt", Type::FLOAT);
    spec.declare_var("ack", Type::FLOAT);
    spec.declare_var("out", Type::FLOAT);
    
    spec.semantics(StlSemantics::STANDARD);
    
    spec.spec("out = (req and eventually[1:3](gnt or once[0:1]ack))");
    
    spec.parse();
    
    double out;
    
    out = spec.update(0, {In("req", -3.1), In("gnt", 2.4), In("ack", 1.5)});
    ASSERT_EQ(out, -std::numeric_limits<double>::infinity());
    
    out = spec.update(1, {In("req", -0.6), In("gnt", 7.6), In("ack", 8.3)});
    ASSERT_EQ(out, -std::numeric_limits<double>::infinity());
    
    out = spec.update(2, {In("req", 2.3), In("gnt", 0.4), In("ack", 0.2)});
    ASSERT_EQ(out, -std::numeric_limits<double>::infinity());
    
    out = spec.update(3, {In("req", 0.4), In("gnt", -0.3), In("ack", 7.1)});
    ASSERT_EQ(out, -3.1);
    
    out = spec.update(4, {In("req", 2.1), In("gnt", -7.1), In("ack", 0.5)});
    ASSERT_EQ(out, -0.6);
    
    out = spec.update(5, {In("req", 8.7), In("gnt", -5), In("ack", -0.5)});
    ASSERT_EQ(out, 2.3);
    
    out = spec.update(6, {In("req", 0.1), In("gnt", 1.1), In("ack", 1.3)});
    ASSERT_EQ(out, 0.4);
    
    out = spec.update(7, {In("req", -0.1), In("gnt", 2.4), In("ack", 2.1)});
    ASSERT_EQ(out, 2.1);
    
    out = spec.update(8, {In("req", 2.2), In("gnt", 1.5), In("ack", 7.3)});
    ASSERT_EQ(out, 7.3);
    
    out = spec.update(9, {In("req", -3), In("gnt", 8.8), In("ack", 2.5)});
    ASSERT_EQ(out, 0.1);
}


TEST_F (StlSpecificationTest, complex_random_spec_2) {
    StlSpecification spec;
    
    spec.declare_var("req", Type::FLOAT);
    spec.declare_var("gnt", Type::FLOAT);
    spec.declare_var("ack", Type::FLOAT);
    spec.declare_var("out", Type::FLOAT);
    
    spec.semantics(StlSemantics::STANDARD);
    
    spec.spec("out = (req until[1:2] gnt) or eventually[3:4](historically[1:2]ack)");
    
    spec.parse();
    
    double out;
    
    out = spec.update(0, {In("req", -3.1), In("gnt", 2.4), In("ack", 1.5)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(1, {In("req", -0.6), In("gnt", 7.6), In("ack", 8.3)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(2, {In("req", 2.3), In("gnt", 0.4), In("ack", 0.2)});
    ASSERT_EQ(out, 1.5);
    
    out = spec.update(3, {In("req", 0.4), In("gnt", -0.3), In("ack", 7.1)});
    ASSERT_EQ(out, 1.5);
    
    out = spec.update(4, {In("req", 2.1), In("gnt", -7.1), In("ack", 0.5)});
    ASSERT_EQ(out, 0.2);
    
    out = spec.update(5, {In("req", 8.7), In("gnt", -5), In("ack", -0.5)});
    ASSERT_EQ(out, 0.5);
    
    out = spec.update(6, {In("req", 0.1), In("gnt", 1.1), In("ack", 1.3)});
    ASSERT_EQ(out, 0.5);
    
    out = spec.update(7, {In("req", -0.1), In("gnt", 2.4), In("ack", 2.1)});
    ASSERT_EQ(out, -0.5);
    
    out = spec.update(8, {In("req", 2.2), In("gnt", 1.5), In("ack", 7.3)});
    ASSERT_EQ(out, 1.3);
    
    out = spec.update(9, {In("req", -3), In("gnt", 8.8), In("ack", 2.5)});
    ASSERT_EQ(out, 2.1);
}

TEST_F (StlSpecificationTest, complex_random_spec_3) {
    StlSpecification spec;
    
    spec.declare_var("req", Type::FLOAT);
    spec.declare_var("gnt", Type::FLOAT);
    spec.declare_var("ack", Type::FLOAT);
    spec.declare_var("out", Type::FLOAT);
    
    spec.semantics(StlSemantics::STANDARD);
    
    spec.spec("out = (once[2:3]req) -> (gnt since[1:2] ack)");
    
    spec.parse();
    
    double out;
    
    out = spec.update(0, {In("req", -3.1), In("gnt", 2.4), In("ack", 1.5)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(1, {In("req", -0.6), In("gnt", 7.6), In("ack", 8.3)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(2, {In("req", 2.3), In("gnt", 0.4), In("ack", 0.2)});
    ASSERT_EQ(out, 3.1);
    
    out = spec.update(3, {In("req", 0.4), In("gnt", -0.3), In("ack", 7.1)});
    ASSERT_EQ(out, 0.6);
    
    out = spec.update(4, {In("req", 2.1), In("gnt", -7.1), In("ack", 0.5)});
    ASSERT_EQ(out, -2.3);
    
    out = spec.update(5, {In("req", 8.7), In("gnt", -5), In("ack", -0.5)});
    ASSERT_EQ(out, -2.3);
    
    out = spec.update(6, {In("req", 0.1), In("gnt", 1.1), In("ack", 1.3)});
    ASSERT_EQ(out, -0.5);
    
    out = spec.update(7, {In("req", -0.1), In("gnt", 2.4), In("ack", 2.1)});
    ASSERT_EQ(out, 1.3);
    
    out = spec.update(8, {In("req", 2.2), In("gnt", 1.5), In("ack", 7.3)});
    ASSERT_EQ(out, 1.5);
    
    out = spec.update(9, {In("req", -3), In("gnt", 8.8), In("ack", 2.5)});
    ASSERT_EQ(out, 7.3);
}

TEST_F (StlSpecificationTest, complex_random_spec_3_1) {
    StlSpecification spec;
    
    spec.declare_var("req", Type::FLOAT);
    spec.declare_var("gnt", Type::FLOAT);
    spec.declare_var("ack", Type::FLOAT);
    spec.declare_var("out", Type::FLOAT);
    
    spec.default_unit(Unit::MS);
    
    spec.semantics(StlSemantics::STANDARD);
    
    spec.spec("out = (once[2000:3000]req) -> (gnt since[1000:2000] ack)");
    
    spec.parse();
    
    double out;
    
    out = spec.update(0, {In("req", -3.1), In("gnt", 2.4), In("ack", 1.5)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(1000, {In("req", -0.6), In("gnt", 7.6), In("ack", 8.3)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(2000, {In("req", 2.3), In("gnt", 0.4), In("ack", 0.2)});
    ASSERT_EQ(out, 3.1);
    
    out = spec.update(3000, {In("req", 0.4), In("gnt", -0.3), In("ack", 7.1)});
    ASSERT_EQ(out, 0.6);
    
    out = spec.update(4000, {In("req", 2.1), In("gnt", -7.1), In("ack", 0.5)});
    ASSERT_EQ(out, -2.3);
    
    out = spec.update(5000, {In("req", 8.7), In("gnt", -5), In("ack", -0.5)});
    ASSERT_EQ(out, -2.3);
    
    out = spec.update(6000, {In("req", 0.1), In("gnt", 1.1), In("ack", 1.3)});
    ASSERT_EQ(out, -0.5);
    
    out = spec.update(7000, {In("req", -0.1), In("gnt", 2.4), In("ack", 2.1)});
    ASSERT_EQ(out, 1.3);
    
    out = spec.update(8000, {In("req", 2.2), In("gnt", 1.5), In("ack", 7.3)});
    ASSERT_EQ(out, 1.5);
    
    out = spec.update(9000, {In("req", -3), In("gnt", 8.8), In("ack", 2.5)});
    ASSERT_EQ(out, 7.3);
}

TEST_F (StlSpecificationTest, complex_random_spec_3_2) {
    StlSpecification spec;
    
    spec.declare_var("req", Type::FLOAT);
    spec.declare_var("gnt", Type::FLOAT);
    spec.declare_var("ack", Type::FLOAT);
    spec.declare_var("out", Type::FLOAT);
    
    spec.default_unit(Unit::MS);
    
    spec.semantics(StlSemantics::STANDARD);
    
    spec.spec("out = (once[2s:3s]req) -> (gnt since[1000:2000] ack)");
    
    spec.parse();
    
    double out;
    
    out = spec.update(0, {In("req", -3.1), In("gnt", 2.4), In("ack", 1.5)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(1000, {In("req", -0.6), In("gnt", 7.6), In("ack", 8.3)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(2000, {In("req", 2.3), In("gnt", 0.4), In("ack", 0.2)});
    ASSERT_EQ(out, 3.1);
    
    out = spec.update(3000, {In("req", 0.4), In("gnt", -0.3), In("ack", 7.1)});
    ASSERT_EQ(out, 0.6);
    
    out = spec.update(4000, {In("req", 2.1), In("gnt", -7.1), In("ack", 0.5)});
    ASSERT_EQ(out, -2.3);
    
    out = spec.update(5000, {In("req", 8.7), In("gnt", -5), In("ack", -0.5)});
    ASSERT_EQ(out, -2.3);
    
    out = spec.update(6000, {In("req", 0.1), In("gnt", 1.1), In("ack", 1.3)});
    ASSERT_EQ(out, -0.5);
    
    out = spec.update(7000, {In("req", -0.1), In("gnt", 2.4), In("ack", 2.1)});
    ASSERT_EQ(out, 1.3);
    
    out = spec.update(8000, {In("req", 2.2), In("gnt", 1.5), In("ack", 7.3)});
    ASSERT_EQ(out, 1.5);
    
    out = spec.update(9000, {In("req", -3), In("gnt", 8.8), In("ack", 2.5)});
    ASSERT_EQ(out, 7.3);
}

TEST_F (StlSpecificationTest, complex_random_spec_3_3) {
    StlSpecification spec;
    
    spec.declare_var("req", Type::FLOAT);
    spec.declare_var("gnt", Type::FLOAT);
    spec.declare_var("ack", Type::FLOAT);
    spec.declare_var("out", Type::FLOAT);
    
    spec.default_unit(Unit::MS);
    spec.sampling_period(1, Unit::MS);
    
    spec.semantics(StlSemantics::STANDARD);
    
    spec.spec("out = (once[2ms:3ms]req) -> (gnt since[0.001s:0.002s] ack)");
    
    spec.parse();
    
    double out;
    
    out = spec.update(0, {In("req", -3.1), In("gnt", 2.4), In("ack", 1.5)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(1, {In("req", -0.6), In("gnt", 7.6), In("ack", 8.3)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(2, {In("req", 2.3), In("gnt", 0.4), In("ack", 0.2)});
    ASSERT_EQ(out, 3.1);
    
    out = spec.update(3, {In("req", 0.4), In("gnt", -0.3), In("ack", 7.1)});
    ASSERT_EQ(out, 0.6);
    
    out = spec.update(4, {In("req", 2.1), In("gnt", -7.1), In("ack", 0.5)});
    ASSERT_EQ(out, -2.3);
    
    out = spec.update(5, {In("req", 8.7), In("gnt", -5), In("ack", -0.5)});
    ASSERT_EQ(out, -2.3);
    
    out = spec.update(6, {In("req", 0.1), In("gnt", 1.1), In("ack", 1.3)});
    ASSERT_EQ(out, -0.5);
    
    out = spec.update(7, {In("req", -0.1), In("gnt", 2.4), In("ack", 2.1)});
    ASSERT_EQ(out, 1.3);
    
    out = spec.update(8, {In("req", 2.2), In("gnt", 1.5), In("ack", 7.3)});
    ASSERT_EQ(out, 1.5);
    
    out = spec.update(9, {In("req", -3), In("gnt", 8.8), In("ack", 2.5)});
    ASSERT_EQ(out, 7.3);
}

TEST_F (StlSpecificationTest, complex_random_spec_3_4) {
    StlSpecification spec;
    
    spec.declare_var("req", Type::FLOAT);
    spec.declare_var("gnt", Type::FLOAT);
    spec.declare_var("ack", Type::FLOAT);
    spec.declare_var("out", Type::FLOAT);
    
    spec.default_unit(Unit::MS);
    spec.sampling_period(1, Unit::MS);
    
    spec.semantics(StlSemantics::STANDARD);
    
    spec.spec("out = (once[2ms:3ms]req) -> (gnt since[.001s:2e-3s] ack)");
    
    spec.parse();
    
    double out;
    
    out = spec.update(0, {In("req", -3.1), In("gnt", 2.4), In("ack", 1.5)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(1, {In("req", -0.6), In("gnt", 7.6), In("ack", 8.3)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(2, {In("req", 2.3), In("gnt", 0.4), In("ack", 0.2)});
    ASSERT_EQ(out, 3.1);
    
    out = spec.update(3, {In("req", 0.4), In("gnt", -0.3), In("ack", 7.1)});
    ASSERT_EQ(out, 0.6);
    
    out = spec.update(4, {In("req", 2.1), In("gnt", -7.1), In("ack", 0.5)});
    ASSERT_EQ(out, -2.3);
    
    out = spec.update(5, {In("req", 8.7), In("gnt", -5), In("ack", -0.5)});
    ASSERT_EQ(out, -2.3);
    
    out = spec.update(6, {In("req", 0.1), In("gnt", 1.1), In("ack", 1.3)});
    ASSERT_EQ(out, -0.5);
    
    out = spec.update(7, {In("req", -0.1), In("gnt", 2.4), In("ack", 2.1)});
    ASSERT_EQ(out, 1.3);
    
    out = spec.update(8, {In("req", 2.2), In("gnt", 1.5), In("ack", 7.3)});
    ASSERT_EQ(out, 1.5);
    
    out = spec.update(9, {In("req", -3), In("gnt", 8.8), In("ack", 2.5)});
    ASSERT_EQ(out, 7.3);
}

TEST_F (StlSpecificationTest, spec_as_pointer) {
    StlSpecification *spec = new StlSpecification();
    
    spec->declare_var("req", Type::FLOAT);
    spec->declare_var("gnt", Type::FLOAT);
    spec->declare_var("out", Type::FLOAT);
    
    spec->var_io_type("req", StlIOType::IN);
    spec->var_io_type("gnt", StlIOType::OUT);
    
    spec->default_unit(Unit::MS);
    spec->sampling_period(10, Unit::MS, 0.1);
    
    spec->semantics(StlSemantics::IN_VACUITY);
    
    spec->spec("out = (req >= 3) -> (eventually[0:50ms](gnt >= 3))");
    
    spec->parse();
    
    double out;
    
    out = spec->update(0, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    delete spec;
}

TEST_F (StlSpecificationTest, spec_copy) {
    StlSpecification *spec = new StlSpecification();
    
    spec->declare_var("req", Type::FLOAT);
    spec->declare_var("gnt", Type::FLOAT);
    spec->declare_var("out", Type::FLOAT);
    
    spec->var_io_type("req", StlIOType::IN);
    spec->var_io_type("gnt", StlIOType::OUT);
    
    spec->default_unit(Unit::MS);
    spec->sampling_period(10, Unit::MS, 0.1);
    
    spec->semantics(StlSemantics::IN_VACUITY);
    
    spec->spec("out = (req >= 3) -> (eventually[0:50ms](gnt >= 3))");
    
    StlSpecification *spec_new = spec;
    
    spec_new->parse();
    
    double out;
    
    out = spec_new->update(0, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    delete spec_new;
}

TEST_F (StlSpecificationTest, spec_copy_2) {
    StlSpecification spec;
    
    spec.declare_var("req", Type::FLOAT);
    spec.declare_var("gnt", Type::FLOAT);
    spec.declare_var("out", Type::FLOAT);
    
    spec.var_io_type("req", StlIOType::IN);
    spec.var_io_type("gnt", StlIOType::OUT);
    
    spec.default_unit(Unit::MS);
    spec.sampling_period(10, Unit::MS, 0.1);
    
    spec.semantics(StlSemantics::IN_VACUITY);
    
    spec.spec("out = (req >= 3) -> (eventually[0:50ms](gnt >= 3))");
    
    StlSpecification spec_new;
    spec_new = spec;
    
    spec_new.parse();
    
    double out;
    
    out = spec_new.update(0, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
}

TEST_F (StlSpecificationTest, complex_constant) {
    StlSpecification spec;
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = always(5 <= 7)");
    
    try {
      spec.parse();
      
      double out;
      out = spec.update(0, {});
    
      EXPECT_EQ(2, out);
      
      out = spec.update(1, {});
    
      EXPECT_EQ(2, out);
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    } 
}


TEST_F (StlSpecificationTest, high_req_high_gnt_in_vacuity) {
    StlSpecification spec;
    
    spec.declare_var("req", Type::FLOAT);
    spec.declare_var("gnt", Type::FLOAT);
    spec.declare_var("out", Type::FLOAT);
    
    spec.var_io_type("req", StlIOType::IN);
    spec.var_io_type("gnt", StlIOType::OUT);
    
    spec.default_unit(Unit::MS);
    spec.sampling_period(10, Unit::MS, 0.1);
    
    spec.semantics(StlSemantics::IN_VACUITY);
    
    spec.spec("out = (req >= 3) -> (eventually[0:50ms](gnt >= 3))");
    
    spec.parse();
    
    double out;
    
    out = spec.update(0, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(10, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(20, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(30, {In("req", 6.0), In("gnt", 0.0)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(40, {In("req", 6.0), In("gnt", 0.0)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(50, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, 3.0);
    
    out = spec.update(60, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, 3.0);
    
    out = spec.update(70, {In("req", 0.0), In("gnt", 6.0)});
    ASSERT_EQ(out, 3.0);
    
    out = spec.update(80, {In("req", 0.0), In("gnt", 6.0)});
    ASSERT_EQ(out, 0.0);
    
    out = spec.update(90, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, 0.0);
    
    out = spec.update(100, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, 3.0);
    
    out = spec.update(110, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, 3.0);
    
    spec.reset();
    
    out = spec.update(0, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(10, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(20, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(30, {In("req", 2.0), In("gnt", 0.0)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(40, {In("req", 2.0), In("gnt", 0.0)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(50, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, 3.0);
    
    out = spec.update(60, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, 3.0);
    
    out = spec.update(70, {In("req", 0.0), In("gnt", 2.0)});
    ASSERT_EQ(out, 3.0);
    
    out = spec.update(80, {In("req", 0.0), In("gnt", 2.0)});
    ASSERT_EQ(out, 1.0);
    
    out = spec.update(90, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, 1.0);
    
    out = spec.update(100, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, 3.0);
    
    out = spec.update(110, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, 3.0);
    
    spec.reset();
    
    out = spec.update(0, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(10, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(20, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(30, {In("req", 1.0), In("gnt", 0.0)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(40, {In("req", 1.0), In("gnt", 0.0)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(50, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, 3.0);
    
    out = spec.update(60, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, 3.0);
    
    out = spec.update(70, {In("req", 0.0), In("gnt", 2.0)});
    ASSERT_EQ(out, 3.0);
    
    out = spec.update(80, {In("req", 0.0), In("gnt", 2.0)});
    ASSERT_EQ(out, 2.0);
    
    out = spec.update(90, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, 2.0);
    
    out = spec.update(100, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, 3.0);
    
    out = spec.update(110, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, 3.0);
    
    spec.reset();
    
    out = spec.update(0, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(10, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(20, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(30, {In("req", 2.5), In("gnt", 0.0)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(40, {In("req", 2.5), In("gnt", 0.0)});
    ASSERT_EQ(out, std::numeric_limits<double>::infinity());
    
    out = spec.update(50, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, 3.0);
    
    out = spec.update(60, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, 3.0);
    
    out = spec.update(70, {In("req", 0.0), In("gnt", 2.0)});
    ASSERT_EQ(out, 3.0);
    
    out = spec.update(80, {In("req", 0.0), In("gnt", 2.0)});
    ASSERT_EQ(out, 0.5);
    
    out = spec.update(90, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, 0.5);
    
    out = spec.update(100, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, 3.0);
    
    out = spec.update(110, {In("req", 0.0), In("gnt", 0.0)});
    ASSERT_EQ(out, 3.0);
}

TEST_F (StlSpecificationTest, constant_declaration_1) {
    StlSpecification spec;
    spec.declare_const("c", rtamt::Type::FLOAT, "2");
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = once[0:1](req >= c)");
    
    try {
      spec.parse();
      
      double out;
    
      out = spec.update(0, single_input_1);
      EXPECT_EQ(98, out);
    
      out = spec.update(1, single_input_2);
      EXPECT_EQ(98, out);
    
      out = spec.update(2, single_input_3);
      EXPECT_EQ(-3, out);
    
      out = spec.update(3, single_input_4);
      EXPECT_EQ(3, out);
    
      out = spec.update(4, single_input_5);
      EXPECT_EQ(3, out);
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    } 
}

TEST_F (StlSpecificationTest, constant_declaration_2) {
    StlSpecification spec;
    spec.declare_const("c", rtamt::Type::FLOAT, "2.1");
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = once[0:1](req >= c)");
    
    try {
      spec.parse();
      
      double out;
    
      out = spec.update(0, single_input_1);
      EXPECT_EQ(97.9, out);
    
      out = spec.update(1, single_input_2);
      EXPECT_EQ(97.9, out);
    
      out = spec.update(2, single_input_3);
      EXPECT_EQ(-3.1, out);
    
      out = spec.update(3, single_input_4);
      EXPECT_EQ(2.9, out);
    
      out = spec.update(4, single_input_5);
      EXPECT_EQ(2.9, out);
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    } 
}

TEST_F (StlSpecificationTest, constant_declaration_3) {
    StlSpecification spec;
    spec.declare_const("c", rtamt::Type::FLOAT, "1");
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = once[0:c](req >= 2)");
    
    try {
      spec.parse();
      
      double out;
    
      out = spec.update(0, single_input_1);
      EXPECT_EQ(98, out);
    
      out = spec.update(1, single_input_2);
      EXPECT_EQ(98, out);
    
      out = spec.update(2, single_input_3);
      EXPECT_EQ(-3, out);
    
      out = spec.update(3, single_input_4);
      EXPECT_EQ(3, out);
    
      out = spec.update(4, single_input_5);
      EXPECT_EQ(3, out);
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    } 
}

TEST_F (StlSpecificationTest, constant_declaration_4) {
    StlSpecification spec;
    spec.declare_const("c", rtamt::Type::FLOAT, "1000");
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("out = once[0:c ms](req >= 2)");
    
    try {
      spec.parse();
      
      double out;
    
      out = spec.update(0, single_input_1);
      EXPECT_EQ(98, out);
    
      out = spec.update(1, single_input_2);
      EXPECT_EQ(98, out);
    
      out = spec.update(2, single_input_3);
      EXPECT_EQ(-3, out);
    
      out = spec.update(3, single_input_4);
      EXPECT_EQ(3, out);
    
      out = spec.update(4, single_input_5);
      EXPECT_EQ(3, out);
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    } 
}

TEST_F (StlSpecificationTest, constant_declaration_5) {
    StlSpecification spec;
    spec.declare_var("req", rtamt::Type::FLOAT);
    spec.declare_var("out", rtamt::Type::FLOAT);
    spec.spec("const float c = 1\nout = once[0:c](req >= 2)");
    
    try {
      spec.parse();
      
      double out;
    
      out = spec.update(0, single_input_1);
      EXPECT_EQ(98, out);
    
      out = spec.update(1, single_input_2);
      EXPECT_EQ(98, out);
    
      out = spec.update(2, single_input_3);
      EXPECT_EQ(-3, out);
    
      out = spec.update(3, single_input_4);
      EXPECT_EQ(3, out);
    
      out = spec.update(4, single_input_5);
      EXPECT_EQ(3, out);
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    } 
}
