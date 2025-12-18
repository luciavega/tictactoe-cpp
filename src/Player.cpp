#include "Player.hpp"
#include <iostream>
#include <limits>

static char ask_symbol(char forbidden = '\0') {
    while (true) {
        std::cout << "Elige un simbolo (X u O): ";
        char s;
        std::cin >> s;

        if (s >= 'a' && s <= 'z') {
            s = s - 'a' + 'A';
        }

        if (s != 'X' && s != 'O') {
            std::cout << "Simbolo invalido. Solo se permite X u O.\n";
            continue;
        }

        if (forbidden != '\0' && s == forbidden) {
            std::cout << "Ese simbolo ya esta en uso. Elegi el otro.\n";
            continue;
        }

        return s;
    }

}

static std::string ask_name() {
    std::string name;
    std::cout << "Nombre del jugador: ";
    std::getline(std::cin, name);
    while (name.empty()) {
        std::cout << "El nombre no puede estar vacio. Probá otra vez: ";
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
