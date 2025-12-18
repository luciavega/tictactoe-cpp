#include <iostream>
#include <limits>
#include "Player.hpp"
#include <cstdlib>
#include <ctime>

void draw_game_board(const char board[9]) {
    std::cout << "| " << board[0] << " | " << board[1] << " | " << board[2] << " |\n";
    std::cout << "| " << board[3] << " | " << board[4] << " | " << board[5] << " |\n";
    std::cout << "| " << board[6] << " | " << board[7] << " | " << board[8] << " |\n";
}

bool is_free_cell(const char board[9], int pos) {
    char expected = static_cast<char>('1' + pos);
    return board[pos] == expected;
}

int ask_move_human(const Player& p, const char board[9]) {
    while (true) {
        std::cout << p.name << " (" << p.symbol << "), choose antoher square (1-9): ";

        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "This is not a number. Try again.\n";
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice < 1 || choice > 9) {
            std::cout << "Out of bounds. Choose between 1 y 9.\n";
            continue;
        }

        int idx = choice - 1;
        if (!is_free_cell(board, idx)) {
            std::cout << "That square is already taken. Choose another one.\n";
            continue;
        }

        return idx;
    }
}

int ask_move_ai(const char board[9]) {
    int free_cells[9];
    int count = 0;

    for (int i = 0; i < 9; i++) {
        if (board[i] == static_cast<char>('1' + i)) {
            free_cells[count++] = i;
        }
    }

    int choice = rand() % count;
    return free_cells[choice];
}

bool is_board_full(const char board[9]) {
    for (int i = 0; i < 9; i++) {
        if (board[i] == static_cast<char>('1' + i)) return false;
    }
    return true;
}

char check_winner_symbol(const char board[9]) {
    const int wins[8][3] = {
        {0,1,2}, {3,4,5}, {6,7,8},
        {0,3,6}, {1,4,7}, {2,5,8},
        {0,4,8}, {2,4,6}
    };

    for (const auto& w : wins) {
        char a = board[w[0]];
        char b = board[w[1]];
        char c = board[w[2]];

        if (a >= '1' && a <= '9') continue; 
        if (a == b && b == c) return a;
    }
    return '\0';
}

int ask_game_mode() {
    while (true) {
        std::cout << "Welcome to TicTacToe\n";
        std::cout << "Select a game mode:\n";
        std::cout << "1. Two players\n";
        std::cout << "2. One player VS IA\n";
        std::cout << "> ";

        int mode;
        std::cin >> mode;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "That is not a number.\n\n";
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (mode == 1 || mode == 2) return mode;

        std::cout << "Opción invalida.\n\n";
    }
}

void play_game_two_players() {
    std::cout << "\n--- Mode: Two players ---\n\n";

    std::cout << "Player 1:\n";
    Player p1 = create_player();

    std::cout << "\nPlayer 2:\n";
    Player p2 = create_player_with_symbol(p1.symbol);

    char board[9] = {'1','2','3','4','5','6','7','8','9'};
    bool p1_turn = true;

    while (true) {
        std::cout << "\n";
        draw_game_board(board);

        Player& current = p1_turn ? p1 : p2;
        int move = ask_move_human(current, board);
        board[move] = current.symbol;

        char winner = check_winner_symbol(board);
        if (winner != '\0') {
            std::cout << "\n";
            draw_game_board(board);
            std::cout << "\nGanó " << (winner == p1.symbol ? p1.name : p2.name) << " 🎉\n";
            break;
        }

        if (is_board_full(board)) {
            std::cout << "\n";
            draw_game_board(board);
            std::cout << "\nTie 🤝 (match nul)\n";
            break;
        }

        p1_turn = !p1_turn;
    }
}

void play_game_vs_ai() {
    std::cout << "\n--- Mode: Player vs IA ---\n\n";

    std::cout << "Player:\n";
    Player human = create_player();

    char ai_symbol = (human.symbol == 'X') ? 'O' : 'X';
    Player ai;
    ai.name = "IA";
    ai.symbol = ai_symbol;

    char board[9] = {'1','2','3','4','5','6','7','8','9'};
    bool human_turn = true;

    while (true) {
        std::cout << "\n";
        draw_game_board(board);

        int move;
        if (human_turn) {
            move = ask_move_human(human, board);
            board[move] = human.symbol;
        } else {
            std::cout << "La IA está pensando...\n";
            move = ask_move_ai(board);
            board[move] = ai.symbol;
        }

        char winner = check_winner_symbol(board);
        if (winner != '\0') {
            std::cout << "\n";
            draw_game_board(board);

            if (winner == human.symbol) {
                std::cout << "\nYou win " << human.name << " 🎉\n";
            } else {
                std::cout << "\nAI won 🤖\n";
            }
            break;
        }

        if (is_board_full(board)) {
            std::cout << "\n";
            draw_game_board(board);
            std::cout << "\nTie 🤝 (match nul)\n";
            break;
        }

        human_turn = !human_turn;
    }
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    int mode = ask_game_mode();

    if (mode == 1) {
        play_game_two_players();
    } else {
        play_game_vs_ai();
    }

    return 0;
}

