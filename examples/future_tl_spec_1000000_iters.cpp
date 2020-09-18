#include <rtamt/stl_specification.hpp>
#include <rtamt/stl_exception.hpp>

using namespace std;
using namespace rtamt;
using In = Input;

int main(int argc, char **argv) {
    StlSpecification spec;
    
    spec.declare_var("req", Type::FLOAT);
    spec.declare_var("gnt", Type::FLOAT);
    spec.declare_var("out", Type::FLOAT);
    
    spec.var_io_type("req", StlIOType::IN);
    spec.var_io_type("gnt", StlIOType::OUT);
    
    spec.semantics(StlSemantics::STANDARD);
    
    spec.spec("out = always((req >= 3) -> eventually[0:1000] (gnt >= 3))");
    
    spec.parse();
    
    double out;
    
    int i;
    
    for(i=0; i< 1000000; i++) {
        out = spec.update(10*i, {In("req", 0.0), In("gnt", 0.0)});
    }
    
    return 0;
}
