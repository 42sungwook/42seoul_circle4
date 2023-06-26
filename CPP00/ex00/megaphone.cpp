#include <iostream>
#include <cstring>
#include <cctype>

#define RED_TEXT "\033[1;31m"
#define RESET_TEXT "\033[0m"

int main(int argc, char **argv) {

    std::string input;

    if (argc < 2) {
        std::cout << RED_TEXT << "No Input Provided!" << RESET_TEXT << std::endl;
        return 1;
    }

    for (int i = 1; i < argc; ++i) {
        input += argv[i];
    }

    for (std::size_t i = 0; i < input.length(); ++i) {
        input[i] = std::toupper(input[i]);
    }

    std::cout << input << std::endl;

    return 0;
}
