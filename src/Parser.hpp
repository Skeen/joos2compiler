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

    Ast::declaration_field* build_field_declaration(Ast::access* access_type, boost::fusion::vector2<boost::optional<boost::iterator_range<std::string::iterator>>, boost::optional<boost::iterator_range<std::string::iterator>>> is_static_is_final, Ast::type_expression* type, Ast::identifier name, Maybe<const Ast::expression*> optional_variable_intializer)
    {
        // Read out static, has type boost::optional<*>, which is implicitly casted to bool
        bool is_static = boost::fusion::at_c<0>(is_static_is_final);
        // Read out final, has type boost::optional<*>, which is implicitly casted to bool
        bool is_final = boost::fusion::at_c<1>(is_static_is_final);
        // Create the field declaration
        Ast::field_declaration field_decl = Ast::field_declaration(access_type, is_static, is_final, type, name, optional_variable_intializer);
        // And use that to create the declaration field
        return (new Ast::declaration_field(field_decl));
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(Ast::declaration_field*, build_field_declaration_, build_field_declaration, 5)

    Maybe<const Ast::expression*> build_optional_expression(boost::optional<Ast::expression*> optional)
    {
        if(optional)
        {
            return Maybe<const Ast::expression*>(*optional);
        }
        else
        {
            return Maybe<const Ast::expression*>();
        }
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(Maybe<const Ast::expression*>, build_optional_expression_, build_optional_expression, 1)

    Ast::declaration_method* build_method_declaration(Ast::access* access_type, boost::fusion::vector3<boost::optional<boost::iterator_range<std::string::iterator>>, boost::optional<boost::iterator_range<std::string::iterator>>, boost::optional<boost::iterator_range<std::string::iterator>>> is_abstract_is_static_is_final, Ast::type_expression* type, Ast::identifier name, std::list<Ast::formal_parameter> params, std::list<const Ast::namedtype*> throws, Maybe<Ast::body> body)
    {
        // Read out abstract, has type boost::optional<*>, which is implicitly casted to bool
        bool is_abstract = boost::fusion::at_c<0>(is_abstract_is_static_is_final);
        // Read out static, has type boost::optional<*>, which is implicitly casted to bool
        bool is_static = boost::fusion::at_c<1>(is_abstract_is_static_is_final);
        // Read out final, has type boost::optional<*>, which is implicitly casted to bool
        bool is_final = boost::fusion::at_c<2>(is_abstract_is_static_is_final);
        // Create the method declaration
        Ast::method_declaration method_decl = Ast::method_declaration(access_type, is_static, is_final, is_abstract, type, name, params, throws, body);
        // And use that to create the declaration method
        return (new Ast::declaration_method(method_decl));
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(Ast::declaration_method*, build_method_declaration_, build_method_declaration, 7)

    Ast::declaration_constructor* build_constructor_declaration(Ast::access* access_type, Ast::identifier name, std::list<Ast::formal_parameter> params, std::list<const Ast::namedtype*> throws, Ast::body body)
    {
        Ast::constructor_declaration constructor_decl = Ast::constructor_declaration(access_type, name, params, throws, body);
        // And use that to create the declaration method
        return (new Ast::declaration_constructor(constructor_decl));
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(Ast::declaration_constructor*, build_constructor_declaration_, build_constructor_declaration, 5)

    Maybe<Ast::body> build_optional_method_body(Ast::body body)
    {
        return Maybe<Ast::body>(body);
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(Maybe<Ast::body>, build_optional_method_body_, build_optional_method_body, 1)

    Ast::declaration_method* build_implicit_method_declaration(boost::optional<boost::iterator_range<std::string::iterator>> abstract_option, Ast::type_expression* type, Ast::identifier name, std::list<Ast::formal_parameter> params, std::list<const Ast::namedtype*> throws, Maybe<Ast::body> body)
    {
        // Read out abstract, has type boost::optional<*>, which is implicitly casted to bool
        bool is_abstract = abstract_option;
        // Create the method declaration
        Ast::method_declaration method_decl = Ast::method_declaration(new Ast::access_public, false, false, is_abstract, type, name, params, throws, body);
        // And use that to create the declaration method
        return (new Ast::declaration_method(method_decl));
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(Ast::declaration_method*, build_implicit_method_declaration_, build_implicit_method_declaration, 6)

    std::list<Ast::formal_parameter> build_formal_parameter_list(boost::optional<boost::fusion::vector2<Ast::formal_parameter, std::vector<Ast::formal_parameter>>> optional_list_of_params)
    {
        std::list<Ast::formal_parameter> return_list;
        // If we matched anything, let's process it
        if(optional_list_of_params)
        {
            // Get the matched vector
            boost::fusion::vector2<Ast::formal_parameter, std::vector<Ast::formal_parameter>> list_of_params = *optional_list_of_params;
            // Get the first type, which was matched
            Ast::formal_parameter matched = boost::fusion::at_c<0>(list_of_params);
            // Add this, to our return list
            return_list.push_back(matched);
            // Get the (possibly empty) list of futher matches
            std::vector<Ast::formal_parameter> matched_list = boost::fusion::at_c<1>(list_of_params);
            // Add each for these, to our return list
            for(Ast::formal_parameter match : matched_list)
            {
                return_list.push_back(match);
            }
        }
        // return the possibly empty list
        return return_list;
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(std::list<Ast::formal_parameter>, build_formal_parameter_list_, build_formal_parameter_list, 1)

    Ast::formal_parameter build_formal_parameter(Ast::type_expression* type, Ast::identifier name)
    {
        return std::make_pair(type, name);
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(Ast::formal_parameter, build_formal_parameter_, build_formal_parameter, 2)

    std::list<const Ast::namedtype*> build_throws_clause(boost::optional<std::list<const Ast::namedtype*>> typenames)
    {
        // If we were passed a list of typenames simply return it
        if(typenames)
        {
            return *typenames;
        }
        // Otherwise return the empty list
        else
        {
            return std::list<const Ast::namedtype*>();
        }
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(std::list<const Ast::namedtype*>, build_throws_clause_, build_throws_clause, 1)
    
    std::list<const Ast::statement*> build_block(std::vector<Ast::statement*> vec)
    {
        return std::list<const Ast::statement*>(vec.begin(), vec.end());
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(std::list<const Ast::statement*>, build_block_, build_block, 1)

    Ast::statement_local_declaration* build_local_variable_declaration(Ast::type_expression* type, Ast::identifier name, Maybe<const Ast::expression*> optional_initializer)
    {
        return (new Ast::statement_local_declaration(type, name, optional_initializer));
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(Ast::statement_local_declaration*, build_local_variable_declaration_, build_local_variable_declaration, 3)

    Ast::statement_super_call* build_super_call_statement(std::list<const Ast::expression*> arguments)
    {
        return (new Ast::statement_super_call(arguments));
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(Ast::statement_super_call*, build_super_call_statement_, build_super_call_statement, 1)

    Ast::statement_this_call* build_this_call_statement(std::list<const Ast::expression*> arguments)
    {
        return (new Ast::statement_this_call(arguments));
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(Ast::statement_this_call*, build_this_call_statement_, build_this_call_statement, 1)

    Ast::statement_throw* build_throw_statement(Ast::expression* throwee)
    {
        return (new Ast::statement_throw(throwee));
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(Ast::statement_throw*, build_throw_statement_, build_throw_statement, 1)

    Ast::statement_if_then* build_if_then_statement(Ast::expression* condition, Ast::statement* body)
    {
        return (new Ast::statement_if_then(condition, body));
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(Ast::statement_if_then*, build_if_then_statement_, build_if_then_statement, 2)

    Ast::statement_if_then_else* build_if_then_else_statement(Ast::expression* condition, Ast::statement* true_body, Ast::statement* false_body)
    {
        return (new Ast::statement_if_then_else(condition, true_body, false_body));
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(Ast::statement_if_then_else*, build_if_then_else_statement_, build_if_then_else_statement, 3)

    Ast::statement_while* build_while_statement(Ast::expression* condition, Ast::statement* body)
    {
        return (new Ast::statement_while(condition, body));
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(Ast::statement_while*, build_while_statement_, build_while_statement, 2)

    Ast::statement_block* build_for_statement(Ast::statement* for_init, Ast::expression* for_condition, Ast::statement* for_update, Ast::statement* body)
    {
        // Create the body, which goes inside the while loop
        std::list<const Ast::statement*> internal_block;
        // First the body
        internal_block.push_back(body);
        // Then the update step
        internal_block.push_back(for_update);

        // Create the entire scope, we're working with
        std::list<const Ast::statement*> block;
        // First the inialization
        block.push_back(for_init);
        // Then the while loop
        block.push_back(new Ast::statement_while(for_condition,
                        new Ast::statement_block(internal_block)));

        // Return it all
        return (new Ast::statement_block(block));
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(Ast::statement_block*, build_for_statement_, build_for_statement, 4)

    Ast::statement_expression* build_for_statement_update(Ast::expression* expression)
    {
        return (new Ast::statement_expression(expression));
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(Ast::statement_expression*, build_for_statement_update_, build_for_statement_update, 1)

    Ast::statement_expression* build_expression_statement(Ast::expression* expression)
    {
        return (new Ast::statement_expression(expression));
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(Ast::statement_expression*, build_expression_statement_, build_expression_statement, 1)

    std::list<const Ast::expression*> build_argument_list(boost::optional<boost::fusion::vector2<Ast::expression*, std::vector<Ast::expression*>>> optional_list_of_arguments)
    {
        std::list<const Ast::expression*> return_list;
        // If we matched anything, let's process it
        if(optional_list_of_arguments)
        {
            // Get the matched vector
            boost::fusion::vector2<Ast::expression*, std::vector<Ast::expression*>> list_of_arguments = *optional_list_of_arguments;
            // Get the first type, which was matched
            Ast::expression* matched = boost::fusion::at_c<0>(list_of_arguments);
            // Add this, to our return list
            return_list.push_back(matched);
            // Get the (possibly empty) list of futher matches
            std::vector<Ast::expression*> matched_list = boost::fusion::at_c<1>(list_of_arguments);
            // Add each for these, to our return list
            for(Ast::expression* match : matched_list)
            {
                return_list.push_back(match);
            }
        }
        // return the possibly empty list
        return return_list;
    }
    BOOST_PHOENIX_ADAPT_FUNCTION(std::list<const Ast::expression*>, build_argument_list_, build_argument_list, 1)

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

                field_declaration = (access >> (qi::token(STATIC) ^ qi::token(FINAL)) >> typeexp >> tok.identifier >> optional_variable_intializer >> qi::raw_token(SEMI_COLON))
                                     [ qi::_val = build_field_declaration_(qi::_1, qi::_2, qi::_3, qi::_4, qi::_5) ]
                                  ;

                optional_variable_intializer = -(qi::raw_token(ASSIGN) >> expression)
                                     [ qi::_val = build_optional_expression_(qi::_1) ]
                                    ;

                method_declaration = (access >> (qi::token(ABSTRACT) ^ qi::token(STATIC) ^ qi::token(FINAL)) >> typeexp >> tok.identifier >> method_parameters >> throws_clause >> optional_method_body)
                                     [ qi::_val = build_method_declaration_(qi::_1, qi::_2, qi::_3, qi::_4, qi::_5, qi::_6, qi::_7) ]
                                    ;

                constructor_declaration = (access >> tok.identifier >> method_parameters >> throws_clause >> constructor_body)
                                     [ qi::_val = build_constructor_declaration_(qi::_1, qi::_2, qi::_3, qi::_4, qi::_5) ]
                                     ;

                constructor_body = block [ qi::_val = qi::_1 ] ;

                optional_method_body = (qi::raw_token(SEMI_COLON))
                                        [ qi::_val = Maybe<Ast::body>() ]
                                     | (method_body)
                                        [ qi::_val = build_optional_method_body_(qi::_1) ]
                                     ;

                method_body = block [ qi::_val = qi::_1 ] ;

                implicit_method_declaration = (-(qi::token(ABSTRACT)) >> typeexp >> tok.identifier >> method_parameters >> throws_clause >> optional_method_body)
                                        [ qi::_val = build_implicit_method_declaration_(qi::_1, qi::_2, qi::_3, qi::_4, qi::_5, qi::_6) ]
                                       ; 

                method_parameters = (qi::raw_token(LEFT_PARENTHESE) >> formal_parameter_list >> qi::raw_token(RIGHT_PARENTHESE))
                                        [ qi::_val = qi::_1 ]
                                  ;

                formal_parameter_list = (-(formal_parameter >> *(qi::raw_token(COMMA) >> formal_parameter)))
                                        [ qi::_val = build_formal_parameter_list_(qi::_1) ]
                                      ;

                formal_parameter = (typeexp >> tok.identifier)
                                        [ qi::_val = build_formal_parameter_(qi::_1, qi::_2) ]
                                 ;
        
                throws_clause = (-(qi::raw_token(THROWS) >> typename_list))
                                        [ qi::_val = build_throws_clause_(qi::_1) ]
                                 ;

                block = (qi::raw_token(LEFT_BRACE) >> *statement_or_declaration >> qi::raw_token(RIGHT_BRACE))
                                        [ qi::_val = build_block_(qi::_1) ]
                      ;

                statement_or_declaration = (statement)
                                           [ qi::_val = qi::_1 ]
                                         | (local_variable_declaration_statement)
                                           [ qi::_val = qi::_1 ]
                                         ;

                local_variable_declaration_statement = (typeexp >> tok.identifier >> optional_variable_intializer)
                        [ qi::_val = build_local_variable_declaration_(qi::_1, qi::_2, qi::_3) ]
                        ;

                statement = super_call_statement
                             [ qi::_val = qi::_1 ]
                          | this_call_statement
                             [ qi::_val = qi::_1 ]
                          | throw_statement
                             [ qi::_val = qi::_1 ]
                          | statement_without_trailing_substatement
                             [ qi::_val = qi::_1 ]
                          | if_then_statement
                             [ qi::_val = qi::_1 ]
                          | if_then_else_statement
                             [ qi::_val = qi::_1 ]
                          | while_statement
                             [ qi::_val = qi::_1 ]
                          | for_statement
                             [ qi::_val = qi::_1 ]
                          ;
                
                super_call_statement = (qi::raw_token(SUPER) >> qi::raw_token(LEFT_PARENTHESE) >> argument_list >> qi::raw_token(RIGHT_PARENTHESE) >> qi::raw_token(SEMI_COLON))
                                        [ qi::_val = build_super_call_statement_(qi::_1) ]
                                     ;

                this_call_statement = (qi::raw_token(THIS) >> qi::raw_token(LEFT_PARENTHESE) >> argument_list >> qi::raw_token(RIGHT_PARENTHESE) >> qi::raw_token(SEMI_COLON))
                                        [ qi::_val = build_this_call_statement_(qi::_1) ]
                                     ;

                throw_statement = (qi::raw_token(THROW) >> expression >> qi::raw_token(SEMI_COLON))
                                        [ qi::_val = build_throw_statement_(qi::_1) ]
                                ;
                
                if_then_statement = (qi::raw_token(IF) >> qi::raw_token(LEFT_PARENTHESE) >> expression >> qi::raw_token(RIGHT_PARENTHESE) >> statement)
                                        [ qi::_val = build_if_then_statement_(qi::_1, qi::_2) ]
                                  ;
                                        
                if_then_else_statement = (qi::raw_token(IF) >> qi::raw_token(LEFT_PARENTHESE) >> expression >> qi::raw_token(RIGHT_PARENTHESE) >> statement >> qi::raw_token(ELSE) >> statement)
                                        [ qi::_val = build_if_then_else_statement_(qi::_1, qi::_2, qi::_3) ]
                                       ;

                while_statement = (qi::raw_token(WHILE) >> qi::raw_token(LEFT_PARENTHESE) >> expression >> qi::raw_token(RIGHT_PARENTHESE) >> statement)
                                        [ qi::_val = build_while_statement_(qi::_1, qi::_2) ]
                                ;

                for_statement = (qi::raw_token(FOR) >> qi::raw_token(LEFT_PARENTHESE) >> for_statement_init >> for_statement_condition >> for_statement_update >> qi::raw_token(RIGHT_PARENTHESE) >> statement)
                                        [ qi::_val = build_for_statement_(qi::_1, qi::_2, qi::_3, qi::_4) ]
                              ;

                for_statement_init = (qi::raw_token(SEMI_COLON))
                                        [ qi::_val = phoenix::new_<Ast::statement_empty>() ]
                                   | (expression_statement)
                                        [ qi::_val = qi::_1 ]
                                   | local_variable_declaration_statement
                                        [ qi::_val = qi::_1 ]
                                   ;

                for_statement_condition = (expression)
                                            [ qi::_val = qi::_1 ]
                                        | (qi::raw_token(SEMI_COLON))
                                            [ qi::_val = phoenix::new_<Ast::expression_boolean_constant>(true) ]
                                        ;

                for_statement_update = (statement_expression)
                                            [ qi::_val = build_for_statement_update_(qi::_1) ]
                                     | (qi::eps)
                                            [ qi::_val = phoenix::new_<Ast::statement_empty>() ]
                                     ;

                expression_statement = (statement_expression >> qi::raw_token(SEMI_COLON))
                                            [ qi::_val = build_expression_statement_(qi::_1) ]
                                     ;

                empty_statement = (qi::raw_token(SEMI_COLON))
                                            [ qi::_val = phoenix::new_<Ast::statement_empty>() ]
                                ;

                statement_without_trailing_substatement = (block_statement)
                                                            [ qi::_val = qi::_1 ]
                                                        | (empty_statement)
                                                            [ qi::_val = qi::_1 ]
                                                        | (expression_statement)
                                                            [ qi::_val = qi::_1 ]
                                                        | (return_statement)
                                                            [ qi::_val = qi::_1 ]
                                                        ;

                block_statement = (block)
                                    [ qi::_val = phoenix::new_<Ast::statement_block>(qi::_1) ]
                                ;

                return_statement = (qi::raw_token(RETURN) >> qi::raw_token(SEMI_COLON))
                                    [ qi::_val = phoenix::new_<Ast::statement_void_return>() ]
                                 | (qi::raw_token(RETURN) >> expression >> qi::raw_token(SEMI_COLON))
                                    [ qi::_val = phoenix::new_<Ast::statement_value_return>(qi::_1) ]
                                 ;

                parentheses_expression = (qi::raw_token(LEFT_PARENTHESE) >> expression >> qi::raw_token(RIGHT_PARENTHESE))
                                    [ qi::_val = phoenix::new_<Ast::expression_parentheses>(qi::_1) ]
                                       ;

                bracket_expression = (qi::raw_token(LEFT_BRACKET) >> expression >> qi::raw_token(RIGHT_BRACKET))
                                    [ qi::_val = qi::_1 ]
                            ;

                argument_list = (-(expression >> *(qi::raw_token(COMMA) >> expression)))
                                    [ qi::_val = build_argument_list_(qi::_1) ]
                              ;


                // MIDDLE

                literal = (integer_literal)     [ qi::_val = qi::_1 ]
                        | (character_literal)   [ qi::_val = qi::_1 ]
                        | (boolean_literal)     [ qi::_val = qi::_1 ]
                        | (string_literal)      [ qi::_val = qi::_1 ]
                        | (null_literal)        [ qi::_val = qi::_1 ]
                        ;
                
                integer_literal = (tok.decimal_literal)
                                   [ qi::_val = phoenix::new_<Ast::expression_integer_constant>(qi::_1) ]
                               ;

                character_literal = (tok.character_literal)
                                   [ qi::_val = phoenix::new_<Ast::expression_character_constant>(qi::_1) ]
                               ;

                string_literal = (tok.string_literal)
                                   [ qi::_val = phoenix::new_<Ast::expression_string_constant>(qi::_1) ]
                               ;

                boolean_literal = (qi::raw_token(TRUE_CONSTANT))
                                   [ qi::_val = phoenix::new_<Ast::expression_boolean_constant>(true) ]
                                | (qi::raw_token(FALSE_CONSTANT))
                                   [ qi::_val = phoenix::new_<Ast::expression_boolean_constant>(false) ]
                                ;
                
                null_literal = (qi::raw_token(NULL_CONSTANT))
                                 [ qi::_val = phoenix::new_<Ast::expression_null>() ]
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
        qi::rule<Iterator, Ast::declaration_field*()> field_declaration;
        qi::rule<Iterator, Maybe<const Ast::expression*>()> optional_variable_intializer;
        qi::rule<Iterator, Ast::declaration_method*()> method_declaration;
        qi::rule<Iterator, Maybe<Ast::body>()> optional_method_body;
        qi::rule<Iterator, Ast::body()> method_body;
        qi::rule<Iterator, Ast::declaration_constructor*()> constructor_declaration;
        qi::rule<Iterator, std::list<const Ast::statement*>()> constructor_body;
        qi::rule<Iterator, Ast::declaration_method*()> implicit_method_declaration;
        qi::rule<Iterator, std::list<Ast::formal_parameter>()> method_parameters;
        qi::rule<Iterator, std::list<Ast::formal_parameter>()> formal_parameter_list;
        qi::rule<Iterator, Ast::formal_parameter()> formal_parameter;
        qi::rule<Iterator, std::list<const Ast::namedtype*>()> throws_clause;
        qi::rule<Iterator, std::list<const Ast::statement*>()> block;
        qi::rule<Iterator, Ast::statement*()> statement_or_declaration;
        // TODO: Check the rule below, against the parser.mly file, something is
        // wrong
        qi::rule<Iterator, Ast::statement_local_declaration*()> local_variable_declaration_statement;
        qi::rule<Iterator, Ast::statement*()> statement;
        qi::rule<Iterator, Ast::statement_super_call*()> super_call_statement;
        qi::rule<Iterator, Ast::statement_this_call*()> this_call_statement;
        qi::rule<Iterator, Ast::statement_throw*()> throw_statement;
        qi::rule<Iterator, Ast::statement_if_then*()> if_then_statement;
        qi::rule<Iterator, Ast::statement_if_then_else*()> if_then_else_statement;
        qi::rule<Iterator, Ast::statement_while*()> while_statement;
        qi::rule<Iterator, Ast::statement_block*()> for_statement;
        qi::rule<Iterator, Ast::statement*()> for_statement_init;
        qi::rule<Iterator, Ast::expression*()> for_statement_condition;
        qi::rule<Iterator, Ast::statement*()> for_statement_update;
        qi::rule<Iterator, Ast::statement_expression*()> expression_statement;
        qi::rule<Iterator, Ast::statement_empty*()> empty_statement;
        qi::rule<Iterator, Ast::statement*()> statement_without_trailing_substatement;
        qi::rule<Iterator, Ast::statement_block*()> block_statement;
        qi::rule<Iterator, Ast::statement*()> return_statement;
        qi::rule<Iterator, Ast::expression_parentheses*()> parentheses_expression;
        qi::rule<Iterator, Ast::expression*()> bracket_expression;
        qi::rule<Iterator, std::list<const Ast::expression*>()> argument_list;
        // Missing declaration start
        // TODO: Check the apperently broken reachablility, in parser.mly
        qi::rule<Iterator, Ast::expression*()> expression;
        qi::rule<Iterator, Ast::expression*()> statement_expression;
        // Missing declaration stop
        qi::rule<Iterator, Ast::expression*()> literal;
        qi::rule<Iterator, Ast::expression_integer_constant*()> integer_literal;
        qi::rule<Iterator, Ast::expression_character_constant*()> character_literal;
        qi::rule<Iterator, Ast::expression_string_constant*()> string_literal;
        qi::rule<Iterator, Ast::expression_boolean_constant*()> boolean_literal;
        qi::rule<Iterator, Ast::expression_null*()> null_literal;
        qi::rule<Iterator, Ast::type_expression*()> typeexp;
        qi::rule<Iterator, Ast::type_expression*()> reference_typeexp;
        qi::rule<Iterator, Ast::type_expression_base*()> primitive_typeexp;
        qi::rule<Iterator, Ast::type_expression_named*()> named_typeexp;
        qi::rule<Iterator, Ast::type_expression_tarray*()> array_typeexp;
        // TODO: Shouldn't return a bool(), but rather an int, indicating the number
        // of matches of the rule
        qi::rule<Iterator, bool()> empty_brackets;
        qi::rule<Iterator, Ast::access*()> access;
        qi::rule<Iterator, Ast::name*()> name;
    };


    template<typename T>
    using parser = java_grammar<T>;
}

#endif // _PARSER_HPP
