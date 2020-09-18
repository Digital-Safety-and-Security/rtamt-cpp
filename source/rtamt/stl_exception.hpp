#include <exception>
#include <iostream>
#include <string>

#ifndef STL_EXCEPTION_HPP
#define STL_EXCEPTION_HPP

namespace rtamt {

/**
 * @brief Generic exception class for RTAMT-CPP library.
 *
 */
class StlException : public std::exception {
private:
  std::string _message;

public:
  explicit StlException(const std::string& message) { _message = message; }

  const char* what() const noexcept override { return _message.c_str(); }
};

/**
 * @brief Class for specification-related exceptions.
 *
 */

class StlSpecificationException : public StlException {
public:
  explicit StlSpecificationException(const std::string& var_name) : StlException(var_name) {}
};

/**
 * @brief Class for exceptions encountered during parsing of STL specifications.
 *
 */
class StlParseException : public StlException {
public:
  explicit StlParseException(const std::string& var_name) : StlException(var_name) {}
};

/**
 * @brief Class for exceptions encountered during monitoring of STL specifications.
 *
 */
class StlMonitorException : public StlException {
public:
  explicit StlMonitorException(const std::string& var_name) : StlException(var_name) {}
};

/**
 * @brief Class for exceptions encountered in STL nodes.
 *
 */
class StlNodeException : public StlException {
public:
  explicit StlNodeException(const std::string& var_name) : StlException(var_name) {}
};

/**
 * @brief Class for exceptions related to invalid operation calls in the library.
 *
 */
class StlInvalidOperationException : public StlException {
public:
  explicit StlInvalidOperationException(const std::string& var_name) : StlException(var_name) {}
};

} // namespace rtamt

#endif // STL_EXCEPTION_HPP
