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
    
    spec.default_unit(Unit::MS);
    spec.sampling_period(10, Unit::MS, 0.1);
    
    spec.semantics(StlSemantics::STANDARD);
    
    spec.spec("out = always((req >= 3) -> (gnt >= 3))");
    
    spec.parse();
    
    double out;
    
    int i;
    
    for(i=0; i< 100000; i++) {
        out = spec.update(10*i, {In("req", 0.0), In("gnt", 0.0)});
    }
    
    return 0;
}
