#include "Error.hpp"

#include "to_string.hpp"

#include <iostream>

namespace Error
{
    Generic_Error::Generic_Error(std::string error_text)
        : error_text(error_text)
    {
    }

    Generic_Error::Generic_Error(std::string error_text_init, std::string::iterator, std::string::iterator end, std::string::iterator issue)
    {
        error_text  = error_text_init;

        error_text.append(std::string(issue, end));
/*
        std::string::iterator line_start = raw_input_start;
        std::string::iterator line_end = raw_input_start;

        std::string raw_input(raw_input_start, raw_input_end);
        std::istringstream raw_input_stream(raw_input);

        while(raw_input_stream)
        {
            if(line_start < begin && begin < line_end)
            {
                std::cout << "FOUND";
                break;
            }
            std::string line;
            getline(raw_input_stream, line);

            line_start = line.begin();
            line_end = line.end();
        }

        std::string line(line_start, line_end);
        error_text.append(to_string(line.length()));
        //error_text.append(to_string(line_number));
        error_text.append("[");
        error_text.append(line);
        error_text.append("]");
        */
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
        : Generic_Error(std::string("Syntax Error:\n"))
    {
    }            

    Syntax_Error::Syntax_Error(std::string::iterator raw_input_start, std::string::iterator raw_input_end, std::string::iterator begin)
        : Generic_Error(std::string("Syntax Error:\n"), raw_input_start, raw_input_end, begin)
    {
    }
}

