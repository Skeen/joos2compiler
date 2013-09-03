#ifndef _LEXER_HPP
#define _LEXER_HPP

#include "Boost_Spirit_Config.hpp"
#include <boost/spirit/include/lex_lexertl.hpp>

#include "Tokens.hpp"

namespace lex = boost::spirit::lex;
/*
namespace Lexer
{
*/
    template<typename Lexer>
    struct java_tokens : lex::lexer<Lexer>
    {
        lex::token_def<std::string> decimal_literal;
        lex::token_def<std::string> character_literal;
        lex::token_def<std::string> string_literal;

        lex::token_def<std::string> identifier;

        lex::token_def<> line_terminator;
        lex::token_def<> whitespace;
        lex::token_def<std::string> line_comment;
        lex::token_def<std::string> block_comment;

        lex::token_def<> double_or;
        lex::token_def<> double_plus;

        java_tokens()
        {
        // Define regex macros
        this->self.add_pattern
            ("DIGIT",           "[0-9]")
            ("NON_ZERO_DIGIT",  "[1-9]")
            ("OCTAL_DIGIT",     "[0-7]")
            ("ZERO_TO_THREE",   "[0-3]")
            ("LINE_FEED",       "\n")
            ("CARRIAGE_RETURN", "\r")
            ("SPACE",           " ")
            ("HORIZONTAL_TAB",  "\t")
            ("OR_CHARACTER",    "\\|")
            ("STAR_CHARACTER",  "\\*")
            ("PLUS_CHARACTER",  "\\+")
            ("ASCII_CHARACTER", "[\\000-\\255]")
            ("LATIN1_LETTER",   "[A-Z]|[a-z]") //"[A-Z]|[a-z]|\\0170|\\181|\\186|[\\192-\\214]|[\\216-\\246]|[\\248-\\255]")
            ("JAVA_LETTER",     "{LATIN1_LETTER}|$|_")
            ("JAVA_LETTER_OR_DIGIT", "{JAVA_LETTER}|{DIGIT}")
            ("OCTAL_ESCAPE",    "\\\\{ZERO_TO_THREE}{OCTAL_DIGIT}{OCTAL_DIGIT}|{OCTAL_DIGIT}{OCTAL_DIGIT}?")
            ("ESCAPE_SEQUENCE", "\\\\b|\\\\t|\\\\n|\\\\f|\\\\r|\\\\\\\"|'|\\\\\\\\|{OCTAL_ESCAPE}") 
            ("SINGLE_CHARACTER", "[^\r\n'\\\\\\\\]|{ESCAPE_SEQUENCE}")
            ("STRING_CHARACTER", "[^\r\n\"\\\\\\\\]|{ESCAPE_SEQUENCE}")
        ;

        // Define the tokens' regular expressions
        decimal_literal     = "0|{NON_ZERO_DIGIT}{DIGIT}*";
        character_literal   = "'{SINGLE_CHARACTER}'";
        string_literal      = "\\\"{STRING_CHARACTER}*\\\"";

        identifier      = "{JAVA_LETTER}{JAVA_LETTER_OR_DIGIT}*"; // TODO: Check that this does not form a keyword

        line_terminator = "{LINE_FEED}|{CARRIAGE_RETURN}|{CARRIAGE_RETURN}{LINE_FEED}";
        whitespace      = "{SPACE}|{HORIZONTAL_TAB}";
        line_comment    = "\\/\\/[^\r\n]*";
        block_comment   = "\\/\\*[^(\\*\\/)]*\\*\\/";

        double_or       = "{OR_CHARACTER}{OR_CHARACTER}";
        double_plus     = "{PLUS_CHARACTER}{PLUS_CHARACTER}";

        this->self.add
            // Specials
            (line_terminator, END_OF_LINE)
            (whitespace,    WHITESPACE)
            (line_comment,  LINE_COMMENT)
            (block_comment, BLOCK_COMMENT)
            // Keywords
            ("abstract",    ABSTRACT)
            ("boolean",     BOOLEAN)
            ("break",       BREAK)
            ("byte",        BYTE)
            ("case",        CASE)
            ("catch",       CATCH)
            ("char",        CHAR)
            ("class",       CLASS)
            ("const",       CONST)
            ("continue",    CONTINUE)
            ("default",     DEFAULT)
            ("do",          DO)
            ("double",      DOUBLE)
            ("else",        ELSE)
            ("extends",     EXTENDS)
            ("final",       FINAL)
            ("finally",     FINALLY)
            ("float",       FLOAT)
            ("for",         FOR)
            ("goto",        GOTO)
            ("if",          IF)
            ("implements",  IMPLEMENTS)
            ("import",      IMPORT)
            ("instanceof",  INSTANCEOF)
            ("int",         INT)
            ("interface",   INTERFACE)
            ("long",        LONG)
            ("native",      NATIVE)
            ("new",         NEW)
            ("package",     PACKAGE)
            ("private",     PRIVATE)
            ("protected",   PROTECTED)
            ("public",      PUBLIC)
            ("return",      RETURN)
            ("short",       SHORT)
            ("static",      STATIC)
            ("strictfp",    STRICTFP)
            ("super",       SUPER)
            ("switch",      SWITCH)
            ("this",        THIS)
            ("throw",       THROW)
            ("throws",      THROWS)
            ("transient",   TRANSIENT)
            ("try",         TRY)
            ("void",        VOID)
            ("volatile",    VOLATILE)
            ("while",       WHILE)
            // Special constant valued keywords
            ("true",        TRUE_CONSTANT)
            ("false",       FALSE_CONSTANT)
            ("null",        NULL_CONSTANT)
            // Delimiters
            ('(',           LEFT_PARENTHESE)
            (')',           RIGHT_PARENTHESE)
            ('{',           LEFT_BRACE)
            ('}',           RIGHT_BRACE)
            ('[',           LEFT_BRACKET)
            (']',           RIGHT_BRACKET)
            (';',           SEMI_COLON)
            (',',           COMMA)
            ('.',           DOT)
            // Assignment and logic
            ('=',           ASSIGN)
            ('!',           COMPLEMENT)
            ("&&",          AND_AND)
            (double_or,     OR_OR)
            // Comparison
            ('<',           LT)
            ('>',           GT)
            ("==",          EQ)
            ("<=",          LTEQ)
            (">=",          GTEQ)
            ("!=",          NEQ)
            // Arithmetic
            ("\\+",         PLUS)
            ('-',           MINUS)
            ("\\*",         STAR)
            ('/',           DIVISION)
            ('&',           AND)
            ('|',           OR)
            ('^',           XOR)
            ('%',           MOD)
            (double_plus,   PLUS_PLUS)
            ("--",          MINUS_MINUS)
            // Literals
            (decimal_literal,   DECIMAL_LITERAL)
            (character_literal, CHAR_LITERAL)
            (string_literal,    STRING_LITERAL)
            // Comsume rest as identifiers
            (identifier, IDENTIFIER)
        ;
    }
    };

namespace Lexer
{
    // This is our input type (the type, used to expose the underlying input stream)
     typedef std::string::iterator lexer_iterator_type;
    // This is a list of all the attributes that the lexer exposes
    typedef boost::mpl::vector<std::string> lexer_exposed_types;
    // This is our token type
    typedef lex::lexertl::token<lexer_iterator_type, lexer_exposed_types> lexer_token_type;
    // This is the general form type of our lexer
    typedef lex::lexertl::lexer<lexer_token_type> lexer_type;
    // This is our final lexer type (which can be used)
    typedef java_tokens<lexer_type> lexer;
    // This is the output (iterator) type of our lexer
    typedef lexer::iterator_type lexer_iterator;
}

#endif //_LEXER_HPP
