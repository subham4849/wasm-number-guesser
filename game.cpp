#include <cstdlib>    // For rand() and srand()
#include <ctime>  
#include <cstdio>    // For time()
#include <emscripten.h> // Emscripten helper functions

// These variables will store the game's state
int secretNumber;
int attempts;
int maxAttempts;

// This tells C++ to make these functions available to other languages (like JS)
// EMSCRIPTEN_KEEPALIVE prevents the compiler from removing them as "unused"
extern "C" {

EMSCRIPTEN_KEEPALIVE
void startGame(int difficulty) {
    // Seed the random number generator
    srand(time(0));

    attempts = 0;

    if (difficulty == 1) {
        secretNumber = rand() % 50 + 1;
        maxAttempts = 5;
    } else if (difficulty == 2) {
        secretNumber = rand() % 100 + 1;
        maxAttempts = 7;
    } else {
        secretNumber = rand() % 200 + 1;
        maxAttempts = 10;
    }
}

EMSCRIPTEN_KEEPALIVE
const char* makeGuess(int guess) {
    attempts++;

    if (guess == secretNumber) {
        return "CONGRATULATIONS! You guessed the number!";
    }

    if (attempts >= maxAttempts) {
        // We need a static buffer to safely return a formatted string
        static char loss_message[100];
        snprintf(loss_message, sizeof(loss_message), "You lost! The secret number was %d.", secretNumber);
        return loss_message;
    }

    if (guess > secretNumber) {
        return "Your guess is too high.";
    } else {
        return "Your guess is too low.";
    }
}

EMSCRIPTEN_KEEPALIVE
int getAttempts() {
    return attempts;
}

EMSCRIPTEN_KEEPALIVE
int getMaxAttempts() {
    return maxAttempts;
}

} // extern "C"