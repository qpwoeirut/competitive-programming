#include <iostream>
#include <string>
#include <cmath>

using namespace std;

constexpr int SIZE = 10000;
constexpr int MAX_SPEED = 400;

int main() {
  int C, G, B;
  cin >> C >> G >> B;

  int coins[C][2];
  for (int i=0; i<C; i++) 
    cin >> coins[i][0] >> coins[i][1];

  int n, px, py, p1x, p1y, p2x, p2y, p3x, p3y, p4x, p4y;
  for (int i=0; i<G; i++) {
    cin >> n;
    for (int j=0; j<n; j++) 
      cin >> px >> py >> p1x >> p1y >> p2x >> p2y >> p3x >> p3y >> p4x >> p4y;
  }

  int thiefX, thiefY;
  cin >> thiefX >> thiefY;
 
  int closestDistance = 2 * SIZE;
  int closestId = -1;
  for (int j=0; j<C; j++) {
    int distance = sqrt((thiefX - coins[j][0]) * (thiefX - coins[j][0]) + (thiefY - coins[j][1]) * (thiefY - coins[j][1]));
    if (distance < closestDistance) {
      closestDistance = distance;
      closestId = j;
    }
  }

  cout <<  SIZE / MAX_SPEED + closestDistance/MAX_SPEED+1 << endl;
  for (int i = 0; i < closestDistance/MAX_SPEED+1; i++)
    cout << coins[closestId][0] << " " << coins[closestId][1] << " Will it yield coin?" << endl;

  int ex = coins[closestId][0]<SIZE/2 ? -1 : SIZE;
  int ey = coins[closestId][1]<SIZE/2 ? -1 : SIZE;
  bool xcloser = abs(coins[closestId][0] - ex) < abs(coins[closestId][1] - ey);
  for (int i = 0; i < SIZE / MAX_SPEED; i++) 
    cout << (xcloser?ex:coins[closestId][0]) << " " << (xcloser?coins[closestId][1]:ey) << " Nobody takes what's mine." << endl;

  cout.flush();    
}
