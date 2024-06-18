set(SOURCES website.cpp website.hpp main.cpp html.cpp html.hpp)

add_executable(website ${SOURCES})
target_link_libraries(website PRIVATE Boost::asio Boost::beast)
file(COPY ./templates DESTINATION ${CMAKE_BINARY_DIR}/src)