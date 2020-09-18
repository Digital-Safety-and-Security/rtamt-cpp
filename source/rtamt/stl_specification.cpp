#include <rtamt/stl_exception.hpp>
#include <rtamt/stl_specification.hpp>
#include <spec/stl_inner_specification.hpp>
#include <spec/stl_specification_parser.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <antlr4-runtime.h>
#include <grammar/StlLexer.h>
#include <grammar/StlParser.h>
#include <grammar/StlParserVisitor.h>

using namespace std;
using namespace spec;
using namespace grammar;
using namespace antlr4;
using namespace rtamt;

StlSpecification::StlSpecification() : _spec(std::make_shared<StlInnerSpecification>()) {}

void rtamt::StlSpecification::name(const std::string& name) {
  _spec->name(name);
}

std::string StlSpecification::name() {
  return _spec->name();
}

void rtamt::StlSpecification::spec(const std::string& spec) {
  _spec->spec(spec);
}

std::string StlSpecification::spec() {
  return _spec->spec();
}

void StlSpecification::declare_var(const std::string& var_name, Type type) {
  _spec->declare_var(var_name, type);
}

void StlSpecification::var_type(const std::string& var_name, Type type) {
  _spec->var_type(var_name, type);
}

Type StlSpecification::var_type(const std::string& var_name) {
  return _spec->var_type(var_name);
}

void StlSpecification::var_io_type(const std::string& var_name, StlIOType io_type) {
  _spec->var_io_type(var_name, io_type);
}

rtamt::StlIOType StlSpecification::var_io_type(const std::string& var_name) {
  return _spec->var_io_type(var_name);
}

void StlSpecification::semantics(StlSemantics semantics) {
  return _spec->semantics(semantics);
}

StlSemantics StlSpecification::semantics() {
  return _spec->semantics();
}

void StlSpecification::spec_from_file(const std::string& filename) {
  _spec->spec_from_file(filename);
}

void StlSpecification::parse() {
  _spec->parse();
}

double StlSpecification::update(double time, const std::vector<Input>& inputs) {
  return _spec->update(time, inputs);
}

void StlSpecification::reset() {
  _spec->reset();
}

void StlSpecification::sampling_period(uint64_t period, Unit unit) {
  _spec->sampling_period(period, unit);
}

void StlSpecification::sampling_period(uint64_t period, Unit unit, double tolerance) {
  if (tolerance < 0.0 || tolerance > 1.0) {
    throw StlSpecificationException("Tolerance must be between 0 (0%) and 1 (100%)");
  }
  _spec->sampling_period(period, unit, tolerance);
}

uint64_t StlSpecification::sampling_period() {
  return _spec->sampling_period();
}

double StlSpecification::sampling_tolerance() {
  return _spec->sampling_tolerance();
}

uint64_t StlSpecification::sampling_violation_counter() {
  return _spec->sampling_violation_counter();
}

void StlSpecification::default_unit(Unit unit) {
  _spec->default_unit(unit);
}

Unit StlSpecification::default_unit() {
  return _spec->default_unit();
}
