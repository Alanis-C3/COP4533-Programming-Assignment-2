# Contributors
Alanis Castillo 18144408 

Graciela Strand 80178234


# Compile and Build Instructions
cd path\to\project

mkdir build

cd build

cmake ..

cmake --build .

.\main.exe


# Assumptions
* Cache is initialized as empty
* K >= 1 
* M number of requests is between 50-2560
* Time complexity for FIFO = O(m)
* Time complexity for LRU = O(m*k)
* Time complexity for OPTFF = O(m*log(k))


# **Written Component**
## **Question 1: Empirical Comparison**  
Use at least three nontrivial input files (each containing 50 or more requests).  
For each file, report the number of cache misses for each policy.

| Input File | K | M | FIFO | LRU | OPTFF |
| :---- | :---- | :---- | :---- | :---- | :---- |
| File1 | 3 | 54 | 50 | 49 | 41 |
| File2 | 48 | 103 | 67 | 66 | 63 |
| File3 | 141 | 518 | 395 | 395 | 320 |

Briefly comment: 

Does OPTFF have the fewest misses?

* The OPTFF does have the fewest misses consistently no matter the size of K and M. It still has a large amount of misses because the cache starts empty in our solution so each time the cache is loaded it is a miss. Regardless, the OPTFF performs better than FIFO and LRU because once the cache is loaded the OPTFF has fewer misses overall. 

How does FIFO compare to LRU? 

* FIFO typically has a couple more misses than LRU, or it’ll return the same result. The results may vary based on the frequency of each request found in the randomized list as well as the size of cache. On a few occasions with a large cache and huge request list, FIFO scored slightly less misses.

## **Question 2: Bad Sequence for LRU or FIFO**  
For ( k \= 3 ), investigate whether there exists a request sequence for which OPTFF incurs strictly fewer misses than LRU (or FIFO).

If such a sequence exists:

* Construct one.   
  * {r1 r5 r2 r5 r3 r1 r2 r4 r5 r3}  
* Compute and report the miss counts for both policies  
  * OPTFF   
    * Miss count: 6  
    * Hit count: 4  
  * LRU  
    * Miss count: 9  
    * Hit count: 1

In either case, briefly explain your reasoning.
* In this case LRU performs worse because it evicts the oldest request in cache too soon. In almost every case, the request previously evicted is immediately called again. In contrast, OPTFF keeps in mind the future request so it holds in cache those values longer since it knows the request will be needed sooner, resulting in fewer misses.

## **Question 3: Prove OPTFF is Optimal**  
Let OPTFF be Belady’s Farthest-in-Future algorithm.  
Let ( A ) be any offline algorithm that knows the full request sequence.  
Prove that the number of misses of OPTFF is no larger than that of ( A ) on any fixed sequence.

* Let S be the sequence returned by OPTFF and A is any offline algorithm that knows the full request sequence.  
* Base case: Both A and S will have item 1 be a miss because the item is not in cache as cache is empty to begin with.  
* Inductive hypothesis: Let A and S agree on eviction decisions up until j items.  
* Consider the j+1 request calling item d. At this point in time, both A and S have the same cache contents.  
  * Case 1: If item d is in the cache, no eviction is necessary and it is not a miss. Therefore S and A agree on the optimal sequence up through step j+1.  
  * Case 2: If d is not in the cache, both A and S will evict the same number of values to make space to load d. This results in a singular miss, whereas both sequences would agree on the number of misses through step j+1. Thus, S has no larger misses than sequence A.
