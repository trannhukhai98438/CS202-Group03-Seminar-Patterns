#include <iostream>
#include <string>
#include <memory>

// 1. Base Handler Interface
class Handler : public std::enable_shared_from_this<Handler> {
protected:
    std::shared_ptr<Handler> next_handler_;

public:
    virtual ~Handler() = default;

    // Sets the next handler in the pipeline and supports method chaining
    template <typename T>
    std::shared_ptr<T> SetNext(std::shared_ptr<T> handler) {
        next_handler_ = handler;
        return handler;
    }

    // Primary request handling logic
    virtual std::string Handle(const std::string& request) {
        if (next_handler_) {
            return next_handler_->Handle(request);
        }
        return "SUCCESS: Request processed successfully.\n";
    }
};

// 2. Concrete Handler 1: Authentication
class AuthenticationHandler : public Handler {
public:
    std::string Handle(const std::string& request) override {
        if (request.find("unauthenticated") != std::string::npos) {
            return "ERROR [401]: Authentication failed (Unauthenticated).\n";
        }
        std::cout << "[Auth Pass] Authentication successful.\n";
        return Handler::Handle(request);
    }
};

// 3. Concrete Handler 2: Authorization
class AuthorizationHandler : public Handler {
public:
    std::string Handle(const std::string& request) override {
        if (request.find("unauthorized") != std::string::npos) {
            return "ERROR [403]: Access denied (Unauthorized).\n";
        }
        std::cout << "[Authz Pass] Authorization successful.\n";
        return Handler::Handle(request);
    }
};

// 4. Concrete Handler 3: Validation
class ValidationHandler : public Handler {
public:
    std::string Handle(const std::string& request) override {
        if (request.find("invalid_data") != std::string::npos) {
            return "ERROR [400]: Payload contains invalid data.\n";
        }
        std::cout << "[Validation Pass] Data validation successful.\n";
        return Handler::Handle(request);
    }
};

// Client Code
void ClientCode(Handler& handler, const std::string& request) {
    std::cout << "--- Sending request: \"" << request << "\" ---\n";
    std::string result = handler.Handle(request);
    std::cout << "Result: " << result;
}

int main() {
    // Instantiate handlers
    auto auth = std::make_shared<AuthenticationHandler>();
    auto authz = std::make_shared<AuthorizationHandler>();
    auto validation = std::make_shared<ValidationHandler>();

    // Build the execution chain: Auth -> Authz -> Validation
    auth->SetNext(authz)->SetNext(validation);

    // Scenario 1: Valid request passes through all handlers
    ClientCode(*auth, "valid_request");
    std::cout << "\n";

    // Scenario 2: Request fails at Authentication stage
    ClientCode(*auth, "unauthenticated_request");
    std::cout << "\n";

    // Scenario 3: Request fails at Authorization stage
    ClientCode(*auth, "unauthorized_request");
    std::cout << "\n";

    // Scenario 4: Request fails at Validation stage
    ClientCode(*auth, "invalid_data_request");

    return 0;
}