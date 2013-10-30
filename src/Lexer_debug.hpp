#ifndef _LEXER_DEBUG_HPP
#define _LEXER_DEBUG_HPP

#include <string>
#include <vector>
#include <utility>

namespace Lexer
{
    void debug_lexer(std::string filename, std::string file_contents);
    void debug_lexer(std::vector<std::pair<std::string, std::string>> files_contents);
}

#endif // _PARSER_HPP

