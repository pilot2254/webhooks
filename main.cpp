#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]) {
        if (argc != 2) {
                std::cout << "usage: program.exe <number>\n";
                std::cout << "where <number> is how many webhooks to generate\n";
                return 1;
        }

        int count = std::atoi(argv[1]);

        for (int i = 0; i < count; i++) {
                std::cout << "hello world\n";
        }

        return 0;
}