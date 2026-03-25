#include <iostream>
#include <string>
using namespace std;

struct Song {
    string title;
    string artist;
    int ratings[3];
    Song* next;
    Song* prev;
};

void addSong(Song*& head, Song*& tail, Song*& current, string title, string artist, int r1, int r2, int r3) {
    Song* newSong = new Song;
    newSong->title = title;
    newSong->artist = artist;
    newSong->ratings[0] = r1;
    newSong->ratings[1] = r2;
    newSong->ratings[2] = r3;
    newSong->next = nullptr;
    newSong->prev = nullptr;

    if (head == nullptr) {
        head = newSong;
        tail = newSong;
        current = newSong;
    } else {
        tail->next = newSong;
        newSong->prev = tail;
        tail = newSong;
    }

    cout << "Song added successfully.\n";
}

void moveNext(Song*& current) {
    if (current == nullptr) {
        cout << "Playlist is empty.\n";
        return;
    }

    if (current->next == nullptr) {
        cout << "You are already at the last song.\n";
        return;
    }

    current = current->next;
    cout << "Moved to next song.\n";
}

void movePrev(Song*& current) {
    if (current == nullptr) {
        cout << "Playlist is empty.\n";
        return;
    }

    if (current->prev == nullptr) {
        cout << "You are already at the first song.\n";
        return;
    }

    current = current->prev;
    cout << "Moved to previous song.\n";
}

void removeCurrent(Song*& head, Song*& tail, Song*& current) {
    if (current == nullptr) {
        cout << "There is no current song to remove.\n";
        return;
    }

    Song* toDelete = current;

    if (head == tail) {
        head = nullptr;
        tail = nullptr;
        current = nullptr;
    } 
    else if (toDelete == head) {
        head = head->next;
        head->prev = nullptr;
        current = head;
    } 
    else if (toDelete == tail) {
        tail = tail->prev;
        tail->next = nullptr;
        current = tail;
    } 
    else {
        toDelete->prev->next = toDelete->next;
        toDelete->next->prev = toDelete->prev;
        current = toDelete->next;
    }

    cout << "Removed song: " << toDelete->title << " by " << toDelete->artist << endl;
    delete toDelete;
}

void displayPlaylist(Song* head, Song* current) {
    if (head == nullptr) {
        cout << "Playlist is empty.\n";
        return;
    }

    Song* temp = head;
    cout << "\n========== PLAYLIST ==========\n";

    while (temp != nullptr) {
        if (temp == current) {
            cout << "-> ";
        } else {
            cout << "   ";
        }

        cout << "Title: " << temp->title
             << " | Artist: " << temp->artist
             << " | Ratings: ";

        for (int i = 0; i < 3; i++) {
            cout << temp->ratings[i];
            if (i < 2) {
                cout << ", ";
            }
        }

        cout << endl;
        temp = temp->next;
    }

    cout << "==============================\n";
}

void deleteAll(Song*& head, Song*& tail, Song*& current) {
    Song* temp = head;

    while (temp != nullptr) {
        Song* nextNode = temp->next;
        delete temp;
        temp = nextNode;
    }

    head = nullptr;
    tail = nullptr;
    current = nullptr;
}

int main() {
    Song* head = nullptr;
    Song* tail = nullptr;
    Song* current = nullptr;

    int choice;
    string title, artist;
    int r1, r2, r3;

    do {
        cout << "\n===== Music Playlist Manager =====\n";
        cout << "1. Add a new song\n";
        cout << "2. Move to next song\n";
        cout << "3. Move to previous song\n";
        cout << "4. Remove current song\n";
        cout << "5. Display playlist\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter song title: ";
                getline(cin, title);

                cout << "Enter artist name: ";
                getline(cin, artist);

                cout << "Enter 3 critic ratings: ";
                cin >> r1 >> r2 >> r3;
                cin.ignore();

                addSong(head, tail, current, title, artist, r1, r2, r3);
                break;

            case 2:
                moveNext(current);
                break;

            case 3:
                movePrev(current);
                break;

            case 4:
                removeCurrent(head, tail, current);
                break;

            case 5:
                displayPlaylist(head, current);
                break;

            case 0:
                cout << "Closing playlist manager.\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 0);

    deleteAll(head, tail, current);
    return 0;
}