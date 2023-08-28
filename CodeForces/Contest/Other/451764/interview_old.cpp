#include <bits/stdc++.h>

using namespace std;

constexpr int MN = 101;
constexpr int ZERO_STEP_LIMIT = 5, ONE_STEP_LIMIT = 10, TWO_STEP_LIMIT = 30;  // adjust these to ensure there's no MLE
constexpr float P_ZERO_STEP[ZERO_STEP_LIMIT + 1] = {
    1.0,
    0.3,
    0.09,
    0.027,
    0.0081,
    0.00243
};
constexpr float P_ONE_STEP[ONE_STEP_LIMIT + 1] = {
    1.0,
    0.7941176470588235, 0.6306228373702422, 0.5007887237940158, 0.39768516301289497, 0.31580880592200483,
    0.2507893458792391, 0.19915624525704284, 0.15815348888059283, 0.1255924764640002, 0.09973520189788251,
    //0.07920148386008317, 0.06289529600653664, 0.049946264475779094, 0.0396632100248834, 0.03149725501976034,
    //0.025012526045103803, 0.019862888329935373, 0.01577347014436044, 0.012525990996992116, 0.009947110497611386,
    //0.007899175983397278, 0.006272875045639015, 0.004981400771536864, 0.003955818259749863, 0.0031413850886248913,
    //0.0024946293350844723, 0.001981029177861199, 0.0015731702294780106, 0.0012492822410560672, 0.0009920770737798183,
    //0.0007878259115310321, 0.0006256264591569961, 0.0004968210116834969, 0.0003945343328074828, 0.0003133066760530011,
    //0.00024880236039503023, 0.00019757834501958285, 0.00015690045045672755, 0.000124597416539166, 9.894500725169064e-05,
    //7.85739763469308e-05, 6.239698121668035e-05, 4.955054390736381e-05, 3.934896133820067e-05, 3.124770459210053e-05,
    //2.4814353646668068e-05, 1.9705516131177584e-05, 1.5648498104170435e-05, 1.2426748494488286e-05, 9.868300275034815e-06,
    //7.83659139488059e-06, 6.223175519463997e-06, 4.941933500750821e-06, 3.924476603537416e-06, 3.116496126338537e-06,
    //2.474864570915897e-06, 1.9653336298449767e-06, 1.56070611781807e-06, 1.2393842700319967e-06, 9.842169203195269e-07,
    //7.815840249596242e-07, 6.206696668797015e-07, 4.928847354632925e-07, 3.914084663973205e-07, 3.108243703743427e-07,
    //2.468311176502133e-07, 1.9601294636928705e-07, 1.5565733976384562e-07, 1.2361024040070093e-07, 9.816107325938015e-08,
    //7.795144052950776e-08, 6.190261453813852e-08, 4.915795860381588e-08, 3.903720242067732e-08, 3.1000131334067285e-08,
    //2.461775135352402e-08, 1.9549390780739663e-08, 1.5524516208234437e-08, 1.23282922830097e-08, 9.790114460037115e-09,
    //7.774502659441237e-09, 6.173869758968042e-09, 4.902778926239328e-09, 3.89338326495476e-09, 3.0918043574640743e-09,
    //2.455256401515588e-09, 1.9497624364976732e-09, 1.548340758395211e-09, 1.2295647199020794e-09, 9.764190422751806e-10,
    //7.753915923949964e-10, 6.157521469019089e-10, 4.88979646069163e-10, 3.8830736599609997e-10, 3.083617318204323e-10,
    //2.4487549291622567e-10, 1.9445995025700274e-10, 1.5442407814526688e-10, 1.2263088558594722e-10, 9.738335031825221e-11,
};
constexpr float P_TWO_STEP[TWO_STEP_LIMIT + 1] = {
    1.0,
    0.9391304347826087, 0.8819659735349716, 0.8282810881893646, 0.7778639784734903, 0.7305157363055387,
    0.6860495610521581, 0.6442900225533311, 0.6050723690066065, 0.5682418769801175, 0.5336532409900234,
    0.501170000234109, 0.4706640002198588, 0.44201488716299786, 0.4151096331617719, 0.389842090273664,
    0.36611257173526707, 0.34382745867312037, 0.322898830753887, 0.30324411931669387, 0.28478578161915596,
    0.267450994911903, 0.2511713691346567, 0.23588267710037328, 0.22152460110295924, 0.2080404949488661,
    0.1953771604737177, 0.18348463766227402, 0.17231600754370083, 0.16182720708451903, 0.15197685534893962,
    //0.1427260902407433, 0.1340384151826111, 0.12587955512801738, 0.11821732133761631, 0.11102148438663097,
    //0.10426365490222735, 0.09791717156035264, 0.09195699590015727, 0.08635961354101726, 0.0811029414124336,
    //0.07616624063080721, 0.07153003467936676, 0.06717603256844878, 0.063087056672978, 0.0592469749624489,
    //0.05564063735603896, 0.052253815951758334, 0.04907314889382521, 0.046086087656809764, 0.04328084753856917,
    //0.040646361166656264, 0.03817223483477284, 0.035848707497004056, 0.033666612258055985, 0.031617340207565625,
    //0.029692806455800757, 0.027885418236752016, 0.026188044952775807, 0.024593990042606845, 0.023096964561752514,
    //0.021691062371037146, 0.020370736835408798, 0.019130778941079566, 0.017966296744666026, 0.016872696073251574,
    //0.015845662399227564, 0.014881143818405017, 0.013975335064241232, 0.013124662495113506, 0.012325769995410945,
    //0.011575505734820713, 0.010870909733570756, 0.010209202184570798, 0.009587772486379532, 0.009004168943730342,
    //0.00845608909498154, 0.00794137062833049, 0.007457982850953851, 0.007004018677417529, 0.006577687105748636,
    //0.006177306151485676, 0.005801296211830026, 0.005448173833718633, 0.005116545861231412, 0.004805103939243413,
    //0.004512619351637292, 0.0042379381737115435, 0.0039799767196595365, 0.0037377172671585216, 0.0035102040422010463,
    //0.0032965394483279392, 0.0030958805253862385, 0.002907435623840989, 0.0027304612815202333, 0.002564259290471176,
    //0.002408173942355539, 0.002261589441516506, 0.0021239274755111537, 0.0019946449335235183, 0.0018732317636568692
};
constexpr float G_POW[MN] = {
    0.0,
    1.0, 2.378414230005442, 3.9482220388574776, 5.656854249492381, 7.476743906106103,
    9.390507480439723, 11.3860359318845, 13.454342644059432, 15.588457268119896, 17.78279410038923,
    20.032763155216593, 22.33451661845039, 24.684775987507244, 27.08070988374737, 29.519845068981457,
    32.0, 34.51923414277182, 37.07580859032812, 39.66815496866703, 42.294850537622565,
    44.95459800148952, 47.64620895469586, 50.368590171181374, 53.120732145615435, 55.90169943749474,
    58.71062247318387, 61.54669053777899, 64.40914574615377, 67.29727782607642, 70.21041957962147,
    73.14794291488758, 76.10925536017415, 79.0937969886382, 82.1010376940582, 85.13047476842256,
    88.18163074019441, 91.25405143870744, 94.34730425553876, 97.46097657813594, 100.59467437463483,
    103.74802091184496, 106.92065559091688, 110.11223288733363, 113.32242138366135, 116.55090288501081,
    119.79737160845002, 123.06153343870662, 126.34310524343928, 129.64181424216494, 132.9573974236247,
    136.28960100697321, 139.6381799426978, 143.00289744962853, 146.38352458479486, 149.7798398432325,
    153.1916287851466, 156.61868368810494, 160.06080322216988, 163.51779214608612, 166.98946102282443,
    170.47562595294573, 173.97610832439437, 177.49073457745922, 181.01933598375618, 184.56174843818903,
    188.11781226293868, 191.68737202261246, 195.27027634976125, 198.86637778003842, 202.47553259633546,
    206.09760068128406, 209.73244537756372, 213.37993335549882, 217.03993448747036, 220.7123217287034,
    224.3969710040264, 228.09376110022802, 231.80257356366565, 235.52329260280518, 239.2558049953953,
    243.0, 246.75576927163422, 250.52300678126366, 254.30160873894764, 258.09147352041896,
    261.89250159690755, 265.7045954680296, 269.5276595975732, 273.3616003520252, 277.20632594169206,
    281.06174636427716, 284.92777335078745, 288.8043203136478, 292.69130229691035, 296.58863592845375,
    300.49623937407114, 304.41403229335464, 308.3419357972873, 312.2798724074605, 316.22776601683796
};

constexpr float FAIL_PRELIM = 0.3 * (1 - 0.8) + 0.7 * (1 - 0.2);
constexpr float PASS_PRELIM_FAIL_STANDARD = 0.3 * 0.8 * (1 - 0.9) + 0.7 * 0.2 * (1 - 0.1);
constexpr float PASS_PRELIM_PASS_STANDARD = 0.3 * 0.8 * 0.9 + 0.7 * 0.2 * 0.1;
static_assert(1 - (FAIL_PRELIM + PASS_PRELIM_FAIL_STANDARD + PASS_PRELIM_PASS_STANDARD) < 1e-12);

constexpr float FAIL_STANDARD = 0.3 * (1 - 0.9) + 0.7 * (1 - 0.1);
constexpr float PASS_STANDARD = 0.3 * 0.9 + 0.7 * 0.1;
static_assert(1 - (FAIL_STANDARD + PASS_STANDARD) < 1e-12);

// [candidates left, time spent, 0-step hires, 1-step hires, 2-step hires] = expected score
float cache[MN][4 * MN][ZERO_STEP_LIMIT + 1][ONE_STEP_LIMIT + 1][TWO_STEP_LIMIT + 1];
int N;

float expectimax(int n, int time_spent, int zero_step, int one_step, int two_step, int& action) {
    if (zero_step + one_step + two_step + (N - n) < 5 || zero_step > ZERO_STEP_LIMIT || one_step > ONE_STEP_LIMIT || two_step > TWO_STEP_LIMIT) {
        return 0;
    }
    if (n == N) {
        // this is missing the (mx - mn) in the denominator, but hopefully it doesn't matter too much
        // it looks like the optimal strategy never tries to hire more than 5 candidates anyway
        return (500 * G_POW[zero_step + one_step + two_step] / (time_spent + 0.5)) * P_ZERO_STEP[zero_step] * P_ONE_STEP[one_step] * P_TWO_STEP[two_step];
    }

    if (action != -1 && cache[n][time_spent][zero_step][one_step][two_step] != 0) {
        return cache[n][time_spent][zero_step][one_step][two_step];
    }
    action = 0;
    float options[4] = {
        // reject immediately
        expectimax(n + 1, time_spent, zero_step, one_step, two_step, action),

        // prelim and standard interview
        FAIL_PRELIM *               expectimax(n + 1, time_spent + 1, zero_step, one_step, two_step, action) +
        PASS_PRELIM_FAIL_STANDARD * expectimax(n + 1, time_spent + 4, zero_step, one_step, two_step, action) +
        PASS_PRELIM_PASS_STANDARD * expectimax(n + 1, time_spent + 4, zero_step, one_step, two_step + 1, action),

        // standard interview only
        FAIL_STANDARD * expectimax(n + 1, time_spent + 3, zero_step, one_step, two_step, action) +
        PASS_STANDARD * expectimax(n + 1, time_spent + 3, zero_step, one_step + 1, two_step, action),

        // accept immediately
        expectimax(n + 1, time_spent, zero_step + 1, one_step, two_step, action)
    };

    // prioritize actions 1 and 2 first
    if (options[1] >= options[0] && options[1] >= options[2] && options[1] >= options[3]) {
        action = 1;
    } else if (options[2] >= options[0] && options[2] >= options[1] && options[2] >= options[3]) {
        action = 2;
    } else if (options[0] >= options[1] && options[0] >= options[2] && options[0] >= options[3]) {
        action = 0;
    } else {
        action = 3;
    }
    return cache[n][time_spent][zero_step][one_step][two_step] = options[action];
}

int main() {
    // no fast IO since interactive

    cin >> N;

    int time_spent = 0;
    int zero_step = 0, one_step = 0, two_step = 0;
    char c1, c2, c3, c4;  // faster IO maybe idk
    for (int i = 0; i < N; ++i) {
        int action = -1;
        float expected_score = expectimax(i, time_spent, zero_step, one_step, two_step, action);
        cerr << "E(score), time, 0-step, 1-step, 2_step = " << expected_score << ' ' << time_spent << ' ' << zero_step << ' ' << one_step << ' ' << two_step << endl;

        cout << action << endl;

        if (action == 1) {
            ++time_spent;

            cin >> c1 >> c2 >> c3 >> c4;
            if (c1 == 'p') {
                time_spent += 3;

                cin >> c1 >> c2 >> c3 >> c4;
                two_step += c1 == 'p';
            }
        } else if (action == 2) {
            time_spent += 3;

            cin >> c1 >> c2 >> c3 >> c4;
            one_step += c1 == 'p';
        } else if (action == 3) ++zero_step;
    }
}



/*
Time spent for prelim = 1, time spent for standard = 3
New score formula: 500g / (time + 0.5)


Expectimax with cache of (# of candidates left, time spent, # of hires, P(all hires are good)) -> expected score
For depth=n=100: 100, 4 * 100, 100, 101 * 102 / 2 -> 20,604,000,000 states
For depth = 50:  663,000,000 states
For depth = 40:  220,416,000 states


Assuming that hiring instantly is never optimal
For depth = 100: 404,000,000 states



---------------------------------------------------

Below is a few hours' worth of rambling about ideas.

Initial thoughts:
* Feels like a mathy problem; wouldn't be surprised if there's a provably optimal strategy
    * Start with mathematical calculations first, code later

* Will most strategies only use one interview type?

* This problem doesn't have much input/state
    * Precomputation before submitting is probably going to be useful.
    * For each of the n=100 candidates, the current state is (# of candidates hired, probability that all are good)
        * There's no difference between 1 of them being bad and 2 or more being bad because we'll get the same result (which is a score of 0) for either case
        * How many probabilities can there be?
        * Could we formulate this as a DP problem?

* The scoring function makes it difficult to find a good point to "stop" and reject all other candidates
    * At least, calculating this mathematically will be annoying. Simulation w/ a computer is probably fine
    * This is why CS > math

* Try a Monte Carlo simulation? Picking randomly is a really bad strategy though.


Useful Calculations (good candidate, bad candidate)
* Chance of existing: (0.3, 0.7)
* Chance of passing 1-step interview (p1): (0.9, 0.1)
    * P(good and p1): 0.27
    * P(bad and p1): 0.07
    * P(not p1): 0.66
* Chance of passing 2-step interview (p2): (0.72, 0.02)
    * P(good and p2): 0.216
    * P(bad and p2): 0.014
    * P(not p2): 0.77
* Expected time for 2-step interview (e2): (68, 32)
    * 20 + 0.8 * 60, 20 + 0.2 * 60

* Chance that all p1 are good for n=100: 0.00070517
* Chance that all p2 are good for n=100: 0.24416955


Pursuing DP problem idea
State: [# of hires, P(all good)]
# of hires ≤ n=100

How many values of P(all good) can there be?
P(good) = 0.3
P(good | p1) = 0.27 /0.34 = 0.79411765
P(good | p2) = 0.216/0.23 = 0.93913043

Let the number of distinct values for P(all good) be x(m), where m is the number of candidates hired. (We want all m to be good).
This is equivalent to picking two indexes of a sequence of length m to start the next "section"
x(m) = (m + 1) * (m + 2) / 2
x(100) = 5151, so there are a reasonable amount of distinct values.
100 * 5151 = 515100 << 1e8, so precomputing isn't necessary.

Side note: it took me a really long time to figure out this formula; I originally tried calculating a product of two choose numbers inside two for loops and ended up calculating powers of 3

A quick Python program to sanity check the formula. (In hindsight, I could have ran this loop to find the answer, but too late now.)
s = 0
for i in range(101):
    for j in range(101):
        if 100 - i - j >= 0:
            s += 1

To avoid floating point issues, let's encode the state as [# of hires with no interview, # of hires with 1-step interview, # of hires with 2-step interview]
* If I'd figured out this encoding system earlier, I could have realized that the number of states is O(n^3) and the total runtime would be O(n^4) with good constant and avoided the calculations above

The value of each state will be the expected time to reach it.

There are 4 transitions, each corresponding to one of the actions you can take.
The expected times are as follows:
* Instantly rejecting or accepting: 0
* 1-step interview: 60
* 2-step interview: 42.8
    * As written above in Useful Calculations, the expected time for a good candidate is 68 and the expected time for a bad candidate is 32
    * 0.3 * 68 + 0.7 * 32
    * So a 2-step interview is always better than a 1-step interview?

Possible issues with DP idea
* May not be optimal with given scoring function? idk, requires too much thinking to figure out
    * Something about expected value vs having time being a denominator maybe


HOLD UP
Right after I started coding, I realized that the state also requires which candidate we're currently looking at.
This gets us an O(n^5) runtime with good constant. If we look at the hard numbers, it's n^2 * x(n) = 10000 * 5151 = 51,510,000 which is still okay.

I also realized that we need to pick a path through the DP states.
This becomes an expectimax algorithm, I think. (Plug: I learned about expectimax while making https://github.com/qpwoeirut/2048-solver)
It's probably best to ditch the DP calculation itself, while maintaining the general intuition behind it.
*/
