#include "AccountNetwork.hpp"

const std::string LOGIN_URL = "/login";
const std::string SIGNUP_URL = "/register";

AccountNetwork::AccountNetwork() {
    loginCallback = Callback(
        [this](IResponseUPtr response) {
           return this->OnLoginResponse(std::move(response)); 
        }
    );

    signupCallback = Callback(
        [this](IResponseUPtr response) {
           return this->OnSignupResponse(std::move(response)); 
        }
    );
}

void AccountNetwork::Login(const LoginData& data) {
    auto request = requestCreator_->CreateRequest(LOGIN_URL);
    request.SetBody(serializer_->SerializeLoginData(data));
    networkManager_->Post(std::make_unique<Request>(request), loginCallback);
}

void AccountNetwork::Signup(const SignupData& data) {
    auto request = requestCreator_->CreateRequest(SIGNUP_URL);
    request.SetBody(serializer_->SerializeSignupData(data));
    networkManager_->Post(std::make_unique<Request>(request), signupCallback);
}

void AccountNetwork::OnLoginResponse(IResponseUPtr response) {
    if (response->GetStatus()) {
        auto data = deserializer_->DeserializeUserData(response->GetBody());
        replyHandler_->OnLoginResponse(std::move(data));
    } else {
        replyHandler_->OnLoginResponse("Authorization failed: " + response->GetDescreption());
    }
}

void AccountNetwork::OnSignupResponse(IResponseUPtr response) {
    if (response->GetStatus()) {
        auto data = deserializer_->DeserializeUserData(response->GetBody());
        replyHandler_->OnSignupResponse(std::move(data));
    } else {
        replyHandler_->OnSignupResponse("Registration failed: " + response->GetDescreption());
    }
}
