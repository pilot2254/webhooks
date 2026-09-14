#pragma once

#include "includes.hpp"

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