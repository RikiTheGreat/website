//
// Created by mahdi on 6/16/24.
//

#include "html.hpp"
#include <filesystem>

std::map<std::string, std::string> Html::get_urls() const noexcept{
    return this->_urls;
}

bool Html::does_page_exist(std::string const &page) noexcept {
    if(const auto it = _urls.find(page); it!= _urls.end()) return true;

    return false;
}

std::string Html::get_page(std::string const &page) noexcept {
    if(does_page_exist(page))
        return _urls[page];

    return "";
}
