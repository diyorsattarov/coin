#include <gtest/gtest.h>
#include <client/client.h>
#include <string>

class WebSocketClientTest : public ::testing::Test {
protected:
    net::io_context ioc;
    std::unique_ptr<WebSocketClient> client;

    WebSocketClientTest() {
        // Setup code (runs before each test)
        client = std::make_unique<WebSocketClient>(ioc, "localhost", "8080");
    }

    ~WebSocketClientTest() override {
        // Tear down code (runs after each test)
        client->close();
    }
};

TEST_F(WebSocketClientTest, SendReceiveTest) {
    // Generate a unique hash for the client
    std::string client_hash = generate_hash();

    // Send the hash to the server
    client->send(client_hash);

    // Receive response from the server
    std::string response = client->receive();

    // Test if the response meets your expectations
    // Example: EXPECT_EQ(response, "Expected Response");
}