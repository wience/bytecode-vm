#include <stdio.h>
#include <string.h>

#include "common.h"
#include "scanner.h"

// Structure representing the scanner state.
typedef struct
{
    const char *start;   // Points to the beginning of the current token.
    const char *current; // Points to the current character being scanned.
    int line;            // Current line number in the source code.
} Scanner;

Scanner scanner;

// Initializes the scanner with the source code.
void initScanner(const char *source)
{
    scanner.start = source;
    scanner.current = source;
    scanner.line = 1;
}

// Helper functions to identify character types and token patterns.

static bool isAlpha(char c)
{
    // Checks if the character is an alphabet letter or underscore.
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

static bool isDigit(char c)
{
    // Checks if the character is a digit.
    return c >= '0' && c <= '9';
}

static bool isAtEnd()
{
    // Checks if the end of the source code is reached.
    return *scanner.current == '\0';
}

static char advance()
{
    // Advances the scanner to the next character and returns the current one.
    scanner.current++;
    return scanner.current[-1];
}

static char peek()
{
    // Returns the current character without advancing the scanner.
    return *scanner.current;
}

static char peekNext()
{
    // Peeks at the next character without advancing the scanner.
    if (isAtEnd())
        return '\0';
    return scanner.current[1];
}

static bool match(char expected)
{
    // Checks if the next character is the expected one. Advances the scanner if true.
    if (isAtEnd())
        return false;
    if (*scanner.current != expected)
        return false;
    scanner.current++;
    return true;
}

// Creates a new token of the given type.
static Token makeToken(TokenType type)
{
    Token token;
    token.type = type;
    token.start = scanner.start;
    token.length = (int)(scanner.current - scanner.start);
    token.line = scanner.line;
    return token;
}

// Creates a new error token with a message.
static Token errorToken(const char *message)
{
    Token token;
    token.type = TOKEN_ERROR;
    token.start = message;
    token.length = (int)strlen(message);
    token.line = scanner.line;
    return token;
}

// Skips whitespaces and comments.
static void skipWhitespace()
{
    for (;;)
    {
        char c = peek();
        switch (c)
        {
        // Handles spaces, carriage returns, and tabs.
        case ' ':
        case '\r':
        case '\t':
            advance();
            break;
        // Handles new lines.
        case '\n':
            scanner.line++;
            advance();
            break;
        // Skips comments.
        case '/':
            if (peekNext() == '/')
            {
                while (peek() != '\n' && !isAtEnd())
                    advance();
            }
            else
            {
                return;
            }
            break;
        default:
            return;
        }
    }
}

// Checks if the current token matches a specific keyword.
static TokenType checkKeyword(int start, int length, const char *rest, TokenType type)
{
    if (scanner.current - scanner.start == start + length &&
        memcmp(scanner.start + start, rest, length) == 0)
    {
        return type;
    }
    return TOKEN_IDENTIFIER;
}

// Identifies the type of the identifier token.
static TokenType identifierType()
{
    // Switch on the first character of the identifier to check for keywords.
    switch (scanner.start[0])
    {
    case 'a':
        return checkKeyword(1, 2, "nd", TOKEN_AND);
    case 'c':
        return checkKeyword(1, 4, "lass", TOKEN_CLASS);
    case 'e':
        return checkKeyword(1, 3, "lse", TOKEN_ELSE);
    case 'f':
        if (scanner.current - scanner.start > 1)
        {
            switch (scanner.start[1])
            {
            case 'a':
                return checkKeyword(2, 3, "lse", TOKEN_FALSE);
            case 'o':
                return checkKeyword(2, 1, "r", TOKEN_FOR);
            case 'u':
                return checkKeyword(2, 1, "n", TOKEN_FUN);
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
        if (scanner.current - scanner.start > 1)
        {
            switch (scanner.start[1])
            {
            case 'h':
                return checkKeyword(2, 2, "is", TOKEN_THIS);
            case 'r':
                return checkKeyword(2, 2, "ue", TOKEN_TRUE);
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

// Handles identifier tokens.
static Token identifier()
{
    while (isAlpha(peek()) || isDigit(peek()))
        advance();
    return makeToken(identifierType());
}

// Handles numeric literal tokens.
static Token number()
{
    while (isDigit(peek()))
        advance();

    // Handle fractional part.
    if (peek() == '.' && isDigit(peekNext()))
    {
        advance(); // Consume the dot.
        while (isDigit(peek()))
            advance();
    }

    return makeToken(TOKEN_NUMBER);
}

// Handles string literal tokens.
static Token string()
{
    while (peek() != '"' && !isAtEnd())
    {
        if (peek() == '\n')
            scanner.line++;
        advance();
    }

    if (isAtEnd())
        return errorToken("Unterminated string.");

    advance(); // Consume the closing quote.
    return makeToken(TOKEN_STRING);
}

// The main function that scans the next token from the source code.
Token scanToken()
{
    skipWhitespace();
    scanner.start = scanner.current;

    if (isAtEnd())
        return makeToken(TOKEN_EOF);

    char c = advance();

    // Handle different character beginnings for tokens.
    if (isAlpha(c))
        return identifier();
    if (isDigit(c))
        return number();

    switch (c)
    {
        // Handle single-character tokens and complex ones like '!='.
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
        return makeToken(('=') ? TOKEN_GREATER_EQUAL : TOKEN_GREATER);
    case '"':
        return string();
    }

    return errorToken("Unexpected character.");
}
