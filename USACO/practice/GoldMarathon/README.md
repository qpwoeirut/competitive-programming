# November 2020 USACO Gold Marathon

Starting Thursday, November 12th, I want to solve (or re-solve) every USACO Gold problem from December 2015 onwards. This is in preparation for the upcoming USACO contest season, which will start in December.

## Thursday, November 12th
Start Time: 4:45pm

| Contest  | Time Solved | ID        | Name                      | Method          |
| -------- | ----------- | --------- | ------------------------- | --------------- |
| Dec 2015 | 5:07pm      | cardgame  | High Card Low Card (Gold) | Greedy          |
| Dec 2015 | 5:14pm      | feast     | Fruit Feast               | Knapsack DP     |
| Dec 2015 | 5:41pm      | dream     | Bessie's Dream            | BFS with 4-D states|
| Jan 2016 | 6:32pm      | angry     | Angry Cows                | Precompute prefix/suffix, binary search on answer with sliding window             |
| Jan 2016 | 6:53pm      | radio     | Radio Contact             | Precompute positions, DP\[fj]\[bessie] |
| Jan 2016 | 7:51pm      | lightsout | Lights Out                | Wrote an N<sup>2</sup> log N<sup>2</sup> with hashing, distance precomp<br>Had to look up the ccw function<br>N <= 200 so I didn't have to do N<sup>2</sup> log N<sup>2</sup> but I did anyways

Stopped because of Chemistry H Unit 2 Test tomorrow


## Sunday, November 15th
Start Time: 7:30pm

| Contest  | Time Solved | ID      | Name                    | Method               |
| -------- | ----------- | ------- | ----------------------- | -------------------- |
| Jan 2016 | 7:44pm      | cbarn   | Circular Barn           | Greedy Simulation    |
| Jan 2016 | 8:15pm      | cbarn2  | Circular Barn Revisited | DP\[door]\[i]\[prev] | 
| Jan 2016 | Unfinished (Stopped at 10:17pm, got 9/10) | fencedin | Fenced In | MST |

Need to go finish an essay organizer for an essay on Lord of the Flies

## Monday, November 16th - Wednesday, November 18th
I spent a couple hours trying to constant optimize my Prim's solution.
I changed my solution to use bitshifts to store the items, and used the `push_heap` and `pop_heap` STL functions instead of a `priority_queue` to save on the overhead of container expansion.
I wasn't able to get the last test case.
![](./Feb2016/fencedin_with_prim.png)

In the end I read the editorial and used Kruskal.
The editorial's code makes use of the neat observation that the cost of the edges separating any one row or column will always be the same, so we don't actually need to store and then sort all of the edges.
Instead we just sort the horizontal difference array and the vertical difference array, and then go through both of those.
I glanced at the Plat version's editorial as well, and it seems to be key to the Plat solutions.
Of course, the editorial's text decided to not mention this observation at all.
I had to spend 30 minutes reading the editorial code and drawing things to figure out what it was doing.

My final solution was based on the editorial's code and so they look very similar.
![](./Feb2016/fencedin_with_kruskal.png)

