#define NOMINMAX

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <windows.h>

// Color constants for Windows console
enum ConsoleColor {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,  // Purple/Magenta
    BROWN = 6,
    LIGHTGRAY = 7,
    DARKGRAY = 8,
    LIGHTBLUE = 9,
    LIGHTGREEN = 10,
    LIGHTCYAN = 11,
    LIGHTRED = 12,
    LIGHTMAGENTA = 13,  // Light Purple
    YELLOW = 14,
    WHITE = 15
};

void setColor(int textColor, int bgColor = BLACK) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}

void resetColor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, WHITE);
}

class BombGame {
private:
    int bombLocation;
    int remainingAttempts;
    bool isDiffused;

public:
    BombGame() {
        // Initialize random seed
        srand(static_cast<unsigned int>(time(0)));
        
        // Generate random bomb location (1-10)
        bombLocation = rand() % 10 + 1;
        
        // Set initial values
        remainingAttempts = 3;
        isDiffused = false;
    }

    void playGame() {
        int guess;
        
        // Game loop - continues until no attempts remain or bomb is diffused
        while (remainingAttempts > 0 && !isDiffused) {
            setColor(LIGHTMAGENTA);
            std::cout << "\n** Attempts remaining: " << remainingAttempts << " **" << std::endl;
            setColor(MAGENTA);
            std::cout << "** Enter your guess (1-10): ";
            resetColor();
            
            // Input validation
            while (!(std::cin >> guess) || guess < 1 || guess > 10) {
                setColor(LIGHTRED);
                std::cout << "Invalid input! Please enter a number between 1 and 10: ";
                resetColor();
                std::cin.clear();
                std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            }
            
            // Check guess
            if (guess == bombLocation) {
                isDiffused = true;
            } else {
                remainingAttempts--;
                
                // Provide hint if attempts remain
                if (remainingAttempts > 0) {
                    setColor(YELLOW);
                    std::cout << "Wrong guess! The bomb is ";
                    if (guess < bombLocation) {
                        std::cout << "higher than " << guess << std::endl;
                    } else {
                        std::cout << "lower than " << guess << std::endl;
                    }
                    resetColor();
                }
            }
        }
    }

    void displayResult() {
        if (isDiffused) {
            setColor(LIGHTGREEN, MAGENTA);
            std::cout << "\n+----------------------------------+" << std::endl;
            std::cout << "|     Bomb diffused! You win!     |" << std::endl;
            std::cout << "+----------------------------------+" << std::endl;
            resetColor();
        } else {
            setColor(WHITE, RED);
            std::cout << "\n+----------------------------------+" << std::endl;
            std::cout << "|   BOOM! The bomb exploded!      |" << std::endl;
            std::cout << "|   It was in box " << bombLocation;
            if (bombLocation < 10) std::cout << " ";
            std::cout << "            |" << std::endl;
            std::cout << "+----------------------------------+" << std::endl;
            resetColor();
        }
    }

    bool askPlayAgain() {
        char response;
        setColor(LIGHTMAGENTA);
        std::cout << "\nDo you want to play again? (y/n): ";
        resetColor();
        
        while (!(std::cin >> response) || (response != 'y' && response != 'Y' && response != 'n' && response != 'N')) {
            setColor(LIGHTRED);
            std::cout << "Invalid input! Please enter 'y' or 'n': ";
            resetColor();
            std::cin.clear();
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        }
        
        return (response == 'y' || response == 'Y');
    }
};

int main() {
    // Set console title
    SetConsoleTitle("Purple Bomb Diffusion Game");
    
    // Purple-themed title
    setColor(LIGHTMAGENTA);
    std::cout << "\n+----------------------------------+" << std::endl;
    setColor(WHITE, MAGENTA);
    std::cout << "|     PURPLE BOMB DIFFUSION GAME  |" << std::endl;
    setColor(LIGHTMAGENTA);
    std::cout << "+----------------------------------+" << std::endl;
    
    setColor(MAGENTA);
    std::cout << "Find the bomb's location (1-10) before it explodes!" << std::endl;
    std::cout << "You have 3 attempts to find it." << std::endl;
    resetColor();
    
    bool playAgain = true;
    
    while (playAgain) {
        // Create a new game instance
        BombGame game;
        
        // Start the game
        game.playGame();
        
        // Display the result
        game.displayResult();
        
        // Ask if player wants to play again
        playAgain = game.askPlayAgain();
    }
    
    setColor(LIGHTMAGENTA);
    std::cout << "\n+----------------------------------+" << std::endl;
    std::cout << "|       Thanks for playing!       |" << std::endl;
    std::cout << "+----------------------------------+" << std::endl;
    resetColor();
    
    return 0;
} 