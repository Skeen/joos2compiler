#ifndef _PARSER_HPP
#define _PARSER_HPP

#include "Boost_Spirit_Config.hpp"
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/phoenix/function/adapt_function.hpp>

namespace phoenix = boost::phoenix;
namespace qi  = boost::spirit::qi;

#include <string>

#include <cassert>
// Enable declarations in case clauses, which are disabled by default
#define XTL_CLAUSE_DECL 1
#include "typeswitch/match.hpp"

#include "Tokens.hpp"
#include "Ast.hpp"
#include "Ast_helper.hpp"

namespace Parser
{
    Ast::source_file build_source_file(Maybe<const Ast::package_declaration*> package_decl, std::list<const Ast::import_declaration*> imports_decl)
    {
        return Ast::source_file(std::string("test"), package_decl, imports_decl, nullptr);
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(Ast::source_file, build_source_file_, build_source_file, 2)

    Maybe<const Ast::package_declaration*> build_optional_package(boost::optional<Ast::package_declaration*> package_decl)
    {
        if(package_decl)
        {
            return Maybe<const Ast::package_declaration*>(*package_decl);
        }
        else
        {
            return Maybe<const Ast::package_declaration*>();
        }
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(Maybe<const Ast::package_declaration*>, build_optional_package_, build_optional_package, 1)

    Ast::name* build_simple_name(std::string str)
    {
        std::cout << "P" << std::endl;
        return (new Ast::name_simple(Ast::identifier(str)));
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(Ast::name*, build_simple_name_, build_simple_name, 1)
    
    Ast::name* build_qualified_name(Ast::name* name, std::string str)
    {
        std::cout << "B" << std::endl;
        std::list<Ast::identifier> qualified_name = Ast::name_to_identifier_list(name);
        qualified_name.push_back(Ast::identifier(str));

        return (new Ast::name_qualified(qualified_name));
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(Ast::name*, build_qualified_name_, build_qualified_name, 2)

    std::list<const Ast::import_declaration*> build_imports(std::vector<Ast::import_declaration*> imports)
    {
        std::list<const Ast::import_declaration*> list(imports.begin(), imports.end());
        return list;
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(std::list<const Ast::import_declaration*>, build_imports_, build_imports, 1)

    Ast::import_declaration* build_on_demand_import(Ast::name* name)
    {
        return (new Ast::import_declaration_on_demand(name));
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(Ast::import_declaration*, build_on_demand_import_, build_on_demand_import, 1)

    Ast::import_declaration* build_single_import(Ast::name* name, Ast::identifier class_name)
    {
        return (new Ast::import_declaration_single(name, class_name));
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(Ast::import_declaration*, build_single_import_, build_single_import, 2)

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
                start = source_file [ qi::_val = qi::_1 ]
                      ;

                source_file = /*(*/optional_package/* >> imports)*/
                                [ qi::_val = build_source_file_(qi::_1, std::list<const Ast::import_declaration*>()) ]
                      ;

                optional_package = (-package)
                                [ qi::_val = build_optional_package_(qi::_1) ]
                      ;
                    
                package = (qi::raw_token(PACKAGE) >> name >> qi::raw_token(SEMI_COLON))
                                [ qi::_val = qi::_1 ]
                      ;
/*
                imports = (*import)
                                [ qi::_val = build_imports_(qi::_1) ]
                      ;

                import  = (qi::raw_token(IMPORT) >> name >> qi::raw_token(DOT) >> qi::raw_token(STAR) >> qi::raw_token(SEMI_COLON))
                                [ qi::_val = build_on_demand_import_(qi::_1) ]
                        | (qi::raw_token(IMPORT) >> name >> qi::raw_token(DOT) >> tok.identifier >> qi::raw_token(SEMI_COLON))
                                [ qi::_val = build_single_import_(qi::_1, qi::_2) ]
                      ;
*/
                name = simple_name      [ qi::_val = qi::_1 ]
                     | qualified_name   [ qi::_val = qi::_1 ]
                     ;

                simple_name = (tok.identifier)
                                [ qi::_val = build_simple_name_(qi::_1) ]
                            ;
                qualified_name = (name >> qi::raw_token(DOT) >> tok.identifier)
                                [ qi::_val = build_qualified_name_(qi::_1, qi::_2) ]
                     ;

            }  
        qi::rule<Iterator, Ast::source_file()> start;
        qi::rule<Iterator, Ast::source_file()> source_file;
        qi::rule<Iterator, Maybe<const Ast::package_declaration*>()> optional_package;
        qi::rule<Iterator, Ast::package_declaration*()> package;
        //qi::rule<Iterator, std::list<const Ast::import_declaration*>()> imports;
        //qi::rule<Iterator, Ast::import_declaration*()> import;
        qi::rule<Iterator, Ast::name*()> name;
        qi::rule<Iterator, Ast::name*()> simple_name;
        qi::rule<Iterator, Ast::name*()> qualified_name;
    };


    template<typename T>
    using parser = java_grammar<T>;
}

#endif // _PARSER_HPP
