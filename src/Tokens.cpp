#include "Tokens.hpp"

#include <cassert>

std::string find_enum_type(unsigned value)
{
    switch(getOperationType(value))
    {
        case Specials:
            return "Specials";
        case Comments:
            return "Comments";
        case Keywords:
            return "Keywords";
        case Delimiters:
            return "Delimiters";
        case AssignmentAndLogic:
            return "AssignmentAndLogic";
        case Comparison:
            return "Comparison";
        case Arithmetic:
            return "Arithmetic";
        case Literals:
            return "Literals";
        case Identifier:
            return "Identifier";
        default:
            assert("false");
    }
}
