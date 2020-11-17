#ifndef STL_INNER_SPECIFICATION_H
#define STL_INNER_SPECIFICATION_H

#include "stl_evaluation.hpp"

#include <node/stl_node.hpp>
#include <rtamt/stl_specification.hpp>
#include <spec/stl_evaluation.hpp>

#include <cstdint>
#include <iostream>
#include <map>
#include <set>
#include <string>


namespace spec {

class StlInnerSpecification {
private:
  const uint64_t s_unit  = 1000000000;
  const uint64_t ms_unit = 1000000;
  const uint64_t us_unit = 1000;
  const uint64_t ns_unit = 1;

  const double default_tolerance = 0.1;

  std::map<rtamt::Unit, uint64_t> u{std::make_pair(rtamt::Unit::S, s_unit), std::make_pair(rtamt::Unit::MS, ms_unit),
                                    std::make_pair(rtamt::Unit::US, us_unit), std::make_pair(rtamt::Unit::NS, ns_unit)};

  /**
   * The name of the specification.
   */
  std::string _name{"STL Specification"};

  /**
   * Loaded spec content either from a file or directly.
   */
  std::string _spec;

  /**
   * Parsed variables
   */
  std::set<std::string> _vars;

  /**
   * Name of the output variable.
   */
  std::string _rob_var;

  /**
   * Size opf the sampling period in ns
   */
  uint64_t    _sampling_period{1};
  rtamt::Unit _sampling_period_unit{rtamt::Unit::S};

  double _sampling_tolerance{default_tolerance};

  rtamt::Unit _unit{rtamt::Unit::S};

  /**
   * Map var names to var types
   *
   */
  std::map<std::string, rtamt::Type> _var_type_map;

  /**
   * Map var names to var io signature     *
   */
  std::map<std::string, rtamt::StlIOType> _var_io_map;

  /**
   * Map const var names to var types
   *
   */
  std::map<std::string, rtamt::Type> _const_type_map;

  /**
   * Map const names to values
   *
   */
  std::map<std::string, std::string> _const_val_map;


  /**
   * STL semantics     *
   */
  rtamt::StlSemantics _semantics{rtamt::StlSemantics::STANDARD};

  /**
   * Root node of the tree which represents the parsed specification.     *
   */
  node::StlNode* _specRoot{nullptr};

  double _normalize{1.0};

  uint64_t _update_counter{0};
  double   _previous_time{0.0};
  double   _sampling_violation_counter{0};
  bool     _specification_locked{false};

  std::shared_ptr<spec::StlEvaluation> _eval{nullptr};

public:
  StlInnerSpecification() = default;
  virtual ~StlInnerSpecification();
  StlInnerSpecification(const StlInnerSpecification&) = delete;
  StlInnerSpecification(StlInnerSpecification&&)      = delete;
  StlInnerSpecification& operator=(const StlInnerSpecification&) = delete;
  StlInnerSpecification& operator=(StlInnerSpecification&&) = delete;

  //--------------- GETTERS & SETTERS ------------//

  /**
   * @brief set STL specificiation name
   *
   * @param name
   */
  void name(const std::string& name);
  /**
   * @brief get STL specification name
   *
   * @return std::string
   */
  std::string name();

  /**
   * @brief declare a new typed variable
   *
   * @param var_name
   * @param type 
   */
  void declare_var(const std::string& var_name, rtamt::Type type);
  
  /**
   * @brief declare a new typed constant
   *
   * @param const_name
   * @param type 
   * @param value
   */
  void declare_const(const std::string& var_name, rtamt::Type type, std::string value);
  
  /**
   * @brief set the type of an already declared constant
   *
   * @param const_name
   * @param type 
   */
  void const_type(const std::string& const_name, rtamt::Type type);

  /**
   * @brief get the type of a constant variable
   *
   * @param const_name
   * @return constant variable type as a type enum
   */
  rtamt::Type const_type(const std::string& const_name);
  
  /**
   * @brief set the value of an already declared constant
   *
   * @param const_name
   * @param value
   */
  void const_value(const std::string& const_name, std::string value);

  /**
   * @brief get the value of a constant variable
   *
   * @param const_name
   * @return constant variable value (string)
   */
  std::string const_value(const std::string& const_name);

  /**
   * @brief set the type of an already declared variable
   *
   * @param var_name
   * @param type (string "float", "int" or "long")
   */
  void var_type(const std::string& var_name, rtamt::Type type);

  /**
   * @brief get the type of a variable
   *
   * @param var_name
   * @return variable type as a string
   */
  rtamt::Type var_type(const std::string& var_name);
  
  /**
   * @brief checks if name is a variable
   *
   * @param name
   * @return true if name is a variable
   */
  bool is_var(const std::string& name);
  
  /**
   * @brief checks if name is a constant
   *
   * @param name
   * @return true if name is a constant
   */
  bool is_const(const std::string& name);
  

  /**
   * @brief set the input/output type (signature) of a variable
   *
   * @param var_name
   * @param io_type
   */
  void var_io_type(const std::string& var_name, rtamt::StlIOType io_type);

  /**
   * @brief get the input/output type (signature) of a variable
   *
   * @param var_name
   * @return spec::StlIOType
   */
  rtamt::StlIOType var_io_type(const std::string& var_name);

  /**
   * @brief set STL semantics
   *
   * @param semantics standard, input vacuity, input robustness, output vacuity, output robustness
   */
  void semantics(rtamt::StlSemantics semantics);

  //------------------- METHODS ----------------//

  /**
   * @brief get STL semantics
   *
   * @return spec::StlSemantics
   */
  rtamt::StlSemantics semantics();

  /**
   * @brief Set the robustness variable
   *
   * @param rob_var robustness variable
   */
  void rob_var(std::string rob_var) { _rob_var = std::move(rob_var); }

  /**
   * @brief Get the robstness variable
   *
   * @return std::::string
   */
  std::string rob_var() { return _rob_var; }

  /**
   * @brief load STL specification from file
   *
   * @param filename
   */
  void spec_from_file(const std::string& filename);

  void spec(const std::string& spec) { _spec = spec; }

  std::string spec() { return _spec; }

  void     sampling_period(uint64_t period, rtamt::Unit unit);
  void     sampling_period(uint64_t period, rtamt::Unit unit, double tolerance);
  uint64_t sampling_period();
  double   sampling_tolerance() { return _sampling_tolerance; }

  void default_unit(rtamt::Unit unit);

  rtamt::Unit default_unit() { return _unit; }

  uint64_t sampling_violation_counter() { return _sampling_violation_counter; }

  /**
   * @brief parse STL specification and create STL monitor
   *
   */
  void parse();

  /**
   * @brief evaluate and update STL specification monitor at a specification time with specific inputs
   *
   * @param time
   * @param inputs list of inputs
   * @return double - robustness degree
   */
  double update(double time, const std::vector<rtamt::Input>& inputs);

  /**
   * @brief reset the STL specification monitor
   *
   */
  void reset();
};

} // namespace spec

#endif /* STL_INNER_SPECIFICATION_H */
