#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>

#include "generator.hpp"


//


#define FOLDER  "generated"     //folder name
#define CHUNKS  10              //number of chunks aka subfolders
#define FILES   10              //number of files inside each chunk
#define LINES   10              //number of lines (webhooks) inside each file


//


struct stats
{
        int chunks{};
        int files{};
        int webhooks{};
};


int main()
{
        auto start = std::chrono::steady_clock::now();

        std::filesystem::remove_all(FOLDER);
        std::filesystem::create_directory(FOLDER);

        std::filesystem::path folder = FOLDER;
        std::filesystem::path chunk{};
        std::filesystem::path file{};

        stats stats;

        for(int i{}; i < CHUNKS; i++)
        {
                chunk = folder / ("chunk_" + std::to_string(i));
                std::filesystem::create_directory(chunk);

                for(int j{}; j < FILES; j++)
                {
                        file = chunk / ("webhooks_" + std::to_string(j) + ".txt");

                        std::ofstream current_file(file);

                        if(current_file)
                        {
                                for(int k{}; k < LINES; k++)
                                {
                                        current_file << generate_webhook() << '\n';
                                        stats.webhooks++;
                                }
                        }

                        current_file.close();
                        stats.files++;
                }

                stats.chunks++;
        }

        auto end = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        printf("finished in %dms\n", elapsed.count());
        printf("generated %d chunks, %d files and %d webhooks",stats.chunks, stats.files, stats.webhooks);

        return 0;
}