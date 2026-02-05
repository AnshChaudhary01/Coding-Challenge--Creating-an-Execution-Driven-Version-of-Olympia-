This coding challenge implements an extensible, execution-driven object handling system in C++.
It utilizes the Factory Design Pattern with Self-Registration to mimic the architecture used in modular processor simulators (such as the Olympia RISC-V model).

The goal of this project is to create a system where the main driver (main.cpp) is completely decoupled from the objects it processes. The driver does not contain logic for specific shapes; it acts purely as a dispatcher.

This architecture enforces strict Open/Closed Principles.

## Project Structure

* `object_framework.h` - **The Core.** Defines the `IObject` interface, the singleton `ObjectFactory`, and the `Registrar` template for auto-registration.
* `main.cpp` - **The Driver.** Handles command-line arguments and dispatches requests to the factory. Includes implementations for Circle, Square, and Rectangle.
* `triangle.cpp` - **Extension Example.** A standalone file demonstrating how to add new functionality without modifying existing code.

**1. Standard Version**
To build the standard version with Circle, Square, and Rectangle:

```bash
g++ -std=c++14 -o describe_object main.cpp
```

** To add the Triangle functionality, simply compile the extension file alongside the main driver. (g++ -std=c++14 -o describe_object main.cpp triangle.cpp)

Syntax : 
```bash
./describe_object <object_name> [dimensions...]
```
