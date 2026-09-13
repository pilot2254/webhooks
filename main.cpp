#include <iostream>
#include <fstream>
#include <filesystem>

#include "generator.hpp"


//


#define FOLDER  "generated"     //folder name
#define CHUNKS  2               //number of chunks aka subfolders
#define FILES   2               //number of files inside each chunk
#define LINES   100             //number of lines (webhooks) inside each file


//


struct stats
{
        int chunks{};
        int files{};
        int webhooks{};
};


int main()
{
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

        std::cout << "done" << '\n';
        printf("finished with %d chunks, %d files and %d webhooks",stats.chunks, stats.files, stats.webhooks);

        //std::cout << generate_webhook();

        return 0;
}