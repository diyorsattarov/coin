#ifndef CLIENT_H
#define CLIENT_H
#include <string>
#include <cstdlib>
#include <iostream>
#include <random>

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <utilities/utilities.h>

namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = net::ip::tcp;

class WebSocketClient {
public:
    WebSocketClient(net::io_context& ioc, const std::string& host, const std::string& port);
    void send(const std::string& message);
    std::string receive();
    void close();

private:
    tcp::resolver resolver_;
    websocket::stream<tcp::socket> ws_;
};

std::string generate_hash();
#endif //CLIENT_H