#ifndef WEBSOCKET_SERVER_H
#define WEBSOCKET_SERVER_H

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <memory>
#include <string>
#include <utilities/utilities.h>
namespace net = boost::asio;            // from <boost/asio.hpp>
namespace websocket = boost::beast::websocket;  // from <boost/beast/websocket.hpp>
using tcp = net::ip::tcp;               // from <boost/asio/ip/tcp.hpp>

// Forward declaration
class websocket_session;

class WebSocketServer {
public:
    WebSocketServer(net::io_context& ioc, tcp::endpoint endpoint);

    // Start the server
    void run();

private:
    net::io_context& ioc_;
    tcp::acceptor acceptor_;

    // Function to start accepting incoming connections
    void do_accept();

    // Function to handle a new connection
    void on_accept(boost::beast::error_code ec, tcp::socket socket);
};

#endif // WEBSOCKET_SERVER_H
