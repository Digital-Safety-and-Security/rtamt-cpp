/*
 * This example will take and STL spec, parse it, perform semantic checks and build a DAG. 
 *
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <antlr4-runtime.h>
#include <grammar/StlLexer.h>
#include <grammar/StlParser.h>
#include <grammar/StlParserVisitor.h>
#include <spec/stl_semantic_visitor.hpp>
#include <rtamt/stl_specification.hpp>
#include <spec/stl_inner_specification.hpp>


using namespace std;
using namespace grammar;
using namespace antlr4;
using namespace stl_library;
using namespace rtamt;
using namespace spec;



int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "Specify formula name as argument" << endl;
        return 1;
    }
    //const char* filename = argv[1];

    const char* filename = "build_a_tree.stl";
    string fileStr = "../../test/stl-semantic/";
    fileStr.append(filename);
    
    StlSpecification stlSpec;

    stlSpec.spec_from_file(fileStr);
 
    //stlSpec.parse(); //interno pravi node i popuni
    //create /load trace
    //stlSpec.update()
    
    //myRoot = semVisitor.visitStlfile()
//     stlSpec.getInnerSpec().setStlRoot(myRoot);
//     stlSpec.getInnerSpec().setVarIOType(semVisitor.varIOType)
//     stlSpec.getInnerSpec().setVarType(semVisitor.varType)
    
    
    
    
    
    
    
    
    return 0;
}
