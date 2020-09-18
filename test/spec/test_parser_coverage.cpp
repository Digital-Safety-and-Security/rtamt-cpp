#include <string>
#include <gtest/gtest.h>
#include <rtamt/stl_specification.hpp>
#include <rtamt/stl_exception.hpp>

using namespace rtamt;
using namespace std;

using In = rtamt::Input;

TEST (TestParserCoverage, always_bounded_pass) {
    StlSpecification spec;
    
    spec.declare_var("a", Type::FLOAT);
    spec.declare_var("c", Type::FLOAT);
    spec.var_io_type("a", rtamt::StlIOType::IN);
    spec.spec("c = always[1:2](a <= 2)");
    
    try {
      spec.parse();
      double computed;
      computed = spec.update(0, {In("a", 1.2)});
      ASSERT_EQ(computed, 0.8);
    
      spec.reset();
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    }
}



TEST (TestParserCoverage, always_predicate_pass) {
    StlSpecification spec;
    
    spec.declare_var("a", Type::FLOAT);
    spec.declare_var("c", Type::FLOAT);
    spec.var_io_type("a", rtamt::StlIOType::IN);
    spec.spec("c = always(a <= 2)");
    
    try {
      spec.parse();
      double computed;
      computed = spec.update(0, {In("a", 1.2)});
      ASSERT_EQ(computed, 0.8);
    
      spec.reset();
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    }
}


TEST (TestParserCoverage, bounded_response_pass) {
    StlSpecification spec;
    
    spec.declare_var("a", Type::FLOAT);
    spec.declare_var("b", Type::FLOAT);
    spec.declare_var("c", Type::FLOAT);
    spec.var_io_type("a", rtamt::StlIOType::IN);
    spec.var_io_type("b", rtamt::StlIOType::IN);

    spec.spec("c = always((a <= 2) implies eventually[1:2](b <= 2))");
    
    try {
      spec.parse();
      double computed;
      computed = spec.update(0, {In("a", 1.2)});
      ASSERT_EQ(computed, 2);
    
      spec.reset();
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    }
}


TEST (TestParserCoverage, conjunction_pass) {
    StlSpecification spec;
    
    spec.declare_var("a", Type::FLOAT);
    spec.declare_var("b", Type::FLOAT);
    spec.declare_var("c", Type::FLOAT);
    spec.var_io_type("a", rtamt::StlIOType::IN);
    spec.var_io_type("b", rtamt::StlIOType::IN);

    spec.spec("c = (a <= 2 and b > 3)");
    
    try {
      spec.parse();
      double computed;
      computed = spec.update(0, {In("a", 1.2)});
      ASSERT_EQ(computed, -3);
    
      spec.reset();
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    }
}


TEST (TestParserCoverage, disjunction_pass) {
    StlSpecification spec;
    
    spec.declare_var("a", Type::FLOAT);
    spec.declare_var("b", Type::FLOAT);
    spec.declare_var("c", Type::FLOAT);
    spec.var_io_type("a", rtamt::StlIOType::IN);
    spec.var_io_type("b", rtamt::StlIOType::IN);

    spec.spec("c = (a <= 2 or b > 3)");
    
    try {
      spec.parse();
      double computed;
      computed = spec.update(0, {In("a", 1.2)});
      ASSERT_EQ(computed, 0.8);
    
      spec.reset();
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    }
}



TEST (TestParserCoverage, eventually_bounded_pass) {
    StlSpecification spec;
    
    spec.declare_var("a", Type::FLOAT);
    spec.declare_var("c", Type::FLOAT);
    spec.var_io_type("a", rtamt::StlIOType::IN);

    spec.spec("c = eventually[1:2](a <= 2)");
    
    try {
      spec.parse();
      double computed;
      computed = spec.update(0, {In("a", 1.2)});
      ASSERT_EQ(computed, 0.8);
    
      spec.reset();
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    }
}



TEST (TestParserCoverage, historically_bounded_pass) {
    StlSpecification spec;
    
    spec.declare_var("a", Type::FLOAT);
    spec.declare_var("c", Type::FLOAT);
    spec.var_io_type("a", rtamt::StlIOType::IN);

    spec.spec("c = historically[1:2](a < 2)");
    
    try {
      spec.parse();
      double computed;
      computed = spec.update(0, {In("a", 3)});
      ASSERT_EQ(computed, std::numeric_limits<double>::infinity());
    
      spec.reset();
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    }
}


TEST (TestParserCoverage, implication_pass) {
    StlSpecification spec;
    
    spec.declare_var("a", Type::FLOAT);
    spec.declare_var("b", Type::FLOAT);
    spec.declare_var("c", Type::FLOAT);
    spec.var_io_type("a", rtamt::StlIOType::IN);
    spec.var_io_type("b", rtamt::StlIOType::IN);

    spec.spec("c = (a <= 2 implies b > 3)");
    
    try {
      spec.parse();
      double computed;
      computed = spec.update(0, {In("a", 1), In("b", 4)});
      ASSERT_EQ(computed, 1);
    
      spec.reset();
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    }
}


TEST (TestParserCoverage, once_bounded_pass) {
    StlSpecification spec;
    
    spec.declare_var("a", Type::FLOAT);
    spec.declare_var("c", Type::FLOAT);
    spec.var_io_type("a", rtamt::StlIOType::IN);

    spec.spec("c = once[1:2](a > 2)");
    
    try {
      spec.parse();
      double computed;
                 spec.update(0, {In("a", 3.1)});
      computed = spec.update(1, {In("a", 2.4)});
      ASSERT_EQ(computed, 1.1);
    
      spec.reset();
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    }
}



TEST (TestParserCoverage, predicate_pass) {
    StlSpecification spec;
    
    spec.declare_var("a", Type::FLOAT);
    spec.declare_var("c", Type::FLOAT);
    spec.var_io_type("a", rtamt::StlIOType::IN);

    spec.spec("c = (a <= 2.4)");
    
    try {
      spec.parse();
      double computed;
      computed = spec.update(0, {In("a", 2.4)});
      ASSERT_EQ(computed, 0);
    
      spec.reset();
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    }
}

TEST (TestParserCoverage, since_bounded_fail) {
    StlSpecification spec;
    
    spec.declare_var("a", Type::FLOAT);
    spec.declare_var("b", Type::FLOAT);
    spec.declare_var("c", Type::FLOAT);
    spec.var_io_type("a", rtamt::StlIOType::IN);
    spec.var_io_type("b", rtamt::StlIOType::IN);

    spec.spec("c = (a <= 2 since[1:4] b > 3)");
    
    try {
      spec.parse();
      double computed;
      computed = spec.update(4, {In("a", 0), In("b", 4.4)});
      computed = spec.update(6, {In("a", 1.2), In("b", 4.4)});
      
      ASSERT_EQ(computed, 0.8);
    
      spec.reset();
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    }
}

TEST (TestParserCoverage, since_pass) {
    StlSpecification spec;
    
    spec.declare_var("a", Type::FLOAT);
    spec.declare_var("b", Type::FLOAT);
    spec.declare_var("c", Type::FLOAT);
    spec.var_io_type("a", rtamt::StlIOType::IN);
    spec.var_io_type("b", rtamt::StlIOType::IN);

    spec.spec("c = (a <= 2 since b > 3)");
    
    try {
      spec.parse();
      double computed;
      computed = spec.update(0, {In("a", 0),   In("b", 5)});
      computed = spec.update(1, {In("a", 1.2), In("b", 5)});

      
      ASSERT_EQ(computed, 2);
    
      spec.reset();
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    }
}

TEST (TestParserCoverage, annotation) {
    StlSpecification spec;
    
    spec.declare_var("a", Type::FLOAT);
    spec.declare_var("b", Type::FLOAT);
    spec.declare_var("c", Type::FLOAT);
    spec.var_io_type("a", rtamt::StlIOType::IN);
    spec.var_io_type("b", rtamt::StlIOType::IN);

    spec.spec("@ topic (x,y)  c = (a <= 2 since b > 3)");
    
    try {
      spec.parse();
      double computed;
      computed = spec.update(0, {In("a", 0),   In("b", 5)});
      computed = spec.update(1, {In("a", 1.2), In("b", 5)});
      
      ASSERT_EQ(computed, 2);
    
      spec.reset();
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    }
}


TEST (TestParserCoverage, minus_sign) {
    StlSpecification spec;
    
    spec.declare_var("a", Type::FLOAT);
    spec.declare_var("b", Type::FLOAT);
    spec.declare_var("c", Type::FLOAT);
    spec.var_io_type("a", rtamt::StlIOType::IN);
    spec.var_io_type("b", rtamt::StlIOType::IN);

    spec.spec("c = (a <= -2 since b > -3)");
    
    try {
      spec.parse();
      double computed;
      computed = spec.update(0, {In("a", 0),   In("b", 5)});
      computed = spec.update(1, {In("a", 1.2), In("b", 5)});

      
      ASSERT_EQ(computed, 8);
    
      spec.reset();
      
    } catch ( StlException &e ) {
      FAIL() << e.what();
    }
}
