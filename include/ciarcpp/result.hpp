#ifndef CIARCPP_RESULT_HPP
#define CIARCPP_RESULT_HPP

#include <variant>

namespace ciarcpp {

template <typename T, typename E>
class Result {
  static_assert(not std::is_same_v<T, E>);
  std::variant<T, E> m_value;

public:
  Result(Result&& other) = default;
  Result(T&& result) : m_value(std::forward(result)) {}
  Result(E&& error) : m_value(std::forward(error)) {}
  Result(const T& result) : m_value(result) {}
  Result(const E& error) : m_value(error) {}
  Result& operator=(const Result& other) = default;
  Result& operator=(Result&& other) = default;

  operator bool() const { return ok(); }
  bool ok() const { return std::holds_alternative<T>(m_value); }
  const T& result() const { return std::get<T>(m_value); }
  const E& error() const { return std::get<E>(m_value); }
};

}; // namespace ciarcpp

#endif // !CIARCPP_RESULT_HPP