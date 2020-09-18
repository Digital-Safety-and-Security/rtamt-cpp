#include <rtamt/stl_specification.hpp>
#include <rtamt/stl_exception.hpp>

using namespace std;
using namespace rtamt;
using In = Input;

int main(int argc, char **argv) {
    StlSpecification spec;
    spec.name("My Spec");
    
    spec.declare_var("req", Type::FLOAT);
    spec.declare_var("gnt", Type::FLOAT);
    spec.declare_var("out", Type::FLOAT);
 
    spec.var_io_type("req", StlIOType::IN);
    spec.var_io_type("gnt", StlIOType::OUT); 
 
    spec.default_unit(Unit::MS);
    spec.sampling_period(10, Unit::MS, 0.1);
  
    spec.semantics(StlSemantics::STANDARD);
  
    spec.spec("out = (eventually[0:10ms](gnt >= 3))");
    
    spec.parse();
    
    double out;
    out = spec.update(0, {Input("req", 0.0), Input("gnt", 2.18)});
    out = spec.update(0, {Input("req", 1.1), Input("gnt", 3.43)});
    
    return 0;
}
