#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
  int H;
  cin >> H;
  int W = 8;
     
  // Read the starting grid configuration
  vector<vector<char>> grid(H, vector<char>(W));
  for (int r = 0; r < H; r++)
      for (int c = 0; c < W; c++)
          cin >> grid[r][c];


  while (true)
  {
    //read elapsed time
    int elapsedTime;
    cin >> elapsedTime;

    //read AI's move
    int r1, c1, r2, c2;
    cin >> r1 >> c1 >> r2 >> c2;

    grid[r2][c2]=grid[r1][c1];
    grid[r1][c1]='.';

    //find a move
    bool found=false;
    for (r1=0; r1<H; r1++)
    {
      for (c1=0; c1<W; c1++)
      {
        if (grid[r1][c1]!='P') continue;

        r2=-1;
        c2=-1;
        if (r1-1>=0 && c1-1>=0 && grid[r1-1][c1-1]=='E')
        {
          r2=r1-1;
          c2=c1-1;
        }
        else if (r1-1>=0 && c1+1<W && grid[r1-1][c1+1]=='E')
        {
          r2=r1-1;
          c2=c1+1;
        }       
        else if (r1-1>=0 && grid[r1-1][c1]=='.')
        {
          r2=r1-1;
          c2=c1;
        }     

        //print move
        if (r2!=-1)
        {
          cout << r1 << " " << c1 << " " << r2 << " " << c2 << endl;
          cout.flush();
          found=true;

          //update grid
          grid[r2][c2]=grid[r1][c1];
          grid[r1][c1]='.';
          break;
        }
      }
      if (found) break;
    }
    if (!found) break;    
  }

  cout << "0" << endl;
  cout.flush();
}
