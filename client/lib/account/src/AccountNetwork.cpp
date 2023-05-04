#include "AccountNetwork.hpp"

const std::string LOGIN_URL = "/login";
const std::string SIGNUP_URL = "/signup";
const std::string USER_SETTING_URL = "/setting";
const std::string LOGOUT_URL = "/logout";

using Headers = std::unordered_map<std::string, std::string>;

Request AccountNetwork::CreateRequest(const std::string& url, const Headers& headers) {
    Request request;
    for (auto it = headers.begin(); it != headers.end(); it++) {
        request.SetHeader(it->first, it->second);
    }
    request.SetURL(url);
    return request;
}

void AccountNetwork::Login(const LoginData& data) {
    Headers headers = {{"Content-Type", "JSON"}};
    auto request = CreateRequest(LOGIN_URL, headers);
    auto body = requestSerializer_->SerializeLoginData(data);
    request.SetBody(body);
    Callback callback (
        [this](IResponseUPtr response){
           return this->OnLoginResponse(std::move(response)); 
        }
    );
    networkManager_->Post(std::make_unique<Request>(request), callback);
}

void AccountNetwork::Signup(const SignupData& data) {
    Headers headers = {{"Content-Type", "JSON"}};
    auto request = CreateRequest(SIGNUP_URL, headers);
    auto body = requestSerializer_->SerializeSignupData(data);
    request.SetBody(body);
    Callback callback (
        [this](IResponseUPtr response){
           return this->OnLoginResponse(std::move(response)); 
        }
    ); 
    networkManager_->Post(std::make_unique<Request>(request), callback);
}

void AccountNetwork::UserSetting(const UserSettingData& data) {
    Headers headers = {{"Content-Type", "JSON"}};
    auto request = CreateRequest(USER_SETTING_URL, headers);
    auto body = requestSerializer_->SerializeUserSettingData(data);
    request.SetBody(body);
    Callback callback (
        [this](IResponseUPtr response){
           return this->OnUserSettingResponse(std::move(response)); 
        }
    ); 
    networkManager_->Post(std::make_unique<Request>(request), callback);
}

void AccountNetwork::Logout(const LogoutData& data) {
    Headers headers = {{"Content-Type", "JSON"}};
    auto request = CreateRequest(LOGOUT_URL, headers);
    auto body = requestSerializer_->SerializeLogoutData(data);
    request.SetBody(body);
    Callback callback (
        [this](IResponseUPtr response){
           return this->OnLogoutResponse(std::move(response)); 
        }
    );
    networkManager_->Post(std::make_unique<Request>(request), callback);
}

void AccountNetwork::OnLoginResponse(IResponseUPtr response) {
    auto statusCode = response->GetStatus(LOGIN_URL);
    if (statusCode == 200) {
        auto body = response->GetBody();
        auto userData = responseSerializer_->DeserializeResponse(body);
        replyHandler_->OnLoginResponse(200, std::move(userData));
    } else {
        replyHandler_->OnLoginResponse(statusCode, nullptr);
    }
}

void AccountNetwork::OnSignupResponse(IResponseUPtr response) {
    auto statusCode = response->GetStatus(SIGNUP_URL);
    if (statusCode == 200) {
        auto body = response->GetBody();
        auto userData = responseSerializer_->DeserializeResponse(body);
        replyHandler_->OnSignupResponse(200, std::move(userData));
    } else {
        replyHandler_->OnSignupResponse(statusCode, nullptr);
    }
}

void AccountNetwork::OnUserSettingResponse(IResponseUPtr response) {
    auto statusCode = response->GetStatus(USER_SETTING_URL);
    if (statusCode == 200) {
        auto body = response->GetBody();
        auto userData = responseSerializer_->DeserializeResponse(body);
        replyHandler_->OnUserSettingResponse(200, std::move(userData));
    } else {
        replyHandler_->OnUserSettingResponse(statusCode, nullptr);
    }
}

void AccountNetwork::OnLogoutResponse(IResponseUPtr response) {
    auto statusCode = response->GetStatus(LOGOUT_URL);
    replyHandler_->OnLogoutResponse(statusCode);
}
