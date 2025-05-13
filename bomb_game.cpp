#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

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
            std::cout << "\nAttempts remaining: " << remainingAttempts << std::endl;
            std::cout << "Enter your guess (1-10): ";
            
            // Input validation
            while (!(std::cin >> guess) || guess < 1 || guess > 10) {
                std::cout << "Invalid input! Please enter a number between 1 and 10: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            
            // Check guess
            if (guess == bombLocation) {
                isDiffused = true;
            } else {
                remainingAttempts--;
                
                // Provide hint if attempts remain
                if (remainingAttempts > 0) {
                    std::cout << "Wrong guess! The bomb is ";
                    if (guess < bombLocation) {
                        std::cout << "higher than " << guess << std::endl;
                    } else {
                        std::cout << "lower than " << guess << std::endl;
                    }
                }
            }
        }
    }

    void displayResult() {
        if (isDiffused) {
            std::cout << "\nBomb diffused! You win!" << std::endl;
        } else {
            std::cout << "\nBOOM! The bomb exploded! It was in box " << bombLocation << "." << std::endl;
        }
    }

    bool askPlayAgain() {
        char response;
        std::cout << "\nDo you want to play again? (y/n): ";
        
        while (!(std::cin >> response) || (response != 'y' && response != 'Y' && response != 'n' && response != 'N')) {
            std::cout << "Invalid input! Please enter 'y' or 'n': ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        
        return (response == 'y' || response == 'Y');
    }
};

int main() {
    std::cout << "===== BOMB DIFFUSION GAME =====" << std::endl;
    std::cout << "Find the bomb's location (1-10) before it explodes!" << std::endl;
    std::cout << "You have 3 attempts to find it." << std::endl;
    
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
    
    std::cout << "\nThanks for playing!" << std::endl;
    
    return 0;
} 