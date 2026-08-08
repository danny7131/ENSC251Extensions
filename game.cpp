#include "game.h"
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

Game::Game() {}

// Start and play again loop
void Game::run() {
    cout << "Welcome to Blackjack!\n\n";
    
    // Setup players and prepare the deck before starting the main game loop
    setupPlayers();
    prepareDeck();

    bool keepPlaying = true;
    while (keepPlaying && !players.empty()) {
        resetRound();
        
        takeBets(); // --- NEW: Ask for bets before dealing ---
        
        dealInitialCards();
        displayOpeningHands();
        startRound();
        displayResults();
        
        removeBankruptPlayers(); // --- NEW: Kick out players with $0 ---
        
        if (!players.empty()) {
            keepPlaying = askPlayAgain();
        } else {
            cout << "\nAll players are bankrupt! Game over.\n";
            keepPlaying = false;
        }
    }
}

// Get players info
void Game::setupPlayers() {
    int numPlayers = 0;
    
    cout << "Enter the number of players: ";
    
    // Validate input
    while (!(cin >> numPlayers) || numPlayers < 1) {
        cout << "Please enter a valid number of players (1 or more): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } 

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Get player names
    for (int i = 0; i < numPlayers; i++) {
        string playerName;
        bool duplicateFound;
        
        do {
            duplicateFound = false;
            cout << "Enter name for Player " << (i + 1) << ": ";
            getline(cin, playerName);
            
            // Assign a default name if input is empty
            if (playerName.empty()) {
                playerName = "Player " + to_string(i + 1);
            }
            
            // Check for duplicates
            for (const Player& existingPlayer: players) {
                if (existingPlayer.getName() == playerName) {
                    cout << "Error: That name is already taken. Please choose a different name.\n";
                    duplicateFound = true;
                    break;
                }
            } 
        } while (duplicateFound);

        // Create and add player to the vector (defaults to $1000 bankroll per player.h)
        players.push_back(Player(playerName));
    }
}

// Betting Phase
void Game::takeBets() {
    cout << "\n--- Betting Phase ---\n";
    for (Player& player : players) {
        int bet = 0;
        bool validBet = false;

        while (!validBet) {
            cout << player.getName() << ", you have $" << player.getBankroll() << ". Enter your bet: ";
            
            if (cin >> bet && bet > 0 && bet <= player.getBankroll()) {
                player.placeBet(bet); // Deducts the bet immediately
                validBet = true;
            } else {
                cout << "Invalid bet. Must be greater than 0 and no more than your current bankroll ($" << player.getBankroll() << ").\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }
    // Clear buffer in case of extra characters so the game doesn't skip inputs later
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
}

// Round start
void Game::startRound() {
    // Each player takes their turn
    for (Player& player : players) {
        if (deck.cardsRemaining() == 0) {
            cout << "Deck is empty. Reshuffling...\n";
            prepareDeck();
        }
        player.takeTurn(deck);
    }

    // Dealer takes turn if at least one player hasn't busted
    if (!allPlayersBusted()) {
        dealer.takeTurn(deck);
    } else {
        cout << "All players busted. Dealer wins this round.\n";
    }
}

// Reset round
void Game::resetRound() {
    // Dynamic threshold: ensure enough cards for 2 per person + some hits
    int safeThreshold = (players.size() + 1) * 5; 
    
    if (deck.cardsRemaining() < safeThreshold) {
        cout << "Reshuffling the deck...\n";
        prepareDeck();
    }

    // Reset each player's hand and busted status
    for (Player& player : players) {
        player.resetForRound();
    }
    dealer.resetForRound();
}

// Check before starting a round
void Game::prepareDeck() {
    deck.initialize();
    deck.shuffle();
}

// Deal two cards to each player and the dealer
void Game::dealInitialCards() {
    for (int i = 0; i < 2; i++) {
        for (Player& player : players) {
            player.getHand().addCard(deck.draw());
        }
        dealer.getHand().addCard(deck.draw());
    }
}

// Display the dealer's hand and each player's hand
void Game::displayOpeningHands() const {
    cout << "\n--- Opening Hands ---\n\n";
    dealer.displayHand(); 

    for (const Player& player : players) {
        displayPlayerHand(player);
    }
}

// Display a specific player's hand
void Game::displayPlayerHand(const Player& player) const {
    cout << player.getName() << "'s hand:\n";

    const vector<Card>& cards = player.getHand().getCards();
    for (const Card& card : cards) {
        cout << card.toString() << "\n";
    }

    cout << "Total: " << player.getHand().calculateTotal() << "\n\n";
}

// Check if all players have busted
bool Game::allPlayersBusted() const {
    for (const Player& player : players) {
        if (!player.isBusted()) {
            return false;
        }
    }
    return true;
}

// Handles payouts ('const' is removed from the signature)
void Game::displayResults() {
    cout << "\n--- Round Results ---\n";

    int dealerTotal = dealer.getHand().calculateTotal();
    bool dealerBusted = dealer.getHand().isBust();

    for (Player& player : players) {
        int playerTotal = player.getHand().calculateTotal();
        int betAmount = player.getCurrentBet();

        cout << player.getName() << ": ";
        
        // Determine win/loss status and award money
        if (player.isBusted()) {
            player.loseBet();
            cout << "Busted, loses $" << betAmount << ". ";
        }
        else if (dealerBusted) {
            player.winBet();
            cout << "Dealer busted, wins $" << betAmount << "! ";
        }
        else if (playerTotal > dealerTotal) {
            player.winBet();
            cout << "Wins with " << playerTotal << " against dealer's " << dealerTotal << ". Wins $" << betAmount << ". ";
        }
        else if (playerTotal == dealerTotal) {
            player.pushBet();
            cout << "Push (tie) with " << playerTotal << ". Bet of $" << betAmount << " returned. ";
        }
        else {
            player.loseBet();
            cout << "Loses with " << playerTotal << " against dealer's " << dealerTotal << ". Loses $" << betAmount << ". ";
        }
        
        // Show current bankroll after payouts
        cout << "(Bankroll: $" << player.getBankroll() << ")\n";
    }
}

// Remove players who hit $0
void Game::removeBankruptPlayers() {
    // Iterate backwards so erasing an element doesn't shift the indexes of remaining elements
    for (int i = players.size() - 1; i >= 0; i--) {
        if (players[i].isBankrupt()) {
            cout << "\n" << players[i].getName() << " is out of money and has been removed from the game!\n";
            players.erase(players.begin() + i);
        }
    }
}

// Ask the user if they want to play another round
bool Game::askPlayAgain() const {
    string response;

    while (true) {
        cout << "\nDo you want to play another round? (y/n): ";
        cin >> response;

        if (response == "y" || response == "Y") {
            return true;
        }
        else if (response == "n" || response == "N") {
            return false;
        }
        
        cout << "\nPlease enter a valid input. Enter 'y' for yes or 'n' for no.\n";
    }
}