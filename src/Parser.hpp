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
    Ast::source_file build_source_file(Ast::package_declaration* package, Ast::import_declaration* import)
    {
        Maybe<const Ast::package_declaration*> package_decl = Maybe<const Ast::package_declaration*>(package);
        std::list<const Ast::import_declaration*> imports_decl;
        imports_decl.push_back(import);


        return Ast::source_file("test", package_decl, imports_decl, nullptr);
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(Ast::source_file, build_source_file_, build_source_file, 2)

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
                start = qi::raw_token(PACKAGE) >> tok.identifier >> qi::raw_token(SEMI_COLON) [ qi::_val = Ast::source_file() ]
                      ;
                /*
                start = (optional_package_declaration >> import_declaration) [ qi::_val = build_source_file_(qi::_1, qi::_2) ]
                      ;

                optional_package_declaration = -(package_declaration)
                      ;
                    
                package_declaration = qi::raw_token(PACKAGE) >> tok.whitespace >> name_declaration >> qi::raw_token(SEMI_COLON) 
                      ;
                
                import_declaration  = (qi::raw_token(IMPORT) >> name_declaration
                      ;

                name_declaration = tok.identifier
                      ;
*/
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
        qi::rule<Iterator, Maybe<const Ast::package_declaration*>()> optional_package_declaration;
        qi::rule<Iterator, Ast::package_declaration*()> package_declaration;
        qi::rule<Iterator, Ast::import_declaration*()> import_declaration;
        qi::rule<Iterator, Ast::name*()> name_declaration;
        */
    };


    template<typename T>
    using parser = java_grammar<T>;
}

#endif // _PARSER_HPP
