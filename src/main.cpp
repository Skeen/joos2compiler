#include "ast.hpp"
#include "ast_pp.hpp"

#include "utility.hpp"

#include "ast_generate.hpp"
#include "Error.hpp"

#include "Lexer_debug.hpp"

#include <iostream>
#include <fstream>
#include <string>

///////////////////////////////////////////////////////////////////////////////
//  Helper function reading a file into a string
///////////////////////////////////////////////////////////////////////////////
std::string read_from_file(char const* infile)
{
    std::ifstream instream(infile);
    if (!instream.is_open()) {
        std::cerr << "Couldn't open file: " << infile << std::endl;
        exit(-1);
    }
    instream.unsetf(std::ios::skipws);      // No white space skipping!
    return std::string(std::istreambuf_iterator<char>(instream.rdbuf()),
                       std::istreambuf_iterator<char>());
}

void print_help()
{
    std::cout << "usage:" << std::endl;
    std::cout << "\tCompiler [filenameX.java]+" << std::endl;
}

int main(int argc, char* argv[])
{
    // If we're not given any arguments
    if(argc == 1)
    {
        // Print help
        print_help();
        return 0;
    }
    // If we reach this, we've got arguments!
    // So let's read the files into strings;
    std::list<std::string> files_contents;
    for(int x=1; x<argc; x++)
    {
        // Read the file in argv[x], into a string;
        std::string file_contents(read_from_file(argv[x]));
        // And add it to our list
        files_contents.push_back(file_contents);
    }
    // Start running the compiler
    std::cout << "Applying phases:" << std::endl;
    
        // Debug our lexer
        Lexer::debug_lexer(files_contents.front());
    try
    {
        // Let's lex and parse the input;
        Ast::program ast = apply_phase<Ast::program, std::list<std::string>>("lexing & parsing", Ast::generate_ast, files_contents);
        // Pretty print the ast
        Ast::pretty_print(ast);
        // Let's weed the ast
        // WAst::program wast = apply_phase("weeding", weed, ast);
    }
    catch(Error::Syntax_Error& e)
    {
        std::cout << e.what();
    }

    return 0;
}
