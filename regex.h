#include <vector>

namespace __CHRIS_REGEX {

enum class TokenType {
  character,
  unionbar,
  concatenate,
  star,
  lparen,
  rparen,
};

struct Token {
  static Token makeChar(char c) {
    return {
        .type = TokenType::character,
        .of = {.character = c},
    };
  }

  static Token make(TokenType type) {
    return {.type = type, .of = {.none = nullptr}};
  }

  TokenType type;
  union {
    char character;
    void *none;
  } of;
};

std::vector<Token> lex(const char *);

enum class ExprType {

};

struct Expr {
  ExprType type;
};

Expr parse(std::vector<Token>);

} // namespace __CHRIS_REGEX
