#include <sstream>
#include "Serializable.h"

void Serializable::jsonify_serializable_list(std::ostream &out, const std::string &entry_name, std::list<std::string> &string) {
    if (!entry_name.empty()) out << "\"" << entry_name << "\":" << std::endl;
    bool isFirst = true;
    out << "[";
    for (auto &it : string) {
        if (isFirst) {
            isFirst = false;
        } else {
            out << ',' << std::endl;
        }
        out << it;
    }
    out << "]";
}

std::string Serializable::export_entry(const std::string &entry_name, const std::list<json_entry> &list) {
    std::stringstream string;
    bool isFirst = true;
    if (!entry_name.empty()) string << "\"" << entry_name << "\":";
    string << "{";
    for (auto &it : list) {
        if (isFirst) {
            isFirst = false;
        } else {
            string << ',' << std::endl;
        }
        string << "\"" << it.name << "\": " << "\"" << it.data << "\"";
    }
    string << "}";
    return string.str();
}
