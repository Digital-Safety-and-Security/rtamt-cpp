#ifndef STL_SPECIFICATION_H
#define STL_SPECIFICATION_H

#include <memory>
#include <string>
#include <vector>

namespace spec {
class StlInnerSpecification;
}

namespace rtamt {

/**
 * @brief enumeration class for time units:
 * S - seconds
 * MS - milliseconds
 * US - microseconds
 * NS - nanoseconds
 *
 */
enum class Unit { S, MS, US, NS };

/**
 * @brief enumeration class for variable type
 * FLOAT - floating point variable
 *
 */
enum class Type { FLOAT };

/**
 * @brief enumeration class for variable input/output signature
 * IN - input variable
 * OUT - output variable
 * DEFAULT - default neutral variable (neither input nor output)
 *
 */
enum class StlIOType { IN, OUT, DEFAULT };

/**
 * @brief Type of interface-aware STL semantics:
 * STANDARD - classical infinity-norm semantics
 * OUT_ROBUSTNESS - measures the robustness of the system to outputs only
 * IN_VACUITY - measure whether and by how much is the specification vacuously satisfied by its inputs
 * IN_ROBUSTNESS - measures the robustness of the system to inputs only
 * OUT_VACUITY - measure whether and by how much is the specification vacuously satisfied by its outputs
 */
enum class StlSemantics { STANDARD, OUT_ROBUSTNESS, IN_ROBUSTNESS, OUT_VACUITY, IN_VACUITY };

/**
 * @brief data structure for passing new inputs to the monitor.
 * Consists of the variable name and its associated value.
 *
 */
struct Input {
  std::string name;
  double      value;
  Input(const std::string& name, double value) {
    this->name  = name;
    this->value = value;
  }
};

/**
 * @brief Class that provides API to declaring a bounded-future
 * interface-aware Signal Temporal Logic (STL) specification,
 * automatically generating an online monitor from the specification
 * and evaluating the quantitative robustness degree of a real-valued
 * behavior wrt the specification.
 *
 * Example:
 * StlSpecification spec;
 *
 * spec.name("My Spec");
 *
 * spec.declare_var("req", Type::FLOAT);
 * spec.declare_var("gnt", Type::FLOAT);
 * spec.declare_var("out", Type::FLOAT);
 *
 * spec.var_io_type("req", StlIOType::IN);
 * spec.var_io_type("gnt", StlIOType::OUT);
 *
 * spec.default_unit(Unit::MS);
 * spec.sampling_period(10, Unit::MS, 0.1);
 *
 * spec.semantics(StlSemantics::STANDARD);
 *
 * spec.spec("out = (eventually[0:10ms](gnt >= 3))");
 *
 * spec.parse();
 *
 * double out;
 * out = spec.update(0, {Input("req", 0.0), Input("gnt", 2.18)});
 * out = spec.update(0, {Input("req", 1.1), Input("gnt", 3.43)});
 * ...
 *
 * Notes:
 * The following functions from the examples are optional:
 * - name (default specification name: "STL Specification")
 * - var_io_type (default variable IO type: StlIOType::DEFAULT)
 * - default_unit (default default unit: Unit::S)
 * - sampling_period (default sampling period: 1s, tolerance:10%)
 * - semantics (default semantics: StlSemantics::STANDARD)
 *
 */
class StlSpecification {
private:
  /**
   * @brief Pointer to the object that contains the specification data structures and the monitor.
   *
   */
  std::shared_ptr<spec::StlInnerSpecification> _spec;

public:
  StlSpecification();

  /**
   * @brief sets STL specificiation name. Setting the name is intended to
   * facilitate tracing formal STL specifications to the requirements.
   *
   * @throw StlInvalidOperationException - when the function is called after parse()
   *
   * @param name
   */
  void name(const std::string& name);

  /**
   * @brief gets STL specification name
   *
   * @return std::string
   */
  std::string name();

  /**
   * @brief sets STL specificiation (temporal property) as string.
   * The valid specifications are defined by the STL grammar.
   *
   * Examples:
   * StlSpecification spec;
   * spec.spec("out = always(p>=2 and q <=3.33)");
   * spec.spec("out = eventually[0:20ms](p>=2.3)");
   *
   * @throw StlInvalidOperationException - when the function is called after parse()
   *
   * @param spec
   */
  void spec(const std::string& spec);

  /**
   * @brief gets STL specification (temporal property) as text.
   *
   * @return std::string
   */
  std::string spec();

  /**
   * @brief declares a new typed variable. In this version,
   * the only supported type is Type::FLOAT.
   *
   * @param var_name
   * @param type (enum Type)
   */
  void declare_var(const std::string& var_name, Type type);

  /**
   * @brief declares a new typed constant variable. In this version,
   * the only supported type is Type::FLOAT.
   *
   * @param const_name
   * @param type (enum Type)
   * @param value (double)
   */
  void declare_const(const std::string& const_name, Type type, double value);
  
  /**
   * @brief sets the type of an already declared variable
   *
   * @throw StlInvalidOperationException - when the function is called after parse()
   *
   * @param var_name
   * @param type (enum Type)
   */
  void var_type(const std::string& var_name, Type type);

  /**
   * @brief gets the type of a variable
   *
   * @param var_name
   * @return Type
   */
  Type var_type(const std::string& var_name);

  /**
   * @brief sets the input/output type (signature) of a variable.
   *
   * @throw StlInvalidOperationException - when the function is called after parse()
   *
   * @param var_name
   * @param io_type
   */
  void var_io_type(const std::string& var_name, StlIOType io_type);

  /**
   * @brief gets the input/output type (signature) of a variable
   *
   * @param var_name
   * @return StlIOType
   */
  StlIOType var_io_type(const std::string& var_name);

  /**
   * @brief sets STL semantics
   *
   * @throw StlInvalidOperationException - when the function is called after parse()
   *
   * @param semantics (standard, input vacuity, input robustness, output vacuity, output robustness)
   */
  void semantics(StlSemantics semantics);

  /**
   * @brief gets STL semantics
   *
   * @return spec::StlSemantics
   */
  StlSemantics semantics();

  /**
   * @brief sets the default time unit of the Specification used for:
   * (1) input timestamps,
   * (2) timing bounds of STL temporal operators, and
   * (3) sampling periods
   *
   * @throw StlInvalidOperationException - when the function is called after parse()
   *
   * @param unit
   */
  void default_unit(Unit unit);
  /**
   * @brief gets the default time unit of the STL specification.
   *
   * @return rtamt::Unit
   */
  Unit default_unit();

  /**
   * @brief sets the duration of the expected sampling period of inputs. It
   * implicitely also sets the allowed tolerance of the specified sampling period to
   * +/- 10% of the sampling period.
   *
   * @throw StlInvalidOperationException - when the function is called after parse()
   *
   * @param period
   * @param unit
   */
  void sampling_period(uint64_t period, Unit unit);
  /**
   * @brief sets the duration of the expected sampling period of inputs with
   * the allowed tolerance. The tolerance is expected to be in the interval
   * [0,1] with 0 representing 0% and 1 representing 100% of the
   * sampling period value.
   *
   * @throw StlInvalidOperationException - when the function is called after parse()
   *
   * @param period
   * @param unit
   * @param tolerance
   */
  void sampling_period(uint64_t period, Unit unit, double tolerance);

  /**
   * @brief gets the sampling period in ns.
   *
   * @return uint64_t
   */
  uint64_t sampling_period();
  /**
   * @brief gets the allowed sampling tolerance.
   *
   * @return double
   */
  double sampling_tolerance();

  /**
   * @brief counts the number that the sampling period assumption has been violated so far.
   * It is expected that the duration between every two consecutive input timestamps is
   * within the interval [sampling period - (sampling period * tolerance), sampling period + (sampling period *
   * tolerance)]. Each time this is not the case, the counter is incremented by one. The counter is reset to 0 when
   * reset() is called.
   *
   * @return uint64_t
   */
  uint64_t sampling_violation_counter();

  /**
   * @brief loads STL specification text from file
   *
   * @throw StlInvalidOperationException - when the function is called after parse() or when there is
   * a problem with reading the file specified by the filename.
   *
   * @param filename
   */
  void spec_from_file(const std::string& filename);

  /**
   * @brief parses the STL specification and automatically
   * generates an STL online monitor.
   *
   * @throw StlParseException - when there is a parse problem.
   *
   */
  void parse();

  /**
   * @brief evaluates and updates STL specification monitor at a specific time with specific inputs.
   * 
   * The update function assumes that the user provides inputs for exactly the variables declare in the specification. If the list of inputs:
   * - contains a variable name that is not declared in the specification, StlMonitorException is thrown
   * - repeats twice or more times the same variable name, the last value is used
   * - misses to provide an input for a variable declared in the specification, the value from the previous evaluation step is used
   * 
   *
   * @throw StlMonitorException - when there is a problem with the vector of inputs.
   *
   * @param time
   * @param inputs list of inputs
   * @return double - robustness degree
   */
  double update(double time, const std::vector<Input>& inputs);

  /**
   * @brief resets the internal state of the STL specification monitor.
   * It does not undo the parse of the specification.
   *
   */
  void reset();
};

} // namespace rtamt

#endif /* STL_SPECIFICATION_H */
