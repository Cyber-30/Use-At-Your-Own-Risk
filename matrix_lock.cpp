#include <bits/stdc++.h>
#include <chrono>
#include <thread>
#include <csignal>
using namespace std;

bool running = true;

// Ctrl+C handler
void cleanup(int) {
    cout << "\033[0m\n"; // reset colors
    running = false;
    exit(0);
}

int main() {
    signal(SIGINT, cleanup);

    string word;
    cout << "Enter a string: ";
    getline(cin, word);

    string charset =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789"
        "!@#$%^&*()-_=+[]{};:'\",.<>?/|\\ ";

    srand(time(nullptr));

    string display(word.size(), ' ');
    int locked = 0;

    // SPEED CONTROL (lower = faster)
    int frame_delay_ms = 30;
    int lock_delay_ms  = 600;

    auto last_lock = chrono::steady_clock::now();

    while (running && locked < (int)word.size()) {

        // Check if it's time to lock next character
        auto now = chrono::steady_clock::now();
        if (chrono::duration_cast<chrono::milliseconds>(now - last_lock).count() > lock_delay_ms) {
            display[locked] = word[locked];
            cout << "\a"; // typing sound
            locked++;
            last_lock = now;
        }

        // Generate frame
        for (int i = locked; i < (int)word.size(); i++) {
            display[i] = charset[rand() % charset.size()];
        }

        // 🌈 Rainbow glitch + 🟩 Matrix green
        int color = 32 + rand() % 6; // green-ish range
        cout << "\r\033[" << color << "m" << display << flush;

        this_thread::sleep_for(chrono::milliseconds(frame_delay_ms));
    }

    // Final correct word
    cout << "\r\033[32m" << word << "\033[0m\n";
    return 0;
}
