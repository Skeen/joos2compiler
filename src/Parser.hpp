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
    Ast::source_file build_source_file(Maybe<const Ast::package_declaration*> package_decl, std::list<const Ast::import_declaration*> imports_decl, Ast::type_declaration* type_decl)
    {
        return Ast::source_file(std::string("test"), package_decl, imports_decl, type_decl);
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(Ast::source_file, build_source_file_, build_source_file, 3)

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
    
    Ast::name* build_name(std::string str, std::vector<std::string> vec)
    {
        if(vec.size() == 0)
        {
            return (new Ast::name_simple(Ast::identifier(str)));
        }
        else
        {
            std::list<Ast::identifier> qualified_name;
            qualified_name.push_back(Ast::identifier(str));
            for(std::string value : vec)
            {
                qualified_name.push_back(Ast::identifier(value));
            }
            return (new Ast::name_qualified(qualified_name));
        }
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(Ast::name*, build_name_, build_name, 2)

    std::list<const Ast::import_declaration*> build_imports(std::vector<Ast::import_declaration*> vec)
    {
        return std::list<const Ast::import_declaration*>(vec.begin(), vec.end());
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(std::list<const Ast::import_declaration*>, build_imports_, build_imports, 1)

    Ast::import_declaration* build_on_demand_import(Ast::name* name)
    {
        return (new Ast::import_declaration_on_demand(name));
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(Ast::import_declaration*, build_on_demand_import_, build_on_demand_import, 1)

    Ast::import_declaration* build_single_import(Ast::name* name, bool& pass)
    {
        std::list<Ast::identifier> qualified_name = Ast::name_to_identifier_list(name);
        // A single import statement, has the form of id(.id)+, this means
        // atleast 2 identifiers, otherwise there's a syntax error.
        if(qualified_name.size() < 2)
        {
            pass = false;
            // TODO: Get rid of this assert false, really we should just trigger
            // a parse error, using the pass = false statement.
            assert(false);
            return nullptr;
        }
        else
        {
            Ast::identifier class_name = qualified_name.back();
            qualified_name.pop_back();

            return (new Ast::import_declaration_single(new Ast::name_qualified(qualified_name), class_name));
        }
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(Ast::import_declaration*, build_single_import_, build_single_import, 2)

    Ast::type_declaration_class* build_class_declaration(bool is_final, bool is_abstract, std::string name, Ast::namedtype* extends, std::list<const Ast::namedtype*> implements, std::list<const Ast::declaration*> class_body)
    {
        Ast::class_declaration class_decl(is_final, is_abstract, Ast::identifier(name), extends, implements, class_body);
        return (new Ast::type_declaration_class(class_decl));
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(Ast::type_declaration_class*, build_class_declaration_, build_class_declaration, 6)

    Ast::type_declaration_interface* build_interface_declaration(std::string name, std::list<const Ast::namedtype*> extends, std::list<const Ast::declaration*> interface_body)
    {
        Ast::interface_declaration interface_decl(Ast::identifier(name), extends, interface_body);
        return (new Ast::type_declaration_interface(interface_decl));
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(Ast::type_declaration_interface*, build_interface_declaration_, build_interface_declaration, 3)

    Ast::namedtype* build_class_extends(boost::optional<Ast::namedtype*> extends_option)
    {
        if(extends_option)
        {
            return *extends_option;
        }
        else
        {
            std::list<Ast::identifier> qualified;
            qualified.push_back(Ast::identifier("java"));
            qualified.push_back(Ast::identifier("lang"));
            qualified.push_back(Ast::identifier("Object"));
            
            return (new Ast::name_qualified(qualified));
        }
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(Ast::namedtype*, build_class_extends_, build_class_extends, 1)

    std::list<const Ast::namedtype*> build_implements_decl(boost::optional<std::list<const Ast::namedtype*>> implements_list)
    {
        if(implements_list)
        {
            return *implements_list;
        }
        else
        {
            return std::list<const Ast::namedtype*>();
        }
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(std::list<const Ast::namedtype*>, build_implements_decl_, build_implements_decl, 1)

    std::list<const Ast::namedtype*> build_typename_list(Ast::name* name, std::vector<Ast::name*> vec)
    {
        std::list<const Ast::namedtype*> id_list;
        id_list.push_back(name);
        for(Ast::name* value : vec)
        {
            id_list.push_back(value);
        }
        return id_list;
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(std::list<const Ast::namedtype*>, build_typename_list_, build_typename_list, 2)

    std::list<const Ast::declaration*> declaration_vector_to_list(std::vector<Ast::declaration*> vec)
    {
        return std::list<const Ast::declaration*>(vec.begin(), vec.end());
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(std::list<const Ast::declaration*>, declaration_vector_to_list_, declaration_vector_to_list, 1)

    Ast::type_expression_named* build_named_typeexp(Ast::name* name)
    {
        return (new Ast::type_expression_named(name));
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(Ast::type_expression_named*, build_named_typeexp_, build_named_typeexp, 1)

    Ast::type_expression_tarray* build_array_typeexp(Ast::type_expression* typeexp, std::vector<bool> num_brackets)
    {
        // Create the inner-most array
        Ast::type_expression_tarray* value = new Ast::type_expression_tarray(typeexp);
        // Start wrapping it, one time for each number of brackets
        for(bool b : num_brackets)
        {
            value = new Ast::type_expression_tarray(value);
        }
        // Return the wrapped array
        return value;
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(Ast::type_expression_tarray*, build_array_typeexp_, build_array_typeexp, 2)

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
                // TODO: Consider where we want the expectation '>' operator,
                // rather that the sequence '>>' operator.
                // TODO: Consider if some of the build_* functions should be
                // replaced by phoenix::new_<type>(type_constructor_args);
                // TODO: qi::eps matches \Lambda; Use this to throw meaningful
                // syntax exceptions!
                start = source_file [ qi::_val = qi::_1 ] > qi::eoi
                      ;
                
                source_file = (optional_package >> imports >> type)
                                [ qi::_val = build_source_file_(qi::_1, qi::_2, qi::_3) ]
                      ;

                optional_package = (-package)
                                [ qi::_val = build_optional_package_(qi::_1) ]
                      ;
                    
                package = (qi::raw_token(PACKAGE) >> name >> qi::raw_token(SEMI_COLON))
                                [ qi::_val = qi::_1 ]
                      ;

                imports = (*import)
                                [ qi::_val = build_imports_(qi::_1) ]
                      ;

                import  = (qi::raw_token(IMPORT) >> name >> qi::raw_token(DOT) >> qi::raw_token(STAR) >> qi::raw_token(SEMI_COLON))
                                [ qi::_val = build_on_demand_import_(qi::_1) ]
                        | (qi::raw_token(IMPORT) >> name >> qi::raw_token(SEMI_COLON))
                                [ qi::_val = build_single_import_(qi::_1, qi::_pass) ]
                        ;

                type = (class_type)      [ qi::_val = qi::_1 ]
                     | (interface_type)  [ qi::_val = qi::_1 ]
                     ;

                class_type = (qi::raw_token(PUBLIC) >> (-qi::token(FINAL)) >> (-qi::token(ABSTRACT)) >> qi::raw_token(CLASS) >> tok.identifier >> class_extends_decl >> implements_decl >> class_body)
                        [ qi::_val = build_class_declaration_(qi::_1, qi::_2, qi::_3, qi::_4, qi::_5, qi::_6) ]
                    ;

                interface_type = (qi::raw_token(PUBLIC) >> qi::raw_token(INTERFACE) >> tok.identifier >> interface_extends_decl >> interface_body)
                        [ qi::_val = build_interface_declaration_(qi::_1, qi::_2, qi::_3) ]
                    ;

                class_body = (qi::raw_token(LEFT_BRACE) >> *member_decl >> qi::raw_token(RIGHT_BRACE))
                        [ qi::_val = declaration_vector_to_list_(qi::_1) ]
                        ;

                interface_body = (qi::raw_token(LEFT_BRACE) >> *interface_member_declaration >> qi::raw_token(RIGHT_BRACE))
                        [ qi::_val = declaration_vector_to_list_(qi::_1) ]
                        ;

                class_extends_decl = (-(qi::raw_token(EXTENDS) >> name))
                            [ qi::_val = build_class_extends_(qi::_1) ]
                        ;

                implements_decl = (-(qi::raw_token(IMPLEMENTS) >> typename_list))
                            [ qi::_val = build_implements_decl_(qi::_1) ]
                        ;
                
                interface_extends_decl = (-(qi::raw_token(EXTENDS) >> typename_list))
                            [ qi::_val = build_implements_decl_(qi::_1) ]
                        ;

                typename_list = (name >> *(qi::raw_token(COMMA) >> name))
                            [ qi::_val = build_typename_list_(qi::_1, qi::_2) ]
                        ;

                member_decl = method_declaration        [ qi::_val = qi::_1 ]
                            | constructor_declaration   [ qi::_val = qi::_1 ]
                            | field_declaration         [ qi::_val = qi::_1 ]
                            ;

                interface_member_declaration = implicit_method_declaration [ qi::_val = qi::_1 ]
                                             | member_decl [ qi::_val = qi::_1 ]
                                             ;

                typeexp = primitive_typeexp [ qi::_val = qi::_1 ]
                        | reference_typeexp [ qi::_val = qi::_1 ]
                        ;

                reference_typeexp = (qi::raw_token(VOID))
                                      [ qi::_val = phoenix::new_<Ast::type_expression_base>(phoenix::new_<Ast::base_type_void>()) ]
                                  | named_typeexp
                                      [ qi::_val = qi::_1 ]
                                  | array_typeexp
                                      [ qi::_val = qi::_1 ]
                                  ;

                primitive_typeexp = (qi::raw_token(BOOLEAN))
                                      [ qi::_val = phoenix::new_<Ast::type_expression_base>(phoenix::new_<Ast::base_type_boolean>()) ]
                                  | (qi::raw_token(BYTE))
                                      [ qi::_val = phoenix::new_<Ast::type_expression_base>(phoenix::new_<Ast::base_type_byte>()) ]
                                  | (qi::raw_token(SHORT))
                                      [ qi::_val = phoenix::new_<Ast::type_expression_base>(phoenix::new_<Ast::base_type_short>()) ]
                                  | (qi::raw_token(CHAR))
                                      [ qi::_val = phoenix::new_<Ast::type_expression_base>(phoenix::new_<Ast::base_type_char>()) ]
                                  | (qi::raw_token(INT))
                                      [ qi::_val = phoenix::new_<Ast::type_expression_base>(phoenix::new_<Ast::base_type_int>()) ]
                                  ;

                named_typeexp = name [ qi::_val = build_named_typeexp_(qi::_1) ];

                empty_brackets = (qi::token(LEFT_BRACKET) >> qi::token(RIGHT_BRACKET))
                                    [ qi::_val = true ]
                               ;

                array_typeexp = (primitive_typeexp >> +(empty_brackets))
                                  [ qi::_val = build_array_typeexp_(qi::_1, qi::_2) ]
                              | (named_typeexp >> +(empty_brackets))
                                  [ qi::_val = build_array_typeexp_(qi::_1, qi::_2) ]
                              ;
                
                access = (qi::raw_token(PUBLIC))
                            [ qi::_val = phoenix::new_<Ast::access_public>() ]
                       | (qi::raw_token(PROTECTED))
                            [ qi::_val = phoenix::new_<Ast::access_protected>() ]
                       ; 

                name = (tok.identifier >> *(qi::raw_token(DOT) >> tok.identifier))
                                [ qi::_val = build_name_(qi::_1, qi::_2) ]
                    ;
            }  

        qi::rule<Iterator, Ast::source_file()> start;
        qi::rule<Iterator, Ast::source_file()> source_file;
        qi::rule<Iterator, Maybe<const Ast::package_declaration*>()> optional_package;
        qi::rule<Iterator, Ast::package_declaration*()> package;
        qi::rule<Iterator, std::list<const Ast::import_declaration*>()> imports;
        qi::rule<Iterator, Ast::import_declaration*()> import;
        qi::rule<Iterator, Ast::type_declaration*()> type;
        qi::rule<Iterator, Ast::type_declaration_class*()> class_type;
        qi::rule<Iterator, Ast::type_declaration_interface*()> interface_type;
        qi::rule<Iterator, std::list<const Ast::declaration*>()> class_body;
        qi::rule<Iterator, std::list<const Ast::declaration*>()> interface_body;
        qi::rule<Iterator, Ast::namedtype*()> class_extends_decl;
        qi::rule<Iterator, std::list<const Ast::namedtype*>()> implements_decl;
        qi::rule<Iterator, std::list<const Ast::namedtype*>()> interface_extends_decl;
        qi::rule<Iterator, std::list<const Ast::namedtype*>()> typename_list;
        qi::rule<Iterator, Ast::declaration*()> member_decl;
        qi::rule<Iterator, Ast::declaration*()> interface_member_declaration;
        // Missing declaration start
        qi::rule<Iterator, Ast::declaration_method*()> implicit_method_declaration;
        qi::rule<Iterator, Ast::declaration_method*()> method_declaration;
        qi::rule<Iterator, Ast::declaration_constructor*()> constructor_declaration;
        qi::rule<Iterator, Ast::declaration_field*()> field_declaration;
        // Missing declaration stop
        qi::rule<Iterator, Ast::type_expression*()> typeexp;
        qi::rule<Iterator, Ast::type_expression*()> reference_typeexp;
        qi::rule<Iterator, Ast::type_expression_base*()> primitive_typeexp;
        qi::rule<Iterator, Ast::type_expression_named*()> named_typeexp;
        qi::rule<Iterator, Ast::type_expression_tarray*()> array_typeexp;
        qi::rule<Iterator, bool()> empty_brackets;
        qi::rule<Iterator, Ast::access*()> access;
        qi::rule<Iterator, Ast::name*()> name;
    };


    template<typename T>
    using parser = java_grammar<T>;
}

#endif // _PARSER_HPP
