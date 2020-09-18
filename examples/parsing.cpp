#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <antlr4-runtime.h>
#include <grammar/StlLexer.h>
#include <grammar/StlParser.h>
#include <grammar/StlParserVisitor.h>
#include <spec/stl_semantic_visitor.hpp>

using namespace std;
using namespace grammar;
using namespace antlr4;
using namespace stl_library;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "Specify formula name as argument" << endl;
        return 1;
    }
    //const char* filename = argv[1];

    const char* filename = "identifier_already_defined.stl";

    cout << "Entered filename: \"" << filename << "\"" << endl;

    string fileStr = "../../test/stl-semantic/";
    fileStr.append(filename);

    cout << "Full filename: \"" << fileStr << "\"" << endl;

    ifstream f(fileStr);
    string str;

    if (f) {
        ostringstream ss;
        ss << f.rdbuf();
        str = ss.str();
    }
    else {
        cout << "\nFILE IS NULL" << endl;
    }

    cout << "File content: \"" << str << "\"" << endl;

    ANTLRInputStream antlrinput(str);
    StlLexer lexer(&antlrinput);
    CommonTokenStream tokens(&lexer);
    StlParser parser(&tokens);

    StlParser::StlfileContext* tree = parser.stlfile();

    //walk the tree and perform semantic checks with a semantic visitor

    StlSemanticVisitor semVisitor;

    try {
        semVisitor.visitStlfile(tree);
    }
    catch(StlSemanticException semException) {
        cout<<"SEMANTIC EXCEPTION OCCURED"<<endl;
        cout<<semException.description<<endl;
    }

    return 0;
}
