//
// Created by MSI on 2024/3/12.
//
#include <iostream>
#include "nlohmann/json.hpp"
#include <fstream>
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

    // 写json到文件
    std::ofstream file("test.json");
    file<<j<<std::endl;
    file.close();

    // 反序列化json文件
    // string to json
    std::string s = "{\"answer\": 42, \"everything\": true}";
    json j2 = json::parse(s);
    std::cout<<j2.at("answer")<<std::endl;

    // 后面要加"_json"
    json j3 = "{\"happy\": true, \"pi\": 3.141}"_json;
    std::cout<<j3.at("happy")<<std::endl;

    // 从JSON对象转化为字节序列
    std::string ss = j3.dump();
    std::cout<<ss<<"\n";

    // 以便于查看的方式将json对象写入文件
    std::ofstream file2("test2.json");
    file2<<std::setw(4)<<j3<<std::endl;

    return 0;
}
