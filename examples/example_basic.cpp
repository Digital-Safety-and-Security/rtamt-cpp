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
    
    spec.spec("out = (eventually[0:10](gnt >= 3))");
    
    spec.parse();
    
    double out;
    
    out = spec.update(0, {In("req", 0.0), In("gnt", 0.0)});
    cout << "Time: 0ms, Robustness: " << out << "\n"; 
    
    out = spec.update(10, {In("req", 0.0), In("gnt", 0.0)});
    cout << "Time: 10ms, Robustness: " << out << "\n"; 
    
    out = spec.update(20, {In("req", 0.0), In("gnt", 0.0)});
    cout << "Time: 20ms, Robustness: " << out << "\n"; 
    
    out = spec.update(30, {In("req", 6.0), In("gnt", 0.0)});
    cout << "Time: 30ms, Robustness: " << out << "\n"; 
    
    out = spec.update(40, {In("req", 6.0), In("gnt", 0.0)});
    cout << "Time: 40ms, Robustness: " << out << "\n"; 
    
    out = spec.update(50, {In("req", 0.0), In("gnt", 0.0)});
    cout << "Time: 50ms, Robustness: " << out << "\n"; 
    
    out = spec.update(60, {In("req", 0.0), In("gnt", 0.0)});
    cout << "Time: 60ms, Robustness: " << out << "\n"; 
    
    out = spec.update(70, {In("req", 0.0), In("gnt", 6.0)});
    cout << "Time: 70ms, Robustness: " << out << "\n"; 
    
    out = spec.update(80, {In("req", 0.0), In("gnt", 6.0)});
    cout << "Time: 80ms, Robustness: " << out << "\n"; 
    
    out = spec.update(90, {In("req", 0.0), In("gnt", 0.0)});
    cout << "Time: 90ms, Robustness: " << out << "\n"; 
    
    out = spec.update(100, {In("req", 0.0), In("gnt", 0.0)});
    cout << "Time: 100ms, Robustness: " << out << "\n"; 
    
    out = spec.update(110, {In("req", 0.0), In("gnt", 0.0)});
    cout << "Time: 110ms, Robustness: " << out << "\n"; 
    
    return 0;
}
