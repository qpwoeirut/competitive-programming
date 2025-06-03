import java.awt.*;
import java.awt.geom.*;
import java.awt.geom.Line2D;
import java.util.*;
import java.io.*;
import javax.imageio.*;
import java.util.List;
import java.util.ArrayList;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;
import com.topcoder.marathon.*;


public class HordeChessTester extends MarathonAnimatedVis {
    //parameter ranges
    private static final int minH = 8, maxH = 20;   // grid height range
    private static final double minE = 0, maxE = 0.15;   // empty ratio range

    //Inputs
    private int H;      // grid height
    private double E;   // empty ratio

    //Manual play
    private int lastR1 = -1;
    private int lastC1;
    private int lastR2 = -1;
    private int lastC2;

    //Constants 
    private final static double queenP=0.25;      //probability that a queen is used in each test case
    private final static int W=8;   //grid width    
    private final static boolean allowBlackPromotion=true;
    private final static char Empty = '.';
    private final static char King = 'K';
    private final static char Knight = 'N';
    private final static char Bishop = 'B';
    private final static char Rook = 'R';
    private final static char Queen = 'Q';
    private final static char Pawn = 'P';
    private final static char Enemy = 'E';    //white pawn
    private final static char EnemyPromoted = 'X';    //white queen
    private final static char[] Pieces = {King, Queen, Knight, Bishop, Rook, Pawn};
   
    //Graphics
    private Image kingPic;
    private Image knightPic;
    private Image bishopPic;
    private Image rookPic;
    private Image queenPic;
    private Image pawnPic;
    private Image enemyPic;
    private Image enemyPromotedPic;
    private Color darkColour=new Color(181, 137, 100);      //lichess colours :)
    private Color lightColour=new Color(240, 218, 181);

    //State Control
    private char[][] grid; 
    private int numCaptured;
    private int numEnemies;
    private int numBlack;
    private List<Move> history;     //used for undo in manual mode
    private boolean firstClick;
    private int numTurns;
    private String Result;
    private double score;


    protected void generate()
    {
      H = randomInt(minH, maxH);
      E = randomDouble(minE, maxE);

      //Special cases
      if (seed == 1)
      {
        H = minH;
        E = maxE;
      }
      else if (seed == 2)
      {
        H = maxH;
        E = minE;
      }    
      
      //User defined parameters   
      if (parameters.isDefined("H")) H = randomInt(parameters.getIntRange("H"), minH, maxH); 
      if (parameters.isDefined("E")) E = randomDouble(parameters.getDoubleRange("E"), minE, maxE); 
     
      //initialize parameters
      history=new ArrayList<Move>();
      numTurns=0;
      numEnemies=0;
      numBlack=2*W;
      numCaptured=0;
      Result="";      

      //create grid
      grid=new char[H][W];
      for (int r=0; r<H; r++)
        for (int c=0; c<W; c++)      
          grid[r][c]=Empty;

      //place white pawns
      for (int r=0; r<H-4; r++)
        for (int c=0; c<W; c++)
          if (randomDouble(0,1)>E)
          {
            grid[r][c]=Enemy;
            numEnemies++;
          }

      //place black pawns
      for (int c=0; c<W; c++)
        grid[H-2][c]=Pawn;

      //place remaining black pieces
      boolean useQueen=(randomDouble(0,1)<queenP);     
      while(true)
      {
        boolean hasQueen=false;
        for (int c=0; c<W; c++)
        {
          grid[H-1][c]=Pieces[randomInt(0,4)];
          if (grid[H-1][c]==Queen) hasQueen=true;
        }
        if (useQueen==hasQueen) break;
      }


      //display info
      if (debug)
      {
        System.out.println("Grid height H = " + H);
        System.out.println("Empty ratio E = " + E);
        System.out.println("Grid:");          
        for (int r=0; r<H; r++)
        {
          for (int c=0; c<W; c++)        
            System.out.print(grid[r][c]);
          System.out.println();
        }     
        System.out.println(); 
      }
    }

    //shuffle the array randomly
    protected void shuffle(int[] a)
    {
      for (int i=0; i<a.length; i++)
      {
        int k=randomInt(i,a.length-1);
        int temp=a[i];  
        a[i]=a[k];
        a[k]=temp;  
      }   
    }     
         

    protected boolean isMaximize() {
        return false;
    }
    
    protected double run() throws Exception
    {
      init();
      if (parameters.isDefined("manual"))
      {
        firstClick=true;
        makeAImove();
        updateState();
        return 0;    
      }
      return runAuto();
    }
    

    protected double runAuto() throws Exception
    {
      double score = callSolution();
      if (score < 0) {
        if (!isReadActive()) return getErrorScore();
        return fatalError();
      }
      return score;
    }    
    
 
    private double callSolution() throws Exception
    {
      writeLine(""+H);

      // write grid
      for (int r=0; r<H; r++)
        for (int c=0; c<W; c++)        
          writeLine(""+grid[r][c]); 

      flush();
      if (!isReadActive()) return -1;

      updateState();

      try
      {
        while(true)
        {
          // Write the time elapsed
          writeLine(""+getRunTime());   

          // Write AI's move          
          int result=makeAImove();

          //check for end of game
          if (result==0)
          {
            Result="Enemy promoted";
            break;
          }
          if (result==2)
          {
            Result="Stalemate";
            break;
          }
          if (numBlack==0)
          {
            Result="Black killed";
            break;
          }
          if (!parameters.isDefined("noanimate")) updateState();     

          startTime();
          String line=readLine();
          stopTime();

          if (line.equals("0"))
          {
            Result="Terminated";
            break;
          }

          String[] temp=line.split(" ");
          if (temp.length!=4)
            return fatalError("Each move must contain exactly 4 integers, given: "+line);

          int r1=Integer.parseInt(temp[0]);
          int c1=Integer.parseInt(temp[1]);
          if (!inGrid(r1,c1))
            return fatalError("Selected piece is out of bounds ("+r1+","+c1+")");
          if (!isBlack(grid[r1][c1]))
            return fatalError("Selected piece does not belong to the player ("+r1+","+c1+")");

          int r2=Integer.parseInt(temp[2]);
          int c2=Integer.parseInt(temp[3]);          
          if (!inGrid(r2,c2))
            return fatalError("Target location is out of bounds ("+r2+","+c2+")");
          if (isBlack(grid[r2][c2]))
            return fatalError("Target location must be empty or enemy ("+r2+","+c2+")");          
          if (!isLegal(r1, c1, r2, c2))
            return fatalError("Illegal move: "+line);

       
          makeMove(r1,c1,r2,c2,false);
          if (numEnemies==0)
          {
            Result="Enemy killed";
            break;
          }
          if (!parameters.isDefined("noanimate")) updateState();     
        }
      }
      catch (Exception e) {
        if (debug) System.out.println(e.toString());
        return fatalError("Cannot parse your output");
      }
      updateState();

      return score;
    }

    //makes an AI move
    //0 = promotion reached, game over
    //1 = normal move
    //2 = no available moves (stalemate), also game over
    protected int makeAImove() throws Exception
    {
      //first look for promotions
      for (int c=0; c<W; c++)
      {
        if (grid[H-2][c]!=Enemy) continue;

        if (grid[H-1][c]==Empty)
        {          
          makeMove(H-2,c,H-1,c,true);
          return 0;
        }
        if (c-1>=0 && isBlack(grid[H-1][c-1]))
        {
          makeMove(H-2,c,H-1,c-1,true);   
          return 0;
        }
        if (c+1<W && isBlack(grid[H-1][c+1]))
        {
          makeMove(H-2,c,H-1,c+1,true);        
          return 0;
        }        
      }

      //now look for captures
      List<Move> moves=new ArrayList<Move>();
      for (int r=0; r<H-1; r++)
        for (int c=0; c<W; c++)
        {
          if (grid[r][c]!=Enemy) continue;

          if (c-1>=0 && isBlack(grid[r+1][c-1]))
            moves.add(new Move(r,c,r+1,c-1));
          if (c+1<W && isBlack(grid[r+1][c+1]))          
            moves.add(new Move(r,c,r+1,c+1));
        }     

      if (moves.size()>0)
      {
        int id=randomInt(0,moves.size()-1);
        Move m=moves.get(id);
        makeMove(m.r1, m.c1, m.r2, m.c2, true);
        return 1;
      }   

      //defend the weak - pieces that are not defended
      for (int r=2; r<H-1; r++)
        for (int c=0; c<W; c++)      
          if (isWeak(r,c))
          {
            if (c-1>=0 && grid[r-1][c-1]==Empty && grid[r-2][c-1]==Enemy)
              moves.add(new Move(r-2,c-1,r-1,c-1));
            if (c+1<W && grid[r-1][c+1]==Empty && grid[r-2][c+1]==Enemy)
              moves.add(new Move(r-2,c+1,r-1,c+1));
          }

      if (moves.size()>0)
      {
        int id=randomInt(0,moves.size()-1);
        Move m=moves.get(id);
        makeMove(m.r1, m.c1, m.r2, m.c2, true);
        return 1;
      }             

      //make a random advance that doesn't expose you
      for (int r=0; r<H-1; r++)
        for (int c=0; c<W; c++)
          if (grid[r][c]==Enemy && grid[r+1][c]==Empty && ((c-1>=0 && grid[r][c-1]==Enemy) || (c+1<W && grid[r][c+1]==Enemy))) 
            moves.add(new Move(r,c,r+1,c));                

      if (moves.size()>0)
      {
        int id=randomInt(0,moves.size()-1);
        Move m=moves.get(id);
        makeMove(m.r1, m.c1, m.r2, m.c2, true);
        return 1;
      }     

      //otherwise make a random advance
      for (int r=0; r<H-1; r++)
        for (int c=0; c<W; c++)
          if (grid[r][c]==Enemy && grid[r+1][c]==Empty)
            moves.add(new Move(r,c,r+1,c));    

      if (moves.size()>0)
      {
        int id=randomInt(0,moves.size()-1);
        Move m=moves.get(id);
        makeMove(m.r1, m.c1, m.r2, m.c2, true);
        return 1;
      }                   

      if (!parameters.isDefined("manual"))
      {
        writeLine("0");
        flush();
      }
      return 2;     
    }

    protected boolean isBlack(char c)
    {
        return !(c==Empty || c==Enemy);
    }

    private void makeMove(int r1, int c1, int r2, int c2, boolean isAI) throws Exception
    {
      numTurns++;

      lastR1=r1;
      lastC1=c1;
      lastR2=r2;
      lastC2=c2;

      if (parameters.isDefined("manual"))
      {
        history.add(new Move(r1,c1,r2,c2,grid[r1][c1],grid[r2][c2]));
      }

      if (isAI && !parameters.isDefined("manual"))
      {
        writeLine(""+r1+" "+c1+" "+r2+" "+c2);
        flush();   
      }

      if (!isAI && grid[r2][c2]==Enemy)
      {
        numCaptured++;
        numEnemies--;
      }

      if (isAI && isBlack(grid[r2][c2]))
      {
        numBlack--;
      }

      grid[r2][c2]=grid[r1][c1];
      grid[r1][c1]=Empty;

      //black promotion
      if (!isAI && allowBlackPromotion && grid[r2][c2]==Pawn && r2==0)
        grid[r2][c2]=Queen;

      //white promotion
      if (isAI && grid[r2][c2]==Enemy && r2==H-1)
        grid[r2][c2]=EnemyPromoted;      

      updateScore();
    }      


    //check that black's proposed move is legal
    protected boolean isLegal(int r1, int c1, int r2, int c2)
    {
      char piece=grid[r1][c1];

      int dr=Math.abs(r2-r1);
      int dc=Math.abs(c2-c1);      

      if (piece==Pawn)
      {
        if (r1-r2!=1) return false;

        if (c1==c2)
        {
          if (grid[r2][c2]==Empty) return true;
          else return false;
        }
        else if (dc==1)
        {
          if (grid[r2][c2]==Enemy) return true;
          else return false;
        }
        else return false;
      }

      if (piece==King)
      {
        if (dr<=1 && dc<=1) return true;
        else return false;
      }

      if (piece==Knight)
      {
        if (dr*dc==2) return true;
        else return false;
      }

      if (dr!=0) dr=(r2-r1)/dr;
      if (dc!=0) dc=(c2-c1)/dc;

      if (piece==Bishop && Math.abs(dr)*Math.abs(dc)!=1) return false;
      if (piece==Rook && Math.abs(dr)+Math.abs(dc)!=1) return false;
      if (piece==Queen && !(Math.abs(dr)<=1 && Math.abs(dc)<=1)) return false;      

      int r3=r1+dr;
      int c3=c1+dc;

      while(true)
      {
        if (r3==r2 && c3==c2) return true;    //reached target
        if (grid[r3][c3]!=Empty)  return false;   //bumped into something
        r3+=dr;
        c3+=dc;
      }
    }
   
    
    protected boolean inGrid(int r, int c)
    {
      return (r>=0 && r<H && c>=0 && c<W);
    }  


    protected void updateState()
    {
      if (hasVis()) 
      {      
        synchronized (updateLock) 
        {
          addInfo("Turns", numTurns);
          addInfo("Enemies", numEnemies);
          addInfo("Captured", numCaptured);
          addInfo("Score", shorten(score));
          addInfo("Result", Result);
          addInfo("Time", getRunTime());
        }
        updateDelay();
      }
    }

    protected void updateScore()
    {
      score = numTurns + H*W*numEnemies;      
    }

    protected void timeout()
    {
      addInfo("Score", "-1 (Timeout)");
      addInfo("Time", getRunTime());
      update();
    }     

    protected void undo()
    {
      if (history.size()==0) return;

      Move m=history.remove(history.size()-1);

      grid[m.r1][m.c1]=m.piece1;
      grid[m.r2][m.c2]=m.piece2;

      //undo capture
      if (m.piece2==Enemy)
      {
        numCaptured--;
        numEnemies++;
      }
      if (isBlack(m.piece2))
      {
        numBlack++;
      }

      numTurns--;
      lastR1 = lastC1 = -1;
      lastR2 = lastC2 = -1;      
      updateScore();
      updateState();
    }

    protected void contentClicked(double x, double y, int mouseButton, int clickCount)
    {
      if (!parameters.isDefined("manual")) return;
      if (Result.length()>0) return;    //game already finished
      
      //undo both moves with right click
      if (mouseButton == java.awt.event.MouseEvent.BUTTON3 && history.size()>1)
      {
        undo();
        undo();
        return;
      }

      int r=(int)Math.floor(y);
      int c=(int)Math.floor(x);
      if (!inGrid(r,c)) return;         //not in grid

      //left click
      if (mouseButton == java.awt.event.MouseEvent.BUTTON1)
      {
        //first click must be a black piece
        if (firstClick)
        {
          if (!isBlack(grid[r][c])) return;
          
          lastR1 = r;
          lastC1 = c;
          lastR2 = lastC2 = -1;
          firstClick=false;
          update();
        }
        //second click must be where you want to move
        else
        {         
          //unselect
          if (r==lastR1 && c==lastC1)
          {
            lastR1 = lastC1 = -1;
            lastR2 = lastC2 = -1;
            firstClick=true;
            update();
            return;
          }

          if (isBlack(grid[r][c])) return;    //must capture or move to an empty location

          if (isLegal(lastR1,lastC1,r,c))
          {
            firstClick=true;
            try
            {
              makeMove(lastR1,lastC1,r,c,false);
            }
            catch(Exception e){}

            lastR1 = lastC1 = -1;
            lastR2 = lastC2 = -1;      
            if (numEnemies==0)
            {
              Result="Enemy killed";
              updateState();
              return;
            }                 
            updateState();

            try
            {
              int result=makeAImove();

              //check for end of game
              if (result==0) Result="Enemy promoted";
              if (result==2) Result="Stalemate";
              if (numBlack==0) Result="Black killed";
              updateState();
            }
            catch(Exception e){}                        
          }
        }
      }
    }     


    protected boolean isWeak(int r, int c)
    {
      if (grid[r][c]!=Enemy) return false;
      return r==0 || (!(c-1>=0 && grid[r-1][c-1]==Enemy) && !(c+1<W && grid[r-1][c+1]==Enemy));
    }
     

    protected void paintContent(Graphics2D g)
    {      
      g.setColor(lightColour);
      g.fillRect(0,0,W,H);     

      //paint the cells in a checkerboard pattern
      g.setColor(darkColour);
      for (int r = 0; r < H; r++)
        for (int c = 0; c < W; c++)
          if ((r+c)%2==1)
            g.fillRect(c,r,1,1);

      //highlight unprotected enemies
      if (parameters.isDefined("showWeak"))
      {
        g.setColor(Color.cyan);
        for (int r = 0; r < H; r++)
          for (int c = 0; c < W; c++)        
            if (isWeak(r,c))
              g.fillRect(c,r,1,1);
      }

      //highlight black pieces under attack
      if (parameters.isDefined("showAttacks"))
      {
        g.setColor(Color.red);
        for (int r = 0; r < H; r++)
          for (int c = 0; c < W; c++)        
            if (r>0 && isBlack(grid[r][c]) && ((c-1>=0 && grid[r-1][c-1]==Enemy) || (c+1<W && grid[r-1][c+1]==Enemy)))
              g.fillRect(c,r,1,1);
      }      


      //draw pieces and targets
      for (int r = 0; r < H; r++)
        for (int c = 0; c < W; c++)
        {   
          if (grid[r][c]==King)
            g.drawImage(kingPic,c,r,1,1,null);            
          if (grid[r][c]==Knight)
            g.drawImage(knightPic,c,r,1,1,null);            
          if (grid[r][c]==Bishop)
            g.drawImage(bishopPic,c,r,1,1,null);            
          if (grid[r][c]==Rook)
            g.drawImage(rookPic,c,r,1,1,null);            
          if (grid[r][c]==Queen)
            g.drawImage(queenPic,c,r,1,1,null);            
          if (grid[r][c]==Pawn)
            g.drawImage(pawnPic,c,r,1,1,null);                      
          if (grid[r][c]==Enemy)
            g.drawImage(enemyPic,c,r,1,1,null);               
          if (grid[r][c]==EnemyPromoted)
            g.drawImage(enemyPromotedPic,c,r,1,1,null);             
        }
        
      //draw grid lines
      g.setColor(Color.black);
      g.setStroke(new BasicStroke(0.005f, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND));
      for (int i=0; i<=H; i++) g.drawLine(0,i,W,i);
      for (int i=0; i<=W; i++) g.drawLine(i,0,i,H);
        
      //draw selection squares
      if (lastR1!=-1)
      {
        g.setColor(Color.black);
        g.setStroke(new BasicStroke(0.1f, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND));
        g.drawRect(lastC1, lastR1, 1, 1);
      }
      if (lastR2!=-1)
      {
        g.setColor(Color.black);        
        g.setStroke(new BasicStroke(0.1f, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND));
        g.drawRect(lastC2, lastR2, 1, 1);
      }      
    }

    private double shorten(double a)
    {
      return (double)Math.round(a * 1000.0) / 1000.0;
    }

    Image loadImage(String name) {
      try{
        Image im=ImageIO.read(getClass().getResourceAsStream(name));
        return im;
      } catch (Exception e) { 
        return null;  
      }             
    }     

    private void init()
    {
      numTurns = 0;
      if (hasVis())
      {
        //load images
        //from https://en.wikipedia.org/wiki/Chess_piece
        kingPic = loadImage("images/king_black.png");
        knightPic = loadImage("images/knight_black.png");
        bishopPic = loadImage("images/bishop_black.png");
        rookPic = loadImage("images/rook_black.png");
        queenPic = loadImage("images/queen_black.png");
        pawnPic = loadImage("images/pawn_black.png");
        enemyPic = loadImage("images/pawn_white.png");
        enemyPromotedPic = loadImage("images/queen_white.png");

        lastR1 = lastC1 = lastR2 = lastC2 = -1;
        setContentRect(0, 0, W, H);
        setInfoMaxDimension(22, 15);    //horizontal, vertical
        setDefaultDelay(2000);

        addInfo("Seed", seed);
        addInfo("Height H", H);
        addInfo("EmptyRatio E", shorten(E));
        addInfoBreak();           
        addInfo("Turns", numTurns);
        addInfo("Enemies","-");
        addInfo("Captured", "-");
        addInfoBreak();
        addInfo("Result", "-");        
        addInfo("Time", 0);
        addInfo("Score", score);        
        update();
      }
    }
    
    public static void main(String[] args) {
        new MarathonController().run(args);
    }



  public class Move
  {
    int r1;
    int c1;
    int r2;
    int c2;
    char piece1;
    char piece2;

    public Move(int r1a, int c1a, int r2a, int c2a)
    {
      r1=r1a;
      c1=c1a;
      r2=r2a;
      c2=c2a;
    }

    public Move(int r1a, int c1a, int r2a, int c2a, char p1, char p2)
    {
      r1=r1a;
      c1=c1a;
      r2=r2a;
      c2=c2a;
      piece1=p1;
      piece2=p2;
    }    
  }
}