#ifndef _LEXER_DEBUG_HPP
#define _LEXER_DEBUG_HPP
// TODO: Uncomment and fix, possibly turn into some kind of testing

#include "Boost_Spirit_Config.hpp"
#include <boost/spirit/include/lex_lexertl.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/ref.hpp>

#include <boost/range/iterator_range.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/iterator.hpp>

#include <utility>      // std::pair
#include <vector>       // std::vector
#include <fstream>

#include "Tokens.hpp"

#include "Lexer.hpp"

struct token_collector
{
    using result_type = bool;

    template <typename Token>
    bool operator()(Token const& t, std::vector<std::pair<unsigned, std::string>>& vec) const
    {
        std::string str = "";
        if(t.value().which() == 0)
        {
                //std::cout << "0" << std::endl;
                boost::iterator_range<std::string::iterator> ptr = boost::get<boost::iterator_range<std::string::iterator>>(t.value());

                std::string::iterator begin = ptr.begin();
                std::string::iterator end = ptr.end();

                str = std::string(begin, end);

        }
        //std::cout << find_enum_type(t) << " : " << str << std::endl;
        vec.push_back(std::make_pair(static_cast<unsigned>(t), str));
        return true;
    }
};

namespace Lexer
{
    // lex is the lexer (token definition instance) needed to invoke the lexical analyzer
    void debug_lexer(std::string filename, std::string file_contents)
    {
        // Instance the lexer
        Lexer::lexer lex;
        token_collector parse;

        // tokenize the given string, the bound functor gets invoked for each of 
        // the matched tokens
        Lexer::lexer_iterator_type begin = file_contents.begin();
        Lexer::lexer_iterator_type end = file_contents.end();

        std::vector<std::pair<unsigned, std::string>> vec;

        bool r = lex::tokenize(begin, end, lex, boost::bind(parse, _1, boost::ref(vec)));

        std::string output_file_name = filename;
        output_file_name += "_lexer.log";

        std::ofstream out(output_file_name);
        // print results
        if (r)
        {
            for(std::pair<unsigned, std::string> value : vec)
            {
                out << find_enum_type(std::get<0>(value)) << ":\t" << std::get<1>(value) << std::endl;
            }
        }
        else
        {
            std::string rest(begin, end);
            out << "Lexical analysis failed\n" << "stopped at: \"" << rest << "\"" << std::endl;
        }
        out.close();
    }
    
    void debug_lexer(std::vector<std::pair<std::string, std::string>> files_contents)
    {
        for(std::pair<std::string, std::string> pair : files_contents)
        {
            std::string filename = std::get<0>(pair);
            std::string file_contents = std::get<1>(pair);

            debug_lexer(filename, file_contents);
        }
    }
}

#endif // _PARSER_HPP
