#include <gtest/gtest.h>
#include "Errors.hpp"
#include "Forms.hpp"

const std::string CORRECT_LOGIN{"login"};
const std::string INCORRECT_LOGIN{"log in"};
const std::string CORRECT_PASSWORD{"NormalPassword1"};
const std::string INCORRECT_PASSWORD{"pass"};
const std::string CORRECT_NICKNAME{"Nickname"};
const std::string INCORRECT_NICKNAME{"Nick name"};
const std::string CORRECT_FIRSTNAME{"Firstname"};
const std::string INCORRECT_FIRSTNAME{"1irstname"};
const std::string CORRECT_LASTNAME{"Lastname"};
const std::string INCORRECT_LASTNAME{"1astname"};

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
    SignupForm form{
        CORRECT_LOGIN,
        INCORRECT_NICKNAME,
        CORRECT_PASSWORD,
        ""
    };
    EXPECT_THROW(form.validate(), FormError);
}

TEST(SignupFormValidation, EmptyNicknameCase) {
    SignupForm form{
        CORRECT_LOGIN,
        "",
        CORRECT_PASSWORD,
        CORRECT_PASSWORD
    };
    EXPECT_THROW(form.validate(), FormError);
}

TEST(SignupFormValidation, IncorrectNicknameCase) {
    SignupForm form{
        CORRECT_LOGIN,
        INCORRECT_NICKNAME,
        CORRECT_PASSWORD,
        CORRECT_PASSWORD
    };
    EXPECT_THROW(form.validate(), FormError);
}

TEST(SignupFormValidation, CorrectNicknameCase) {
    SignupForm form{
        CORRECT_LOGIN,
        CORRECT_NICKNAME,
        CORRECT_PASSWORD,
        CORRECT_PASSWORD
    };
    EXPECT_NO_THROW(form.validate());
}

TEST(UserSettingFormValidation, EmptyNicknameCase) {
    UserSettingForm form{std::string{}};
    EXPECT_THROW(form.validate(), FormError);
}

TEST(UserSettingFormValidation, IncorrectNicknameCase) {
    UserSettingForm form{INCORRECT_NICKNAME};
    EXPECT_THROW(form.validate(), FormError);
}

TEST(UserSettingFormValidation, CorrectNicknameCase) {
    UserSettingForm form{CORRECT_NICKNAME};
    EXPECT_NO_THROW(form.validate());
}

TEST(UserSettingFormValidation, CorrectFirstnameCase) {
    UserSettingForm form{CORRECT_NICKNAME};
    form.SetFirstname(CORRECT_FIRSTNAME);
    EXPECT_NO_THROW(form.validate());
}

TEST(UserSettingFormValidation, IncorrectFirstnameCase) {
    UserSettingForm form{CORRECT_NICKNAME};
    form.SetFirstname(INCORRECT_FIRSTNAME);
    EXPECT_THROW(form.validate(), FormError);
}

TEST(UserSettingFormValidation, CorrectLastnameCase) {
    UserSettingForm form{CORRECT_NICKNAME};
    form.SetFirstname(CORRECT_FIRSTNAME);
    form.SetLastname(CORRECT_LASTNAME);
    EXPECT_NO_THROW(form.validate());
}

TEST(UserSettingFormValidation, IncorrectLastnameCase) {
    UserSettingForm form{CORRECT_NICKNAME};
    form.SetFirstname(CORRECT_FIRSTNAME);
    form.SetLastname(INCORRECT_LASTNAME);
    EXPECT_THROW(form.validate(), FormError);
}
