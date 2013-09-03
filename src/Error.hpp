#ifndef _ERROR_HPP
#define _ERROR_HPP

namespace Error
{
    struct Generic_Error : std::exception
    {
        private:
            const std::string error_text;
        protected:
            Generic_Error(std::string error_text)
                : error_text(error_text)
            {
            }
        public:
            const char* what() const noexcept final override
            {
                return error_text.c_str();
            }
            virtual ~Generic_Error() {}
    };

    struct Syntax_Error : Generic_Error
    {
        Syntax_Error(std::string issuing_string)
            : Generic_Error(std::string("Syntax Error: ").append(issuing_string))
        {
        }
    };
}

#endif //_ERROR_HPP
