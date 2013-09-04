#include "ast_pp.hpp"

#include "ast_helper.hpp"

#include "utility.hpp"

// Enable declarations in case clauses, which are disabled by default
#define XTL_CLAUSE_DECL 1
#include "typeswitch/match.hpp"

#include <iostream>
#include <cassert>

namespace Ast
{
    // Type expressions
    void pretty_print(const type_expression* type)
    {
        Match(type)
        {
            Case(const type_expression_base type)
            {
                pretty_print(type);
            }
            
            Case(const type_expression_tarray type)
            {
                pretty_print(type);
            }
            
            Case(const type_expression_named type)
            {
                pretty_print(type);
            }
            
            Otherwise()
            {
                assert(false);
            }
        }
        EndMatch;
    }

    void pretty_print(const type_expression_base type)
    {
        const base_type* base_typ = type.type;
        std::cout << base_type_to_string(base_typ);
    }

    void pretty_print(const type_expression_tarray type)
    {
        pretty_print(type.type);
        std::cout << "[]";
    }

    void pretty_print(const type_expression_named type)
    {
        std::cout << name_to_string(type.type);
    }

    // L-Value
    void pretty_print(const lvalue* lvalue)
    {
        Match(lvalue)
        {
            Case(const lvalue_non_static_field lvalue)
            {
                pretty_print(lvalue);
            }

            Case(const lvalue_array lvalue)
            {
                pretty_print(lvalue);
            }

            Case(const lvalue_array lvalue)
            {
                pretty_print(lvalue);
            }

            Otherwise()
            {
                assert(false);
            }
        }
        EndMatch;
    }

    void pretty_print(const lvalue_non_static_field lvalue)
    {
        pretty_print(lvalue.exp);
        std::cout << "." << lvalue.name.identifier_string;
    }

    void pretty_print(const lvalue_array lvalue)
    {
        pretty_print(lvalue.array_exp);
        std::cout << "[";
        pretty_print(lvalue.index_exp);
        std::cout << "]";
    }

    void pretty_print(const lvalue_ambiguous_name lvalue)
    {
        std::cout << name_to_string(lvalue.ambiguous);
    }
    
    // Expressions
    void pretty_print(const expression* exp)
    {
        Match(exp)
        {
            Case(const expression_binop exp)
            {
                pretty_print(exp);
            }

            Case(const expression_unop exp)
            {
                pretty_print(exp);
            }

            Case(const expression_integer_constant exp)
            {
                pretty_print(exp);
            }

            Case(const expression_character_constant exp)
            {
                pretty_print(exp);
            }

            Case(const expression_string_constant exp)
            {
                pretty_print(exp);
            }

            Case(const expression_boolean_constant exp)
            {
                pretty_print(exp);
            }

            Case(const expression_null exp)
            {
                pretty_print(exp);
            }

            Case(const expression_this exp)
            {
                pretty_print(exp);
            }

            Case(const expression_static_invoke exp)
            {
                pretty_print(exp);
            }

            Case(const expression_non_static_invoke exp)
            {
                pretty_print(exp);
            }

            Case(const expression_simple_invoke exp)
            {
                pretty_print(exp);
            }

            Case(const expression_ambiguous_invoke exp)
            {
                pretty_print(exp);
            }

            Case(const expression_new exp)
            {
                pretty_print(exp);
            }

            Case(const expression_new_array exp)
            {
                pretty_print(exp);
            }

            Case(const expression_lvalue exp)
            {
                pretty_print(exp);
            }

            Case(const expression_assignment exp)
            {
                pretty_print(exp);
            }

            Case(const expression_incdec exp)
            {
                pretty_print(exp);
            }

            Case(const expression_cast exp)
            {
                pretty_print(exp);
            }

            Case(const expression_ambiguous_cast exp)
            {
                pretty_print(exp);
            }
            
            Case(const expression_instance_of exp)
            {
                pretty_print(exp);
            }
            
            Case(const expression_parentheses exp)
            {
                pretty_print(exp);
            }

            Otherwise()
            {
                assert(false);
            }
        }
        EndMatch;
    }

    void pretty_print(const expression_binop exp)
    {
        pretty_print(exp.operand1);
        std::cout << " " << binop_to_string(exp.operatur) << " ";
        pretty_print(exp.operand2);
    }

    void pretty_print(const expression_unop exp)
    {
        std::cout << unop_to_string(exp.operatur);
        pretty_print(exp.operand);
    }

    void pretty_print(const expression_integer_constant exp)
    {
        std::cout << exp.value;
    }

    void pretty_print(const expression_character_constant exp)
    {
        std::cout << exp.value;
    }

    void pretty_print(const expression_string_constant exp)
    {
        std::cout << exp.value;
    }

    void pretty_print(const expression_boolean_constant exp)
    {
        if(exp.value)
        {
            std::cout << "true";
        }
        else
        {
            std::cout << "false";
        }
    }

    void pretty_print(const expression_null)
    {
        std::cout << "null";
    }

    void pretty_print(const expression_this)
    {
        std::cout << "this";
    }

    void pretty_print(const expression_static_invoke exp)
    {
        std::cout << name_to_string(exp.type) << ".";
        std::cout << exp.method_name.identifier_string;
        std::cout << "(";
        //TODO: argument list
        std::cout << ")";
    }

    void pretty_print(const expression_non_static_invoke exp)
    {
        pretty_print(exp.context);
        std::cout << ".";
        std::cout << exp.method_name.identifier_string;
        std::cout << "(";
        //TODO: argument list
        std::cout << ")";
    }

    void pretty_print(const expression_simple_invoke exp)
    {
        std::cout << exp.method_name.identifier_string;
        std::cout << "(";
        //TODO: argument list
        std::cout << ")";
    }

    void pretty_print(const expression_ambiguous_invoke exp)
    {
        std::cout << name_to_string(exp.ambiguous) << ".";
        std::cout << exp.method_name.identifier_string;
        std::cout << "(";
        //TODO: argument list
        std::cout << ")";
    }

    void pretty_print(const expression_new exp)
    {
        std::cout << "new ";
        pretty_print(exp.type);
        std::cout << "(";
        //TODO: argument list
        std::cout << ")";
    }

    void pretty_print(const expression_new_array exp)
    {
        std::cout << "new ";
        pretty_print(exp.type);
        std::cout << "[]";
        std::cout << "(";
        //TODO: argument list
        std::cout << ")";
    }

    void pretty_print(const expression_lvalue exp)
    {
        pretty_print(exp.variable);
    }

    void pretty_print(const expression_assignment exp)
    {
        pretty_print(exp.variable);
        std::cout << " = ";
        pretty_print(exp.value);
    }

    void pretty_print(const expression_incdec exp)
    {
        Match(exp.operatur)
        {
            Case(const inc_dec_op_preinc op)
            {
                std::cout << "++";
                pretty_print(exp.variable);
            }

            Case(const inc_dec_op_predec op)
            {
                std::cout << "--";
                pretty_print(exp.variable);
            }

            Case(const inc_dec_op_postinc op)
            {
                pretty_print(exp.variable);
                std::cout << "++";
            }

            Case(const inc_dec_op_postdec op)
            {
                pretty_print(exp.variable);
                std::cout << "--";
            }

            Otherwise()
            {
                assert(false);
            }
        }
        EndMatch;
    }

    void pretty_print(const expression_cast exp)
    {
        std::cout << "(";
        pretty_print(exp.type);
        std::cout << ")";
        std::cout << " ";
        pretty_print(exp.value);
    }

    void pretty_print(const expression_ambiguous_cast exp)
    {
        std::cout << "(";
        pretty_print(exp.type);
        std::cout << ")";
        std::cout << " ";
        pretty_print(exp.value);
    }

    void pretty_print(const expression_instance_of exp)
    {
        pretty_print(exp.value);
        std::cout << " instanceof ";
        pretty_print(exp.type);
    }

    void pretty_print(const expression_parentheses exp)
    {
        std::cout << "(";
        pretty_print(exp.inside);
        std::cout << ")";
    }

    // Statements
    void pretty_print(const statement* stm)
    {
        Match(stm)
        {
            Case(const statement_expression stm)
            {
                pretty_print(stm);
            }
            
            Case(const statement_if_then stm)
            {
                pretty_print(stm);
            }

            Case(const statement_if_then_else stm)
            {
                pretty_print(stm);
            }
            
            Case(const statement_while stm)
            {
                pretty_print(stm);
            }

            Case(const statement_empty stm)
            {
                pretty_print(stm);
            }
            
            Case(const statement_block stm)
            {
                pretty_print(stm);
            }
            
            Case(const statement_void_return stm)
            {
                pretty_print(stm);
            }
            
            Case(const statement_value_return stm)
            {
                pretty_print(stm);
            }
            
            Case(const statement_local_declaration stm)
            {
                pretty_print(stm);
            }
            
            Case(const statement_throw stm)
            {
                pretty_print(stm);
            }
            
            Case(const statement_super_call stm)
            {
                pretty_print(stm);
            }
            
            Case(const statement_this_call stm)
            {
                pretty_print(stm);
            }
            
            Otherwise()
            {
                assert(false);
            }
        }
        EndMatch;
    }

    void pretty_print(const statement_expression stm)
    {
        // Print the expression
        pretty_print(stm.value);
        // Add a ";" as this is a statement.
        std::cout << ";";
    }

    void pretty_print(const statement_if_then stm)
    {
        // Print the condition
        std::cout << "if( ";
        pretty_print(stm.condition);
        std::cout << ")";
        // Print a newline for the 'If' body
        std::cout << std::endl;
        // Print the body
        pretty_print(stm.true_statement);
    }

    void pretty_print(const statement_if_then_else stm)
    {
        // Print the condition
        std::cout << "if( ";
        pretty_print(stm.condition);
        std::cout << ")";
        // Print a newline for the 'If' body
        std::cout << std::endl;
        // Print the true_body
        pretty_print(stm.true_statement);
        // Print the else,
        std::cout << std::endl << "else" << std::endl;
        // Print the false_body
        pretty_print(stm.false_statement);
    }

    void pretty_print(const statement_while stm)
    {
        // Print the condition
        std::cout << "while( ";
        pretty_print(stm.condition);
        std::cout << ")";
        // Print a newline for the 'If' body
        std::cout << std::endl;
        // Print the body
        pretty_print(stm.loop_statement);
    }

    void pretty_print(const statement_empty)
    {
        // Empty statement, simply print the semicolon
        std::cout << ";";
    }

    void pretty_print(const statement_block stm)
    {
        // Print the block start, brace
        std::cout << "{" << std::endl;
        // Print all the statments in the body
        unpack_list(stm.body, pretty_print);
        // Print the block end, brace
        std::cout << "}" << std::endl;
    }

    void pretty_print(const statement_void_return)
    {
        std::cout << "return;";
    }

    void pretty_print(const statement_value_return stm)
    {
        std::cout << "return ";
        pretty_print(stm.value);
        std::cout << ";";
    }
    
    void pretty_print(const statement_local_declaration stm)
    {
        pretty_print(stm.type);
        std::cout << " ";
        std::cout << stm.name.identifier_string;
        maybe_if(stm.optional_initializer, [](const expression* exp)
        {
            std::cout << " ";
            pretty_print(exp);
        });
        std::cout << ";";
    }

    void pretty_print(const statement_throw stm)
    {
        std::cout << "throw ";
        pretty_print(stm.throwee);
        std::cout << ";";
    }

    void pretty_print(const statement_super_call)
    {
        std::cout << "super(";
        // TODO: Implementation of expression list
        std::cout << ");";
    }
    
    void pretty_print(const statement_this_call)
    {
        std::cout << "this(";
        // TODO: Implementation of expression list
        std::cout << ");";
    }

    // Declarations
    void pretty_print(const declaration* decl)
    {
        Match(decl)
        {
            Case(const declaration_field field)
            {
                pretty_print(field);
            }
            
            Case(const declaration_method method)
            {
                pretty_print(method);
            }

            Case(const declaration_constructor constructor)
            {
                pretty_print(constructor);
            }
            
            Otherwise()
            {
                assert(false);
            }
        }
        EndMatch;
    }

    void pretty_print(const declaration_field field)
    {
        field_declaration info = field.decl;
        // Print our access modifier
        std::cout << access_to_string(info.access_type) << " ";
        // Print static, if we are
        if(info.is_static)
        {
            std::cout << "static ";
        }
        // Print final, if we are
        if(info.is_final)
        {
            std::cout << "final ";
        }
        // Pretty print the type
        pretty_print(info.type);
        std::cout << " ";
        // Print the name of the field
        std::cout << info.name.identifier_string;
        // Print the intializer if any
        maybe_if(info.optional_initializer, [](const expression* exp)
        {
            std::cout << " = ";
            pretty_print(exp);
        });
        std::cout << ";";
        // Newline for less messy'ness
        std::cout << std::endl;
    }

    void pretty_print(const declaration_method method)
    {
        method_declaration info = method.decl;
        // Print our access modifier
        std::cout << access_to_string(info.access_type) << " ";
        // Print static, if we are
        if(info.is_static)
        {
            std::cout << "static ";
        }
        // Print final, if we are
        if(info.is_final)
        {
            std::cout << "final ";
        }
        // Print abstract, if we are
        if(info.is_abstract)
        {
            std::cout << "abstract ";
        }
        // Pretty print the return-type
        pretty_print(info.return_type);
        std::cout << " ";
        // Print the name of the function
        std::cout << info.name.identifier_string;
        // Print parameteres, incapsulated in braces
        std::cout << "(";
        // TODO: Handle parameters
        std::cout << ")";
        // Print throws
        if(info.throws.empty() == false)
        {
            std::cout << " throws " << concat(info.throws, name_to_string, ", ");
        }
        // Print body (if any)
        maybe_if(info.method_body, [](body method_body)
        {
            // Print spacing, before body
            std::cout << std::endl;
            // Print body opening brace
            std::cout << "{" << std::endl;
            // Print statements one at a time
            unpack_list(method_body, pretty_print);
            // Print body closing brace
            std::cout << "}" << std::endl;
        }).otherwise([]()
        {
            std::cout << ";";
        });
        // Newline for less messy'ness
        std::cout << std::endl;
    }

    void pretty_print(const declaration_constructor constructor)
    {
        constructor_declaration info = constructor.decl;
        // Print our access modifier
        std::cout << access_to_string(info.access_type) << " ";
        // Print the name of the function
        std::cout << info.name.identifier_string;
        // Print parameteres, incapsulated in braces
        std::cout << "(";
        // TODO: Handle parameters
        std::cout << ")";
        // Print throws
        if(info.throws.empty() == false)
        {
            std::cout << " throws " << concat(info.throws, name_to_string, ", ");
        }
        // Print spacing, before body
        std::cout << std::endl;
        // Print body (if any)
        maybe_if(info.method_body, [](body method_body)
        {
            // Print spacing, before body
            std::cout << std::endl;
            // Print body opening brace
            std::cout << "{" << std::endl;
            // Print statements one at a time
            unpack_list(method_body, pretty_print);
            // Print body closing brace
            std::cout << "}" << std::endl;
        }).otherwise([]()
        {
            std::cout << ";";
        });
        // Newline for less messy'ness
        std::cout << std::endl;
    }

    // Type declarations
    void pretty_print(const type_declaration* type_decl)
    {
        Match(type_decl)
        {
            Case(const type_declaration_class klass)
            {
                pretty_print(klass);
            }

            Case(const type_declaration_interface interface)
            {
                pretty_print(interface);
            }
            
            Otherwise()
            {
                assert(false);
            }
        }
        EndMatch;
    }

    void pretty_print(const type_declaration_class klass)
    {
        // Get the info struct
        class_declaration info = klass.type;
        // Print final, if we are
        if(info.is_final)
        {
            std::cout << "final ";
        }
        // Print abstract, if we are
        if(info.is_abstract)
        {
            std::cout << "abstract ";
        }
        // Print the 'class' keyword, the class name, and the class we extend
        // (in non inheriting classes this will be java.lang.Object).
        std::cout << "class " << info.name.identifier_string << " extends " << name_to_string(info.extends);
        // If we're implementing anything
        if(info.implements.empty() == false)
        {
            // Then write out the 'implements' keyword, and a comma seperated
            // list of implements 
            std::cout << " implements ";
            std::cout << concat(info.implements, name_to_string, ", ");
        }
        // Newline because we like allman style
        std::cout << std::endl;
        // Start brace, and newline
        std::cout << "{" << std::endl;
        // Print all members
        unpack_list(info.members, pretty_print);
        // End brace, and newline
        std::cout << "}" << std::endl;
    }

    void pretty_print(const type_declaration_interface interface)
    {
        // Get the info struct
        interface_declaration info = interface.type;
        // Print the 'interface' keyword, and the interface name
        std::cout << "interface " << info.name.identifier_string;
        // If we're extend anything
        if(info.extends.empty() == false)
        {
            // Then write out the 'extends' keyword, and a comma seperated
            // list of extends 
            std::cout << " extends ";
            std::cout << concat(info.extends, name_to_string, ", ");
        }
        // Newline because we like allman style
        std::cout << std::endl;
        // Start brace, and newline
        std::cout << "{" << std::endl;
        // Print all members
        unpack_list(info.members, pretty_print);
        // End brace, and newline
        std::cout << "}" << std::endl;
    }

    // Import declarations
    void pretty_print(const import_declaration* import)
    {
        Match(import)
        {
            Case(const import_declaration_on_demand import)
            {
                pretty_print(import);
            }
            Case(const import_declaration_single import)
            {
                pretty_print(import);
            }

            Otherwise()
            {
                assert(false);
            }
        }
        EndMatch;
    }


    void pretty_print(const import_declaration_on_demand import)
    {
        const name* import_name = import.import;
        std::cout << "import " << name_to_string(import_name) << ".*;" << std::endl;
    }

    void pretty_print(const import_declaration_single import)
    {
        const name* import_name = import.import;
        std::cout << "import " << name_to_string(import_name) << "." << import.class_name.identifier_string << ";" << std::endl;
    }

    // Package declaration
    void pretty_print(const package_declaration* package)
    {
        std::cout << "package " << name_to_string(package) << ";" << std::endl;
    }

    // Source file
    void pretty_print(source_file sf)
    {
        // Start marker
        std::cout << ">>>> File: " << sf.name << " Start <<<<" << std::endl;

        // Print package declaration if any
        call_if(sf.package, pretty_print);
        // Print imports
        unpack_list(sf.imports, pretty_print);
        // Print the type, inside the file
        //pretty_print(sf.type);
        
        // End Marker
        std::cout << ">>>> File: " << sf.name << " End <<<<" << std::endl;
    }

    // Program
    void pretty_print(program prog)
    {
        std::cout << " *** " << "pretty printing Ast::program" << " *** " << std::endl;
        // Pretty print each source file in program
        unpack_list(prog, pretty_print);
    }
}
