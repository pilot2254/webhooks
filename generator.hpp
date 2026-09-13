#include <cstdlib>
#include <string>
#include <random>

inline uint64_t generate_id()
{
        static std::random_device rd;
        static std::mt19937_64 gen(rd());

        std::uniform_int_distribution<uint64_t> dist(1000000000000000000ULL, 9999999999999999999ULL);

        return dist(gen);
}

inline std::string generate_token()
{
        static constexpr char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "abcdefghijklmnopqrstuvwxyz" "0123456789-_";

        std::random_device rd;
        
        int length = sizeof(alphabet)/sizeof(char) - 1; //because i dont want to hardcode 64

        std::string result{};
        result.reserve(length);

        for (int i = 0; i < length; ++i)
        {
                result += alphabet[rd() % length];
        }

        return result;
}

inline std::string generate_webhook()
{
        return "https://discord.com/api/webhooks/" + std::to_string(generate_id()) + "/" + generate_token();
}