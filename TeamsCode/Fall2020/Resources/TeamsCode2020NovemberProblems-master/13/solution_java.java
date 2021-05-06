import java.util.Arrays;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

public class Hanoi
{
    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);
        String[] l1 = input.nextLine().split(" ");
        int N = Integer.parseInt(l1[0]);
        int K = Integer.parseInt(l1[1]);
        Queue<HanoiState> statesQueue = new LinkedList<>();
        HashMap<String, Boolean> statesSeen = new HashMap<>();
        HanoiState startState = generateStartState(N, K);
        HanoiState endState = generateEndState(N, K);
        statesQueue.add(startState);
        while (!statesQueue.isEmpty())
        {
            HanoiState curState = statesQueue.poll();
            
            String curTowersStr = curState.towersStr();
            if (statesSeen.containsKey(curTowersStr))
            {
                continue;
            }
            statesSeen.put(curTowersStr, true);
            
            //System.out.println(curState.iteration + "," + curTowersStr);
            
            if (curState.towersMatch(endState))
            {
                System.out.println(curState.iteration + "\n");
                break;
            }
            
            for (int i = 0; i < K; i++)
            {
                for (int j = 0; j < K; j++)
                {
                    if (i != j)
                    {
                        if (curState.canMove(i, j))
                        {
                            statesQueue.add(curState.moveDisk(i, j));
                        }
                    }
                }
            }
        }
    }

    public static HanoiState generateStartState(int N, int K)
    {
        HanoiState hState = new HanoiState(0, new String[K]);
        for (int i = 0; i < K; i++)
        {
            hState.towers[i] = "";
        }
        for (int i = N; i > 0; i--)
        {
            hState.towers[0] += i + "";
        }
        return hState;
    }

    public static HanoiState generateEndState(int N, int K)
    {
        HanoiState hState = new HanoiState(0, new String[K]);
        for (int i = 0; i < K; i++)
        {
            hState.towers[i] = "";
        }
        for (int i = N; i > 0; i--)
        {
            hState.towers[K - 1] += i + "";
        }
        return hState;
    }
}

class HanoiState
{
    public int iteration;
    public String[] towers;

    public HanoiState(int iteration, String[] towers)
    {
        this.iteration = iteration;
        this.towers = towers;
    }

    public HanoiState moveDisk(int from, int to)
    {
        String newFrom = towers[from].substring(0, towers[from].length() - 1);
        String newTo = towers[to] + towers[from].charAt(towers[from].length() - 1);
        String[] newTowers = new String[towers.length];
        for (int i = 0; i < towers.length; i++)
        {
            newTowers[i] = i == from ? newFrom : i == to ? newTo : this.towers[i];
        }
        return new HanoiState(this.iteration + 1, newTowers);
    }

    public boolean canMove(int from, int to)
    {
        if (towers[from].length() == 0)
        {
            return false;
        }
        
        if (towers[to].length() == 0)
        {
            return true;
        }

        if (towers[from].charAt(towers[from].length() - 1) >= towers[to].charAt(towers[to].length() - 1))
        {
            return false;
        }

        return true;
    }

    public boolean towersMatch(HanoiState other)
    {
        if (other.towers.length != this.towers.length)
        {
            return false;
        }

        for (int i = 0; i < this.towers.length; i++)
        {
            if (!this.towers[i].equals(other.towers[i]))
            {
                return false;
            }
        }

        return true;
    }
    
    public String towersStr()
    {
        return Arrays.toString(this.towers);
    }
}
