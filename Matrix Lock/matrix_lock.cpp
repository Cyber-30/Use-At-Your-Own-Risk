#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <csignal>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

bool running = true;

// Ctrl+C handler
void cleanup(int) {
    cout << "\033[0m\n"; // reset colors
    running = false;
    exit(0);
}

#ifdef _WIN32
void enableANSI() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return;

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}
#endif

int main() {

#ifdef _WIN32
    enableANSI();   // Enable colors on Windows
#endif

    signal(SIGINT, cleanup);

    string word;
    cout << "Enter a string: ";
    getline(cin, word);

    string charset =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789"
        "!@#$%^&*()-_=+[]{};:'\",.<>?/|\\ ";

    srand(static_cast<unsigned>(time(nullptr)));

    string display(word.size(), ' ');
    int locked = 0;

    // SPEED CONTROL
    int frame_delay_ms = 30;
    int lock_delay_ms  = 600;

    auto last_lock = chrono::steady_clock::now();

    while (running && locked < (int)word.size()) {

        auto now = chrono::steady_clock::now();
        if (chrono::duration_cast<chrono::milliseconds>(now - last_lock).count() > lock_delay_ms) {
            display[locked] = word[locked];
            cout << "\a"; // beep
            locked++;
            last_lock = now;
        }

        for (int i = locked; i < (int)word.size(); i++) {
            display[i] = charset[rand() % charset.size()];
        }

        int color = 32 + rand() % 6;
        cout << "\r\033[" << color << "m" << display << flush;

        this_thread::sleep_for(chrono::milliseconds(frame_delay_ms));
    }

    cout << "\r\033[32m" << word << "\033[0m\n";
    return 0;
}
