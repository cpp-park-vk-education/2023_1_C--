#include "AccountNetwork.hpp"
#include "Communication.hpp"
#include "AccountData.hpp"

const std::string LOGIN_URL = "login";
const std::string SIGNUP_URL = "register";
const std::string USER_SETTING_URL = "setting";
const std::string LOGOUT_URL = "logout";

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
    auto request = CreateRequest(LOGIN_URL);
    auto byteArray = serializer_->SerializeLoginData(data);
    qDebug() << "Inside Login()";
    networkManager_->Post(request, GetQByteArray(byteArray), loginCallback);
}

void AccountNetwork::Signup(const SignupData& data) {
    auto request = CreateRequest(SIGNUP_URL);
    auto byteArray = serializer_->SerializeSignupData(data);
    networkManager_->Post(request, GetQByteArray(byteArray), signupCallback);
}

void AccountNetwork::UserSetting(const UserSettingData& data) {}
void AccountNetwork::Logout(const LogoutData& data) {}

void AccountNetwork::OnLoginResponse(IResponseUPtr response) {
    qDebug() << "Inside OnLoginResponse()";
    auto statusCode = response->GetStatus();
    if (statusCode == 200) {
        auto data = deserializer_->DeserializeUserData(response->GetBody());
        replyHandler_->OnLoginResponse(200, std::move(data));
    } else {
        replyHandler_->OnLoginResponse(statusCode, UserData{});
    }
}

void AccountNetwork::OnSignupResponse(IResponseUPtr response) {
    auto statusCode = response->GetStatus();
    if (statusCode == 200) {
        auto data = deserializer_->DeserializeUserData(response->GetBody());
        replyHandler_->OnLoginResponse(200, std::move(data));
    } else {
        replyHandler_->OnSignupResponse(statusCode, UserData{});
    }
}

void AccountNetwork::OnUserSettingResponse(IResponseUPtr response) {}
void AccountNetwork::OnLogoutResponse(IResponseUPtr response) {}
