#include "ast_helper.hpp"

#include <cassert>

// Enable declarations in case clauses, which are disabled by default
#define XTL_CLAUSE_DECL 1

#include <boost/variant.hpp>

namespace Ast
{
    std::list<identifier> name_to_identifier_list(name_simple    const& navn)
    {
        return { navn.name };
    }

    std::list<identifier> name_to_identifier_list(name_qualified const& navn)
    {
        return navn.name; 
    }

    std::list<identifier> name_to_identifier_list(name const& navn)
    {
        return 
        Match(navn, std::list<identifier>)
            Case(const name_simple& navn)    
            {
                return name_to_identifier_list(navn); 
            }
            Case(const name_qualified& navn)
            {
                return name_to_identifier_list(navn); 
            }
        EndMatch;
    }

    /** Convert a name to its string representation */
    std::string name_to_string(const name& navn)
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
    std::string type_decl_name(const type_declaration& td)
    {
        return 
        Match(td, std::string)
            Case(const type_declaration_class& klass)
            {
                return klass.name.identifier_string; 
            }
            Case(const type_declaration_interface& interface)
            {
                return interface.name.identifier_string;
            }
        EndMatch;
    }

    std::string type_decl_kind(const type_declaration& td)
    {
        return 
        Match(td, std::string)
            Case(const type_declaration_class&)
            {
                return "Class"; 
            }
            Case(const type_declaration_interface&) 
            {
                return "Interface"; 
            }
        EndMatch;
    }

    std::string access_to_string(const access& ass)
    {
        return 
        Match(ass, std::string)
            Case(const access_public) 
            {
                return "public"; 
            }
            Case(const access_protected) 
            {
                return "protected"; 
            }
        EndMatch;
    }

    std::string base_type_to_string(const type_expression_base& type)
    {
        return 
        Match(type, std::string)
            Case(base_type_void    const&) 
            {
                return "void";
            }
            Case(base_type_byte    const&) 
            {
                return "byte";
            }
            Case(base_type_short   const&) 
            {
                return "short";   
            }
            Case(base_type_int     const&) 
            {
                return "int";     
            }
            /*
            Case(base_type_long    const&) 
            {
                return "long";    
            }
            */
            Case(base_type_char    const&) 
            {
                return "char";    
            }
            /*
            Case(base_type_float   const&) 
            {
                return "float";   
            }
            Case(base_type_double  const&) 
            {
                return "double";  
            }
            */
            Case(base_type_boolean const&) 
            {
                return "boolean"; 
            }
        EndMatch;
    }

    std::string unop_to_string(const unop& uno)
    {
        return 
        Match(uno, std::string)
            Case(const unop_negate) 
            {
                return "-"; 
            }
            Case(const unop_complement) 
            { 
                return "~"; 
            }
        EndMatch;
    }

    std::string binop_to_string(const binop& bino)
    {
        return 
        Match(bino, std::string)
            Case(const binop_plus)   
            { 
                return "+";  
            } 
            Case(const binop_minus)  
            {
                return "-";  
            } 
            Case(const binop_times)  
            {
                return "*";  
            } 
            Case(const binop_divide) 
            {
                return "/";  
            } 
            Case(const binop_modulo) 
            {
                return "%";  
            } 
            Case(const binop_eq)          
            {
                return "=="; 
            } 
            Case(const binop_ne)          
            {
                return "!="; 
            } 
            Case(const binop_lt)          
            {
                return "<";  
            } 
            Case(const binop_le)          
            {
                return "<="; 
            } 
            Case(const binop_gt)          
            {
                return ">";  
            } 
            Case(const binop_ge)          
            {
                return ">="; 
            } 
            Case(const binop_and)         
            {
                return "&";  
            } 
            Case(const binop_or)          
            {
                return "|";  
            } 
            Case(const binop_xor)         
            {
                return "^";  
            } 
            Case(const binop_lazyand)     
            {
                return "&&"; 
            } 
            Case(const binop_lazyor)      
            {
                return "||";
            }
        EndMatch;
    }
}
