#include <vector>

enum class TokenType {
  character,
  unionbar,
  concatenate,
  star,
  lparen,
  rparen,
};

struct Token {
  TokenType type;
  union {
    char character;
  } of;
};

std::vector<Token> lex(const char *);

enum class ExprType {

};

struct Expr {
  ExprType type;
};

Expr parse(std::vector<Token>);
