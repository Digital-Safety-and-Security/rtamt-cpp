#include <string>
#include <gtest/gtest.h>
#include <boost/rational.hpp>
#include <rtamt/stl_exception.hpp>
#include <spec/stl_specification_parser.hpp>



using namespace spec;
using namespace std;
using namespace rtamt;

TEST (StlTimeUnits, general) {
    boost::rational<uint64_t> out = StlSpecificationParser::str_to_rational(std::string("13.4"));
    
    ASSERT_EQ(out, boost::rational<uint64_t>(134, 10));
    
    
    out = StlSpecificationParser::str_to_rational(std::string(".456"));
    
    ASSERT_EQ(out, boost::rational<uint64_t>(456, 1000));
    
    out = StlSpecificationParser::str_to_rational(std::string("52"));
    
    ASSERT_EQ(out, boost::rational<uint64_t>(52, 1));
    
    out = StlSpecificationParser::str_to_rational(std::string("52e-2"));
    
    ASSERT_EQ(out, boost::rational<uint64_t>(52, 100));
    
    out = StlSpecificationParser::str_to_rational(std::string("1.333E2"));
    
    ASSERT_EQ(out, boost::rational<uint64_t>(133300, 1000));
    
    try {
        out = StlSpecificationParser::str_to_rational(std::string("1.333E2e3"));
        FAIL() << "Two dots in a string";
    } catch (StlParseException &e) {
        SUCCEED();
    } catch (...) {
        FAIL() << "Caught unexpected exception";
    }
    
    try {
        out = StlSpecificationParser::str_to_rational(std::string("5.44.33"));
        FAIL() << "Two dots in a string.";
    } catch (StlParseException &e) {
        SUCCEED();
    } catch (...) {
        FAIL() << "Caught unexpected exception";
    }
}
