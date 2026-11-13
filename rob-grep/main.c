#include <stdio.h>  // fprintf(), stderr
#include <stdlib.h> // abort()
#include <string.h> // memcpy()

bool match(char *regexp, char *text);
bool matchhere(char *regexp, char *text);
bool matchstar(int c, char *regexp, char *text);

/* match: search for regexp anywhere in text */
bool match(char *regexp, char *text) {
  if (regexp[0] == '^')
    return matchhere(regexp + 1, text);
  do { /* must look even if string is empty */
    if (matchhere(regexp, text))
      return true;
  } while (*text++ != '\0');
  return false;
}

/* matchhere: search for regexp at beginning of text */
bool matchhere(char *regexp, char *text) {
  if (regexp[0] == '\0')
    return true;
  if (regexp[1] == '*')
    return matchstar(regexp[0], regexp + 2, text);
  if (regexp[0] == '$' && regexp[1] == '\0')
    return *text == '\0';
  if (*text != '\0' && (regexp[0] == '.' || regexp[0] == *text))
    return matchhere(regexp + 1, text + 1);
  return false;
}

/* matchstar: search for c*regexp at beginning of text */
bool matchstar(int c, char *regexp, char *text) {
  do { /* a * matches zero or more instances */
    if (matchhere(regexp, text))
      return true;
  } while (*text != '\0' && (*text++ == c || c == '.'));
  return false;
}

typedef struct Buffer {
  // char buffer[BUFSIZ];
  char buffer[1];
  struct Buffer *next;
  size_t len;
} Buffer;

// TODO: this can be cleaned up with `realloc()` and a single buffer
char *read_stdin() {
  Buffer *initial = calloc(1, sizeof(Buffer));
  Buffer *current = initial;
  *current = (Buffer){
      .buffer = {},
      .next = nullptr,
      .len = 0,
  };
  size_t string_len = 0;

  while (1) {
    size_t n =
        fread(current->buffer, sizeof(char), sizeof(current->buffer), stdin);
    if (n < sizeof(current->buffer)) {
      if (ferror(stdin)) {
        fprintf(stderr, "fread(stdin) failed!\n");
        abort();
      }
      current->len = n;
      string_len += n + 1;
      break;
    }
    string_len += n + 1;
    current->len = n;
    current->next = calloc(1, sizeof(Buffer));
    *(current->next) = (Buffer){
        .buffer = {},
        .next = nullptr,
        .len = 0,
    };
    current = current->next;
  }

  char *str_init = calloc(1, string_len);
  char *str_cur = str_init;
  Buffer *to_free = nullptr;
  for (current = initial; current != nullptr; current = current->next) {
    free(to_free);
    memcpy(str_cur, current->buffer, current->len);
    str_cur += current->len;
    to_free = current;
  }
  free(to_free);

  return str_init;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: grep PATTERN\n");
    return 1;
  }
  {
    char *const input = read_stdin();
    bool result = match(argv[1], input);
    printf("result = %d\n", result);
    free((void *)input);
  }
}
