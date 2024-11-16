#ifndef CIARCPP_ERRORS_HPP
#define CIARCPP_ERRORS_HPP

#include <cpr/cpr.h>
#include <string>
#include <variant>

namespace ciarcpp {
namespace errors {

class ConnectionError {
  std::string m_message;
  uint32_t m_error_code;
  
public:
  ConnectionError(const std::string& msg, uint32_t error_code) : m_message(msg), m_error_code(error_code) {}

  const std::string& message() { return m_message; }
  uint32_t error_code() { return m_error_code; }
};

class JsonDeserializationError {
  std::string m_type_name;
  std::string m_json;
  uint32_t m_error_code;

public:
  JsonDeserializationError(const std::string& type_name, const std::string& json, uint32_t error_code) : m_type_name(type_name), m_json(json), m_error_code(error_code) {}
  const std::string& type_name() { return m_type_name; }
  const std::string& json() { return m_json; }
  uint32_t error_code() { return m_error_code; }
};

class JsonSerializationError {
  std::string m_type_name;
  uint32_t m_error_code;

public:
  JsonSerializationError(const std::string& type_name, uint32_t error_code) : m_type_name(type_name), m_error_code(error_code) {}
  const std::string& type_name() { return m_type_name; }
  uint32_t error_code() { return m_error_code; }
};

class UnhandledAPIError {
  int m_http_status_code;
  std::string m_response_text;
public:
  UnhandledAPIError(int http_status_code, const std::string& response_text) : m_http_status_code(http_status_code), m_response_text(response_text) {}
  const std::string& response_text() { return m_response_text; }
  int http_status_code() { return m_http_status_code; }
};

class GenericAPIErrorMessage {
  int m_http_status_code;
  std::string m_message;

public:
  GenericAPIErrorMessage(int http_status_code, const std::string& message) : m_http_status_code(http_status_code), m_message(message) {};
  const std::string& message() { return m_message; }
  int http_status_code() { return m_http_status_code; }
};

using ErrorsWithSerialization = std::variant<GenericAPIErrorMessage, UnhandledAPIError, JsonSerializationError, JsonDeserializationError, ConnectionError>;
using Errors = std::variant<GenericAPIErrorMessage, UnhandledAPIError, JsonDeserializationError, ConnectionError>;

}; // namespace errors
}; // namespace ciarcpp

#endif // !CIARCPP_ERRORS_HPP