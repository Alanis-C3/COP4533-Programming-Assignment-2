#include <vector>
#include <string>
#include <queue>
#include <iostream>
#include <unordered_set>
using namespace std;

int fifo(int k, int m, vector<string> requests){
    int misses = 0;
    queue<string> cacheQ;
    unordered_set<string> cacheValues;

    for (int i=0; i<m; i++){
        // iteration syntax taken from https://www.geeksforgeeks.org/cpp/unordered_set-in-cpp-stl/
        auto it = cacheValues.find(requests[i]);
        if (it != cacheValues.end()){ // found!
            //cout << "Hit " << requests[i] << endl;
            continue;
        } else {  // miss
            //cout << "Miss " << requests[i] << endl;
            misses++;
            if (cacheQ.size()==k){
                // max capacity of queue reached
                string firstRequest = cacheQ.front();
                cacheValues.erase(firstRequest); // get rid of value in cache set
                cacheQ.pop(); // get rid of the first request in queue
            }
            cacheQ.push(requests[i]);
            cacheValues.insert(requests[i]);
        }
    }

    return misses;
}