#ifndef _COMPILER_AST_HELPER_HPP
#define _COMPILER_AST_HELPER_HPP

#include "ast.hpp"

#include <string>

/************************************************************************/
/** {2 Helper functions for the AST}                                    */
/************************************************************************/
namespace Ast
{
    /** {3 Converstion helpers} */
    /** Convert a name to its string representation */
    std::string name_to_string(const name* navn);

    /** {3 Predicate helpers} */
    template<typename INPUT, typename T>
        bool generic_test(const INPUT& input)
        {
            try
            {
                dynamic_cast<T&>(input);
                return true;
            }
            catch(std::bad_cast bc)
            {
                return false;
            }
        }

    template<typename T>
        bool generic_type_test(const type_expression& arg)
        {
            return generic_test<type_expression, T>(arg);
        }

    template<typename T>
        bool generic_type_test_base(const type_expression& t)
        {
            try
            {
                const type_expression_base& type = dynamic_cast<const type_expression_base&>(t);
                dynamic_cast<T&>(type);
                return true;
            }
            catch(std::bad_cast bc)
            {
                return false;
            }
        }

    /* typeexp -> bool */
    const auto is_base_type   = generic_type_test<const type_expression_base>;
    const auto is_array       = generic_type_test<const type_expression_tarray>;
    const auto is_named_type  = generic_type_test<const type_expression_named>;

    const auto is_void    = generic_type_test_base<const base_type_void>;
    const auto is_byte    = generic_type_test_base<const base_type_byte>;
    const auto is_short   = generic_type_test_base<const base_type_short>;
    const auto is_int     = generic_type_test_base<const base_type_int>;
    const auto is_long    = generic_type_test_base<const base_type_long>;
    const auto is_char    = generic_type_test_base<const base_type_char>;
    const auto is_float   = generic_type_test_base<const base_type_float>;
    const auto is_double  = generic_type_test_base<const base_type_double>;
    const auto is_boolean = generic_type_test_base<const base_type_boolean>;

    /* exp -> bool */
    bool is_true_constant_throws(const expression& e);
    bool is_false_const(const expression& e);
    bool is_true_const(const expression& e);

    /* access -> bool */
    template<typename T>
        bool generic_access_test(const access& arg)
        {
            return generic_test<access, T>(arg);
        }

    const auto is_public      = generic_access_test<const access_public>;
    const auto is_protected   = generic_access_test<const access_protected>;

    /* decl -> bool */
    template<typename T>
        bool generic_declaration_test(const declaration& arg)
        {
            return generic_test<declaration, T>(arg);
        }

    const auto is_field       = generic_declaration_test<const declaration_field>;
    const auto is_method      = generic_declaration_test<const declaration_method>;
    const auto is_constructor = generic_declaration_test<const declaration_constructor>;

    /* type_decl -> bool */
    template<typename T>
        bool generic_type_declaration_test(const type_declaration& arg)
        {
            return generic_test<type_declaration, T>(arg);
        }

    const auto is_class       = generic_type_declaration_test<const type_declaration_class>;
    const auto is_interface   = generic_type_declaration_test<const type_declaration_interface>;

    /** {3 Accessor helpers}  */
    std::string type_decl_name(const type_declaration& td);
    LexerPosition type_decl_pos(const type_declaration& td);
    std::string type_decl_kind(const type_declaration& td);
    std::string access_to_string(const access* ass);
    std::string base_type_to_string(const base_type* type);
    std::string unop_to_string(const unop* uno);
    std::string binop_to_string(const binop* bino);
}

#endif //_COMPILER_AST_HELPER_HPP
