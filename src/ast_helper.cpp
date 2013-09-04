#include "ast_helper.hpp"

#include <cassert>

// Enable declarations in case clauses, which are disabled by default
#define XTL_CLAUSE_DECL 1
#include "typeswitch/match.hpp"

namespace Ast
{
    std::list<identifier> name_to_identifier_list(name_simple navn)
    {
        std::list<identifier> output;
        output.push_back(navn.name);
        return output;
    }

    std::list<identifier> name_to_identifier_list(name_qualified navn)
    {
        return navn.name;
    }

    std::list<identifier> name_to_identifier_list(const name* navn)
    {
        Match(navn)
        {
            Case(const name_simple navn)
            {
                return name_to_identifier_list(navn);
            }

            Case(const name_qualified navn)
            {
                return name_to_identifier_list(navn);
            }

            When()
            {
                assert(false);
            }
        }
        EndMatch;
        return std::list<identifier>();
    }

    /** Convert a name to its string representation */
    std::string name_to_string(const name* navn)
    {
        // Get a list of identifiers
        std::list<identifier> identifiers = name_to_identifier_list(navn);
        // Generate output string
        std::string output_name = "";
        // Transform list of identifiers into a string
        for(identifier id : identifiers)
        {
            output_name.append(id.identifier_string);
            output_name.append(".");
        }
        // At this point, we've added a "." too much, let's remove it
        output_name.pop_back();
        return output_name;
    }

    /* exp -> bool */
    bool is_true_constant_throws(const expression& e)
    {
        const expression_boolean_constant& exp = dynamic_cast<const expression_boolean_constant&>(e);
        return exp.value;
    }

    bool is_false_const(const expression& e)
    {
        try
        {
            return !(is_true_constant_throws(e));
        }
        catch(std::bad_cast bc)
        {
            return false;
        }
    }

    bool is_true_const(const expression& e)
    {
        try
        {
            return is_true_constant_throws(e);
        }
        catch(std::bad_cast bc)
        {
            return false;
        }
    }

    std::string type_decl_name(const type_declaration& td)
    {
        Match(td)
        {
            Case(const type_declaration_class& klass)
            {
                return klass.type.name.identifier_string;
            }

            Case(const type_declaration_interface& interface)
            {
                return interface.type.name.identifier_string;
            }
            
            When()
            {
                assert(false);
            }
        }
        EndMatch;
        return "";
    }

    LexerPosition type_decl_pos(const type_declaration& td)
    {
        return td.position;
    }

    std::string type_decl_kind(const type_declaration& td)
    {
        Match(td)
        {
            Case(const type_declaration_class& klass)
            {
                return "Class";
            }

            Case(const type_declaration_interface& interface)
            {
                return "Interface";
            }
            
            When()
            {
                assert(false);
            }
        }
        EndMatch;
        return "";
    }

    std::string access_to_string(const access* ass)
    {
        Match(ass)
        {
            Case(const access_public as)
            {
                return "public";
            }

            Case(const access_protected as)
            {
                return "protected";
            }
            
            When()
            {
                assert(false);
            }
        }
        EndMatch;
        return "";
    }

    std::string base_type_to_string(const base_type* type)
    {
        Match(type)
        {
            Case(const base_type_void type)
            {
                return "void";
            }

            Case(const base_type_byte type)
            {
                return "byte";
            }

            Case(const base_type_short type)
            {
                return "short";
            }

            Case(const base_type_int type)
            {
                return "int";
            }

            Case(const base_type_long type)
            {
                return "long";
            }

            Case(const base_type_char type)
            {
                return "char";
            }

            Case(const base_type_float type)
            {
                return "float";
            }

            Case(const base_type_double type)
            {
                return "double";
            }

            Case(const base_type_boolean type)
            {
                return "boolean";
            }
            
            When()
            {
                assert(false);
            }
        }
        EndMatch;
        return "";
    }

    std::string unop_to_string(const unop* uno)
    {
        Match(uno)
        {
            Case(const unop_negate neg)
            {
                return "-";
            }

            Case(const unop_complement com)
            {
                return "~";
            }

            When()
            {
                assert(false);
            }
        }
        EndMatch;
        return "";
    }

    std::string binop_to_string(const binop* bino)
    {
        Match(bino)
        {
            Case(const binop_plus bino)
            {
                return "+";
            }

            Case(const binop_minus bino)
            {
                return "-";
            }
            
            Case(const binop_times bino)
            {
                return "*";
            }
            
            Case(const binop_divide bino)
            {
                return "/";
            }
            
            Case(const binop_modulo bino)
            {
                return "%";
            }

            When()
            {
                assert(false);
            }
        }
        EndMatch;
        return "";
    }
}






