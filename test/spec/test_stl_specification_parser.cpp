#include <string>
#include <gtest/gtest.h>
#include <antlr4-runtime.h>
#include <grammar/StlLexer.h>
#include <grammar/StlParser.h>
#include <grammar/StlParserVisitor.h>
#include <spec/stl_specification_parser.hpp>
#include <rtamt/stl_specification.hpp>
#include <rtamt/stl_exception.hpp>


using namespace node;
using namespace spec;
using namespace std;
using namespace grammar;
using namespace antlr4;
using namespace rtamt;

TEST (StlSpecificationParser, general) {
    string str;
    ostringstream spec_str;
    spec_str << "specification always_bounded_pass\n";
    spec_str << "input float a\n";
    spec_str << "float c\n";
    spec_str << "c = always[1:2](a <= 2)\n";
    
    str = spec_str.str();

    ANTLRInputStream antlrinput ( str );
    StlLexer lexer ( &antlrinput );
    CommonTokenStream tokens ( &lexer );
    StlParser parser ( &tokens );

    StlParser::StlfileContext* tree = parser.stlfile();
    StlInnerSpecification spec;
    StlSpecificationParser specParser(&spec);

    try {
        specParser.visitStlfile ( tree );
    } catch ( StlParseException &semException ) {
        FAIL() << "Semantic exception occured";
    } catch (...) {
        FAIL() << "Exception occured";
    }
    
    const string expected_spec_name = "always_bounded_pass";
    ASSERT_EQ(specParser.spec()->name(), expected_spec_name);
    
    const string expected_rob_var = "c";
    ASSERT_EQ(specParser.spec()->rob_var(), expected_rob_var);
    
    rtamt::StlIOType expected_var_a_io_type = StlIOType::IN;
    ASSERT_EQ(specParser.spec()->var_io_type("a"), expected_var_a_io_type);
    
    rtamt::StlIOType expected_var_c_io_type = StlIOType::DEFAULT;
    ASSERT_EQ(specParser.spec()->var_io_type("c"), expected_var_c_io_type);
    
    StlNode *node = specParser.root();
    std::ostringstream stream;
    double constant = 2.0;
    stream << "always[1,2]((a)<=(" << std::to_string(constant) << "))";
    const string expected_spec = stream.str();
    ASSERT_EQ(node->getName(), expected_spec);
    delete node;
}
