#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <stdexcept>

// Target data element
struct Track {
    std::string title;
    std::string artist;
};

// 1. Iterator Interface
class TrackIterator {
public:
    virtual ~TrackIterator() = default;
    virtual bool hasNext() const = 0;
    virtual const Track& next() = 0;
};

// 2. Aggregate Interface
class TrackAggregate {
public:
    virtual ~TrackAggregate() = default;
    virtual std::unique_ptr<TrackIterator> createIterator() const = 0;
};

// 3. Concrete Aggregate
class PlaylistQueue : public TrackAggregate {
private:
    std::vector<Track> tracks;

    // Concrete Iterator as an inner class
    class VectorTrackIterator : public TrackIterator {
    private:
        const std::vector<Track>& items;
        size_t cursor = 0;

    public:
        explicit VectorTrackIterator(const std::vector<Track>& target)
            : items(target) {}

        bool hasNext() const override {
            return cursor < items.size();
        }

        const Track& next() override {
            if (!hasNext()) {
                throw std::out_of_range("VectorTrackIterator::next(): Iterator out of bounds.");
            }
            return items[cursor++];
        }
    };

public:
    void addTrack(const Track& track) {
        tracks.push_back(track);
    }

    std::unique_ptr<TrackIterator> createIterator() const override {
        return std::make_unique<VectorTrackIterator>(tracks);
    }
};

// 4. Client Usage (Uniform Traversal)
void printPlaylist(const TrackAggregate& playlist) {
    std::unique_ptr<TrackIterator> it = playlist.createIterator();
    int index = 1;
    while (it->hasNext()) {
        const Track& t = it->next();
        std::cout << index++ << ". " << t.title 
                  << " by " << t.artist << "\n";
    }
}

int main() {
    try {
        PlaylistQueue playlist;
        playlist.addTrack({"Bohemian Rhapsody", "Queen"});
        playlist.addTrack({"Hotel California", "Eagles"});
        playlist.addTrack({"Stairway to Heaven", "Led Zeppelin"});

        std::cout << "--- Playlist Tracks ---" << std::endl;
        printPlaylist(playlist);

        // Demonstrate bounds checking
        std::cout << "\n--- Testing Bounds Protection ---" << std::endl;
        auto emptyQueue = PlaylistQueue();
        auto emptyIt = emptyQueue.createIterator();
        std::cout << "Has next on empty: " << std::boolalpha << emptyIt->hasNext() << std::endl;
        // The following line safely throws std::out_of_range instead of undefined behavior
        // emptyIt->next();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
