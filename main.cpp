#include <stdio.h>
#include <vector>

// Inductive operators
// Union R = S | T (lowest precedence)
// Concatenation R = S ⋅ T
// Closure R = S* (highest precedence)

/// Sample program alpha
const char alpha[] = "(a|b)*c";

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

void debugToken(const Token &token) {
  using enum TokenType;

  switch (token.type) {
  case character:
    printf("character (%c)\n", token.of.character);
    break;
  case unionbar:
    printf("unionbar\n");
    break;
  case concatenate:
    printf("concatenate\n");
    break;
  case star:
    printf("star\n");
    break;
  case lparen:
    printf("lparen\n");
    break;
  case rparen:
    printf("rparen\n");
    break;
  }
}

struct Expr {};

std::vector<Token> lex(const char *);

Expr parse(std::vector<Token>);

int main() {
  auto tokens = lex(alpha);
  for (const auto &token : tokens) {
    debugToken(token);
  }
}

std::vector<Token> lex(const char *program) {
  using enum TokenType;

  // This value won't be used, but just so we don't insert a leading concatenate...
  Token previousToken = Token{.type = concatenate};
  std::vector<Token> tokens = {};
  char c;
  for (int i = 0; (c = program[i]) != '\0';) {
    // Should we scan implicit concat?
    if (previousToken.type != lparen && previousToken.type != unionbar && previousToken.type != concatenate) {
      if (c != ')' && c != '|' && c != '*') {
        previousToken = Token{.type = concatenate};
        tokens.push_back(previousToken);
        continue;
      }
    }
    if (c == '(') {
      previousToken = Token{.type = lparen};
      tokens.push_back(previousToken);
    } else if (c == ')') {
      previousToken = Token{.type = rparen};
      tokens.push_back(previousToken);
    } else if (c == '|') {
      previousToken = Token{.type = unionbar};
      tokens.push_back(previousToken);
    } else if (c == '*') {
      previousToken = Token{.type = star};
      tokens.push_back(previousToken);
    } else { // TODO
      previousToken = Token{.type = character, .of = {c}};
      tokens.push_back(previousToken);
    }
    i += 1;
  }

  // TODO: can this be a move?
  return tokens;
}
