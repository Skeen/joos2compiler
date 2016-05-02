#include "ast_helper.hpp"

#include <cassert>

// Enable declarations in case clauses, which are disabled by default
#define XTL_CLAUSE_DECL 1

#include <boost/variant.hpp>

namespace Ast
{
    std::list<identifier> name_to_identifier_list(name_simple    const& navn) { return { navn.name }; }
    std::list<identifier> name_to_identifier_list(name_qualified const& navn) { return navn.name; }

    std::list<identifier> name_to_identifier_list(name const& navn)
    {
        return boost::apply_visitor(make_visitor<std::list<identifier>>(
                    [] (const name_simple& navn)    { return name_to_identifier_list(navn); },
                    [] (const name_qualified& navn) { return name_to_identifier_list(navn); }
                    // todo catch all?
                    ), navn);
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
        return boost::apply_visitor(make_visitor<std::string>(
            [](const type_declaration_class& klass) { return klass.name.identifier_string; },
            [](const type_declaration_interface& interface) { return interface.name.identifier_string; }
            ), td);
    }

    std::string type_decl_kind(const type_declaration& td)
    {
        return boost::apply_visitor(make_visitor<std::string>(
            [](const type_declaration_class& klass) { return "Class"; },
            [](const type_declaration_interface& interface) { return "Interface"; }
            ), td);
    }

    std::string access_to_string(const access& ass)
    {
        return boost::apply_visitor(make_visitor<std::string>(
            [](const access_public as) { return "public"; },
            [](const access_protected as) { return "protected"; }
            ), ass);
    }

    std::string base_type_to_string(const type_expression_base& type)
    {
        return boost::apply_visitor(make_visitor<std::string>(
            [](base_type_void    const&) { return "void";    },
            [](base_type_byte    const&) { return "byte";    },
            [](base_type_short   const&) { return "short";   },
            [](base_type_int     const&) { return "int";     },
          //[](base_type_long    const&) { return "long";    },
            [](base_type_char    const&) { return "char";    },
          //[](base_type_float   const&) { return "float";   },
          //[](base_type_double  const&) { return "double";  },
            [](base_type_boolean const&) { return "boolean"; }
            //Otherwise() { assert(false); }
            ), type);
        return "";
    }

    std::string unop_to_string(const unop& uno)
    {
        return boost::apply_visitor(make_visitor<std::string>(
            [](const unop_negate neg) { return "-"; },
            [](const unop_complement com) { return "~"; }
            ), uno);
    }

    std::string binop_to_string(const binop& bino)
    {
        return boost::apply_visitor(make_visitor<std::string>(
            [](const binop_plus bino)   { return "+";  }, 
            [](const binop_minus bino)  { return "-";  }, 
            [](const binop_times bino)  { return "*";  }, 
            [](const binop_divide bino) { return "/";  }, 
            [](const binop_modulo bino) { return "%";  }, 
            [](const binop_eq)          { return "=="; }, 
            [](const binop_ne)          { return "!="; }, 
            [](const binop_lt)          { return "<";  }, 
            [](const binop_le)          { return "<="; }, 
            [](const binop_gt)          { return ">";  }, 
            [](const binop_ge)          { return ">="; }, 
            [](const binop_and)         { return "&";  }, 
            [](const binop_or)          { return "|";  }, 
            [](const binop_xor)         { return "^";  }, 
            [](const binop_lazyand)     { return "&&"; }, 
            [](const binop_lazyor)      { return "||"; }
            ), bino);
    }
}
