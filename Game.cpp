#include "Game.hpp"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cctype>

// Colors ANSI for console
#define COLOR_RESET   "\033[0m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_RED     "\033[31m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_CYAN    "\033[36m"

// Messages
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
const std::string Game::YOU_LOSE =
    std::string(COLOR_RED) + "💔 Game Over! You've run out of attempts!" + COLOR_RESET;
const std::string Game::TRY_TO_GUESS_NUMBER =
    "Try to guess the number in this range: from 0 to ";
const std::string Game::START_SCREEN_BASE_MESSAGE =
"╔══════════════════════════════════╗\n"
"║ 🎯 Guess the Number Game!        ║\n"
"║ Type /start to play              ║\n";
const std::string Game::STATS_OPTION_MESSAGE =
"║ Type /stats to see TOP 5         ║\n";
const std::string Game::START_SCREEN_END_MESSAGE =
"╚══════════════════════════════════╝\n";

// util function to check if a string is a number
static bool isNumber(const std::string& s) {
    if (s.empty()) return false;
    for (char c : s) {
        if (!isdigit(static_cast<unsigned char>(c))) return false;
    }
    return true;
}

// Printing something inside a box
void Game::print_box(const std::string &text) {
    std::cout << COLOR_CYAN << "╔";
    for (size_t i = 0; i < text.size() + 2; i++) std::cout << "═";
    std::cout << "╗\n║ " << COLOR_RESET << text << COLOR_CYAN << " ║\n╚";
    for (size_t i = 0; i < text.size() + 2; i++) std::cout << "═";
    std::cout << "╝" << COLOR_RESET << "\n";
}

// Question about bet mode
bool Game::ask_for_bet_mode() {
    std::string input;
    std::cout << COLOR_CYAN << "Do you want to play in bet mode? (yes/no): " << COLOR_RESET;
    std::cin >> input;
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);

    if (input == "yes" || input == "y") return true;
    if (input == "no" || input == "n") return false;

    print_something(COLOR_RED + std::string("Invalid input!") + COLOR_RESET);
    return ask_for_bet_mode();
}

// Qouanitiy of attempts
int Game::get_max_attempts() {
    std::string input;
    std::cout << COLOR_CYAN << "Enter maximum number of attempts: " << COLOR_RESET;
    std::cin >> input;

    if (isNumber(input)) {
        try {
            int attempts = std::stoi(input);
            if (attempts > 0) return attempts;
            print_something(COLOR_RED + std::string("Number must be greater than 0!") + COLOR_RESET);
        } catch (...) {
            print_something(COLOR_RED + std::string("Invalid number!") + COLOR_RESET);
        }
    } else {
        print_something(COLOR_RED + std::string("Invalid input!") + COLOR_RESET);
    }
    return get_max_attempts();
}

// Generate secret number
int Game::generate_num(Level level) {
    return rand() % level;
}

// Checking the guess
int Game::make_guess() {
    std::string input;
    std::cin >> input;
    if (isNumber(input)) return std::stoi(input);
    std::cout << COLOR_RED << "Invalid input. Please enter a number." << COLOR_RESET << std::endl;
    return make_guess();
}

// Getting commancd from user
std::string Game::get_message_from_user() {
    std::string input;
    std::cout << COLOR_CYAN << "\n> " << COLOR_RESET;
    std::cin >> input;
    return input;
}

// Printing a message
void Game::print_something(const std::string &message_to_print) {
    std::cout << message_to_print << std::endl;
}

// Getting difficulty level
Level Game::get_difficult_of_game(bool repeat) {
    if (!repeat)
        print_something(CHOOSE_DIFFICULT_MESSAGE);
    else
        print_something(CHOOSE_DIFFICULT_AGAIN_MESSAGE);

    std::string level_string;
    std::cin >> level_string;
    std::transform(level_string.begin(), level_string.end(), level_string.begin(), ::tolower);

    if (level_string == "easy") return EASY;
    if (level_string == "medium") return MEDIUM;
    if (level_string == "high") return HIGH;

    return get_difficult_of_game(true);
}

// Main game loop
void Game::start_game() {
    srand(static_cast<unsigned>(time(nullptr)));

    while (true) {
        std::string start_screen = START_SCREEN_BASE_MESSAGE;
        if (!last_games.empty()) start_screen += STATS_OPTION_MESSAGE;
        start_screen += START_SCREEN_END_MESSAGE;

        std::cout << COLOR_CYAN << start_screen << COLOR_RESET;

        std::string cmd = get_message_from_user();

        if (cmd == "/start") {
            std::string user_name;
            Level level = get_difficult_of_game();

            bool bet_mode = ask_for_bet_mode();
            int max_attempts = bet_mode ? get_max_attempts() : -1;

            int secret = generate_num(level);
            int attempts = 0;
            int guess = -1;
            bool win = false;

            std::string msg = TRY_TO_GUESS_NUMBER + std::to_string(level - 1);
            if (bet_mode) msg += " | Max attempts: " + std::to_string(max_attempts);
            print_box(msg);

            while (true) {
                std::cout << COLOR_CYAN << "Enter number: " << COLOR_RESET;
                guess = make_guess();
                attempts++;

                if (guess < secret) {
                    print_something(std::to_string(attempts) + " " + YOUR_NUMBER_IS_SMALLER_THAN_SECRET_NUMBER);
                } else if (guess > secret) {
                    print_something(std::to_string(attempts) + " " + YOUR_NUMBER_IS_BIGGER_THAN_SECRET_NUMBER);
                } else {
                    print_something(YOU_WIN);
                    std::cout << COLOR_YELLOW << "Enter your name: " << COLOR_RESET;
                    std::cin >> user_name;

                    last_games.push_back({level, user_name, attempts});
                    std::sort(last_games.begin(), last_games.end(),
                        [](const GameResult& a, const GameResult& b){ return a.attempts < b.attempts; });
                    if (last_games.size() > 5) last_games.resize(5);
                    win = true;
                    break;
                }

                if (bet_mode && attempts >= max_attempts) {
                    print_something(YOU_LOSE);
                    std::cout << COLOR_RED << "The secret number was: " << secret << COLOR_RESET << std::endl;
                    break;
                }
            }

        } else if (cmd == "/stats") {
            if (last_games.empty()) print_something("No games yet.");
            else show_stats_menu();
        } else {
            print_something("Unknown command. Please write /start or /stats.");
        }
    }
}

// Menu to show stats
//method to show stats menu with difficulty tabs
void Game::show_stats_menu() {
    std::string input;
    while (true) {
        std::cout << COLOR_CYAN << "\nSelect difficulty to view stats:" << COLOR_RESET << std::endl;
        std::cout << COLOR_YELLOW << "[1] Easy  [2] Medium  [3] High  [exit] Return to menu" << COLOR_RESET << std::endl;
        std::cout << COLOR_CYAN << "> " << COLOR_RESET;
        std::cin >> input;
        std::transform(input.begin(), input.end(), input.begin(), ::tolower);

        if (input == "exit") {
            break;
        }

        Level selected_level;
        if (input == "1") {
            selected_level = EASY;
        } else if (input == "2") {
            selected_level = MEDIUM;
        } else if (input == "3") {
            selected_level = HIGH;
        } else {
            print_something(COLOR_RED + std::string("Invalid option!") + COLOR_RESET);
            continue;
        }

        // now print stats for the selected level
        print_stats_by_level(selected_level);
    }
}


// Print stats by level
void Game::print_stats_by_level(Level level) {
    std::string name = (level == EASY ? "EASY" : level == MEDIUM ? "MEDIUM" : "HIGH");
    std::vector<GameResult> filtered;
    for (auto& g : last_games) if (g.level == level) filtered.push_back(g);

    std::sort(filtered.begin(), filtered.end(),
        [](const GameResult& a, const GameResult& b){ return a.attempts < b.attempts; });

    if (filtered.size() > 5) filtered.resize(5);
    print_box("🏆 TOP 5 - " + name + " 🏆");

    if (filtered.empty())
        std::cout << COLOR_YELLOW << "No games for this level." << COLOR_RESET << std::endl;
    else
        for (size_t i = 0; i < filtered.size(); i++)
            std::cout << COLOR_GREEN << (i+1) << ". " << filtered[i].name_of_user
                      << " | Attempts: " << filtered[i].attempts << COLOR_RESET << std::endl;
}
