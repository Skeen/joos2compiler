#ifndef _AST_GENERATE_HPP
#define _AST_GENERATE_HPP

#include "ast.hpp"

#include <vector>
#include <string>
#include <utility>

namespace Ast
{
    Ast::program generate_ast(std::vector<std::pair<std::string, std::string>> files_contents);
    //Ast::source_file generate_ast(std::string filename, std::string file_contents);
}

#endif //_AST_GENERATE_HPP
