#ifndef GRAPHICSENGINE_SERIALIZABLE_H
#define GRAPHICSENGINE_SERIALIZABLE_H

#include <ostream>
#include <list>

struct json_entry {
    std::string name;
    std::string data;
};


class Serializable {
public:
    Serializable() = default;

    virtual ~Serializable() = default;

    static void jsonify_serializable_list(std::ostream &out, std::list<Serializable *> &list);

    static void export_entry(std::ostream &out, const std::string &entry_name, std::list<json_entry> list);

    virtual void serialize(std::ostream &stream) = 0;

    virtual void deserialize(std::istream &stream) = 0;
};


#endif //GRAPHICSENGINE_SERIALIZABLE_H
