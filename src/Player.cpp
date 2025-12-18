#include "Player.hpp"
#include <iostream>
#include <limits>

static char ask_symbol(char forbidden = '\0') {
    while (true) {
        std::cout << "Choose a symbol (X or O): ";
        char s;
        std::cin >> s;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Normalize to uppercase
        if (s >= 'a' && s <= 'z') {
            s = s - 'a' + 'A';
        }

        if (s != 'X' && s != 'O') {
            std::cout << "Invalid symbol. Please choose X or O.\n";
            continue;
        }

        if (forbidden != '\0' && s == forbidden) {
            std::cout << "This symbol is already taken. Please choose the other one.\n";
            continue;
        }

        return s;
    }
}

static std::string ask_name() {
    std::string name;
    std::cout << "Player name: ";
    std::getline(std::cin, name);

    while (name.empty()) {
        std::cout << "Name cannot be empty. Please try again: ";
        std::getline(std::cin, name);
    }

    return name;
}

Player create_player() {
    Player p;
    p.name = ask_name();
    p.symbol = ask_symbol();
    return p;
}

Player create_player_with_symbol(char forbidden) {
    Player p;
    p.name = ask_name();
    p.symbol = ask_symbol(forbidden);
    return p;
}
