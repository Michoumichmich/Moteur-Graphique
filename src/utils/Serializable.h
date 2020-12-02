#ifndef GRAPHICSENGINE_SERIALIZABLE_H
#define GRAPHICSENGINE_SERIALIZABLE_H

#include <ostream>
#include <list>
#include <sstream>

struct json_entry {
    std::string name;
    std::string data;
};

#define Serialize_Serializable_List(out, entry_name, string) \
    {if (entry_name[0]!='\0') {out << "\"" << entry_name << "\":" << std::endl;} \
    bool isFirst = true;out << "[";\
    for (auto &it : string) {if (isFirst) {isFirst = false;} \
    else {out << ',' << std::endl;}it->serialize(out); } out << "]";}

#define Serialize_Atributes_List(out, entry_name, string) \
    {if (entry_name[0]!='\0') {out << "\"" << entry_name << "\":" << std::endl;} \
    bool isFirst = true;out << "{";\
    for (auto &it : string) {if (isFirst) {isFirst = false;} \
    else {out << ',' << std::endl;}it->serialize(out); } out << "}";}


class Serializable {
public:
    Serializable() = default;

    virtual ~Serializable() = default;

    static void jsonify_serializable_list(std::ostream &out, const std::string &entry_name, std::list<std::string> &string);

    static std::string export_entry(const std::string &entry_name, std::list<json_entry> list);

    virtual void serialize(std::stringstream &stream) = 0;

    virtual void deserialize(std::istream &stream) = 0;
};


#endif //GRAPHICSENGINE_SERIALIZABLE_H
