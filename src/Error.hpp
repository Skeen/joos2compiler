#ifndef _ERROR_HPP
#define _ERROR_HPP

#include <string>
#include <exception>

namespace Error
{
    struct Generic_Error : std::exception
    {
        private:
            std::string error_text;

        protected:
            Generic_Error(std::string error_text);
            Generic_Error(std::string error_text_init, std::string::iterator raw_input_start, std::string::iterator raw_input_end, std::string::iterator begin);
            /*
            Generic_Error(std::string error_text_init, std::string raw_input, std::string::iterator begin, std::string::iterator end);
            */
        public:
            const char* what() const noexcept final override;
            virtual ~Generic_Error() noexcept;
    };

    struct Syntax_Error : Generic_Error
    {
        Syntax_Error();
        Syntax_Error(std::string::iterator raw_input_start, std::string::iterator raw_input_end, std::string::iterator begin);
    };
}

#endif //_ERROR_HPP
