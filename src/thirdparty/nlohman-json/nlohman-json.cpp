//
// Created by MSI on 2024/3/12.
//
#include <iostream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

int main(){

    json j;

    j["pi"] = 3.141;
    j["happy"] = true;
    j["name"] = "Niels";
    j["nothing"] = nullptr;
    j["answer"]["everything"] = 42;
    j["list"] = {1, 0, 2};
    j["object"] = {
            {"currency", "USD"},
            {"value", 42.99}
    };

    std::cout << j << std::endl;

    return 0;
}
