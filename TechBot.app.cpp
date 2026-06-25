#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 1. Post/Video Structure
struct Post {
    string username;
    string contentUrl; // Video ya Image ka link
    string caption;
};

// 2. Server Class
class DiscordServer {
private:
    string serverName;
    string serverAddress;
    vector<string> textChannels;
    vector<Post> socialFeed;
    
    // Limits (Slots) jise aapne pucha tha
    vector<string> customEmojis;  // Max 30
    vector<string> customStickers; // Max 5

public:
    // Constructor
    DiscordServer(string name, string address) {
        serverName = name;
        serverAddress = address;
        textChannels.push_back("general"); // Default channel
    }

    // Overview: Server Naam aur Address badalne ka feature
    void updateServerOverview(string newName, string newAddress) {
        serverName = newName;
        serverAddress = newAddress;
        cout << "\n[SUCCESS] Server Overview Updated!" << endl;
        cout << "New Name: " << serverName << " | New Address: " << serverAddress << endl;
    }

    // Emoji Daalne ka Feature (Max 30 Slots)
    void addCustomEmoji(string emojiName) {
        if (customEmojis.size() < 30) {
            customEmojis.push_back(emojiName);
            cout << "[EMOJI] " << emojiName << " added. (" << customEmojis.size() << "/30 slots used)" << endl;
        } else {
            cout << "[ERROR] Cannot add emoji! 30 Slots full." << endl;
        }
    }

    // Sticker Daalne ka Feature (Max 5 Slots)
    void addCustomSticker(string stickerName) {
        if (customStickers.size() < 5) {
            customStickers.push_back(stickerName);
            cout << "[STICKER] " << stickerName << " added. (" << customStickers.size() << "/5 slots used)" << endl;
        } else {
            cout << "[ERROR] Cannot add sticker! 5 Slots full." << endl;
        }
    }

    // Post/Video Daalne ka Feature
    void uploadPost(string user, string url, string cap) {
        Post newPost = {user, url, cap};
        socialFeed.push_back(newPost);
        cout << "[FEED] New Post/Video uploaded by " << user << "!" << endl;
    }

    // Chatting Simulation
    void sendMessage(string user, string msg) {
        cout << "[" << serverName << " -> #general] " << user << ": " << msg << endl;
    }
};

// Main function jahan app run hogi
int main() {
    cout << "--- Starting Your Custom Discord App Backend ---" << endl;

    // 1. Ek naya server banaya
    DiscordServer myServer("Gamers Zone", "app.link/gamers123");

    // 2. Server Overview Badla (Naam aur Address)
    myServer.updateServerOverview("Alpha Gamers", "app.link/alpha777");

    // 3. Chatting ki
    myServer.sendMessage("Rahul", "Hey guys! Welcome to my new server.");

    // 4. Post/Video Upload ki
    myServer.uploadPost("Rahul", "https://video.cdn/gameplay.mp4", "Check out my new clutch video!");

    // 5. Custom Emojis add kiye (Testing Slot Limit)
    cout << "\n--- Testing Emoji Slots ---" << endl;
    for(int i = 1; i <= 32; i++) { // 32 baar try karte hain taaki limit check ho
        myServer.addCustomEmoji("emoji_" + to_string(i));
    }

    // 6. Custom Stickers add kiye (Testing Slot Limit)
    cout << "\n--- Testing Sticker Slots ---" << endl;
    for(int i = 1; i <= 7; i++) { // 7 baar try karte hain taaki limit check ho
        myServer.addCustomSticker("sticker_" + to_string(i));
    }

    return 0;
}
