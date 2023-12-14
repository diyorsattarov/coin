#include <server/session.h>

websocket_session::websocket_session(tcp::socket socket)
    : ws_(std::move(socket)) {
}

void websocket_session::run() {
    Utilities::console_logger()->info("Session: Starting WebSocket handshake...");
    ws_.async_accept(
        [self = shared_from_this()](boost::beast::error_code ec) {
            if(!ec) {
                Utilities::console_logger()->info("Session: WebSocket handshake successful.");
                self->do_read();
            } else {
                Utilities::console_logger()->info("Session: WebSocket handshake failed: {}", ec.message());
            }
        });
}

void websocket_session::do_read() {
    ws_.async_read(
        buffer_,
        [self = shared_from_this()](boost::beast::error_code ec, std::size_t bytes_transferred) {
            self->on_read(ec, bytes_transferred);
        });
}

void websocket_session::on_read(boost::beast::error_code ec, std::size_t bytes_transferred) {
    if(ec) {
        Utilities::console_logger()->info("Session: Read failed: {}", ec.message());
        return;
    }

    std::string received_message = boost::beast::buffers_to_string(buffer_.data());
    Utilities::console_logger()->info("Session: Received message: {}", received_message);

    do_write(bytes_transferred);
    buffer_.consume(buffer_.size());
}

void websocket_session::do_write(std::size_t length) {
    Utilities::console_logger()->info("Session: Sending message...");
    ws_.async_write(
        buffer_.data(),
        boost::beast::bind_front_handler(
            &websocket_session::on_write,
            shared_from_this()));
}

void websocket_session::on_write(boost::beast::error_code ec, std::size_t bytes_transferred) {
    if(ec) {
        Utilities::console_logger()->info("Session: Write failed: {}", ec.message());
        return;
    }

    buffer_.consume(buffer_.size());
    Utilities::console_logger()->info("Session: Message sent successfully.");
    do_read();
}
