#include <iostream>
#include "website.hpp"

int main() {
    boost::asio::io_context io;
    WebSite website(io, 4444);
    website.start();
    io.run();
    return 0;
}
