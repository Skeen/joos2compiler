#include "ast_pp.hpp"
#include "ast_helper.hpp"
#include "utility.hpp"

// Enable declarations in case clauses, which are disabled by default
#define XTL_CLAUSE_DECL 1

#include <iostream>
#include <cassert>

namespace Ast
{
    // Type expressions
    void pretty_print(type_expression const& type)
    {
        ApplyForAll(type, void, pretty_print);
    }

    void pretty_print(type_expression_base const& type)
    {
        std::cout << base_type_to_string(type);
    }

    void pretty_print(type_expression_tarray const& type)
    {
        pretty_print(type.type);
        std::cout << "[]";
    }

    void pretty_print(type_expression_named const& type)
    {
        std::cout << name_to_string(type.type);
    }

    // L-Value
    void pretty_print(lvalue const& lvalue)
    {
        ApplyForAll(lvalue, void, pretty_print);
    }

    void pretty_print(lvalue_non_static_field const& lvalue)
    {
        pretty_print(lvalue.exp);
        std::cout << "." << lvalue.name.identifier_string;
    }

    void pretty_print(lvalue_array const& lvalue)
    {
        pretty_print(lvalue.array_exp);
        std::cout << "[";
        pretty_print(lvalue.index_exp);
        std::cout << "]";
    }

    void pretty_print(lvalue_ambiguous_name const& lvalue)
    {
        std::cout << name_to_string(lvalue.ambiguous);
    }
    
    // Expressions
    void pretty_print(expression const& exp)
    {
        ApplyForAll(exp, void, pretty_print);
    }

    void pretty_print(expression_binop const& exp)
    {
        pretty_print(exp.operand1);
        std::cout << " " << binop_to_string(exp.operatur) << " ";
        pretty_print(exp.operand2);
    }

    void pretty_print(expression_unop const& exp)
    {
        std::cout << unop_to_string(exp.operatur);
        pretty_print(exp.operand);
    }

    void pretty_print(expression_integer_constant const& exp)
    {
        std::cout << exp.value;
    }

    void pretty_print(expression_character_constant const& exp)
    {
        std::cout << exp.value;
    }

    void pretty_print(expression_string_constant const& exp)
    {
        std::cout << exp.value;
    }

    void pretty_print(expression_boolean_constant const& exp)
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

    void pretty_print(expression_null const&)
    {
        std::cout << "null";
    }

    void pretty_print(expression_this const&)
    {
        std::cout << "this";
    }

    void pretty_print(expression_static_invoke const& exp)
    {
        std::cout << name_to_string(exp.type) << ".";
        std::cout << exp.method_name.identifier_string;
        std::cout << "(";
        //TODO: argument list
        std::cout << ")";
    }

    void pretty_print(expression_non_static_invoke const& exp)
    {
        pretty_print(exp.context);
        std::cout << ".";
        std::cout << exp.method_name.identifier_string;
        std::cout << "(";
        //TODO: argument list
        std::cout << ")";
    }

    void pretty_print(expression_simple_invoke const& exp)
    {
        std::cout << exp.method_name.identifier_string;
        std::cout << "(";
        //TODO: argument list
        std::cout << ")";
    }

    void pretty_print(expression_ambiguous_invoke const& exp)
    {
        std::cout << name_to_string(exp.ambiguous) << ".";
        std::cout << exp.method_name.identifier_string;
        std::cout << "(";
        //TODO: argument list
        std::cout << ")";
    }

    void pretty_print(expression_new const& exp)
    {
        std::cout << "new ";
        pretty_print(exp.type);
        std::cout << "(";
        //TODO: argument list
        std::cout << ")";
    }

    void pretty_print(expression_new_array const& exp)
    {
        std::cout << "new ";
        pretty_print(exp.type);
        std::cout << "[]";
        std::cout << "(";
        //TODO: argument list
        std::cout << ")";
    }

    void pretty_print(expression_lvalue const& exp)
    {
        pretty_print(exp.variable);
    }

    void pretty_print(expression_assignment const& exp)
    {
        pretty_print(exp.variable);
        std::cout << " = ";
        pretty_print(exp.value);
    }

    void pretty_print(expression_incdec const& exp)
    {
        Match(exp.operatur, void)
            Case(inc_dec_op_preinc const&)  
            { 
                std::cout << "++";
                pretty_print(exp.variable); 
            }
            Case(inc_dec_op_predec const&)  
            {
                std::cout << "--"; 
                pretty_print(exp.variable); 
            } 
            Case(inc_dec_op_postinc const&) 
            {
                pretty_print(exp.variable); 
                std::cout << "++"; 
            } 
            Case(inc_dec_op_postdec const&) 
            {
                pretty_print(exp.variable); 
                std::cout << "--"; 
            }
        EndMatch;
    }

    void pretty_print(expression_cast const& exp)
    {
        std::cout << "(";
        pretty_print(exp.type);
        std::cout << ")";
        std::cout << " ";
        pretty_print(exp.value);
    }

    void pretty_print(expression_ambiguous_cast const& exp)
    {
        std::cout << "(";
        pretty_print(exp.type);
        std::cout << ")";
        std::cout << " ";
        pretty_print(exp.value);
    }

    void pretty_print(expression_instance_of const& exp)
    {
        pretty_print(exp.value);
        std::cout << " instanceof ";
        pretty_print(exp.type);
    }

    void pretty_print(expression_parentheses const& exp)
    {
        std::cout << "(";
        pretty_print(exp.inside);
        std::cout << ")";
    }

    // Statements
    void pretty_print(statement const& stm)
    {
        ApplyForAll(stm, void, pretty_print);
    }

    void pretty_print(statement_expression const& stm)
    {
        // Print the expression
        pretty_print(stm.value);
        // Add a ";" as this is a statement.
        std::cout << ";";
    }

    void pretty_print(statement_if_then const& stm)
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

    void pretty_print(statement_if_then_else const& stm)
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

    void pretty_print(statement_while const& stm)
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

    void pretty_print(statement_empty const&)
    {
        // Empty statement, simply print the semicolon
        std::cout << ";";
    }

    void pretty_print(statement_block const& stm)
    {
        // Print the block start, brace
        std::cout << "{" << std::endl;
        // Print all the statments in the body
        for(auto& substm : stm.body) 
        {
	        pretty_print(substm);
        }
        // Print the block end, brace
        std::cout << "}" << std::endl;
    }

    void pretty_print(statement_void_return const&)
    {
        std::cout << "return;";
    }

    void pretty_print(statement_value_return const& stm)
    {
        std::cout << "return ";
        pretty_print(stm.value);
        std::cout << ";";
    }
    
    void pretty_print(statement_local_declaration const& stm)
    {
        pretty_print(stm.type);
        std::cout << " ";
        std::cout << stm.name.identifier_string;
        if (stm.optional_initializer)
        {
            std::cout << " ";
            pretty_print(*stm.optional_initializer);
        }
        std::cout << ";";
    }

    void pretty_print(statement_throw const& stm)
    {
        std::cout << "throw ";
        pretty_print(stm.throwee);
        std::cout << ";";
    }

    void pretty_print(statement_super_call const&)
    {
        std::cout << "super(";
        // TODO: Implementation of expression list
        std::cout << ");";
    }
    
    void pretty_print(statement_this_call const&)
    {
        std::cout << "this(";
        // TODO: Implementation of expression list
        std::cout << ");";
    }

    // Declarations
    void pretty_print(declaration const& decl)
    {
        ApplyForAll(decl, void, pretty_print);
    }

    void pretty_print(declaration_field const& field)
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
        if (info.optional_initializer)
        {
            std::cout << " = ";
            pretty_print(*info.optional_initializer);
        }
        std::cout << ";";
        // Newline for less messy'ness
        std::cout << std::endl;
    }

    void pretty_print(declaration_method const& method)
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
            //std::cout << " throws " << concat(info.throws, name_to_string, ", "); // TODO FIXME
        }
        // Print body (if any)
        if (info.method_body)
        {
            body const& method_body = *info.method_body;

            // Print spacing, before body
            std::cout << std::endl;
            // Print body opening brace
            std::cout << "{" << std::endl;
            // Print statements one at a time
            for(auto& substm : method_body) 
            {
                pretty_print(substm);
            }
            // Print body closing brace
            std::cout << "}" << std::endl;
        }
        else
        {
            std::cout << ";";
        }
        // Newline for less messy'ness
        std::cout << std::endl;
    }

    void pretty_print(declaration_constructor const& constructor)
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
            //std::cout << " throws " << concat(info.throws, name_to_string, ", "); // TODO FIXME
        }
        // Print spacing, before body
        std::cout << std::endl;
        // Print body (if any)
        if(info.method_body)
        {
            body const& method_body = *info.method_body;
            // Print spacing, before body
            std::cout << std::endl;
            // Print body opening brace
            std::cout << "{" << std::endl;
            // Print statements one at a time
            for(auto& substm : method_body) 
            {
                pretty_print(substm);
            }
            // Print body closing brace
            std::cout << "}" << std::endl;
        }
        else
        {
            std::cout << ";";
        }
        // Newline for less messy'ness
        std::cout << std::endl;
    }

    // Type declarations
    void pretty_print(type_declaration const& type_decl)
    {
        ApplyForAll(type_decl, void, pretty_print);
    }

    void pretty_print(type_declaration_class const& klass)
    {
        // Get the info struct
        class_declaration info = klass;
        // Always public
        std::cout << "public ";
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
            //std::cout << " implements " << concat(info.implements, name_to_string, ", ");  // TODO FIXME
        }
        // Newline because we like allman style
        std::cout << std::endl;
        // Start brace, and newline
        std::cout << "{" << std::endl;
        // Print all members
        for(auto& mem : info.members) 
        {
	        pretty_print(mem);
        }
        // End brace, and newline
        std::cout << "}" << std::endl;
    }

    void pretty_print(type_declaration_interface const& interface)
    {
        // Get the info struct
        interface_declaration info = interface;
        // Always public
        std::cout << "public ";
        // Print the 'interface' keyword, and the interface name
        std::cout << "interface " << info.name.identifier_string;
        // If we're extend anything
        if(info.extends.empty() == false)
        {
            // Then write out the 'extends' keyword, and a comma seperated
            // list of extends 
            //std::cout << " extends " << concat(info.extends, name_to_string, ", "); // TODO FIXME
        }
        // Newline because we like allman style
        std::cout << std::endl;
        // Start brace, and newline
        std::cout << "{" << std::endl;
        // Print all members
        for(auto& mem : info.members) 
        {
	        pretty_print(mem);
        }
        // End brace, and newline
        std::cout << "}" << std::endl;
    }

    // Import declarations
    void pretty_print(import_declaration const& import)
    {
        ApplyForAll(import, void, pretty_print);
    }

    void pretty_print(import_declaration_on_demand const& import)
    {
        name const& import_name = import.import;
        std::cout << "import " << name_to_string(import_name) << ".*;" << std::endl;
    }

    void pretty_print(import_declaration_single const& import)
    {
        name const& import_name = import.import;
        std::cout << "import " << name_to_string(import_name) << "." << import.class_name.identifier_string << ";" << std::endl;
    }

    // Package declaration
    void pretty_print(package_declaration const& package)
    {
        std::cout << "package " << name_to_string(package) << ";" << std::endl;
    }

    // Source file
    void pretty_print(source_file const& sf)
    {
        // Start marker
        std::cout << ">>>> File: " << sf.name << " Start <<<<" << std::endl;

        // Print package declaration if any
        if(sf.package) 
	    pretty_print(*sf.package);
        // Print imports
        for(auto& i : sf.imports)
        {
            pretty_print(i);
        }
        // Print the type, inside the file
        pretty_print(sf.type);
        
        // End Marker
        std::cout << ">>>> File: " << sf.name << " End <<<<" << std::endl;
    }

    // Program
    void pretty_print(program const& prog)
    {
        std::cout << " *** " << "pretty printing Ast::program" << " *** " << std::endl;
        // Pretty print each source file in program
        for(auto& file : prog)
        {
            pretty_print(file);
        }
    }
}
