#ifndef JSON_READER_H
#define JSON_READER_H

#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class JsonReader {
private:
    json jsonObj;

public:
    JsonReader()=default;
    
    /**
     * @brief Construct a new JsonReader object
     * 
     * @param path the path of the .json file
     */
    JsonReader(const std::string path);

    /**
     * @brief Get the Json Obj property
     * 
     * @return json 
     */
    json getJsonObj();

    /**
     * @brief setter of jsonObj property
     * 
     * @param path path of the .json file
     */
    void setPath(const std::string path);
};

#endif