#ifndef _COMPILER_AST_PP_HPP
#define _COMPILER_AST_PP_HPP

#include "ast.hpp"

namespace Ast
{
    // Type expressions
    void pretty_print(type_expression const& type);
    void pretty_print(type_expression_base const& type);
    void pretty_print(type_expression_tarray const& type);
    void pretty_print(type_expression_named const& type);
    
    // L-Value
    void pretty_print(lvalue const& lvalue);
    void pretty_print(lvalue_non_static_field const& lvalue);
    void pretty_print(lvalue_array const& lvalue);
    void pretty_print(lvalue_ambiguous_name const& lvalue);

    // Expressions
    void pretty_print(expression const& exp);
    void pretty_print(expression_binop const& exp);
    void pretty_print(expression_unop const& exp);
    void pretty_print(expression_integer_constant const& exp);
    void pretty_print(expression_character_constant const& exp);
    void pretty_print(expression_string_constant const& exp);
    void pretty_print(expression_boolean_constant const& exp);
    void pretty_print(expression_null const& exp);
    void pretty_print(expression_this const& exp);
    void pretty_print(expression_static_invoke const& exp);
    void pretty_print(expression_non_static_invoke const& exp);
    void pretty_print(expression_simple_invoke const& exp);
    void pretty_print(expression_ambiguous_invoke const& exp);
    void pretty_print(expression_new const& exp);
    void pretty_print(expression_new_array const& exp);
    void pretty_print(expression_lvalue const& exp);
    void pretty_print(expression_assignment const& exp);
    void pretty_print(expression_incdec const& exp);
    void pretty_print(expression_cast const& exp);
    void pretty_print(expression_ambiguous_cast const& exp);
    void pretty_print(expression_instance_of const& exp);
    void pretty_print(expression_parentheses const& exp);
    
    // Statements
    void pretty_print(statement const& stm);
    void pretty_print(statement_expression const& stm);
    void pretty_print(statement_if_then const& stm);
    void pretty_print(statement_if_then_else const& stm);
    void pretty_print(statement_while const& stm);
    void pretty_print(statement_empty const& stm);
    void pretty_print(statement_block const& stm);
    void pretty_print(statement_void_return const& stm);
    void pretty_print(statement_value_return const& stm);
    void pretty_print(statement_local_declaration const& stm);
    void pretty_print(statement_throw const& stm);
    void pretty_print(statement_super_call const& stm);
    void pretty_print(statement_this_call const& stm);

    // Declarations
    void pretty_print(declaration const& decl);
    void pretty_print(declaration_field const& field);
    void pretty_print(declaration_method const& method);
    void pretty_print(declaration_constructor const& constructor);

    // Type declarations
    void pretty_print(type_declaration const& type_decl);
    void pretty_print(type_declaration_class const& klass);
    void pretty_print(type_declaration_interface const& interface);
    
    // Import declarations
    void pretty_print(import_declaration const& import);
    void pretty_print(import_declaration_on_demand const& import);
    void pretty_print(import_declaration_single const& import);

    // Package declaration
    void pretty_print(package_declaration const& package);

    // Source file
    void pretty_print(source_file const& sf);

    // Program
    void pretty_print(program const& prog);
}

#endif //_COMPILER_AST_PP_HPP
