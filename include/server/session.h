#ifndef WEBSOCKET_SESSION_H
#define WEBSOCKET_SESSION_H
#include <memory>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <utilities/utilities.h>
namespace net = boost::asio;            // from <boost/asio.hpp>
namespace websocket = boost::beast::websocket;  // from <boost/beast/websocket.hpp>
using tcp = net::ip::tcp;               // from <boost/asio/ip/tcp.hpp>

class websocket_session : public std::enable_shared_from_this<websocket_session> {
public:
    // Take ownership of the socket
    explicit websocket_session(tcp::socket socket);

    // Start the WebSocket session
    void run();

private:
    websocket::stream<tcp::socket> ws_;
    boost::beast::flat_buffer buffer_;

    // Function to read a message
    void do_read();

    // Function to handle the received message
    void on_read(boost::beast::error_code ec, std::size_t bytes_transferred);

    // Function to send a message
    void do_write(std::size_t length);

    // Function to handle the completion of a write operation
    void on_write(boost::beast::error_code ec, std::size_t bytes_transferred);
};

#endif // WEBSOCKET_SESSION_H
