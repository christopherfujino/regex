#include "regex.h"
#include <stdexcept>

// Inductive operators
// Union R = S | T (lowest precedence)
// Concatenation R = S ⋅ T
// Closure R = S* (highest precedence)

Expr parse(std::vector<Token>) {
  throw std::runtime_error("TODO");
}
