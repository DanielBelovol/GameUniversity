#include "Game.hpp"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

// Ansi colors for console
#define COLOR_RESET   "\033[0m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_RED     "\033[31m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_CYAN    "\033[36m"

// messages
const std::string Game::CHOOSE_DIFFICULT_MESSAGE =
    "Please choose the difficulty of the game (easy / medium / high):";
const std::string Game::CHOOSE_DIFFICULT_AGAIN_MESSAGE =
    "Invalid input. Please choose the difficulty again (easy / medium / high):";
const std::string Game::YOUR_NUMBER_IS_SMALLER_THAN_SECRET_NUMBER =
    std::string(COLOR_YELLOW) + "❌ Too small! Try a bigger number." + COLOR_RESET;
const std::string Game::YOUR_NUMBER_IS_BIGGER_THAN_SECRET_NUMBER =
    std::string(COLOR_YELLOW) + "❌ Too big! Try a smaller number." + COLOR_RESET;
const std::string Game::YOU_WIN =
    std::string(COLOR_GREEN) + "✅ Congratulations! You guessed the number!" + COLOR_RESET;
const std::string Game::TRY_TO_GUESS_NUMBER =
    "Try to guess the number in this range: from 0 to ";
const std::string Game::START_SCREEN_MESSAGE =
"╔══════════════════════════════════╗\n"
"║ 🎯 Guess the Number Game!        ║\n"
"║ Type /start to play              ║\n"
"║ Type /stats to see TOP 5         ║\n"
"╚══════════════════════════════════╝\n";

//method to print something in graphic box
void Game::print_box(const std::string &text) {
    std::cout << COLOR_CYAN << "╔";
    for(int i = 0; i<text.size();i++){
        std::cout<<"═";
    }
    std::cout << "╗\n";
    std::cout << "║"<< COLOR_CYAN<< text<< "║\n";
    std::cout<<"╚";
    for(int i = 0; i<text.size();i++){
        std::cout<<"═";
    }
    std::cout<<"╝\n";
}

//main method to start game
void Game::start_game() {
    while (true) {
        std::cout<<COLOR_CYAN<<START_SCREEN_MESSAGE<<std::endl;
        // /start or /stats
        std::string message_from_user = get_message_from_user();

        if (message_from_user == "/start") {
            std::string user_name;
            //gettin difficult from user
            Level level = get_difficult_of_game();
            //generating random number
            int random_num = generate_num(level);
            int num_from_user = -1;
            int attempts = 0;

            print_box(TRY_TO_GUESS_NUMBER + std::to_string(level - 1));

            while (num_from_user != random_num) {
                std::cout << COLOR_CYAN << "Enter number: " << COLOR_RESET;
                num_from_user = make_guess();
                attempts++;

                if (num_from_user < random_num)
                    print_something(YOUR_NUMBER_IS_SMALLER_THAN_SECRET_NUMBER);
                else if (num_from_user > random_num)
                    print_something(YOUR_NUMBER_IS_BIGGER_THAN_SECRET_NUMBER);
                else {
                    print_something(YOU_WIN);
                    std::cout << COLOR_YELLOW << "Enter your name: " << COLOR_RESET;
                    std::cin >> user_name;
                }
            }

            // saving results of game
            last_games.push_back({level, user_name, attempts});

            // sorting top 5 games
            std::sort(last_games.begin(), last_games.end(),
                      [](const GameResult &a, const GameResult &b) {
                          return a.attempts < b.attempts;
                      });


            // if size of last games is bigger than 5 we change size to top 5
            if (last_games.size() > 5)
                last_games.resize(5);

        } else if (message_from_user == "/stats") {
            print_stats();
        } else {
            print_something("Unknown command. Please write /start or /stats.");
        }
    }
}

int Game::generate_num(Level level) { return rand() % level; }

//user tries to guess number
int Game::make_guess() {
    int res;
    std::cin >> res;
    return res;
}

//user writes /start or /stats
std::string Game::get_message_from_user() {
    std::string input;
    std::cout << COLOR_CYAN << "\n> " << COLOR_RESET;
    std::cin >> input;
    return input;
}

//method to print something
void Game::print_something(const std::string &message_to_print) {
    std::cout << message_to_print << std::endl;
}

//user writes difficult of game
Level Game::get_difficult_of_game(bool repeat) {
    if (!repeat)
        print_something(CHOOSE_DIFFICULT_MESSAGE);
    else
        print_something(CHOOSE_DIFFICULT_AGAIN_MESSAGE);

    std::string level_string;
    std::cin >> level_string;
    std::transform(level_string.begin(), level_string.end(), level_string.begin(), ::tolower);

    if (level_string == "easy")
        return EASY;
    else if (level_string == "medium")
        return MEDIUM;
    else if (level_string == "high")
        return HIGH;
    else
        return get_difficult_of_game(true);
}

//method that prints stats of games
void Game::print_stats() {
    if (last_games.empty()) {
        print_box("You have no games yet!");
        return;
    }

    print_box("🏆 TOP 5 PLAYERS 🏆");
    for (size_t i = 0; i < last_games.size(); ++i) {
        std::string level_name;
        switch (last_games[i].level) {
        case EASY: level_name = "Easy"; break;
        case MEDIUM: level_name = "Medium"; break;
        case HIGH: level_name = "High"; break;
        }

        std::cout << COLOR_GREEN
                  << (i + 1) << ". "
                  << last_games[i].name_of_user
                  << " — Level: " << level_name
                  << " | Attempts: " << last_games[i].attempts
                  << COLOR_RESET << std::endl;
    }
}
