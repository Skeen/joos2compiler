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
std::string read_from_file(std::string infile)
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

#include <boost/program_options.hpp>
namespace po = boost::program_options;

int main(int argc, char* argv[])
{
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("debug-file", po::value<std::vector<std::string>>(), "output a debug file for the specified phases")
        ("input-file", po::value<std::vector<std::string>>(), "input file")
        ;

    po::positional_options_description p;
    p.add("input-file", -1);

    po::variables_map vm;        
    po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
    po::notify(vm);    

    if (vm.count("help"))
    {
        std::cout << "Usage: options_description [options]" << std::endl;
        std::cout << desc << std::endl;
        return 0;
    }

    if (!vm.count("input-file"))
    {
        std::cout << "Remember to specify files;" << std::endl;
        return 0;
    }

    std::vector<std::string> files = vm["input-file"].as<std::vector<std::string>>();
    std::cout << "Input files are: ";
    for(std::string file : files)
    {
        std::cout << file;
    } 
    std::cout << std::endl;

    // If we reach this, we've got arguments!
    // So let's read the files into strings;
    std::vector<std::pair<std::string, std::string>> files_contents;
    for(unsigned int x=0; x<files.size(); x++)
    {
        // Read the file in argv[x], into a string;
        std::string file_contents(read_from_file(files[x]));
        // And add it to our list
        files_contents.push_back(std::make_pair(files[x], file_contents));
    }

    if (vm.count("debug-file"))
    {
        std::vector<std::string> debug_files = vm["debug-file"].as<std::vector<std::string>>();
        std::cout << "Generating debug output for phases: ";
        for(std::string file : debug_files)
        {
            std::cout << file;
        } 
        std::cout << std::endl;

        std::vector<std::string>::iterator it = std::find_if(debug_files.begin(), debug_files.end(), [](std::string str){ return str == "lexer"; });
        if(it != debug_files.end())
        {
            // Debug our lexer
            Lexer::debug_lexer(files_contents);
        }
  
    } 

    // Start running the compiler
    std::cout << "Applying phases:" << std::endl;
    
    /*
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
    */

    return 0;
}
