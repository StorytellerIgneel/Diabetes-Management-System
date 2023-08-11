#include <iostream>
#include <json/json.h>

int main() {
    const char* jsonStr = "{\"name\":\"John\",\"age\":30,\"city\":\"New York\"}";

    Json::Value root;
    Json::CharReaderBuilder reader;
    std::istringstream jsonStream(jsonStr);
    std::string errs;
    Json::parseFromStream(reader, jsonStream, &root, &errs);

    std::cout << "Name: " << root["name"].asString() << std::endl;
    std::cout << "Age: " << root["age"].asInt() << std::endl;
    std::cout << "City: " << root["city"].asString() << std::endl;

    Json::Value newRoot;
    newRoot["country"] = "USA";
    newRoot["population"] = 328200000;

    Json::StreamWriterBuilder writer;
    std::string newJsonStr = Json::writeString(writer, newRoot);

    std::cout << "Generated JSON: " << newJsonStr << std::endl;

    return 0;
}