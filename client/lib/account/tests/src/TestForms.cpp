#include <gtest/gtest.h>
#include "Errors.hpp"
#include "Forms.hpp"

const std::string CORRECT_LOGIN{"login"};
const std::string INCORRECT_LOGIN{"l"};
const std::string CORRECT_PASSWORD{"NormalPassword1"};
const std::string INCORRECT_PASSWORD{"pass"};
const std::string CORRECT_NICKNAME{"Nickname"};
const std::string INCORRECT_NICKNAME{"!~"};

TEST(LoginFormValidationTest, EmptyFormCase) {
    LoginForm form{"", ""};
    EXPECT_THROW(form.validate(), FormError);
}

TEST(LoginFormValidationTest, IncorrectLoginCase) {
    LoginForm form{INCORRECT_LOGIN, CORRECT_PASSWORD};
    EXPECT_THROW(form.validate(), FormError);
}

TEST(LoginFormValidationTest, IncorrectPasswordCase) {
    LoginForm form{CORRECT_LOGIN, INCORRECT_PASSWORD};
    EXPECT_THROW(form.validate(), FormError);
}

TEST(LoginFormValidationTest, CorrectCase) {
    LoginForm form{CORRECT_LOGIN, CORRECT_PASSWORD};
    EXPECT_NO_THROW(form.validate());
}

TEST(SignupFormValidation, DifferentPasswordCase) {
    SignupForm form{CORRECT_LOGIN, CORRECT_PASSWORD};
    form.SetNickname(INCORRECT_NICKNAME);
    form.SetRepeatedPassword(INCORRECT_PASSWORD);
    EXPECT_THROW(form.validate(), FormError);
}

TEST(SignupFormValidation, EmptyNicknameCase) {
    SignupForm form{CORRECT_LOGIN, CORRECT_PASSWORD};
    EXPECT_THROW(form.validate(), FormError);
}

TEST(SignupFormValidation, IncorrectNicknameCase) {
    SignupForm form{CORRECT_LOGIN, CORRECT_PASSWORD};
    form.SetNickname(INCORRECT_NICKNAME);
    form.SetRepeatedPassword(CORRECT_PASSWORD);
    EXPECT_THROW(form.validate(), FormError);
}

TEST(SignupFormValidation, CorrectNicknameCase) {
    SignupForm form{CORRECT_LOGIN, CORRECT_PASSWORD};
    form.SetNickname(CORRECT_NICKNAME);
    form.SetRepeatedPassword(CORRECT_PASSWORD);
    EXPECT_NO_THROW(form.validate());
}

TEST(UserSettingFormValidation, DifferentPasswordCase) {
    UserSettingForm form{CORRECT_LOGIN, CORRECT_PASSWORD};
    form.SetRepeatedPassword(INCORRECT_PASSWORD);
    EXPECT_THROW(form.validate(), FormError);
}

TEST(UserSettingFormValidation, EmptyNicknameCase) {
    UserSettingForm form{CORRECT_LOGIN, CORRECT_PASSWORD};
    form.SetRepeatedPassword(CORRECT_PASSWORD);
    EXPECT_THROW(form.validate(), FormError);
}

TEST(UserSettingFormValidation, IncorrectNicknameCase) {
    UserSettingForm form{CORRECT_LOGIN, CORRECT_PASSWORD};
    form.SetNickname(INCORRECT_NICKNAME);
    form.SetRepeatedPassword(CORRECT_PASSWORD);
    EXPECT_THROW(form.validate(), FormError);
}

TEST(UserSettingFormValidation, CorrectNicknameCase) {
    UserSettingForm form{CORRECT_LOGIN, CORRECT_PASSWORD};
    form.SetNickname(CORRECT_NICKNAME);
    form.SetRepeatedPassword(CORRECT_PASSWORD);
    EXPECT_NO_THROW(form.validate());
}
