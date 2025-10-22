#include "Game.hpp"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

const std::string Game::CHOOSE_DIFFICULT_MESSAGE =
    "Please choose the difficulty of the game (easy / medium / high):";
const std::string Game::CHOOSE_DIFFICULT_AGAIN_MESSAGE =
    "Invalid input. Please choose the difficulty again (easy / medium / high):";
const std::string Game::YOUR_NUMBER_IS_SMALLER_THAN_SECRET_NUMBER =
    "❌ You didn’t guess it — your guess is smaller than the secret number.";
const std::string Game::YOUR_NUMBER_IS_BIGGER_THAN_SECRET_NUMBER =
    "❌ You didn’t guess it — your guess is bigger than the secret number.";
const std::string Game::YOU_WIN =
    "✅ Congratulations, you won!";
const std::string Game::TRY_TO_GUESS_NUMBER =
    "Try to guess the number in this range: from 0 to ";
const std::string Game::START_SCREEN_MESSAGE =
    "Hi! Write /start to start the game or /stats to view your last 5 games.";

void Game::start_screen() {
    print_something(START_SCREEN_MESSAGE);
}

void Game::start_game() {
    while (true) {
        print_something(START_SCREEN_MESSAGE);
        std::string message_from_user = get_message_from_user();

        if (message_from_user == "/start") {
            Level level = get_difficult_of_game();
            int random_num = generate_num(level);
            int num_from_user = -1;
            int attempts = 0;

            print_something(TRY_TO_GUESS_NUMBER + std::to_string(level - 1));

            while (num_from_user != random_num) {
                num_from_user = make_choose();
                attempts++;

                if (num_from_user < random_num) {
                    print_something(YOUR_NUMBER_IS_SMALLER_THAN_SECRET_NUMBER);
                } else if (num_from_user > random_num) {
                    print_something(YOUR_NUMBER_IS_BIGGER_THAN_SECRET_NUMBER);
                } else {
                    print_something(YOU_WIN);
                }
            }

            // сохраняем количество попыток
            // сохраняем результат
        if (last_games.size() == 5) {
            last_games.erase(last_games.begin());
        }
        last_games.push_back({ level, attempts });


        } else if (message_from_user == "/stats") {
            print_stats();
        } else {
            print_something("Unknown command. Please write /start or /stats.");
        }
    }
}

int Game::generate_num(Level level) {
    return rand() % level;
}

int Game::make_choose() {
    int res;
    std::cin >> res;
    return res;
}

std::string Game::get_message_from_user() {
    std::string input;
    std::cout << "\n> ";
    std::cin >> input;
    return input;
}

void Game::print_something(const std::string& message_to_print) {
    std::cout << message_to_print << std::endl;
}

Level Game::get_difficult_of_game(bool repeat) {
    if (!repeat) {
        print_something(CHOOSE_DIFFICULT_MESSAGE);
    } else {
        print_something(CHOOSE_DIFFICULT_AGAIN_MESSAGE);
    }

    std::string level_string;
    std::cin >> level_string;
    std::transform(level_string.begin(), level_string.end(), level_string.begin(), ::tolower);

    if (level_string == "easy") {
        return EASY;
    } else if (level_string == "medium") {
        return MEDIUM;
    } else if (level_string == "high") {
        return HIGH;
    } else {
        return get_difficult_of_game(true);
    }
}

void Game::print_stats() {
    if (last_games.empty()) {
        print_something("You have no games yet!");
        return;
    }

    print_something("📊 Last 5 games (attempts needed to win):");
    for (size_t i = 0; i < last_games.size(); ++i) {
    std::string level_name;
    switch (last_games[i].level) {
        case EASY: level_name = "Easy"; break;
        case MEDIUM: level_name = "Medium"; break;
        case HIGH: level_name = "High"; break;
    }

    std::cout << "Game " << (i + 1)
              << " — Level: " << level_name
              << " | Attempts: " << last_games[i].attempts
              << std::endl;
}

}
