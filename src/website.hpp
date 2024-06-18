//
// Created by mahdi on 6/16/24.
//

#ifndef WEBSITE_HPP
#define WEBSITE_HPP

#include <boost/beast.hpp>
#include <string_view>
#include <boost/asio.hpp>
#include "html.hpp"
#include <variant>
#include <any>


using Html_Response = std::variant<boost::beast::http::response<boost::beast::http::file_body>,
        boost::beast::http::response<boost::beast::http::string_body>>;

class WebSite {
public:
    WebSite(boost::asio::io_context& io, unsigned short port);
    void start() noexcept;
    boost::asio::awaitable<void> do_listen();
    boost::asio::awaitable<void> do_session(boost::beast::tcp_stream client_stream) noexcept;

private:
    Html_Response
        handle_request(boost::beast::http::request<boost::beast::http::string_body> const& request);
private:
    boost::asio::io_context& _io;
    unsigned short _port{};
    Html _html;

};
#endif //WEBSITE_HPP
