#include "json_reader.h"

json JsonReader::jsonObj;

json JsonReader::getJsonObj() {
    return JsonReader::jsonObj;
}

void JsonReader::read(const std::string path) {
    std::ifstream file(path);
    JsonReader::jsonObj = json::parse(file);
    file.close();
}