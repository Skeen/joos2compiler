#ifndef _COMPILER_AST_HPP
#define _COMPILER_AST_HPP

#include "Lexer_Position.hpp"
#include "utility.hpp"

#include <boost/fusion/adapted/struct.hpp>

#include <string>
#include <list>
#include <utility>

#include "Match/algebraic_datatype.hpp"

/************************************************************************/
/** AST type produced by the parser                                     */
/************************************************************************/
/** PASSES JOOS1 AND JOOS2 */
namespace Ast
{
    struct identifier
    {
        identifier() = default;
        identifier(identifier const&) = default;
        identifier(std::string s) : identifier_string(std::move(s)) {}
        std::string identifier_string;
    };

    struct name_simple final
    {
        identifier name;
    };

    struct name_qualified final
    {
        std::list<identifier> name;
    };

    using name      = algebraic_datatype<name_simple, name_qualified>;
    using namedtype = name;

    /* *************** Types *************** */
    template<typename Tag>
    struct base_type_generator
    {
    };

    using base_type_void     = base_type_generator<struct void_tag>;
    using base_type_byte     = base_type_generator<struct byte_tag>;
    using base_type_short    = base_type_generator<struct short_tag>;
    using base_type_int      = base_type_generator<struct int_tag>;
    //using base_type_long   = base_type_generator<struct long_tag>;
    using base_type_char     = base_type_generator<struct char_tag>;
    //using base_type_float  = base_type_generator<struct float_tag>;
    //using base_type_double = base_type_generator<struct double_tag>;
    using base_type_boolean  = base_type_generator<struct boolean_tag>;

    using type_expression_base = algebraic_datatype<
        base_type_void,
        base_type_byte,
        base_type_short,
        base_type_int,
        //base_type_long,
        base_type_char,
        //base_type_float,
        //base_type_double,
        base_type_boolean>;

    struct type_expression_tarray;
    
    struct type_expression_named final
    {
        type_expression_named() = default;
        type_expression_named(type_expression_named const&) = default;
        type_expression_named(namedtype t) : type(std::move(t)) {}
        namedtype type;
    };

    using type_expression = algebraic_datatype<
        type_expression_base,
        type_expression_named,
        algebraic_recursive<type_expression_tarray>>;

    struct type_expression_tarray final
    {
        type_expression type;
    };
    
    /* *************** Operators *************** */
    // Binary operators
    template<typename Tag>
    struct binop_generator
    {
    };
    // Arithmetic operators
    using binop_plus    = binop_generator<struct tag_binop_plus>;
    using binop_minus   = binop_generator<struct tag_binop_minus>;
    using binop_times   = binop_generator<struct tag_binop_times>;
    using binop_divide  = binop_generator<struct tag_binop_divide>;
    using binop_modulo  = binop_generator<struct tag_binop_modulo>;
    // Comparison operators
    using binop_eq      = binop_generator<struct tag_binop_eq>;
    using binop_ne      = binop_generator<struct tag_binop_ne>;
    using binop_lt      = binop_generator<struct tag_binop_lt>;
    using binop_le      = binop_generator<struct tag_binop_le>;
    using binop_gt      = binop_generator<struct tag_binop_gt>;
    using binop_ge      = binop_generator<struct tag_binop_ge>;
    using binop_and     = binop_generator<struct tag_binop_and>;
    using binop_or      = binop_generator<struct tag_binop_or>;
    // Binary operators
    using binop_xor     = binop_generator<struct tag_binop_xor>;
    using binop_lazyand = binop_generator<struct tag_binop_lazyand>;
    using binop_lazyor  = binop_generator<struct tag_binop_lazyor>;

    using binop = algebraic_datatype<
        // Arithmetic operators
        binop_plus, binop_minus, binop_times, binop_divide, binop_modulo,
        // Comparison operators
        binop_eq, binop_ne, binop_lt, binop_le, binop_gt, binop_ge, binop_and, binop_or,
        // Binary operators
        binop_xor, binop_lazyand, binop_lazyor>;

    // Unary operators
    template<typename Tag>
    struct unop_generator
    {
    };
    using unop_negate     = unop_generator<struct tag_unop_negate>;
    using unop_complement = unop_generator<struct tag_unop_complement>;

    using unop = algebraic_datatype<
        unop_negate,
        unop_complement>;

    // Increment/Decrement operators
    template<typename Tag>
    struct inc_dec_op_generator
    {
    };
    using inc_dec_op_preinc  = inc_dec_op_generator<struct tag_inc_dec_op_preinc>;
    using inc_dec_op_predec  = inc_dec_op_generator<struct tag_inc_dec_op_predec>;
    using inc_dec_op_postinc = inc_dec_op_generator<struct tag_inc_dec_op_postinc>;
    using inc_dec_op_postdec = inc_dec_op_generator<struct tag_inc_dec_op_postdec>;

    using inc_dec_op = algebraic_datatype<
        inc_dec_op_preinc,
        inc_dec_op_predec,
        inc_dec_op_postinc,
        inc_dec_op_postdec>;

    /* *************** Expressions *************** */
    // Prototype for expression;

    // L-Value
    struct lvalue_non_static_field;
    struct lvalue_array;
    struct lvalue_ambiguous_name final
    {
        name ambiguous;
    };

    using lvalue = algebraic_datatype<
        algebraic_recursive<lvalue_non_static_field>,
        algebraic_recursive<lvalue_array>>;

    // Expressions
    struct expression_integer_constant final
    {
        std::string value;
    };
    
    struct expression_character_constant final
    {
        std::string value;
    };

    struct expression_string_constant final
    {
        std::string value;
    };

    struct expression_boolean_constant final
    {
        bool value;
    };

    struct expression_null final
    {
    };

    struct expression_this final
    {
    };

    struct expression_ambiguous_cast;
    struct expression_ambiguous_invoke;
    struct expression_assignment;
    struct expression_binop;
    struct expression_boolean_constant;
    struct expression_cast;
    struct expression_incdec;
    struct expression_instance_of;
    struct expression_integer_constant;
    struct expression_lvalue;
    struct expression_new;
    struct expression_new_array;
    struct expression_non_static_invoke;
    struct expression_null;
    struct expression_parentheses;
    struct expression_simple_invoke;
    struct expression_static_invoke;
    struct expression_string_constant;
    struct expression_this;
    struct expression_unop;

    using expression = algebraic_datatype<
        expression_integer_constant,
        expression_string_constant,
        expression_boolean_constant,
        expression_null,
        expression_this,
        lvalue_ambiguous_name,
        // Recursive members
        algebraic_recursive<expression_binop>,
        algebraic_recursive<expression_unop>,
        algebraic_recursive<expression_static_invoke>,
        algebraic_recursive<expression_non_static_invoke>,
        algebraic_recursive<expression_simple_invoke>,
        algebraic_recursive<expression_ambiguous_invoke>,
        algebraic_recursive<expression_instance_of>,
        algebraic_recursive<expression_parentheses>,
        algebraic_recursive<lvalue_non_static_field>,
        algebraic_recursive<lvalue_array>,
        algebraic_recursive<expression_binop>,
        algebraic_recursive<expression_unop>,
        algebraic_recursive<expression_static_invoke>,
        algebraic_recursive<expression_non_static_invoke>,
        algebraic_recursive<expression_simple_invoke>,
        algebraic_recursive<expression_ambiguous_invoke>,
        algebraic_recursive<expression_new>,
        algebraic_recursive<expression_new_array>,
        algebraic_recursive<expression_lvalue>,
        algebraic_recursive<expression_assignment>,
        algebraic_recursive<expression_incdec>,
        algebraic_recursive<expression_cast>,
        algebraic_recursive<expression_ambiguous_cast>,
        algebraic_recursive<expression_instance_of>
        >;

    struct lvalue_non_static_field final
    {
        expression exp;
        identifier name;
    };

    struct lvalue_array final
    {
        expression array_exp;
        expression index_exp;
    };
    
    struct expression_binop final
    {
        expression operand1;
        binop      operatur;
        expression operand2;
    };

    struct expression_unop final
    {
        unop       operatur;
        expression operand;
    };

    struct expression_static_invoke final
    {
        namedtype             type;
        identifier            method_name;
        std::list<expression> arguments;
    };

    struct expression_non_static_invoke final
    {
        expression            context;
        identifier            method_name;
        std::list<expression> arguments;
    };

    struct expression_simple_invoke final
    {
        identifier            method_name;
        std::list<expression> arguments;
    };

    struct expression_ambiguous_invoke final
    {
        name                  ambiguous;
        identifier            method_name;
        std::list<expression> arguments;
    };
    
    struct expression_new final
    {
        type_expression       type;
        std::list<expression> arguments;
    };
    
    struct expression_new_array final
    {
        type_expression              type;
        expression                   context;
        std::list<Maybe<expression>> arguments;
    };
    
    struct expression_lvalue final
    {
        lvalue variable;
    };
    
    struct expression_assignment final
    {
        lvalue     variable;
        expression value;
    };
    
    struct expression_incdec final
    {
        lvalue     variable;
        inc_dec_op operatur;
    };
    
    struct expression_cast final
    {
        type_expression type;
        expression      value;
    };
    
    struct expression_ambiguous_cast final
    {
        expression type;
        expression value;
    };

    struct expression_instance_of final
    {
        expression      value;
        type_expression type;
    };

    struct expression_parentheses final
    {
        expression inside;
    };

    /* *************** Blocks and statements *************** */
    // Prototype
    struct statement_expression final
    {
        expression value;
    };

    struct statement_empty final
    {
    };

    struct statement_void_return final
    {
    };

    struct statement_value_return final
    {
        expression value;
    };

    struct statement_local_declaration final
    {
        type_expression type;
        identifier name;
        Maybe<expression> optional_initializer;
    };

    struct statement_throw final
    {
        expression throwee;
    };
    
    struct statement_super_call final
    {
        std::list<expression> arguments;
    };
    
    struct statement_this_call final
    {
        std::list<expression> arguments;
    };

    struct statement_if_then;
    struct statement_if_then_else;
    
    struct statement_while;
    struct statement_block;

    using statement = algebraic_datatype<
        statement_expression,
        statement_empty,
        statement_void_return,
        statement_value_return,
        statement_local_declaration,
        statement_throw,
        statement_super_call,
        statement_this_call,
        // Recursive below
        algebraic_recursive<statement_if_then>,
        algebraic_recursive<statement_if_then_else>,
        algebraic_recursive<statement_while>,
        algebraic_recursive<statement_block>
    >;

    using block = std::list<statement>;

    struct statement_if_then final
    {
        expression condition;
        statement true_statement;
    };

    struct statement_if_then_else final
    {
        expression condition;
        statement true_statement;
        statement false_statement;
    };
    
    struct statement_while final
    {
        expression condition;
        statement loop_statement;
    };

    struct statement_block final
    {
        block body;
    };

    using body = block;

    /* *************** Package and imports **************** */
    using package_declaration = name;

    struct import_declaration_on_demand final
    {
        name import;
    };

    struct import_declaration_single final
    {
        //import_declaration_single() = default;
        name import;
        identifier class_name;
    };

    using import_declaration = algebraic_datatype<
        import_declaration_on_demand, 
        import_declaration_single>;

    /* *************** Field and method declarations *************** */
    template<typename Tag>
    struct access_specifier final
    {
    };

    using access_public    = access_specifier<struct access_public_tag>;
    using access_protected = access_specifier<struct access_protected_tag>;
    using access           = algebraic_datatype<
        access_public, 
        access_protected>;

    using formal_parameter = std::pair<expression, identifier>;

    struct field_declaration
    {
        access access_type;
        bool is_static;
        bool is_final;
        type_expression type;
        identifier name;
        Maybe<expression> optional_initializer;
    };

    struct method_declaration
    {
        access access_type;
        bool is_static;
        bool is_final;
        bool is_abstract;
        type_expression return_type;
        identifier name;
        std::list<formal_parameter> formal_parameters;
        std::list<namedtype> throws;
        Maybe<body> method_body;
    };

    struct constructor_declaration
    {
        access access_type;
        identifier name;
        std::list<formal_parameter> formal_parameters;
        std::list<namedtype> throws;
        Maybe<body> method_body;
    };

    struct declaration_field final
    {
        field_declaration decl;
    };

    struct declaration_method final
    {
        method_declaration decl;
    };

    struct declaration_constructor final
    {
        constructor_declaration decl;
    };

    using declaration = algebraic_datatype<
        declaration_field, 
        declaration_method, 
        declaration_constructor>;

    /* *************** Type declarations **************** */
    struct class_declaration
    {
        bool is_final;
        bool is_abstract;
        identifier name;
        namedtype extends;
        std::list<namedtype> implements;
        std::list<declaration> members;
    };

    struct interface_declaration
    {
        identifier name;
        std::list<namedtype> extends;
        std::list<declaration> members;
    };

    using type_declaration = algebraic_datatype<
        class_declaration, 
        interface_declaration>;

    using type_declaration_class     = class_declaration;
    using type_declaration_interface = interface_declaration;

    /* *************** Programs **************** */
    struct source_file
    {
        std::string name;
        Maybe<package_declaration> package;
        std::list<import_declaration> imports;
        type_declaration type;
    };

    using program = std::list<source_file>;
}

BOOST_FUSION_ADAPT_STRUCT(Ast::source_file, (std::string, name)(Maybe<Ast::package_declaration>, package)
        (std::list<Ast::import_declaration>, imports)
        (Ast::type_declaration, type))

BOOST_FUSION_ADAPT_STRUCT(Ast::class_declaration, (bool, is_final)(bool, is_abstract)(Ast::identifier, name)
        (Ast::namedtype, extends)(std::list<Ast::namedtype>, implements)(std::list<Ast::declaration>, members))

BOOST_FUSION_ADAPT_STRUCT(Ast::interface_declaration, 
        (Ast::identifier, name)
        (std::list<Ast::namedtype>, extends)
        (std::list<Ast::declaration>, members))

#endif //_COMPILER_AST_HPP
