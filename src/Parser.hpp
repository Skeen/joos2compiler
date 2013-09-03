#ifndef _PARSER_HPP
#define _PARSER_HPP

#include "Boost_Spirit_Config.hpp"
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/phoenix/function/adapt_function.hpp>

namespace phoenix = boost::phoenix;
namespace qi  = boost::spirit::qi;

#include <string>

#include "Tokens.hpp"
#include "Ast.hpp"

namespace Parser
{
    /*
       ast::expression* build_binop_expression(ast::expression* t1, ast::binop* operatur, ast::expression* t2)
       {
       return (new ast::binop_expression(t1, operatur, t2));
       }
       BOOST_PHOENIX_ADAPT_FUNCTION(ast::expression*, build_binop_expression_, build_binop_expression, 3)
       */

    ///////////////////////////////////////////////////////////////////////////////
    //  Grammar definition
    ///////////////////////////////////////////////////////////////////////////////
    template <typename Iterator>
        struct java_grammar : qi::grammar<Iterator, Ast::source_file()>
    {
        template <typename TokenDef>
            java_grammar(TokenDef const& tok)
            : java_grammar::base_type(start)
            {
                start = qi::token(PACKAGE) >> tok.identifier >> qi::token(SEMI_COLON) [ qi::_val = Ast::source_file() ]
                    ;
                /*
                   expression = (term >> tok.plus  >> term) [ qi::_val = build_binop_expression_(qi::_1, phoenix::new_<ast::binop_plus>(), qi::_2) ]
                   | (term >> tok.minus >> term) [ qi::_val = build_binop_expression_(qi::_1, phoenix::new_<ast::binop_minus>(), qi::_2) ]
                   | term                        [ qi::_val = qi::_1 ]
                   ;

                   term = (factor >> tok.multiplication >> factor)   [ qi::_val = build_binop_expression_(qi::_1, phoenix::new_<ast::binop_times>(), qi::_2) ]
                   | (factor >> tok.division       >> factor)   [ qi::_val = build_binop_expression_(qi::_1, phoenix::new_<ast::binop_divide>(), qi::_2) ]
                   | factor                                     [ qi::_val = qi::_1 ]
                   ;

                   factor = (tok.minus >> plus_factor)               [ qi::_val = build_unary_minus_expression_(qi::_1) ]
                   | plus_factor                              [ qi::_val = qi::_1 ]
                   ;

                   plus_factor = tok.number                        [ qi::_val = build_integer_constant_expression_(qi::_1) ]
                   | (tok.left_paren >> expression >> tok.right_paren) [ qi::_val = qi::_1 ]
                   ;
                   } 
                   */
            }  
        qi::rule<Iterator, Ast::source_file()> start;
    /*
        qi::rule<Iterator, ast::expression*()> expression;
        qi::rule<Iterator, ast::expression*()> term;
        qi::rule<Iterator, ast::expression*()> factor;
        qi::rule<Iterator, ast::expression*()> plus_factor;
       */    
    };


    template<typename T>
    using parser = java_grammar<T>;
}

#endif // _PARSER_HPP
