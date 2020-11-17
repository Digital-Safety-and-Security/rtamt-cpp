#include <rtamt/stl_exception.hpp>
#include <rtamt/stl_specification.hpp>
#include <spec/stl_error_listener.hpp>
#include <spec/stl_evaluation.hpp>
#include <spec/stl_inner_specification.hpp>
#include <spec/stl_pastification.hpp>
#include <spec/stl_reset_monitor_state.hpp>
#include <spec/stl_specification_parser.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <antlr4-runtime.h>
#include <grammar/StlLexer.h>
#include <grammar/StlParser.h>
#include <grammar/StlParserVisitor.h>

using namespace spec;
using namespace rtamt;
using namespace node;
using namespace grammar;
using namespace antlr4;

StlInnerSpecification::~StlInnerSpecification() {
  delete _specRoot;
}

void StlInnerSpecification::name(const std::string& name) {
  if (_specification_locked) {
    throw StlInvalidOperationException("Specification is locked - new variables cannot be added.");
  }

  this->_name = name;
}

std::string StlInnerSpecification::name() {
  return this->_name;
}

void StlInnerSpecification::declare_var(const std::string& var_name, rtamt::Type type) {
  if (_specification_locked) {
    throw StlInvalidOperationException("Specification is locked - new variables cannot be added.");
  }

  if ((_vars.find(var_name) != _vars.end()) || (_var_type_map.find(var_name) != _var_type_map.end())) {
    std::stringstream ss("Variable ");
    ss << var_name << " already defined.\n";
    throw StlInvalidOperationException(ss.str());
  }

  _vars.insert(var_name);
  _var_type_map.insert(std::make_pair(var_name, type));
  _var_io_map.insert(std::make_pair(var_name, rtamt::StlIOType::DEFAULT));
}

void StlInnerSpecification::declare_const(const std::string& const_name, rtamt::Type type, std::string value) {
  if (_specification_locked) {
    throw StlInvalidOperationException("Specification is locked - new constant variables cannot be added.");
  }

  if ((_vars.find(const_name) != _vars.end()) || (_const_type_map.find(const_name) != _const_type_map.end())) {
    std::stringstream ss("Constant variable ");
    ss << const_name << " already defined.\n";
    throw StlInvalidOperationException(ss.str());
  }

  _vars.insert(const_name);
  _const_type_map.insert(std::make_pair(const_name, type));
  _const_val_map.insert(std::make_pair(const_name, value));
}

void StlInnerSpecification::const_type(const std::string& const_name, rtamt::Type type) {
  if (_specification_locked) {
    throw StlInvalidOperationException("Specification is locked - constant variable type cannot be changed.");
  }

  std::map<std::string, rtamt::Type>::iterator it = _const_type_map.find(const_name);
  if (it != _const_type_map.end()) {
    it->second = type;
  } else {
    std::stringstream ss("You cannot change the type of constant variable ");
    ss << const_name << " because it is not defined.\n";
    throw StlInvalidOperationException(ss.str());
  }
}

rtamt::Type StlInnerSpecification::const_type(const std::string& const_name) {
  return _const_type_map[const_name];
}

void StlInnerSpecification::const_value(const std::string& const_name, std::string value) {
  if (_specification_locked) {
    throw StlInvalidOperationException("Specification is locked - constant variable value cannot be changed.");
  }

  std::map<std::string, std::string>::iterator it = _const_val_map.find(const_name);
  if (it != _const_val_map.end()) {
    it->second = value;
  } else {
    std::stringstream ss("You cannot change the value of constant variable ");
    ss << const_name << " because it is not defined.\n";
    throw StlInvalidOperationException(ss.str());
  }
}

std::string StlInnerSpecification::const_value(const std::string& const_name) {
  return _const_val_map[const_name];
}

bool StlInnerSpecification::is_var(const std::string& name) {
  std::map<std::string, rtamt::Type>::iterator it = _var_type_map.find(name);
  if (it != _var_type_map.end()) {
    return true;
  } else {
    return false;
  }
}

bool StlInnerSpecification::is_const(const std::string& name) {
  std::map<std::string, rtamt::Type>::iterator it = _const_type_map.find(name);
  if (it != _const_type_map.end()) {
    return true;
  } else {
    return false;
  }
}

void StlInnerSpecification::var_type(const std::string& var_name, rtamt::Type type) {
  if (_specification_locked) {
    throw StlInvalidOperationException("Specification is locked - variable type cannot be changed.");
  }

  std::map<std::string, rtamt::Type>::iterator it = _var_type_map.find(var_name);
  if (it != _var_type_map.end()) {
    it->second = type;
  } else {
    std::stringstream ss("You cannot change the type of variable ");
    ss << var_name << " because it is not defined.\n";
    throw StlInvalidOperationException(ss.str());
  }
}

rtamt::Type StlInnerSpecification::var_type(const std::string& var_name) {
  return _var_type_map[var_name];
}

void StlInnerSpecification::var_io_type(const std::string& var_name, rtamt::StlIOType io_type) {
  if (_specification_locked) {
    throw StlInvalidOperationException("Specification is locked - variable I/O signature cannot be changed.");
  }

  std::map<std::string, rtamt::StlIOType>::iterator it = _var_io_map.find(var_name);
  if (it != _var_io_map.end()) {
    it->second = io_type;
  } else {
    std::stringstream ss("You cannot change the IO type of variable ");
    ss << var_name << " because it is not defined.\n";
    throw StlInvalidOperationException(ss.str());
  }
}

rtamt::StlIOType StlInnerSpecification::var_io_type(const std::string& var_name) {
  return _var_io_map[var_name];
}

void StlInnerSpecification::semantics(rtamt::StlSemantics semantics) {
  if (_specification_locked) {
    throw StlInvalidOperationException("Specification is locked - variable type cannot be changed.");
  }
  _semantics = semantics;
}

rtamt::StlSemantics StlInnerSpecification::semantics() {
  return _semantics;
}

void StlInnerSpecification::spec_from_file(const std::string& filename) {
  if (_specification_locked) {
    throw StlInvalidOperationException("Specification is locked - new specification cannot be opened from a file.");
  }

  std::ifstream f(filename);

  if (f) {
    std::stringstream ss;
    ss << f.rdbuf();
    _spec = ss.str();
    f.close();
  }
}

void StlInnerSpecification::parse() {
  if (_specification_locked) {
    throw StlInvalidOperationException("Cannot call parse() twice in a row.");
  }

  try {
    StlErrorListener listener;
    ANTLRInputStream antlrinput(_spec);
    StlLexer         lexer(&antlrinput);
    lexer.removeErrorListeners();
    lexer.addErrorListener(&listener);
    CommonTokenStream tokens(&lexer);
    StlParser         parser(&tokens);
    parser.removeErrorListeners();
    parser.addErrorListener(&listener);

    // This pointer is owned by StlParser
    // the tree is deleted by its desctructor
    StlParser::StlfileContext* tree = parser.stlfile();

    StlSpecificationParser specParser(this);

    specParser.visitStlfile(tree);
    std::unique_ptr<StlNode> sn(specParser.root());

    StlPastification pastification;
    StlNode*         pastify_output = pastification.pastify(sn.get());
    delete _specRoot;
    _specRoot = pastify_output;

    _eval = std::make_shared<StlEvaluation>(_specRoot, _vars, _var_io_map);

    _normalize            = static_cast<double>(u[_unit]) / static_cast<double>(u[_sampling_period_unit]);
    _specification_locked = true;
  } catch (const std::exception& e) {
    throw StlParseException(e.what());
  }
}

void StlInnerSpecification::reset() {
  StlResetMonitorState reset;
  _specRoot->accept(reset);
  _update_counter             = 0;
  _previous_time              = 0.0;
  _sampling_violation_counter = 0;
}

double StlInnerSpecification::update(double time, const std::vector<rtamt::Input>& inputs) {
  double out;

  if (_specRoot == nullptr || _eval == nullptr) {
    throw StlMonitorException("The specification monitor does not exist.");
  }

  if (_update_counter > 0) {
    double duration  = (time - _previous_time) * _normalize;
    double tolerance = _sampling_period * _sampling_tolerance;
    if (duration < (_sampling_period - tolerance) || duration > (_sampling_period + tolerance)) {
      _sampling_violation_counter++;
    }
  }

  out            = _eval->update(_update_counter, inputs);
  _previous_time = time;
  _update_counter++;

  return out;
}

void StlInnerSpecification::sampling_period(uint64_t period, rtamt::Unit unit) {
  if (_specification_locked) {
    throw StlInvalidOperationException("Specification is locked - sampling period cannot be changed.");
  }
  _sampling_period      = period;
  _sampling_period_unit = unit;
}

void StlInnerSpecification::sampling_period(uint64_t period, rtamt::Unit unit, double tolerance) {
  if (_specification_locked) {
    throw StlInvalidOperationException("Specification is locked - sampling period cannot be changed.");
  }
  sampling_period(period, unit);
  _sampling_tolerance = tolerance;
}

uint64_t StlInnerSpecification::sampling_period() {
  return _sampling_period * u[_sampling_period_unit];
}

void StlInnerSpecification::default_unit(rtamt::Unit unit) {
  if (_specification_locked) {
    throw StlInvalidOperationException("Specification is locked - default unit cannot be changed.");
  }

  _unit = unit;
}
