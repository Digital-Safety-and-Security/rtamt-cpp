#include <rtamt/stl_exception.hpp>

#include "antlr4-runtime.h"

#ifndef STL_ERROR_LISTENER_HPP
#define STL_ERROR_LISTENER_HPP

namespace spec {

class StlErrorListener : public antlr4::BaseErrorListener {
  void syntaxError(antlr4::Recognizer* /*recognizer*/, antlr4::Token* /*offendingSymbol*/, size_t /*line*/,
                   size_t /*charPositionInLine*/, const std::string& /*msg*/, std::exception_ptr /*e*/) override {
    throw rtamt::StlParseException("ANTLR4 parse error");
  }
};
} // namespace spec

#endif // STL_ERROR_LISTENER_HPP
