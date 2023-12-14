#include <gtest/gtest.h>
#include <server/server.h>
#include <client/client.h>
#include <thread>

class WebSocketServerTest : public ::testing::Test {
protected:
    net::io_context ioc;
    tcp::endpoint endpoint{tcp::v4(), 8080};
    WebSocketServer server{ioc, endpoint};
    std::thread server_thread;

    WebSocketServerTest() {
        // Start the server in a separate thread
        server_thread = std::thread([this]{ ioc.run(); });
    }

    ~WebSocketServerTest() override {
        ioc.stop();
        server_thread.join();
    }
};

TEST_F(WebSocketServerTest, ClientServerCommunication) {
    // Client setup and communication
    WebSocketClient client(ioc, "localhost", "8080");
    std::string client_hash = generate_hash();
    client.send(client_hash);

    // Server should receive and log the client hash
    // Implement server-side logic to handle and log the received hash

    client.close();
}