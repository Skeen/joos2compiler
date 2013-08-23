#include "ast.hpp"
#include "ast_pp.hpp"

#include "utility.hpp"

#include "lexer.hpp"
#include "parser.hpp"

#include <iostream>
#include <fstream>
#include <string>

// Dummy code START
/*
Ast::program parse(std::string)
{
    return Ast::program();
}

namespace WAst
{
    typedef Ast::program program;
}

WAst::program weed(Ast::program)
{
    return WAst::program();
}

namespace Ast
{
    program generate()
    {
        program p = program();

        { // Joede.java

            // import joede.per
            std::list<const import_declaration*> imports = {
                new import_declaration_on_demand(
                        new name_simple(identifier("joede.per"))),
            };

            std::list<const namedtype*> extends = {
                new name_simple(identifier("Menneske")),
                new name_simple(identifier("Dyr"))
            };

            std::list<const declaration*> members = {
                new declaration_field(field_declaration(
                            new access_public(), true, true,
                            new type_expression_base(new base_type_long()),
                            identifier("min_variabel"),
                            Maybe<const expression*>()
                            )),
                new declaration_method(method_declaration(
                            new access_public(), true, true, true,
                            new type_expression_base(new base_type_void()),
                            identifier("min_metode"),
                            std::list<formal_parameter>(),
                            std::list<const namedtype*>(),
                            Maybe<body>()
                            ))
            };

            source_file s = source_file(
                    "Joede.java",
                    Maybe<const package_declaration*>(new name_simple(identifier("nazi"))),
                    imports, 
                    new type_declaration_interface(interface_declaration(
                            identifier("Joede"),
                            extends,
                            members
                            ))
                    );
            
            p.push_back(s);
        }


        return p;
    }
}
// Dummy code END
*/

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
    std::cout << "\tCompiler filename.java" << std::endl;
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
    // We'll read the file in argv[1], into a string;
    std::string file_contents(read_from_file(argv[1]));
    // Start running the compiler
    std::cout << "Applying phases:" << std::endl;
    // Let's lex and parse the input;
    Ast::program ast = apply_phase("lexing & parsing", Parser::lex_parse<Lexer::lexer_type, Parser::parser_type>, file_contents);
    // Pretty print the ast
    // Ast::pretty_print(ast);
    // Let's weed the ast
    // WAst::program wast = apply_phase("weeding", weed, ast);

    return 0;
}
