#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include <string>
#include "UserData.hpp"

using TextData = std::unordered_map<std::string, std::string>; 

class ITextSerializer {
public:
    virtual ~ITextSerializer() {}
    virtual std::vector<char> SerializeText(TextData textData) = 0;
    virtual IUserDataUPtr DeserializeText(std::vector<char> data) = 0;
};

using ITextSerializerUPtr = std::unique_ptr<ITextSerializer>;
