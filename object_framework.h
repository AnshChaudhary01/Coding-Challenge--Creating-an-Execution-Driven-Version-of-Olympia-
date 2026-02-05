#ifndef OBJECT_FRAMEWORK_H
#define OBJECT_FRAMEWORK_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <functional>


class IObject {
public:
    virtual ~IObject() = default;
    virtual void printDescription() const = 0;
    virtual void calculate(const std::vector<double>& args) const = 0;
    virtual int requiredArgs() const = 0;
};


class ObjectFactory {
public:
    using CreatorFunc = std::function<std::unique_ptr<IObject>()>;

    static ObjectFactory& instance() {
        static ObjectFactory factory;
        return factory;
    }

    void registerObject(const std::string& name, CreatorFunc creator) {
        registry_[name] = creator;
    }

    std::unique_ptr<IObject> create(const std::string& name) {
        if (registry_.find(name) != registry_.end()) {
            return registry_[name]();
        }
        return nullptr;
    }

    void listObjects() const {
        std::cout << "Known objects: ";
        for (const auto& pair : registry_) {
            std::cout << pair.first << " ";
        }
        std::cout << "\n";
    }

private:
    std::map<std::string, CreatorFunc> registry_;
    ObjectFactory() = default;
};


template<typename T>
class Registrar {
public:
    Registrar(const std::string& name) {
        ObjectFactory::instance().registerObject(name, []() -> std::unique_ptr<IObject> {
            return std::make_unique<T>();
        });
    }
};

#endif 