#ifndef _PARSER_HPP
#define _PARSER_HPP

#define BOOST_SPIRIT_LEXERTL_DEBUG
#include <boost/spirit/include/lex_lexertl.hpp>
#include <boost/bind.hpp>
#include <boost/ref.hpp>

#include <boost/range/iterator_range.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/iterator.hpp>

#include <string>

#include "Tokens.hpp"

struct token_collector_string
{
    typedef void result_type;

    void operator()(char c, std::string& str) const
    {
        str.push_back(c);
    }
};

struct token_collector
{
    typedef bool result_type;

    template <typename Token>
    bool operator()(Token const& t, std::vector<std::pair<unsigned, std::string>>& c) const
    {
        switch(t.id())
        {
            case WHITESPACE:
                c.push_back(std::make_pair(WHITESPACE, "WHITESPACE"));
                break;
            case END_OF_LINE:
                c.push_back(std::make_pair(END_OF_LINE, "END_OF_LINE"));
                break;
            default:
                std::string str;
                boost::for_each(t.value(),
                        boost::bind(token_collector_string(), _1, boost::ref(str)));
                c.push_back(std::make_pair(t.id(), str));
                break;
        }
        return true;
    }
};

namespace Parser
{
    typedef token_collector parser_type;

    // lex is the lexer (token definition instance) needed to invoke the lexical analyzer
    template<typename LEXER, typename PARSER>
    Ast::program lex_parse(std::string file_contents)
    {
        // Instance the lexer
        LEXER lex;
        PARSER parse;

        // tokenize the given string, the bound functor gets invoked for each of 
        // the matched tokens
        char const* first = file_contents.c_str();
        char const* last = &first[file_contents.size()];

        std::vector<std::pair<unsigned, std::string>> vec;
        bool r = lex::tokenize(first, last, lex, 
                boost::bind(parse, _1, boost::ref(vec)));
        vec.push_back(std::make_pair(END_OF_FILE, "END_OF_FILE"));

        // print results
        if (r) {
            std::cout << "tokens are:" << std::endl;
            for(std::pair<unsigned, std::string> value : vec)
            {
                std::cout << find_enum_type(std::get<0>(value)) << ":\t" << std::get<1>(value) << std::endl;
            }
        }
        else {
            std::string rest(first, last);
            std::cout << "Lexical analysis failed\n" << "stopped at: \"" 
                << rest << "\"\n";
        }
        
        exit(-1);
        return Ast::program();

/*
        // Local variable, to pass reference to
        Ast::program program;
        // tokenize and parse the program
        bool r = lex::tokenize(first, last, lex, boost::bind(parse, _1, boost::ref(program)));
        // Evaluate results
        if (r) 
        {
            // Succesful parsing
            return program;
        }
        else 
        {
            std::string rest(first, last);
            std::cout << "Lexical analysis failed\n" << "stopped at: \"" << rest << "\"\n";
            exit(-1);
        }
        */
    }
}

#endif // _PARSER_HPP
