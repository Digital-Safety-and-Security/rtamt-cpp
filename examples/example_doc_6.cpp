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
    
    spec.sampling_period(1, Unit::S, 0.2);
    
    spec.spec("out = (req >= 3) -> (eventually[0:5](gnt >= 3))");
    
    spec.parse();
    
    double out;

    
    out = spec.update(0, {In("req", 0.0), In("gnt", 0.0)}); // out = inf
    cout << "Time: " << "0s, Robustness: " << out << "\n";

    out = spec.update(1.11, {In("req", 0.0), In("gnt", 0.0)}); // out = inf
    cout << "Time: " << "1.11s, Robustness: " << out << "\n";
    
    out = spec.update(2.08, {In("req", 0.0), In("gnt", 0.0)}); // out = inf
    cout << "Time: " << "2.08s, Robustness: " << out << "\n";
    
    out = spec.update(3.03, {In("req", 6.0), In("gnt", 0.0)}); // out = inf
    cout << "Time: " << "3.03s, Robustness: " << out << "\n";
    
    out = spec.update(4.01, {In("req", 6.0), In("gnt", 0.0)}); // out = inf
    cout << "Time: " << "4.01s, Robustness: " << out << "\n";
    
    out = spec.update(4.99, {In("req", 0.0), In("gnt", 0.0)}); // out = 3
    cout << "Time: " << "4.99s, Robustness: " << out << "\n";
    
    out = spec.update(6.01, {In("req", 0.0), In("gnt", 0.0)}); // out = 3
    cout << "Time: " << "6.01s, Robustness: " << out << "\n";

    double nb_violations = spec.sampling_violation_counter(); // nb_violations = 0
    cout << "NB. of violations: " << nb_violations << "\n";

    
    return 0;
}
