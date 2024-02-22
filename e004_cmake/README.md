## Summary
For this exercise, we replaced the Makefile with CMake to build the project, but we kept the Makefile to run CMake and upload the code to the board.

Why use cmake?
CMake is like an assistant that generates specific files for your system and compiler, making it easy to take your project to different platforms.

Makefile, though powerful in Unix systems, can become complex and requires manual adjustments to be as portable across various platforms.

When it comes to configuration, CMake is simpler and independent of the compiler and operating system, making it easier to manage different build configurations like Debug or Release. In contrast, a Makefile can be more complex and dependent on the system.

Regarding dependency management, CMake comes with built-in tools to handle them and find libraries in the system. On the other hand, in a Makefile, you may need to manually configure dependencies, which could be more error-prone and less maintainable.

Support for multiple generators: CMake can generate build files for various systems, such as Makefile, Ninja, or Visual Studio, providing flexibility. In contrast, a Makefile is more tied to specific systems and may require substantial adjustments to switch between build systems.

For larger projects with complex structures and advanced dependency management, CMake is particularly useful. However, for smaller and simpler projects, a Makefile might be more suitable.


Commands created in the Makefile to execute the code:
- 'make '
create the build folder and compile the project inside the folder.
- 'make clean'
delete the build folder.
- 'make flash'
loads the elf file onto the board.

