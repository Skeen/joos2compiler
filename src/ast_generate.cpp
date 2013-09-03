#include "ast_generate.hpp"

#include "Parser.hpp"
#include "Lexer.hpp"
#include "Error.hpp"

#include "Boost_Spirit_Config.hpp"
#include <boost/spirit/include/lex_lexertl.hpp>

namespace lex = boost::spirit::lex;

namespace Ast
{
    Ast::program generate_ast(std::list<std::string> files_contents)
    {
        // Prepare the output list
        std::list<source_file> program;
        // Process all arguments
        for(std::string& file_contents : files_contents)
        {
            // Generate the source-file for each (parse each)
            Ast::source_file f = generate_ast(file_contents);
            // Add them to the output list
            program.push_back(f);
        }
        // Return the output list
        return program;
    }
    
    Ast::source_file generate_ast(std::string file_contents)
    {
        // We'll instance our lexer
        Lexer::lexer lexi;
        // And our parser, based upon our lexer
        Parser::parser<Lexer::lexer_iterator> parsi(lexi);
        // Then we'll prepare an output variable
        Ast::source_file source;
        // And we'll prepare our input iterators
        Lexer::lexer_iterator_type begin = file_contents.begin();
        Lexer::lexer_iterator_type end   = file_contents.end();
        // Now let's run the lexer, and pipe it into the parser, to generate the source_file node.
        bool b = lex::tokenize_and_parse(begin, end, lexi, parsi, source);
        // If we were able to lex and parse
        if(b)
        {
            // Return the parsed ast node
            return source;
        }
        // Unable to lex and parse == error
        else
        {
            // Get the rest of the buffer
            std::string rest(begin, end);
            // Throw an exception corresponding to the error
            throw Error::Syntax_Error(rest);
        }
    }
}
