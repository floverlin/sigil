#include "lexer.h"

#include <stdio.h>
#include <string.h>

#include "common.h"

typedef struct {
    const char *start;
    const char *current;
    int line;
} Lexer;

Lexer lexer;

static Token makeToken(TokenType type) {
    Token t;
    t.type = type;
    t.start = lexer.start;
    t.length = (int)(lexer.current - lexer.start);
    t.line = lexer.line;
    return t;
}

static Token errorToken(const char *message) {
    Token t;
    t.type = TOKEN_ERROR;
    t.start = message;
    t.length = strlen(message);
    t.line = lexer.line;
    return t;
}

static bool isAtEnd() { return *lexer.current == '\0'; }

static char advance() {
    lexer.current++;
    return lexer.current[-1];
}

static bool isDigit(char target) { return '0' <= target && target <= '9'; }

static bool isAlpha(char target) {
    return ('a' <= target && target <= 'z') ||
           ('A' <= target && target <= 'Z') || target == '_';
}

static bool match(char expected) {
    if (isAtEnd()) {
        return false;
    }
    if (*lexer.current == expected) {
        lexer.current++;
        return true;
    }
    return false;
}

static char peek() { return *lexer.current; }

static char peekNext() {
    if (isAtEnd()) {
        return '\0';
    }

    return lexer.current[1];
}

static void skipWhitespace() {
    for (;;) {
        char c = peek();
        switch (c) {
            case '\n':
                lexer.line++;
            case '\r':
            case '\t':
            case ' ':
                advance();
                break;
            case '#':
                if (!isAtEnd() && peek() != '\n') {
                    advance();
                }
            default:
                return;
        }
    }
}

static Token string() {
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') {
            lexer.line++;
        }
        advance();
    }
    if (isAtEnd()) {
        return errorToken("Unterminated string");
    }
    advance();
    return makeToken(TOKEN_STRING);
}

static Token number() {
    while (isDigit(peek())) {
        advance();
    }
    if (peek() == '.' && isDigit(peekNext())) {
        advance();
        while (isDigit(peek())) {
            advance();
        }
    }
    return makeToken(TOKEN_NUMBER);
}

static TokenType checkKeyword(
    int start, int length, const char *rest, TokenType type) {
    if (lexer.current - lexer.start == start + length &&
        memcmp(lexer.start + start, rest, length) == 0) {
        return type;
    }
    return TOKEN_IDENTIFIER;
}

static TokenType identifierType() {
    switch (*lexer.start) {
        case 'a':
            return checkKeyword(1, 2, "nd", TOKEN_AND);
        case 'c':
            return checkKeyword(1, 4, "lass", TOKEN_CLASS);
        case 'e':
            return checkKeyword(1, 3, "lse", TOKEN_ELSE);
        case 'f':
            if (lexer.current - lexer.start > 1) {
                switch (lexer.start[1]) {
                    case 'a':
                        return checkKeyword(2, 3, "lse ", TOKEN_FALSE);
                    case 'o':
                        return checkKeyword(2, 1, "r ", TOKEN_FOR);
                    case 'u':
                        return checkKeyword(2, 1, "n ", TOKEN_FUN);
                }
            }
            break;
        case 'i':
            return checkKeyword(1, 1, "f", TOKEN_IF);
        case 'n':
            return checkKeyword(1, 2, "il", TOKEN_NIL);
        case 'o':
            return checkKeyword(1, 1, "r", TOKEN_OR);
        case 'p':
            return checkKeyword(1, 4, "rint", TOKEN_PRINT);
        case 'r':
            return checkKeyword(1, 5, "eturn", TOKEN_RETURN);
        case 's':
            return checkKeyword(1, 4, "uper", TOKEN_SUPER);
        case 't':
            if (lexer.current - lexer.start > 1) {
                switch (lexer.start[1]) {
                    case 'h':
                        return checkKeyword(2, 2, "is ", TOKEN_THIS);
                    case 'r':
                        return checkKeyword(2, 2, "ue ", TOKEN_TRUE);
                }
            }
            break;
        case 'v':
            return checkKeyword(1, 2, "ar", TOKEN_VAR);
        case 'w':
            return checkKeyword(1, 4, "hile", TOKEN_WHILE);
    }

    return TOKEN_IDENTIFIER;
}

static Token identifier() {
    while (isAlpha(peek()) || isDigit(peek())) {
        advance();
    }
    return makeToken(identifierType());
}

void initLexer(const char *source) {
    lexer.start = lexer.current = source;
    lexer.line = 1;
}

Token nextToken() {
    skipWhitespace();
    lexer.start = lexer.current;

    if (isAtEnd()) {
        return makeToken(TOKEN_EOF);
    }

    char c = advance();

    if (isDigit(c)) {
        return number();
    } else if (isAlpha(c)) {
        return identifier();
    }

    switch (c) {
        case '(':
            return makeToken(TOKEN_LEFT_PAREN);
        case ')':
            return makeToken(TOKEN_RIGHT_PAREN);
        case '{':
            return makeToken(TOKEN_LEFT_BRACE);
        case '}':
            return makeToken(TOKEN_RIGHT_BRACE);
        case ';':
            return makeToken(TOKEN_SEMICOLON);
        case ',':
            return makeToken(TOKEN_COMMA);
        case '.':
            return makeToken(TOKEN_DOT);
        case '-':
            return makeToken(TOKEN_MINUS);
        case '+':
            return makeToken(TOKEN_PLUS);
        case '/':
            return makeToken(TOKEN_SLASH);
        case '*':
            return makeToken(TOKEN_STAR);

        case '!':
            return makeToken(match('=') ? TOKEN_BANG_EQUAL : TOKEN_BANG);
        case '=':
            return makeToken(match('=') ? TOKEN_EQUAL_EQUAL : TOKEN_EQUAL);
        case '<':
            return makeToken(match('=') ? TOKEN_LESS_EQUAL : TOKEN_LESS);
        case '>':
            return makeToken(match('=') ? TOKEN_GREATER_EQUAL : TOKEN_GREATER);

        case '"':
            return string();
    }

    return errorToken("Unexpected symbol");
}