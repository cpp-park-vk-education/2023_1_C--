#include "AccountNetwork.hpp"
#include "Communication.hpp"
#include "AccountData.hpp"

const std::string LOGIN_URL = "login/";
const std::string SIGNUP_URL = "signup/";
const std::string USER_SETTING_URL = "setting/";
const std::string LOGOUT_URL = "logout/";

static QByteArray GetQByteArray(std::vector<char> byteArray) {
    QByteArray qByteArray;
    for (auto byte: byteArray)
        qByteArray.push_back(byte);
    return qByteArray;
}

void AccountNetwork::Login(const LoginData& data) {
    auto request = CreateRequest(LOGIN_URL);
    auto byteArray = serializer_->SerializeLoginData(data);
    Callback callback (
        [this](IResponseUPtr response){
           return this->OnLoginResponse(std::move(response)); 
        }
    ); 
    networkManager_->Post(request, GetQByteArray(byteArray), callback);
}

void AccountNetwork::Signup(const SignupData& data) {}
void AccountNetwork::UserSetting(const UserSettingData& data) {}
void AccountNetwork::Logout(const LogoutData& data) {}

void AccountNetwork::OnLoginResponse(IResponseUPtr response) {
    auto statusCode = response->GetStatus();
    if (statusCode == 200) {
        UserData data = deserializer_->DeserializeUserData(response->GetBody());
        replyHandler_->OnLoginResponse(200, data);
    } else {
        replyHandler_->OnLoginResponse(statusCode, UserData{});
    }
}

void AccountNetwork::OnSignupResponse(IResponseUPtr response) {}
void AccountNetwork::OnUserSettingResponse(IResponseUPtr response) {}
void AccountNetwork::OnLogoutResponse(IResponseUPtr response) {}
