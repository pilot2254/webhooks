#pragma once

#include "includes.hpp"

inline uint64_t generate_id()
{
        static std::random_device rd;
        static std::mt19937_64 gen(rd());

        static std::uniform_int_distribution<uint64_t> dist(1000000000000000000ULL, 9999999999999999999ULL);

        return dist(gen);
}

inline std::string generate_token()
{
        static constexpr char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "abcdefghijklmnopqrstuvwxyz" "0123456789-_";

        static constexpr std::size_t length = sizeof(alphabet) - 1;

        static std::random_device rd;
        static std::mt19937_64 gen(rd());
        static std::uniform_int_distribution<std::size_t> dist(0, length - 1);

        std::string result;
        result.resize(length);

        for (char &c : result) c = alphabet[dist(gen)];

        return result;
}

inline std::string generate_webhook()
{
        return "https://discord.com/api/webhooks/" + std::to_string(generate_id()) + "/" + generate_token();
}