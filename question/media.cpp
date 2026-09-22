#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class Playable {
public:
    virtual string play() = 0;
    virtual string play(int fromSecond) = 0;
    virtual string pause() = 0;
    virtual ~Playable() {}
};

class MediaFile {
protected:
    const string fileId;
    inline static int counter = 1000;

public:
    MediaFile() : fileId("MF-" + to_string(++counter)) {}

    virtual string getFormatInfo() = 0;

    string getFileId() {
        return fileId;
    }

    virtual ~MediaFile() {}
};

class AudioFile : public MediaFile, public Playable {
private:
    string title;

public:
    AudioFile(string title) {
        this->title = title;
    }

    string play() override {
        return "Playing audio: " + title;
    }

    string play(int fromSecond) override {
        int minutes = fromSecond / 60;
        int seconds = fromSecond % 60;

        return "Playing audio: " + title + " from " +
               to_string(minutes) + ":" +
               (seconds < 10 ? "0" : "") +
               to_string(seconds);
    }

    string pause() override {
        return "Audio paused: " + title;
    }

    string getFormatInfo() override {
        return "Audio file, ID: " + fileId;
    }
};

class Podcast : public Playable {
private:
    string showName;
    int episodeNumber;

public:
    Podcast(string showName, int episodeNumber) {
        this->showName = showName;
        this->episodeNumber = episodeNumber;
    }

    string play() override {
        return "Streaming episode " + to_string(episodeNumber) +
               " of " + showName;
    }

    string play(int fromSecond) override {
        return "Streaming episode " + to_string(episodeNumber) +
               " of " + showName + " from " + to_string(fromSecond) + " seconds";
    }

    string pause() override {
        return "Podcast paused: " + showName;
    }
};

void launchAll(Playable* items[], int size) {
    for (int i = 0; i < size; i++) {
        cout << items[i]->play() << endl;
    }
}

int main() {
    AudioFile a("Morning Jazz");

    cout << a.play() << endl;
    cout << a.play(30) << endl;
    cout << a.getFormatInfo() << endl;

    Podcast p("Tech Talk", 12);

    cout << p.play() << endl;

    Playable* ref = &a;

    cout << ref->play() << endl;

    Playable* items[] = {ref, &p};

    launchAll(items, 2);

    return 0;
}