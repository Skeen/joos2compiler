#ifndef _TOKENS_HPP
#define _TOKENS_HPP

enum TypesStart
{
    Specials            = 0x0000,
    Comments            = 0x0100,
    Keywords            = 0x0200,
    Delimiters          = 0x0300,
    AssignmentAndLogic  = 0x0400,
    Comparison          = 0x0500,
    Arithmetic          = 0x0600,
    Literals            = 0x0700,
    Identifier          = 0x0800
};

enum SpecialsType
{
    Specials_Start = Specials,
    // Values:
    END_OF_FILE,   // "\0" // NOTE: This is explicitly added after the lexing
    END_OF_LINE,   // "\n", "\r" or "\r\n"
    WHITESPACE,    // " " or "\t"
};

enum CommentsType
{
    Comments_Start = Comments,
    // Values:
    BLOCK_COMMENT, // "/* ... */"
    LINE_COMMENT   // "//"
};

enum KeywordsType
{
    Keywords_Start = Keywords,
    // Values:
    ABSTRACT,
    BOOLEAN,
    BREAK,
    BYTE,
    CASE,
    CATCH,
    CHAR,
    CLASS,
    CONST,
    CONTINUE,
    DEFAULT,
    DO,
    DOUBLE,
    ELSE,
    EXTENDS,
    FINAL,
    FINALLY,
    FLOAT,
    FOR,
    GOTO,
    IF,
    IMPLEMENTS,
    IMPORT,
    INSTANCEOF,
    INT,
    INTERFACE,
    LONG,
    NATIVE,
    NEW,
    PACKAGE,
    PRIVATE,
    PROTECTED,
    PUBLIC,
    RETURN,
    SHORT,
    STATIC,
    STRICTFP,
    SUPER,
    SWITCH,
    SYNCHRONIZED,
    THIS,
    THROW,
    THROWS,
    TRANSIENT,
    TRY,
    VOID,
    VOLATILE,
    WHILE,
    // Special valued once
    TRUE_CONSTANT,
    FALSE_CONSTANT,
    NULL_CONSTANT,
};

enum DelimitersType
{
    Delimiters_Start = Delimiters,
    // Values
    LEFT_PARENTHESE,    // "("
    RIGHT_PARENTHESE,   // ")"
    LEFT_BRACE,         // "{"
    RIGHT_BRACE,        // "}"
    LEFT_BRACKET,       // "["
    RIGHT_BRACKET,      // "]"
    SEMI_COLON,         // ";"
    COMMA,              // ","
    DOT                 // "."
};

enum AssignmentAndLogicType
{
    AssignmentAndLogic_Start = AssignmentAndLogic,
    // Values
    ASSIGN,     // "="
    COMPLEMENT, // "!"
    AND_AND,    // "&&"
    OR_OR       // "||"
};

enum ComparisonType
{
    Comparison_Start = Comparison,
    // Values
    LT,     // "<"
    GT,     // ">"
    EQ,     // "=="
    LTEQ,   // "<="
    GTEQ,   // ">="
    NEQ     // "!="
};

enum ArithmeticType
{
    Arithmetic_Start = Arithmetic,
    // Values
    PLUS,       // "+"
    MINUS,      // "-"
    STAR,       // "*"
    DIVISION,   // "/"
    AND,        // "&"
    OR,         // "|"
    XOR,        // "^"
    MOD,        // "%"
    PLUS_PLUS,  // "++"
    MINUS_MINUS // "--"
};

enum LiteralsType
{
    Literals_Start = Literals,
    // Values
    DECIMAL_LITERAL,
    CHAR_LITERAL,
    STRING_LITERAL
};

enum IdentifierType
{
    Identifier_Start = Identifier,
    // Values
    IDENTIFIER   // Pretty much, consumes everything else
};

constexpr TypesStart getOperationType(unsigned value)
{
    return static_cast<TypesStart>(value & 0xFF00);
}

#include <string>

std::string find_enum_type(unsigned value);

#endif //_TOKENS_HPP
