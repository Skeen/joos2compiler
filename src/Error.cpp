#include "Error.hpp"

#include "to_string.hpp"

#include <iostream>

namespace Error
{
    Generic_Error::Generic_Error(std::string error_text)
        : error_text(error_text)
    {
    }

    Generic_Error::Generic_Error(std::string error_text_init, std::string::iterator begin, std::string::iterator end, std::string::iterator issue)
    {
        // Get the error text string
        error_text = error_text_init;
        error_text.append(":\n");

        // Create a string, from the beginning of our input, to the issue
        std::string start_input(begin, issue);
        // Now let's detect the last line break, before the line, where begin is
        std::string::iterator line_start;
        // Search for the last newline
        size_t found = start_input.find_last_of("\n");
        // If we didnt find one;
        if(found == std::string::npos)
        {
            // Use the beginning of the file
            line_start = begin;
        }
        // If we found one
        else
        {
            // Let's set line start to the character after that
            line_start = begin + found + 1;
        }
        // At this point line_start points to the first character of the faulty line
        // We'll save this for later!

        // Create a string, form the issue, to the end of our input
        std::string end_input(issue, end);
        // Now let's detect the first line break, after the line, where begin is
        std::string::iterator line_end;
        // Search for the first newline
        found = end_input.find_first_of("\n");
        // If we didnt find one;
        if(found == std::string::npos)
        {
            // Use the end of the file
            line_end = end;
        }
        // If we found one
        else
        {
            // Let's set line end to the character before that
            line_end = issue + found;
        }
        // At this point line_end points to the last character of the faulty line
        // Let's create a string, holding the exact faulty line
        std::string faulty_line(line_start, line_end);
        // Append the faulty line to the error_text
        error_text.append(faulty_line).append("\n");
        // Now let's find out where to put our fine small '^^^' to indicate the error
        // Let's find the number of characters from the start of the line, until
        // the issue;
        size_t num_required_spaces = std::distance(line_start, issue);
        // Then let's find the length of the rest of the error.
        size_t num_following_wedges = faulty_line.size() - num_required_spaces;
        // Now let's generate our string. (using fill constructors)
        std::string error_indicator_spacing(num_required_spaces, ' ');
        std::string error_indicator_indicator(num_following_wedges, '^');
        // And append this indicator to the error_text
        error_text.append(error_indicator_spacing).append(error_indicator_indicator).append("\n");


    }
    /*
       Generic_Error(std::string error_text_init, std::string raw_input, std::string::iterator begin, std::string::iterator end)
       {
       error_text = error_text_init;
       }
       */
    const char* Generic_Error::what() const noexcept
    {
        return error_text.c_str();
    }

    Generic_Error::~Generic_Error()
    {
    }

    Syntax_Error::Syntax_Error()
        : Generic_Error(std::string("Syntax Error"))
    {
    }            

    Syntax_Error::Syntax_Error(std::string::iterator raw_input_start, std::string::iterator raw_input_end, std::string::iterator begin)
        : Generic_Error(std::string("Syntax Error"), raw_input_start, raw_input_end, begin)
    {
    }
}

