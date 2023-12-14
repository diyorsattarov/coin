#include <server/server.h>
#include <server/session.h>

WebSocketServer::WebSocketServer(net::io_context& ioc, tcp::endpoint endpoint)
    : ioc_(ioc), acceptor_(ioc, endpoint) {
    boost::beast::error_code ec;

    // Open the acceptor
    acceptor_.open(endpoint.protocol(), ec);
    if(ec) {
        Utilities::console_logger()->info("Server: Open acceptor error: {}", ec.message());
        return; // Handle error
    }

    // Bind to the server address
    acceptor_.bind(endpoint, ec);
    if(ec) {
        Utilities::console_logger()->info("Server: Bind error: {}", ec.message());
        return; // Handle error
    }

    // Start listening for connections
    acceptor_.listen(net::socket_base::max_listen_connections, ec);
    if(ec) {
        Utilities::console_logger()->info("Server: Listen error: {}", ec.message());
        return; // Handle error
    }

    do_accept();
}

void WebSocketServer::run() {
    Utilities::console_logger()->info("Server: Running server...");
    do_accept();
}

void WebSocketServer::do_accept() {
    Utilities::console_logger()->info("Server: Waiting for new connection...");
    acceptor_.async_accept(
        [this](boost::beast::error_code ec, tcp::socket socket) {
            if(!ec) {
                Utilities::console_logger()->info("Server: New connection established.");
                std::make_shared<websocket_session>(std::move(socket))->run();
            } else {
                Utilities::console_logger()->info("Server: Failed to establish connection: {}", ec.message());
            }
            do_accept();
        });
}

void WebSocketServer::on_accept(boost::beast::error_code ec, tcp::socket socket) {
    if(ec) {
        Utilities::console_logger()->info("Server: Accept error: {}", ec.message());
        return;
    }

    Utilities::console_logger()->info("Server: Session created for new connection.");
    std::make_shared<websocket_session>(std::move(socket))->run();
}