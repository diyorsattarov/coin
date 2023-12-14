// client.cpp
#include <client/client.h>

WebSocketClient::WebSocketClient(net::io_context& ioc, const std::string& host, const std::string& port)
    : resolver_(ioc), ws_(ioc) {
    Utilities::console_logger()->info("Resolving host and connecting...");
    auto const results = resolver_.resolve(host, port);
    auto ep = net::connect(ws_.next_layer(), results);

    Utilities::console_logger()->info("Performing WebSocket handshake...");
    ws_.handshake(host, "/");
    Utilities::console_logger()->info("Handshake successful.");
}

void WebSocketClient::send(const std::string& message) {
    Utilities::console_logger()->info("Sending message: {}", message);
    ws_.write(net::buffer(std::string(message)));
    Utilities::console_logger()->info("Message sent.");
}

std::string WebSocketClient::receive() {
    Utilities::console_logger()->info("Receiving message...");
    beast::flat_buffer buffer;
    ws_.read(buffer);
    std::string received = beast::buffers_to_string(buffer.data());
    Utilities::console_logger()->info("Received message: {}", received);
    return received;
}

void WebSocketClient::close() {
    Utilities::console_logger()->info("Closing WebSocket connection.");
    ws_.close(websocket::close_code::normal);
    Utilities::console_logger()->info("Connection closed.");
}

std::string generate_hash() {
    Utilities::console_logger()->info("Generating client hash...");
    std::string chars("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890");
    std::random_device rd;
    std::mt19937 generator(rd());
    std::shuffle(chars.begin(), chars.end(), generator);
    std::string hash = chars.substr(0, 8);
    Utilities::console_logger()->info("Generated hash: {}", hash);
    return hash;
}