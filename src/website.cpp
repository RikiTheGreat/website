//
// Created by mahdi on 6/16/24.
//

#include "website.hpp"
#include <iostream>
#include <fstream>


WebSite::WebSite(boost::asio::io_context& io, unsigned short port): _io(io), _port(port) {}

void WebSite::start() noexcept {
    boost::asio::co_spawn(_io, this->do_listen(), boost::asio::detached);
}

boost::asio::awaitable<void> WebSite::do_listen() {
    boost::asio::ip::tcp::acceptor acceptor(_io,
        boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), _port));
    for(;;) {
        auto sock = co_await acceptor.async_accept(boost::asio::use_awaitable);
        boost::beast::tcp_stream client_stream (std::move(sock));
        boost::asio::co_spawn(_io, this->do_session(std::move(client_stream)), boost::asio::detached);
    }
}

boost::asio::awaitable<void> WebSite::do_session(boost::beast::tcp_stream client_stream) noexcept {
    try {
        boost::beast::flat_buffer buffer;
        boost::beast::http::request<boost::beast::http::string_body> request;

        co_await boost::beast::http::async_read(client_stream, buffer, request, boost::asio::use_awaitable);

        boost::beast::http::response<boost::beast::http::file_body> res_file;
        boost::beast::http::response<boost::beast::http::string_body> res_str;

        if(request.method() == boost::beast::http::verb::get) {
            res_file=  std::get<boost::beast::http::response<boost::beast::http::file_body>>(handle_request(request));
            co_await boost::beast::http::async_write(client_stream, res_file, boost::asio::use_awaitable);

        }else {
            res_str=
               std::get<boost::beast::http::response<boost::beast::http::string_body>>(handle_request(request));
            co_await boost::beast::http::async_write(client_stream, res_str, boost::asio::use_awaitable);
        }



    }catch(boost::system::system_error const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        exit(-1);
    }
}

Html_Response WebSite::handle_request(
    boost::beast::http::request<boost::beast::http::string_body> const &request) {
    boost::beast::http::file_body::value_type body;
    boost::beast::error_code e;
    boost::beast::http::status status = boost::beast::http::status::ok;


    if(request.method() == boost::beast::http::verb::get) {
        if(_html.does_page_exist(request.target())) {
            body.open(_html.get_page(request.target()).c_str(), boost::beast::file_mode::read, e);

        }else {
            status = boost::beast::http::status::not_found;
            body.open("templates/not_found.html", boost::beast::file_mode::read, e);
            if(e) {
                std::cerr << "Error: " << e.message() << std::endl;
                status = boost::beast::http::status::internal_server_error;
            }

        }

        boost::beast::http::response<boost::beast::http::file_body> response {
            std::piecewise_construct,
                std::make_tuple(std::move(body)),
                std::make_tuple(status, request.version()) };

        response.set(boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
        response.set(boost::beast::http::field::content_type, "text/html");
        response.content_length(body.size());
        response.keep_alive(request.keep_alive());

        return Html_Response(std::move(response));

    } else if(request.method() == boost::beast::http::verb::post) {
        boost::beast::http::response<boost::beast::http::string_body> response;
        if(_html.does_page_exist(request.target())) {
            std::ifstream html_file_stream(_html.get_page(request.target()));
            std::string data(std::istreambuf_iterator<char>(html_file_stream), {});
            if(auto index =request.body().find("name="); index != std::string::npos) {
                std::string name = request.body().substr(index + 5, request.body().size());
                std::cout << "name: " << name << std::endl;
                data += "<h1> Hello " + name + "</h1>";
                response.body() = data;
                html_file_stream.close();


            }

        } // if file doesn't exist
        else {
            std::ifstream html_file_stream("templates/not_found.html");
            std::string data(std::istreambuf_iterator<char>(html_file_stream), {});
            response.body() = data;
        }


        response.version(11);
        response.result(status);
        response.set(boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
        response.set(boost::beast::http::field::content_type, "text/html");
        response.content_length(body.size());
        response.keep_alive(request.keep_alive());
        response.prepare_payload();

        return Html_Response(std::move(response));
    } // end of post request

    body.open("templates/what_is_this.html", boost::beast::file_mode::read, e);
    status = boost::beast::http::status::bad_request;

    boost::beast::http::response<boost::beast::http::file_body> response {
        std::piecewise_construct,
            std::make_tuple(std::move(body)),
            std::make_tuple(status, request.version()) };

    response.set(boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
    response.set(boost::beast::http::field::content_type, "text/html");
    response.content_length(body.size());
    response.keep_alive(request.keep_alive());

    return Html_Response(std::move(response));
}

