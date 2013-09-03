#ifndef _TOKENS_HPP
#define _TOKENS_HPP

#include "Boost_Spirit_Config.hpp"
#include <boost/spirit/include/lex_lexertl.hpp>

namespace lex = boost::spirit::lex;

enum TypesStart
{
    // 256 elements in each container
    Specials            = (lex::min_token_id + 0x0100) & 0xFF00,
    Comments            = Specials           + 0x0100,
    Keywords            = Comments           + 0x0100,
    Delimiters          = Keywords           + 0x0100,
    AssignmentAndLogic  = Delimiters         + 0x0100,
    Comparison          = AssignmentAndLogic + 0x0100,
    Arithmetic          = Comparison         + 0x0100,
    Literals            = Arithmetic         + 0x0100,
    Identifier          = Literals           + 0x0100
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
