//
// Created by mahdi on 6/16/24.
//

#include "html.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>

// Html_Response
//     Html::handle_request(boost::beast::http::request<boost::beast::http::string_body> const &request) {
//     if(request.method() == boost::beast::http::verb::get)
//         return this->handle_get_request(request);
//     else if(request.method() == boost::beast::http::verb::post)
//         return this->handle_post_request(request);
//     else
//         return this->handle_other_requests();
// }
//
// Html_Response
//     Html::handle_get_request(boost::beast::http::request<boost::beast::http::string_body> const &request) {
//     boost::beast::http::file_body::value_type body;
//     boost::beast::error_code e;
//     boost::beast::http::status status = boost::beast::http::status::ok;
//
//     if(const auto it = _urls.find(request.target()); it!= _urls.end()) {
//         body.open(it->second.c_str(), boost::beast::file_mode::read,e);
//         if(e) {
//             std::cerr << "Unknown error " << e.what();
//             status = boost::beast::http::status::internal_server_error;
//         }
//
//     }else {
//         std::cout << "page " << request.target() << " notfound" << std::endl;
//         body.open("templates/not_found.html", boost::beast::file_mode::read,e);
//         status = boost::beast::http::status::not_found;
//     }
//
//     return {status, (std::move(body))};
// }
//
//
// Html_Response
//     Html::handle_post_request(boost::beast::http::request<boost::beast::http::string_body> const &request) {
//     std::cout << "request.body " << request.body().c_str() << std::endl;
//     boost::beast::http::file_body::value_type body;
//     boost::beast::error_code e;
//     boost::beast::http::status status = boost::beast::http::status::ok;
//
//     if(const auto it = _urls.find(request.target()); it!= _urls.end()) {
//         body.open(it->second.c_str(), boost::beast::file_mode::read,e);
//         if(e) {
//             std::cerr << "Unknown error " << e.what();
//             status = boost::beast::http::status::internal_server_error;
//         }
//
//
//     }else {
//         std::cout << "page " << request.target() << " notfound" << std::endl;
//         body.open("templates/not_found.html", boost::beast::file_mode::read,e);
//         status = boost::beast::http::status::not_found;
//     }
//
//     return {status, (std::move(body))};
// }
//
// Html_Response Html::handle_other_requests() {
//
//     boost::beast::http::file_body::value_type body;
//     boost::beast::error_code e;
//     boost::beast::http::status status = boost::beast::http::status::bad_request;
//     body.open("templates/what_is_this.html", boost::beast::file_mode::read,e);
//     if(e) {
//         std::cerr << "Unknown error " << e.what();
//         status = boost::beast::http::status::internal_server_error;
//     }
//
//     return {status, (std::move(body))};
// }

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
