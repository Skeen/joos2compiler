#ifndef _AST_GENERATE_HPP
#define _AST_GENERATE_HPP

#include "ast.hpp"

#include <list>
#include <string>

namespace Ast
{
    Ast::program generate_ast(std::list<std::string> files_contents);
    Ast::source_file generate_ast(std::string file_contents);
}

#endif //_AST_GENERATE_HPP
