#ifndef JSON_READER_H
#define JSON_READER_H

#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class JsonReader {
private:
    static json jsonObj;

public:
    /**
     * @brief Get the Json Obj property
     * 
     * @return json 
     */
    static json getJsonObj();

    /**
     * @brief read from a json file
     * 
     * @param path path of the json file
     */
    static void read(const std::string path);
};

#endif