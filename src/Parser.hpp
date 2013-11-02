#ifndef _PARSER_HPP
#define _PARSER_HPP

#include "Boost_Spirit_Config.hpp"
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/phoenix/function/adapt_function.hpp>

namespace phoenix = boost::phoenix;
namespace qi      = boost::spirit::qi;

#include <string>

#include <cassert>
// Enable declarations in case clauses, which are disabled by default
#define XTL_CLAUSE_DECL 1

#include "Tokens.hpp"
#include "ast.hpp"
#include "ast_helper.hpp"

namespace boost { namespace spirit { namespace traits {

    template </*typename Exposed, typename Transformed, typename Domain, typename Enable*/>
        struct transform_attribute<Ast::import_declaration_on_demand, Ast::name, qi::domain, void>
        {
            using type = Ast::name;

            static type pre (Ast::import_declaration_on_demand&)                 { return {}; }
            static void post(Ast::import_declaration_on_demand& val, type attr)  { val = { attr }; }
            static void fail(Ast::import_declaration_on_demand&)                 { }
        }; 

}}}

namespace Parser
{
    Ast::name build_name(const std::string& str, const std::vector<std::string>& vec)
    {
        if(vec.size() == 0)
        {
            return Ast::name_simple { Ast::identifier{str} };
        }
        else
        {
            std::list<Ast::identifier> qualified_name { begin(vec), end(vec) };
            qualified_name.insert(begin(qualified_name), {str});
            return Ast::name_qualified{ qualified_name };
        }
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(Ast::name, build_name_, build_name, 2)

    Ast::import_declaration_single build_single_import(Ast::name const& name, bool& pass)
    {
        std::list<Ast::identifier> qualified_name = Ast::name_to_identifier_list(name);
        // A single import statement, has the form of id(.id)+, this means
        // atleast 2 identifiers, otherwise there's a syntax error.
        pass = qualified_name.size() > 1;
        if (pass)
        {
            Ast::identifier class_name = qualified_name.back();
            qualified_name.pop_back();

            return { Ast::name_qualified { qualified_name }, class_name };
        } else
        {
            return { Ast::name_qualified { { } }, { "" } };
        }
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(Ast::import_declaration_single, build_single_import_, build_single_import, 2)

    Ast::type_declaration_class build_class_declaration(bool is_final, bool is_abstract, const std::string& name, Ast::namedtype extends, std::list<Ast::namedtype> implements, std::list<Ast::declaration> class_body)
    {
        return { is_final, is_abstract, Ast::identifier{name}, extends, implements, class_body };
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(Ast::type_declaration_class, build_class_declaration_, build_class_declaration, 6)

    Ast::type_declaration_interface build_interface_declaration(std::string name, std::list<Ast::namedtype> extends, std::list<Ast::declaration> interface_body)
    {
        return { Ast::identifier { name }, extends, interface_body };
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(Ast::type_declaration_interface, build_interface_declaration_, build_interface_declaration, 3)

    Ast::namedtype build_class_extends(boost::optional<Ast::namedtype> extends_option)
    {
        static const Ast::name_qualified default_ { { {"java"}, {"lang"}, {"Object"} } };
        return extends_option? *extends_option : default_;
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(Ast::namedtype, build_class_extends_, build_class_extends, 1)

    Ast::type_expression_tarray build_array_typeexp(Ast::type_expression typeexp, unsigned num_brackets)
    {
        Ast::type_expression_tarray value { typeexp }; // Create the inner-most array
        return num_brackets <= 1? value : build_array_typeexp(value, num_brackets-1);
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(Ast::type_expression_tarray, build_array_typeexp_, build_array_typeexp, 2)

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
                start = source_file  > qi::eoi
                      ;
                
                source_file = (qi::attr(std::string("test")) >> optional_package >> imports >> type)
                      ;

                optional_package = -package
                      ;
                    
                package = (qi::raw_token(PACKAGE) >> name >> qi::raw_token(SEMI_COLON))
                      ;

                imports = (*import)
                      ;

                import_on_demand = 
                    qi::raw_token(IMPORT) >> name >> qi::raw_token(DOT) >> qi::raw_token(STAR) >> qi::raw_token(SEMI_COLON)
                    ;

                import_single = 
                    (qi::raw_token(IMPORT) >> name >> qi::raw_token(SEMI_COLON))
                        [ qi::_val = build_single_import_(qi::_1, qi::_pass) ]
                    ;

                import  = import_on_demand
                        | import_single
                        ;

                type = (class_type)      
                     | (interface_type)  
                     ;

                class_type = 
                    (
                        qi::raw_token(PUBLIC)                    >> 
                        (qi::token(FINAL) ^ qi::token(ABSTRACT)) >> 
                        qi::raw_token(CLASS)                     >> 
                        tok.identifier                           >> 
                        class_extends_decl                       >> 
                        implements_decl                          >> 
                        class_body
                    )
                        [ qi::_val = build_class_declaration_(phoenix::at_c<0>(qi::_1), phoenix::at_c<1>(qi::_1), qi::_2, qi::_3, qi::_4, qi::_5) ]
                    ;

                interface_type = (qi::raw_token(PUBLIC) >> qi::raw_token(INTERFACE) >> tok.identifier >> interface_extends_decl >> interface_body)
                        [ qi::_val = build_interface_declaration_(qi::_1, qi::_2, qi::_3) ]
                    ;

                class_body = (qi::raw_token(LEFT_BRACE) >> *member_decl >> qi::raw_token(RIGHT_BRACE))
                        ;

                interface_body = (qi::raw_token(LEFT_BRACE) >> *interface_member_declaration >> qi::raw_token(RIGHT_BRACE))
                        ;

                class_extends_decl = (-(qi::raw_token(EXTENDS) >> name))
                            [ qi::_val = build_class_extends_(qi::_1) ]
                        ;

                implements_decl = (-(qi::raw_token(IMPLEMENTS) >> typename_list))
                        ;
                
                interface_extends_decl = (-(qi::raw_token(EXTENDS) >> typename_list))
                        ;

                typename_list = (name >> *(qi::raw_token(COMMA) >> name))
                        ;

                member_decl = method_declaration        
                            | constructor_declaration   
                            | field_declaration         
                            ;

                interface_member_declaration = implicit_method_declaration 
                                             | member_decl 
                                             ;

                typeexp = primitive_typeexp
                        | reference_typeexp
                        ;

                reference_typeexp = 
                      qi::attr_cast<Ast::base_type_void> (qi::raw_token(VOID))
                    | named_typeexp
                    | array_typeexp
                    ;

                primitive_typeexp = 
                      qi::attr_cast<Ast::base_type_boolean>(qi::raw_token(BOOLEAN))
                    | qi::attr_cast<Ast::base_type_byte>(qi::raw_token(BYTE))
                    | qi::attr_cast<Ast::base_type_short>(qi::raw_token(SHORT))
                    | qi::attr_cast<Ast::base_type_char>(qi::raw_token(CHAR))
                    | qi::attr_cast<Ast::base_type_int>(qi::raw_token(INT))
                    ;

                named_typeexp = name; // [ qi::_val = build_named_typeexp(qi::_1) ];

                empty_brackets = qi::token(LEFT_BRACKET) >> qi::token(RIGHT_BRACKET);

                n_empty_brackets = qi::eps [ qi::_val = 0 ] >> +empty_brackets [ ++qi::_val ];
                element_type     = primitive_typeexp | named_typeexp;

                array_typeexp = 
                    (element_type >> n_empty_brackets)
                    [ qi::_val = build_array_typeexp_(qi::_1, qi::_2) ]
                    ;
                
                access = qi::attr_cast<Ast::access_public>    (qi::raw_token(PUBLIC))
                       | qi::attr_cast<Ast::access_protected> (qi::raw_token(PROTECTED))
                       ; 

                name = 
                    (tok.identifier >> *(qi::raw_token(DOT) >> tok.identifier))
                    [ qi::_val = build_name_(qi::_1, qi::_2) ];
            }  

        qi::rule<Iterator, Ast::source_file()> start;
        qi::rule<Iterator, Ast::source_file()> source_file;
        qi::rule<Iterator, Maybe<Ast::package_declaration>()> optional_package;
        qi::rule<Iterator, Ast::package_declaration()> package;
        qi::rule<Iterator, std::list<Ast::import_declaration>()> imports;
        qi::rule<Iterator, Ast::import_declaration_on_demand()> import_on_demand;
        qi::rule<Iterator, Ast::import_declaration_single()> import_single;
        qi::rule<Iterator, Ast::import_declaration()> import;
        qi::rule<Iterator, Ast::type_declaration()> type;
        qi::rule<Iterator, Ast::type_declaration_class()> class_type;
        qi::rule<Iterator, Ast::type_declaration_interface()> interface_type;
        qi::rule<Iterator, std::list<Ast::declaration>()> class_body;
        qi::rule<Iterator, std::list<Ast::declaration>()> interface_body;
        qi::rule<Iterator, Ast::namedtype()> class_extends_decl;
        qi::rule<Iterator, std::list<Ast::namedtype>()> implements_decl;
        qi::rule<Iterator, std::list<Ast::namedtype>()> interface_extends_decl;
        qi::rule<Iterator, std::list<Ast::namedtype>()> typename_list;
        qi::rule<Iterator, Ast::declaration()> member_decl;
        qi::rule<Iterator, Ast::declaration()> interface_member_declaration;
        // Missing declaration start
        qi::rule<Iterator, Ast::declaration_method()> implicit_method_declaration;
        qi::rule<Iterator, Ast::declaration_method()> method_declaration;
        qi::rule<Iterator, Ast::declaration_constructor()> constructor_declaration;
        qi::rule<Iterator, Ast::declaration_field()> field_declaration;
        // Missing declaration stop
        qi::rule<Iterator, Ast::type_expression()> typeexp;
        qi::rule<Iterator, Ast::type_expression()> reference_typeexp;
        qi::rule<Iterator, Ast::type_expression_base()> primitive_typeexp;
        qi::rule<Iterator, Ast::type_expression_named()> named_typeexp;
        qi::rule<Iterator, unsigned()> n_empty_brackets;
        qi::rule<Iterator, Ast::type_expression()> element_type;
        qi::rule<Iterator, Ast::type_expression_tarray()> array_typeexp;
        qi::rule<Iterator> empty_brackets;
        qi::rule<Iterator, Ast::access()> access;
        qi::rule<Iterator, Ast::name()> name;
    };


    template<typename T>
    using parser = java_grammar<T>;
}

#endif // _PARSER_HPP
