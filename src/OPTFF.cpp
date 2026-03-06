#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <queue>
using namespace std;

int OPTFF(vector<string> inputs, int k) {
    map<string, queue<int>> indexRequest;
    // Time complexity: O(m)
    // inserting index of each request into map
    for (int i = 0; i < inputs.size(); i++) {
        indexRequest[inputs[i]].push(i);
    }

    int misses = 0;
    unordered_set<string> cache;
    priority_queue<pair<int, string>> Furthest;

    for (int i = 0; i < inputs.size(); i++) {
        // MISS
        if (cache.find(inputs[i]) == cache.end()) {

            // CACHE FULL
            if (cache.size() == k) {
                // ensure the value being removed is valid
                while (!Furthest.empty()){
                    auto evicted = Furthest.top();

                    // stale entry case, top value not in cache anymore
                    if (cache.find(evicted.second) == cache.end()){
                        Furthest.pop(); // pop it and go again
                        continue;
                    }

                    // stale entry case, index has passed
                    if (!indexRequest[evicted.second].empty() && indexRequest[evicted.second].front() != evicted.first) {
                        // if the future indices queue for the current request isn't empty (prevents throwing error for .front())
                        // and if we're working with a pair (#, r#) that is passed,
                        //   meaning that the request's future indices queue no longer contains that number (!=)
                        //   then it's stale, and we need to get rid of it
                        Furthest.pop();
                        continue;
                    }
                    break;
                }
                // remove from the heap/cache to make room for new data
                auto evicted = Furthest.top();
                cache.erase(evicted.second);
                Furthest.pop();
            }
            //insert next value into cache and heap
            cache.insert(inputs[i]);
            indexRequest[inputs[i]].pop();
            if (!indexRequest[inputs[i]].empty()) {
                int further = indexRequest[inputs[i]].front();
                Furthest.emplace(make_pair(further, inputs[i]));
            } else {
                // INT_MAX taken from https://www.digitalocean.com/community/tutorials/int-max-min-c-plus-plus
                // if there are no more request for this job,
                // add a pair that will always be furthest in the future,
                // so it'll be removed from the cache next
                Furthest.emplace(make_pair(INT_MAX, inputs[i]));
            }
            misses++;
        }
        // HIT
        else {
            //pop off top index of queue in map (basically current index)
            indexRequest[inputs[i]].pop();
            //add next index if exist into heap
            if (!indexRequest[inputs[i]].empty()) {
                int further = indexRequest[inputs[i]].front();
                Furthest.emplace(make_pair(further, inputs[i]));
            } else {
                Furthest.emplace(make_pair(INT_MAX, inputs[i]));
            }
        }
    }
    return misses;
}
