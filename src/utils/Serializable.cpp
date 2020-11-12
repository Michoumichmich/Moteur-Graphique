#include <sstream>
#include "Serializable.h"

void Serializable::jsonify_serializable_list(std::ostream &out, std::list<Serializable *> &list) {
    //   out << '{' << typeid(this).name() ;
    out << "[";
    for (auto &it : list) {
        it->serialize(out);
    }
    out << "]";
}


void Serializable::export_entry(std::ostream &out, const std::string &entry_name, std::list<json_entry> list) {
    bool isFirst = true;
    if (!entry_name.empty()) out << "\"" << entry_name << "\":" << std::endl;
    out << "{";
    for (auto &it : list) {
        if (isFirst) {
            isFirst = false;
        } else {
            out << ',' << std::endl;
        }
        out << "\"" << it.name << "\": " << "\"" << it.data << "\"";
    }
    out << "}";
}
