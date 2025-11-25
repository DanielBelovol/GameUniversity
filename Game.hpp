#define GAME_HPP

#include <string>
#include <vector>

enum Level {
    EASY = 51,
    MEDIUM = 101,
    HIGH = 251
};

struct GameResult {
    Level level;
    std::string name_of_user;
    int attempts;
};

class Game {
public:
    static const std::string CHOOSE_DIFFICULT_MESSAGE;
    static const std::string CHOOSE_DIFFICULT_AGAIN_MESSAGE;
    static const std::string YOUR_NUMBER_IS_SMALLER_THAN_SECRET_NUMBER;
    static const std::string YOUR_NUMBER_IS_BIGGER_THAN_SECRET_NUMBER;
    static const std::string YOU_WIN;
    static const std::string YOU_LOSE;
    static const std::string TRY_TO_GUESS_NUMBER;
    static const std::string START_SCREEN_BASE_MESSAGE;
    static const std::string STATS_OPTION_MESSAGE;
    static const std::string START_SCREEN_END_MESSAGE;

    void start_game();
    void print_something(const std::string& message_to_print);
    Level get_difficult_of_game(bool repeat = false);
    int generate_num(Level level);
    int make_guess();
    std::string get_message_from_user();
    void print_stats_by_level(Level level);
    bool ask_for_bet_mode();
    int get_max_attempts();
    void show_stats_menu();
    void print_stats();

private:
    std::vector<GameResult> last_games;
    void print_box(const std::string& text);
};

