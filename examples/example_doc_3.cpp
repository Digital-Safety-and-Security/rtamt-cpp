#include <rtamt/stl_specification.hpp>
#include <rtamt/stl_exception.hpp>

using namespace std;
using namespace rtamt;
using In = Input;

int main(int argc, char **argv) {
    StlSpecification spec;

    spec.name("Bounded-response Request-Grant");
    
    spec.declare_var("req", Type::FLOAT);
    spec.declare_var("gnt", Type::FLOAT);
    spec.declare_var("out", Type::FLOAT);
    
    spec.var_io_type("req", StlIOType::IN);
    spec.var_io_type("gnt", StlIOType::OUT);
    
    spec.semantics(StlSemantics::STANDARD);
    
    spec.spec("out = (req >= 3) -> (eventually[0:5](gnt >= 3))");
    
    spec.parse();
    
    double out;
    
    out = spec.update(0, {In("req", 0.0), In("gnt", 0.0)}); // out = inf
    cout << "Time: " << "0s, Robustness: " << out << "\n";

    out = spec.update(1, {In("req", 0.0), In("gnt", 0.0)}); // out = inf
    cout << "Time: " << "1s, Robustness: " << out << "\n";
    
    out = spec.update(2, {In("req", 0.0), In("gnt", 0.0)}); // out = inf
    cout << "Time: " << "2s, Robustness: " << out << "\n";
    
    out = spec.update(3, {In("req", 6.0), In("gnt", 0.0)}); // out = inf
    cout << "Time: " << "3s, Robustness: " << out << "\n";
    
    out = spec.update(4, {In("req", 6.0), In("gnt", 0.0)}); // out = inf
    cout << "Time: " << "4s, Robustness: " << out << "\n";
    
    out = spec.update(5, {In("req", 0.0), In("gnt", 0.0)}); // out = 3
    cout << "Time: " << "5s, Robustness: " << out << "\n";
    
    out = spec.update(6, {In("req", 0.0), In("gnt", 0.0)}); // out = 3
    cout << "Time: " << "6s, Robustness: " << out << "\n";

    double nb_violations = spec.sampling_violation_counter(); // nb_violations = 0
    cout << "NB. of violations: " << nb_violations << "\n";

    
    return 0;
}
