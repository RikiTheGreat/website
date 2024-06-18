//
// Created by mahdi on 6/16/24.
//

#ifndef HTML_HPP
#define HTML_HPP

#include <map>
#include <string>
#include <boost/beast.hpp>
#include <string>



class Html {
public:
    [[nodiscard]] std::map<std::string, std::string> get_urls() const noexcept;
    bool does_page_exist(std::string const& page) noexcept;
    std::string get_page(std::string const& page) noexcept;
private:
     std::map<std::string, std::string> _urls {
        {"/", "./templates/index.html"},
         {"/about/", "./templates/about.html"},
         {"/about", "./templates/about.html"}
    };
};



#endif //HTML_HPP
