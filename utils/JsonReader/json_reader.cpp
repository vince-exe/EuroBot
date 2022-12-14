#include "json_reader.h"

JsonReader::JsonReader(const std::string path) {
    std::ifstream ifs(path);
    this->jsonObj = json::parse(ifs);
}

json JsonReader::getJsonObj() {
    return this->jsonObj;
}

void JsonReader::setPath(const std::string path) {
    std::ifstream ifs(path);
    this->jsonObj = json::parse(ifs);
}