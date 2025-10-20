#include <iostream>

enum class GameState: u_int8_t {
    GAME = 1,
    INVENTORY = 2,
    CHARACTER_INFO = 3,
    EXIT = 4
};

bool exitGame = false;
GameState currentState = GameState::GAME;

std::string GetTitle(GameState state) {
    using std::string;
    string title;
    switch(state) {
        case GameState::GAME:
            title = "THE LOST CITY OF ZENDAR — Adventure Game";
            break;
        case GameState::INVENTORY:
            title = "INVENTORY — THE LOST CITY";
            break;
        case GameState::CHARACTER_INFO:
            title = "CHARACTER INFO — THE LOST CITY";
            break;
        case GameState::EXIT:
            title = "Exit Game";
            break;
        default:
            title = "Adventure Game";
            break;
    }
    return title;
}
std::string GameBanner(GameState state) {
    using std::string;

    string divider = "============================================================";
    string title = GetTitle(state);

    int titleLength = title.length();
    int dividerLength = divider.length();
    int spacerLength = (dividerLength - titleLength) / 2;

    string spacer = ""; // to center the title
    for (int i = 0; i < spacerLength; ++i) {
        spacer += " ";
    }

    string banner = 
        divider + "\n" +
        spacer + title + "\n" +
        divider + "\n";
    
    return banner;
}

std::string Menu() {
    using std::string, std::array;

    array<string, 4> menuItems = {"Game", "Inventory", "Character Info", "Exit"};

    int currentIndex = static_cast<int>(currentState) - 1;
    menuItems[currentIndex] = "[" + menuItems[currentIndex] + "]";
    
    string menu = "";
    for (const auto& item : menuItems) {
        menu += item + " | ";
    }

    menu.pop_back(); // Remove the last space
    menu.pop_back(); // Remove the last pipe
    menu.pop_back(); // Remove the last space

    return menu;
}

std::string ClearScreen() {
    return "\033[2J\033[H";
}

std::string DisplayGame() {
    return ClearScreen() + "\n" + GameBanner(currentState) + "\n" + Menu();
}

void ProcessCommand(const std::string& command) {
    using std::cout, std::endl, std::string, std::transform;

    string commandLowerCased = command;
    transform(commandLowerCased.begin(), commandLowerCased.end(), commandLowerCased.begin(), ::tolower);

    if (commandLowerCased == "exit" || commandLowerCased == "e") {
        currentState = GameState::EXIT;
        exitGame = true;
    } else if (commandLowerCased == "inventory" || commandLowerCased == "i") {
        currentState = GameState::INVENTORY;
    } else if (commandLowerCased == "character" || commandLowerCased == "c") {
        currentState = GameState::CHARACTER_INFO;
    } else if (commandLowerCased == "game" || commandLowerCased == "g") {
        currentState = GameState::GAME;
    }
}

void InputPrompt() {
    using std::cout;
    using std::cin;
    using std::string;

    string input;
    cout << "\n> ";
    cin >> input;

    ProcessCommand(input);
}

int main() {
    using std::cout;

    while (!exitGame) {
        cout << DisplayGame();
        InputPrompt();
    }

    cout << DisplayGame();
    
    return 0;
}
