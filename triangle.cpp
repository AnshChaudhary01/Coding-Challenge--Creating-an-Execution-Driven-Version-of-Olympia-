#include <iostream>
#include <vector>
#include "object_framework.h" 
#include <cmath>

// Defining class
class Triangle : public IObject {
public:
    void printDescription() const override {
        std::cout << "A triangle. Usage: describe_object triangle <base> <height>\n";
    }

    int requiredArgs() const override { 
        return 2; 
    }

    void calculate(const std::vector<double>& args) const override {
        double base = args[0];
        double height = args[1];
        // Calculate Area
        std::cout << "Area: " << 0.5 * base * height << "\n";
        
        // Perimeter requires side lengths, but let's assume valid isosceles for simplicity 
        double hypotenuse = sqrt(pow(base/2, 2) + pow(height, 2)); 
        std::cout << "Perimeter (assuming isosceles): " << base + 2 * hypotenuse << "\n";
    }
};

static Registrar<Triangle> regTriangle("triangle");