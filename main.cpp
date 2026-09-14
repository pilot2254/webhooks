#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

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


//

std::uintmax_t get_folder_size(const std::filesystem::path &folder)
{
        std::uintmax_t size{};

        for (const auto &entry : std::filesystem::recursive_directory_iterator(folder))
        {
                if (entry.is_regular_file())
                {
                        size += entry.file_size();
                }
        }

        return size;
}


//


std::string format_size(std::uintmax_t bytes)
{
        constexpr std::uintmax_t KB = 1024;
        constexpr std::uintmax_t MB = KB * 1024;
        constexpr std::uintmax_t GB = MB * 1024;

        if (bytes >= GB) return std::to_string(bytes / GB) + " GB";
        if (bytes >= MB) return std::to_string(bytes / MB) + " MB";
        if (bytes >= KB) return std::to_string(bytes / KB) + " KB";

        return std::to_string(bytes) + " bytes";
}


//


int main()
{
        auto start = std::chrono::steady_clock::now();

        std::filesystem::remove_all(FOLDER);
        std::filesystem::create_directory(FOLDER);

        const std::filesystem::path folder = FOLDER;

        stats stats;

        for(int i{}; i < CHUNKS; i++)
        {
                const std::filesystem::path chunk = folder / ("chunk_" + std::to_string(i));

                std::filesystem::create_directory(chunk);

                for(int j{}; j < FILES; j++)
                {
                        const std::filesystem::path file = chunk / ("webhooks_" + std::to_string(j) + ".txt");

                        std::ofstream current_file(file);

                        if(current_file)
                        {
                                std::string buffer;
                                buffer.reserve(LINES * 100);

                                for (int k{}; k < LINES; k++)
                                {
                                        buffer += generate_webhook();
                                        buffer += '\n';

                                        stats.webhooks++;
                                }

                                current_file.write(buffer.data(), buffer.size());

                                stats.files++;
                        }

                        
                }

                stats.chunks++;
        }

        const auto end = std::chrono::steady_clock::now();
        const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        const auto size = get_folder_size(FOLDER);

        std::cout << "finished in " << elapsed.count() << "ms\n";
        std::cout << "folder size: " << format_size(size) << '\n';
        std::cout << "generated " << stats.chunks << " chunks, " << stats.files << " files and " << stats.webhooks << " webhooks\n";

        return 0;
}