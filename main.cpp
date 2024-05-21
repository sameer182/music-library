#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

// Song class definition
class Song {
public:
    string track;
    string artist;
    int duration;

    // Constructor to initialize a song
    Song(string t, string a, int d) {
        track = t;
        artist = a;
        duration = d;
    }

    // Function to print the details of a song
    void printSong() {
        cout << "Track: " << track << endl;
        cout << "Artist: " << artist << endl;
        cout << "Duration (seconds): " << duration << endl;
    }

    // Compare two songs
    bool operator==(const Song& other) const {
        return track == other.track && artist == other.artist && duration == other.duration;
    }
};

vector<Song> songs;

// Check if a song is already in the library
bool isSongInLibrary(const Song& song) {
    return find(songs.begin(), songs.end(), song) != songs.end();
}

// Load songs from a file
void loadSongsFromFile(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Failed to open file " << filename << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        string track, artist, duration_str;
        int duration;
        stringstream ss(line);
        getline(ss, track, '\t');
        getline(ss, artist, '\t');
        getline(ss, duration_str, '\t');
        duration = stoi(duration_str);
        Song song(track, artist, duration);
        if (!isSongInLibrary(song)) {
            songs.push_back(song);
        }
    }
    file.close();
}

// Print all songs in the library
void printSongs() {
    for (int i = 0; i < songs.size(); i++) {
        songs[i].printSong();
        cout << endl;
    }
}

// Search for songs by track name
void searchSongs() {
    string query;
    cout << "Enter track to search: ";
    getline(cin, query);
    bool found = false;
    for (int i = 0; i < songs.size(); i++) {
        if (songs[i].track.find(query) != string::npos) {
            songs[i].printSong();
            cout << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No songs found with track containing \"" << query << "\"" << endl;
    }
}

// Search for songs by artist name
void searchSongsByArtist() {
    string query;
    cout << "Enter artist to search: ";
    getline(cin, query);
    bool found = false;
    for (int i = 0; i < songs.size(); i++) {
        if (songs[i].artist.find(query) != string::npos) {
            songs[i].printSong();
            cout << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No songs found with artist containing \"" << query << "\"" << endl;
    }
}

// Add a new song the library
void addSong() {
    string track, artist, duration_str;
    int duration;
    cout << "Enter track name: ";
    getline(cin, track);
    cout << "Enter artist/band name: ";
    getline(cin, artist);
    cout << "Enter duration (seconds): ";
    getline(cin, duration_str);
    duration = stoi(duration_str);
    Song song(track, artist, duration);
        if (!isSongInLibrary(song)) {
        songs.push_back(song);
        cout << "\n Song added successfully!" << endl;
    } else {
        cout << "\n Song already exists in the library." << endl;
    }
}

// Remove songs from the library
void removeSong() {
    string query;
    cout << "Enter track name to remove: ";
    getline(cin, query);
    bool found = false;
    for (int i = 0; i < songs.size(); i++) {
        if (songs[i].track == query) {
            songs.erase(songs.begin() + i);
            cout << "Song removed successfully!" << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "No songs found with track name \"" << query << "\"" << endl;
    }
}

// Save songs to the file
void saveSongsToFile(string filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Failed to open file " << filename << endl;
        return;
    }

    for (int i = 0; i < songs.size(); i++) {
        file << songs[i].track << "\t" << songs[i].artist << "\t" << songs[i].duration << endl;
    }
    file.close();
    cout << "> Tracks saved to file " << filename << " successfully!" << endl;
}

// Main function
int main() {
    string filename = "Songs.txt";
    loadSongsFromFile(filename);
    while (true) {
        cout << endl << "***** Spotify menu ******\n" << endl;
        cout << "1. Show all Tracks" << endl;
        cout << "2. Search songs by Tracks" << endl;
        cout << "3. Search songs by Artist or Band name" << endl;
        cout << "4. Add a Track" << endl;
        cout << "5. Remove a Track" << endl;
        cout << "6. Save changes and exit" << endl;
        cout << "-----------------------------" << endl;
        cout << "Enter your choice (1-6):" <<endl;
        cout << "***************************" << endl;
        string choice_str;
        getline(cin, choice_str);
        int choice = stoi(choice_str);
        switch (choice) {
        case 1:
            printSongs();
            break;
        case 2:
            searchSongs();
            break;
        case 3:
            searchSongsByArtist();
            break;
        case 4:
            addSong();
            break;
        case 5:
            removeSong();
            break;
        case 6:
            saveSongsToFile(filename);
            return 0;
        default:
	  cout << endl << "Invalid choice, please enter a number from 1 to 6." << endl;
        }
    }
    return 0;
}

   
