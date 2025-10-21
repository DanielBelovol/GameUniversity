class Game {
	public:
	static const std::string CHOOSE_DIFICULT_MESSAGE = "Please choose the dificult of game";
	static const std::string CHOOSE_DIFICULT_AGAIN_MESSAGE = "Please choose the dificult of game again";

	}
	void start_game() {
		int counter;
		get_difficult_of_game();

	}

	int generate_num(Level level) {
		int randomNum = rand() % level;

		cout << randomNum;
		return 0;
	}
	void print_something(std::string message_to_print) {
		std::cout << message_to_print;
	}
	Level get_difficult_of_game(bool repeat = false) {
		if (!repeat) {
			print_something(CHOOSE_DIFICULT_MESSAGE);
		}
		else {
			print_something(CHOOSE_DIFICULT_AGAIN_MESSAGE)
		}
		enum Level level;
		std::string level_string;
		std::cin >> level_string;
		std::transform(level_string.begin(), level_string.end(), level_string.begin(), ::tolower);
		switch (level_string) :
			case"easy":level = EASY;
			break;
			case"medium":level = MEDIUM;
				break;
			case"high":level = HIGH;
				break;
			default:get_difficult_of_game(true)
				return level;
	}

};
enum Level {
	EASY = 51,
	MEDIUM = 101,
	HIGH = 251
};