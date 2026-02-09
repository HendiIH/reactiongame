#include <iostream>
#include <windows.h>
#include <random>
#include <unordered_map>
#include <string>
#include <chrono>
#pragma comment(lib, "user32.lib")

int main()
{

    std::vector<int> keys = {VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT};
    std::vector<std::string> key_names = {"UP", "DOWN", "LEFT", "RIGHT"};

    std::random_device rando;
    
    std::mt19937 gen(rando());
    std::uniform_int_distribution<> distribution(0, key_names.size() - 1);

    bool loop = true;
    while (loop)
    {
        int random_keys = distribution(gen);
        int index_key_names = keys[random_keys];

        std::cout << "Press something the same as what key is appearing" << std::endl;
        std::cout << "Press: " << key_names[random_keys] << std::endl;

        for (int key = 8; key <= 190; ++key)
        {
            while (GetAsyncKeyState(key) & 0x8000)
            {
                Sleep(10);
            }
        }

        auto start = std::chrono::high_resolution_clock::now();

        bool pressed = false;
        bool game_start = true;
        while (game_start)
        {
            if (GetAsyncKeyState(index_key_names) & 0x8000)
            {
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> reaction_time = end - start;
                std::cout << "Correct! Reaction time: " << reaction_time.count() << " ms\n";
                pressed = true;
                game_start = false;
                // Sleep(200);
                break;
            }
            for (int key = 8; key <= 190; ++key)
            {
                if (key != index_key_names && GetAsyncKeyState(key) & 0x8000)
                {
                    std::cout << "Wrong key pressed! You lose.\n";
                    pressed = false;
                    game_start = false;
                    break;
                }
            }

            auto now = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = now - start;
            if (elapsed.count() > 0.48)
            {
                std::cout << "Too slow!\n";
                pressed = false;
                game_start = false;
                break;
            }

            Sleep(100);
        }

        loop = false;
        break;

        Sleep(500);
    }
    return 0;
}