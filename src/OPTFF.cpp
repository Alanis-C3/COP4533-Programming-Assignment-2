#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <queue>
using namespace std;

int OPTFF(vector<string> inputs, int k) {
    map<string, queue<int>> indexRequest;
    // O(m)
    // inserting index of each request into map
    for (int i = 0; i < inputs.size(); i++) {
        indexRequest[inputs[i]].push(i);
    }
    int misses = 0;
    unordered_set<string> cache;
    priority_queue<pair<int, string>> Furthest;
    for (int i = 0; i < inputs.size(); i++) {
        if (cache.find(inputs[i]) == cache.end()) { // miss in cache
            if (cache.size() == k) {
                // cache full
                //so remove top value in cache to make space for new one
                pair<int, string> evicted = Furthest.top();
                cache.erase(evicted.second);
                Furthest.pop();
            }
            //insert next value into cache and heap
            cache.insert(inputs[i]);
            indexRequest[inputs[i]].pop();
            if (!indexRequest[inputs[i]].empty()) {
                int further = indexRequest[inputs[i]].front();
                Furthest.push(make_pair(further, inputs[i]));
            }
            misses++;
        }
        else {// if hit in cache
            //pop off top index of queue in map (basically current index)
            indexRequest[inputs[i]].pop();
            //add next index if exist into heap
            if (!indexRequest[inputs[i]].empty()) {
                int further = indexRequest[inputs[i]].front();
                Furthest.push(make_pair(further, inputs[i]));
            }
        }
    }
    return misses;
}
