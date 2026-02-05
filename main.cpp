#include <iostream>
#include <vector>
#include <string>
#include "object_framework.h"

// ================= Circle =======================
class Circle : public IObject {
public:
    void printDescription() const override {
        std::cout << "A circle has a radius. Usage: describe_object circle <radius>\n";
    }
    int requiredArgs() const override { return 1; }
    void calculate(const std::vector<double>& args) const override {
        double r = args[0];
        const double PI = 3.14159;
        std::cout << "Circumference: " << 2 * PI * r << "\n";
        std::cout << "Area:          " << PI * r * r << "\n";
    }
};
// Auto-register
static Registrar<Circle> regCircle("circle");

// =============== Square ============================
class Square : public IObject {
public:
    void printDescription() const override {
        std::cout << "A square has four equal sides. Usage: describe_object square <length>\n";
    }
    int requiredArgs() const override { return 1; }
    void calculate(const std::vector<double>& args) const override {
        std::cout << "Perimeter: " << 4 * args[0] << "\n";
        std::cout << "Area:      " << args[0] * args[0] << "\n";
    }
};
// Auto-register
static Registrar<Square> regSquare("square");

// ============== Rectangle ===========================
class Rect : public IObject {
public:
    void printDescription() const override {
        std::cout << "A rectangle has width and height. Usage: describe_object rect <w> <h>\n";
    }
    int requiredArgs() const override { return 2; }
    void calculate(const std::vector<double>& args) const override {
        std::cout << "Perimeter: " << 2 * (args[0] + args[1]) << "\n";
        std::cout << "Area:      " << args[0] * args[1] << "\n";
    }
};
// Auto-register
static Registrar<Rect> regRect("rect");


int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: ./describe_object <object_name> [args...]\n";
        ObjectFactory::instance().listObjects();
        return 1;
    }

    std::string name = argv[1];
    auto obj = ObjectFactory::instance().create(name);

    if (!obj) {
        std::cerr << "Unknown object: " << name << "\n";
        ObjectFactory::instance().listObjects();
        return 1;
    }

    // If only name is provided
    if (argc == 2) {
        obj->printDescription();
        return 0;
    }

    // If args are provided, parse and calculate
    std::vector<double> inputs;
    try {
        for (int i = 2; i < argc; ++i) inputs.push_back(std::stod(argv[i]));
    } catch (...) {
        std::cerr << "Error: Arguments must be numbers.\n";
        return 1;
    }

    if (inputs.size() != (size_t)obj->requiredArgs()) {
        std::cerr << "Error: " << name << " needs " << obj->requiredArgs() << " args.\n";
        return 1;
    }

    obj->calculate(inputs);
    return 0;
}