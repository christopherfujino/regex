#include "regex.h"
#include <stdexcept>

// Inductive operators
// Union R = S | T (lowest precedence)
// Concatenation R = S ⋅ T
// Closure R = S* (highest precedence)

namespace __CHRIS_REGEX {

Expr parse(std::vector<Token>) {
  throw std::runtime_error("TODO");
}

} // namespace __CHRIS_REGEX
