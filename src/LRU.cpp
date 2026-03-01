#include <map>
#include <vector>
#include <string>
using namespace std;

int LRU(vector<string> inputs, int K ) {
    map<string, int> cache;
    int counter = 0;
    int missed = 0;
    for (auto in: inputs) {
        if (cache.find(in) == cache.end()) {
            if (cache.size() == K) { // checks if map is at size capacity
                auto it = cache.begin(); // gets first value
               string  nextEvicted = it->first; //first key
                int lru = it->second; // first value for comparision for min valu
                for (auto val : cache) {
                    if (val.second < lru) { //finds smallest val that would be oldest value
                        lru = val.second;
                        nextEvicted = val.first;
                    }
                }
                cache.erase(nextEvicted);
                cache[in] = counter;
                counter++;
                missed++; // missed cache so missed counter goes up

            }
            else {
                cache[in] = counter;
                counter++;
                missed++;
            }
        }
        else { //value in map and only update counter since now recently used
            cache[in] = counter; // updated to counters most recent value
            counter++;
        }
    }
    return missed;
}
