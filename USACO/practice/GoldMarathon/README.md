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
| Feb 2016 | 7:44pm      | cbarn   | Circular Barn           | Greedy Simulation    |
| Feb 2016 | 8:15pm      | cbarn2  | Circular Barn Revisited | DP\[door]\[i]\[prev] | 
| Feb 2016 | Unfinished (Stopped at 10:17pm, got 9/10) | fencedin | Fenced In | MST |

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


## Thursday, November 19th
Start Time: 6:50pm<br>
Read Open 2016 editorials from 7:51-7:58<br>
Dinner + talking w/ family until 9pm<br>

| Contest   | Time Solved | ID        | Name                | Method                  |
| --------- | ----------- | --------- | ------------------- | ----------------------- |
| Open 2016 | 7:12pm      | split     | Splitting the Field | Sweepline               |
| Open 2016 | 7:26pm      | closing   | Closing the Farm    | Reverse input, DSU      |
| Open 2016 | 7:51pm      | 248       | 248                 | Interval DP             |
| Dec 2016  | 9:17pm      | moocast   | Moocast             | Euclidean MST w/ Prim   |
| Dec 2016  | 9:37pm      | checklist | Cow Checklist       | DP\[h]\[g]\[prev]       |
| Dec 2016  | 10:52pm     | lasers    | Lasers and Mirrors  | Model as graph, 0-1 BFS |


## Sunday, November 22nd
Start Time: 7:00pm<br>
Pause to eat dinner: 8:06pm -  8:34pm<br>

| Contest   | Time Solved | ID        | Name                | Method                  |
| --------- | ----------- | --------- | ------------------- | ----------------------- |
| Jan 2017  | 7:10pm      | bphoto    | Balanced Photo      | BIT                     |
| Jan 2017  | 7:19pm      | hps       | Hoof, Paper, Scissors | DP\[game]\[changes]\[cur] |
| Jan 2017  | 8:02pm      | cownav    | Cow Navigation      | BFS with lots of state info |
| Feb 2017  | 8:53pm      | visitfj   | WDTCCTR             | Dijkstra                |
| Feb 2017  | 9:02pm      | nocross   | WDTCCTR II          | DP\[left]\[right\       |
| Feb 2017  | 9:32pm      | circlecross | WDTCCTR III       | BIT                     |
| Open 2017 | 10:56pm (unfinished) | cownomics | Bovine Genomics | String hash + binsearch |     



## Monday, November 23rd
Solved Bovine Genomics by fixing the substring hash calculation<br>
N and M were also swapped when fixing the left endpoint of the position search, so I fixed that too.<br>
It doesn't seem like there were any anti-hash hacks so I changed `MCT` to 1 and only used 1e9 + 7.<br>
I could probably make this a bit faster by removing the creation of arrays but it passes comfortably already so I won't bother.<br>
![](./Open2017/cownomics.png)


## Wednesday, November 25th
Started solving Modern Art 2 around 9:15pm<br>
Finished at 9:37pm<br>
![](./Open2017/art2.png)

Recap of Open 2017:<br>
| Contest   | Time Solved | ID        | Name                | Method                  |
| --------- | ----------- | --------- | ------------------- | ----------------------- |
| Open 2017 |             | cownomics | Bovine Genomics     | String hash + binsearch |
| Open 2017 | 9:37pm      | art2      | Modern Art 2        | Observation + stack     |


## Thursday, November 26th
Start Time: 5:10pm
Thanksgiving Dinner w/ family: 6:00pm - 7:55pm

| Contest   | Time Solved | ID        | Name                | Method                  |
| --------- | ----------- | --------- | ------------------- | ----------------------- |
| Dec 2017  | 5:56pm      | piepie    | A Pie for a Pie     | BFS with sketchy unvisited set |
| Dec 2017  | 8:29pm      | barnpainting | Barn Painting    | DP on tree              |
| Dec 2017  | 8:36pm      | hayfeast  | Haybale Feast       | Two pointers            |
| Jan 2018  | 8:57pm      | mootube   | MooTube             | Offine queries w/ DSU   |
| Jan 2018  | 9:17pm      | atlarge   | Cow At Large        | DFS and dist in tree    |
| Jan 2018  | 10:20pm     | spainting | Stamp Painting      | DP + psum + combo + bpow |


## Friday, November 27th
Start Time: 4:50pm

| Contest   | Time Solved | ID        | Name                | Method                  |
| --------- | ----------- | --------- | ------------------- | ----------------------- |
| Feb 2018  | 5:31pm      | snowboots | Snow Boots          | Offine queries w/ DSU   |
| Feb 2018  | 6:03pm      | dirtraverse | Directory Traversal | DP on tree            |
| Feb 2018  | 6:18pm      | taming    | Taming the Herd     | DP\[day]\[breakout]\[val] |
| Open 2018 | 6:58pm      | sort      | Out of Sorts        | Remembering what the editorial said |
| Open 2018 | 7:15pm      | milkorder | Milking Order       | Binsearch + toposort    |
| Open 2018 | 7:47pm      | talent    | Talent Show         | Knapsack on both weight and talent |
