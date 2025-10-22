# 🎯 Guess The Number Game (C++)

## 📘 Description  
This is a console-based C++ game where the player tries to guess a secret number chosen by the program.  
The game allows you to select a difficulty level and keeps track of your last 5 games.

## 🕹️ How to Play  
1. When the program starts, you’ll see a welcome message.  
2. Type `/start` to begin the game or `/stats` to view your recent game stats.  
3. Choose the difficulty level:  
   - **easy** — range from 0 to 50  
   - **medium** — range from 0 to 100  
   - **high** — range from 0 to 250  
4. The program will generate a random secret number within the selected range.  
5. Keep guessing until you find the correct number.  
6. After each guess, you’ll be told whether your number is smaller or bigger than the secret one.  
7. When you win, the result (difficulty and attempts) is saved in your game history.

## 📊 Statistics  
The `/stats` command displays your top 5 games, sorted by the fewest attempts.  

## How to start a game?
You need to compile and start your project with these commands:
g++ Main.cpp Game.cpp -o GuessGame
./GuessGame
