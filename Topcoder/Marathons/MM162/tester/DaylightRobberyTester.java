import java.awt.*;
import java.awt.geom.*;
import java.util.*;
import java.util.List;
import java.util.ArrayList;
import java.awt.event.KeyEvent;

import com.topcoder.marathon.*;


public class DaylightRobberyTester extends MarathonAnimatedVis {
  //parameter ranges
  private static final int minC = 20, maxC = 100;    // number of valuables range
  private static final int minG = 15, maxG = 50;     // number of guards range
  private static final int minB = 0, maxB = 10;       // multiplier for bribe penalty range

  //Inputs
  private int G;            // number of guards
  private int C;            // number of valuables
  private int B;            // bribe penalty multiplier

  //Constants other
  private static final int MAX_TURNS = 1000;
  private static final int SIZE = 10000;           // grid size

  private static final int SPOTTED_PENALTY = 5000;
  private static final int SCORE_BRIBE_PENALTY_MULT = 20;
  private static final int SCORE_VALUABLE_BASE = MAX_TURNS;

  private static final int GUARD_VIEWCONE_ANGLE = 25;
  private int GUARD_DETECT_STAY = 3200;            // distance the guards can see
  private int GUARD_DETECT_CROUCH =2000;            // distance the guards can see
  private int[] SPEED_STAY_CROUCH = {400, 200}; // for staying, crouching

  //Constants for polygons
  private static final int minSides=3;
  private static final int maxLowpolySides=4;
  private static final int maxSides=10;
  private static final double minPolygonRadius = 250.0;
  private static final double minPolygonArea = minPolygonRadius * minPolygonRadius;
  private static final double maxPolygonRadius = 1500.0;
  private static final double irregularity = 0.75;
  private static final double spikiness = 0.75;
  // and Generation
  private static final int generationCollisionRadius =150;
  private static final int generationThiefSidebound = 1000;
  private static final int generationMaxGuardSteplength = 500;
  private static final double generationLineProbability = 0.3;
  private static final double generationLowpolyProabability = 0.3;
  private static final int generationLineMinLength = 100;
  private static final int generationLineMaxLength = 6000;
  private static final boolean generationDisallowPathsInside = true;
  private static final boolean generationDisallowIntersecting = true;

  //Graphics
  private static final int selectiveViewconesDistance = 500;
  private static final int guardVisRadius = 100;
  private static final int valuableVisRadius = 100;
  private static final int thiefVisRadius = 100;

  //pre-computed stuff
  private List<Point>[] guardRoutes;
  private List<List<Point>>[] guardsConeOfViewStay;
  private List<List<Point>>[] guardsConeOfViewCrouch;

  //State Control
  private Point thief =null;
  private Point attemptedThief =null;
  private Point oldThief =null;
  private int thiefCrouching=1;

  private int turn;
  private int collected;
  private boolean unspotted=true;
  private int subdued=0;
  private int subduedNow=-1;
  private double score;

  private int[] guardsPositions;
  private boolean guardSpotted[];
  private boolean guardActive[];
  private Point[] valuables;
  private MessageHandler msgHandler= new MessageHandler();


  protected void generate()
  {
    C = randomInt(minC, maxC);
    G = randomInt(minG, maxG);
    B = randomInt(minB, maxB);

    //Special cases
    if (seed == 1)
    {
      C = minC;
      G = minG;
      B = minB;
    }
    else if (seed == 2)
    {
      C = maxC;
      G = maxG;
      B = maxB;
    }

    //User defined parameters
    if (parameters.isDefined("C")) C = randomInt(parameters.getIntRange("C"), minC, maxC);
    if (parameters.isDefined("G")) G = randomInt(parameters.getIntRange("G"), minG, maxG);
    if (parameters.isDefined("B")) B = randomInt(parameters.getIntRange("B"), minB, maxB);

    //generate random map
    valuables = new Point[C];
    guardRoutes = new ArrayList[G];
    guardsConeOfViewStay = new ArrayList[G];
    guardsConeOfViewCrouch = new ArrayList[G];
    guardsPositions = new int[G];
    guardSpotted = new boolean[G];
    guardActive = new boolean[G];

    thief = generateThiefPosition();

    double extra= 0;

    for (int i=0; i< G;)
    {
      guardRoutes[i] = generateGuardRoute();

      boolean ok=true;
      for (int k = 0; k < guardRoutes[i].size(); k++) {if ( distPoint2Point(guardRoutes[i].get(k), thief) < GUARD_DETECT_CROUCH) { ok =false; break;}}
      if (!ok) continue;

      boolean valid = true;
      for (int k = 0; k < guardRoutes[i].size(); k++) {
        if (guardRoutes[i].get(k).x < extra || guardRoutes[i].get(k).x > SIZE -extra || guardRoutes[i].get(k).y < extra || guardRoutes[i].get(k).y > SIZE -extra) {
          valid = false;
        }
      }
      for (int j = 0; j < i && valid; j++) {
        if (generationDisallowPathsInside) {
          if (isPointInsidePoly(guardRoutes[j].get(0), guardRoutes[i]) || isPointInsidePoly(guardRoutes[i].get(0), guardRoutes[j])) {
            valid = false;
            break;
          }
        }
        if (generationDisallowIntersecting) {
          for (int k1 = 0; k1 < guardRoutes[j].size(); k1++) {
            for (int k2 = 0; k2 < guardRoutes[i].size(); k2++) {
              if (linesIntersect(guardRoutes[j].get(k1).x, guardRoutes[j].get(k1).y,
                      guardRoutes[j].get((k1 + 1) % guardRoutes[j].size()).x, guardRoutes[j].get((k1 + 1) % guardRoutes[j].size()).y,
                      guardRoutes[i].get(k2).x, guardRoutes[i].get(k2).y,
                      guardRoutes[i].get((k2 + 1) % guardRoutes[i].size()).x, guardRoutes[i].get((k2 + 1) % guardRoutes[i].size()).y)) {
                valid = false;
                break;
              }
            }
          }
        }
      }
      if (valid)
      {
        guardRoutes[i] = fixPatrolsEdges(guardRoutes[i]);
        precomputeGuardPathViewcones(i);
        i++;
      }
    }

    generateValuables();

    if (debug)
    {
      System.out.println("Coins, C = " + C);
      System.out.println("Guards, G = " + G);
      System.out.println("Bribe, B = " + B);
      System.out.println("Thief: x = "+thief.x+" y = "+thief.y);
    }
    score = C * SCORE_VALUABLE_BASE + SPOTTED_PENALTY;
  }


  protected Point generateThiefPosition() {
    int x=randomInt(generationCollisionRadius, generationThiefSidebound -1- generationCollisionRadius);
    int y=randomInt(generationCollisionRadius, SIZE -1 - generationCollisionRadius - generationThiefSidebound);
    int r=randomInt(0, 3);
    if (r==0) return new Point(x,y);
    if (r==1) return new Point(y,SIZE-x);
    if (r==2) return new Point(SIZE-x,SIZE-y);
    if (r==3) return new Point(SIZE-y,x);
    return null;
  }

  protected void generateValuables() {
    for (int i=0; i< C; )
    {
      int x=randomInt(generationCollisionRadius, SIZE -1- generationCollisionRadius);
      int y=randomInt(generationCollisionRadius, SIZE -1- generationCollisionRadius);
      Point p=new Point(x,y);
      if (!isPointOk(p, generationCollisionRadius)) continue;
      valuables[i]=p;
      i++;
    }
  }

  private boolean isPointOk(Point p, int radius)
  {
    if (distPoint2Point(p,thief) < radius) return false;
    for (int i = 0; i< C; i++) if (valuables[i]!=null && distPoint2Point(valuables[i], p) < radius) return false;

    for (int i = 0; i< G; i++) {
      if (guardRoutes[i] == null) continue;
      for (int k = 0; k < guardRoutes[i].size(); k++)
        if (guardRoutes[i].get(k) != null && distPoint2Point(guardRoutes[i].get(k), p) < radius) return false;
    }
    return true;
  }

  private ArrayList<Point> generateLine() {
    while (true) { // is this wise?
      int x = randomInt(generationCollisionRadius, SIZE - 1 - generationCollisionRadius);
      int y = randomInt(generationCollisionRadius, SIZE - 1 - generationCollisionRadius);
      int len = randomInt(generationLineMinLength, generationLineMaxLength);
      int angle = randomInt(0, 359);
      int nx = x + (int) Math.round(len * Math.cos(angle));
      int ny = y + (int) Math.round(len * Math.sin(angle));
//      int nx = randomInt(generationCollisionRadius, SIZE - 1 - generationCollisionRadius);
//      int ny = randomInt(generationCollisionRadius, SIZE - 1 - generationCollisionRadius);
      if (nx < generationCollisionRadius || nx > SIZE - 1 - generationCollisionRadius || ny < generationCollisionRadius || ny > SIZE - 1 - generationCollisionRadius) continue;
      return new ArrayList<>(Arrays.asList(new Point(x, y), new Point(nx, ny)));
    }
  }

  //from sullyper
  protected ArrayList<Point> generatePolygon(boolean lowpoly)
  {
    int num_vertices = lowpoly ? randomInt(minSides, maxLowpolySides) : randomInt(maxLowpolySides+1, maxSides);
    double avg_radius = randomDouble(minPolygonRadius, maxPolygonRadius);
    double irr = irregularity * 2 * Math.PI / num_vertices;
    double sk = spikiness * avg_radius;
    Point center = new Point(randomInt(0, SIZE -1), randomInt(0, SIZE -1));

    double[] angles = new double[num_vertices];
    double lower = (2 * Math.PI / num_vertices) - irr;
    double upper = (2 * Math.PI / num_vertices) + irr;
    double cumsum = 0;
    for (int i = 0; i < num_vertices; i++) {
      cumsum += randomDouble(lower, upper);
      angles[i] = cumsum;
    }

    cumsum /= (2 * Math.PI);
    for (int i = 0; i < num_vertices; i++) {
      angles[i] /= cumsum;
    }

    ArrayList<Point> points = new ArrayList<Point>();

    for (int i = 0; i < num_vertices; i++) {
      double radius = Math.max(1.0, avg_radius + randomGaussian() * sk);
      points.add(new Point(center.x + (int)Math.round(radius * Math.cos(angles[i])),
                           center.y + (int)Math.round(radius * Math.sin(angles[i]))));
    }
    return points;
  }

  protected ArrayList<Point> generateGuardRoute()
  {
    double r = randomDouble(0, 1);
    if (r < generationLineProbability) return generateLine();
    boolean lowpoly = r- generationLineProbability < generationLowpolyProabability;
    for (int tries=0; tries<10; tries++)
    {
      ArrayList<Point> poly = generatePolygon(lowpoly);
      if (areaOfPolygon(poly) >= minPolygonArea) return poly;
    }

    return generateGuardRoute();
  }


  private List<Point> fixPatrolsEdges(List<Point> prepath) {
    List<Point> fixedpath = new ArrayList<>();
    for (int i = 0; i < prepath.size(); i++) {
      Point p1=prepath.get(i);
      Point p2=prepath.get((i+1)% prepath.size());
      double steppoints = Math.ceil(distPoint2Point(p1, p2)/ generationMaxGuardSteplength);
      for (int k = 0; k < steppoints; k++) {
        double perc = k/steppoints;
        int pX=(int)Math.round(p1.x+(p2.x-p1.x)*perc);
        int pY=(int)Math.round(p1.y+(p2.y-p1.y)*perc);
        fixedpath.add(new Point(pX, pY));
      }
    }
    return fixedpath;
  }

  private void precomputeGuardPathViewcones(int i) {
    guardsPositions[i]=0;
    guardSpotted[i]=false;
    guardActive[i]=true;
    guardsConeOfViewStay[i] = new ArrayList<>();
    guardsConeOfViewCrouch[i] = new ArrayList<>();

    for (int k = 0; k<guardRoutes[i].size(); k++) {
      Point p1=guardRoutes[i].get((guardRoutes[i].size()+k-1)%guardRoutes[i].size());
      Point p2=guardRoutes[i].get(k);
      double angle = Math.atan2(p1.y-p2.y,p2.x-p1.x)/2/Math.PI*360;

      int p3X=(int)Math.round(p2.x+Math.cos((angle- GUARD_VIEWCONE_ANGLE)/360.0*2*Math.PI)* GUARD_DETECT_STAY);
      int p3Y=(int)Math.round(p2.y-Math.sin((angle- GUARD_VIEWCONE_ANGLE)/360.0*2*Math.PI)* GUARD_DETECT_STAY);
      int p4X=(int)Math.round(p2.x+Math.cos((angle+ GUARD_VIEWCONE_ANGLE)/360.0*2*Math.PI)* GUARD_DETECT_STAY);
      int p4Y=(int)Math.round(p2.y-Math.sin((angle+ GUARD_VIEWCONE_ANGLE)/360.0*2*Math.PI)* GUARD_DETECT_STAY);

      guardsConeOfViewStay[i].add(new ArrayList<>());
      guardsConeOfViewStay[i].get(k).add(p2); guardsConeOfViewStay[i].get(k).add(new Point(p3X, p3Y)); guardsConeOfViewStay[i].get(k).add(new Point(p4X, p4Y));

      p3X=(int)Math.round(p2.x+Math.cos((angle- GUARD_VIEWCONE_ANGLE)/360.0*2*Math.PI)* GUARD_DETECT_CROUCH);
      p3Y=(int)Math.round(p2.y-Math.sin((angle- GUARD_VIEWCONE_ANGLE)/360.0*2*Math.PI)* GUARD_DETECT_CROUCH);
      p4X=(int)Math.round(p2.x+Math.cos((angle+ GUARD_VIEWCONE_ANGLE)/360.0*2*Math.PI)* GUARD_DETECT_CROUCH);
      p4Y=(int)Math.round(p2.y-Math.sin((angle+ GUARD_VIEWCONE_ANGLE)/360.0*2*Math.PI)* GUARD_DETECT_CROUCH);

      guardsConeOfViewCrouch[i].add(new ArrayList<>());
      guardsConeOfViewCrouch[i].get(k).add(p2); guardsConeOfViewCrouch[i].get(k).add(new Point(p3X, p3Y)); guardsConeOfViewCrouch[i].get(k).add(new Point(p4X, p4Y));
    }
  }


  private boolean gameOver = false;
  private boolean preview = false;
  private Point thiefPreview = null;
  private int thiefCrouchingPreview = 0;
  private int subduedNowPreview = -1;
  private int collectablePreview = -1;
  private boolean crouchingEnable = false;


  protected void handleKeyPressed(KeyEvent e) {
    if (!parameters.isDefined("manual")) return;
    if (e.getKeyCode() == KeyEvent.VK_CONTROL) {
      crouchingEnable = true;
      e.consume();
    }
  }
  protected void handleKeyReleased(KeyEvent e) {
    if (!parameters.isDefined("manual")) return;
    if (e.getKeyCode() == KeyEvent.VK_CONTROL) {
      crouchingEnable = false;
      e.consume();
    }
  }

  protected void contentClicked(double x, double y, int mouseButton, int clickCount)
  {
    if (gameOver) return;
    if (!parameters.isDefined("manual")) return;
    if (mouseButton == java.awt.event.MouseEvent.BUTTON3)
    {
      int atY = (int) Math.floor(y);
      int atX = (int) Math.floor(x);
      int closest = -1;
      int closest_dist = 10000;
      collectablePreview = -1;
      subduedNowPreview = -1;

      if (!preview) {
        for (int i = 0; i< G; i++) { if (guardActive[i]) guardsPositions[i] = ((guardsPositions[i]+1) % guardRoutes[i].size());}
        preview = true;
      }

      for (int i = 0; i < C; i++) {
        if (valuables[i] == null) continue;
        int dist = sq(valuables[i].x - atX) + sq(valuables[i].y - atY);
        if (dist < closest_dist) {
          closest_dist = dist;
          closest = i;
        }
      }
      if (closest >= 0) {
        atX = valuables[closest].x;
        atY = valuables[closest].y;
        int dist = sq(thief.x - atX) + sq(thief.y - atY);
        collectablePreview = dist <= sq(SPEED_STAY_CROUCH[crouchingEnable ? 1 : 0]) ? closest : -1;
      } else {
        // guards subduing
        for (int i = 0; i< G; i++) {
          if (!guardActive[i]) continue;

          int dist = sq(guardRoutes[i].get(guardsPositions[i]).x - atX) + sq(guardRoutes[i].get(guardsPositions[i]).y - atY);
          if (dist < closest_dist) {
            closest_dist = dist;
            closest = i;
          }
        }
        if (closest >= 0) {
          atX = guardRoutes[closest].get(guardsPositions[closest]).x;
          atY = guardRoutes[closest].get(guardsPositions[closest]).y;
          int dist = sq(thief.x - atX) + sq(thief.y - atY);
          subduedNowPreview = dist <= sq(SPEED_STAY_CROUCH[crouchingEnable ? 1 : 0]) ? closest : -1;
        }
      }

      attemptedThief = new Point(atX, atY);
      thiefPreview = new Point(atX, atY);
      double dist = Math.sqrt(sq(thief.y-atY)+sq(thief.x-atX));
      if (dist > SPEED_STAY_CROUCH[crouchingEnable ? 1 : 0]) { // need interpolation
        double perc = SPEED_STAY_CROUCH[crouchingEnable ? 1 : 0]/dist;
        thiefPreview.x = (int)Math.round(thief.x+(atX-thief.x)*perc);
        thiefPreview.y = (int)Math.round(thief.y+(atY-thief.y)*perc);
      }
      thiefCrouchingPreview = ((crouchingEnable || dist <= SPEED_STAY_CROUCH[1]) && subduedNowPreview == -1) ? 1 : 0; // autocrouching if close enough

      for (int i = 0; i< G; i++) {
        if (!inGrid(atX, atY)) continue;
        if (!guardActive[i] || subduedNowPreview == i) continue;

        guardSpotted[i]=false;
        if (isPointInsideTriangle(thiefPreview, thiefCrouchingPreview==1?guardsConeOfViewCrouch[i].get(guardsPositions[i]):guardsConeOfViewStay[i].get(guardsPositions[i])))
        {
          guardSpotted[i]=true;
        }
      }

      updateState();
    }

    if (mouseButton == java.awt.event.MouseEvent.BUTTON1)
    {
      if (thief == null) return;
      if (thiefPreview == null) return;
      preview = false;
      thiefCrouchingPreview = 0;
      subduedNowPreview = -1;
      collectablePreview = -1;
      turn++;
      makeMove(thiefPreview.x, thiefPreview.y, false);
      updateState();
    }
  }

  protected boolean inGrid(int r, int c)
  {
    return r>=0 && r< SIZE && c>=0 && c< SIZE;
  }

  private boolean makeMove(int atX, int atY, boolean moveGuards) {
    oldThief = thief;
    attemptedThief = new Point(atX, atY);
    thief = new Point(atX, atY);
    double dist = distPoint2Point(oldThief, attemptedThief);
    if (dist > SPEED_STAY_CROUCH[crouchingEnable ? 1 : 0]) { // need interpolation
      double perc = SPEED_STAY_CROUCH[crouchingEnable ? 1 : 0]/dist;
      thief.x = (int)Math.floor(oldThief.x+(atX-oldThief.x)*perc);
      thief.y = (int)Math.floor(oldThief.y+(atY-oldThief.y)*perc);
    }
    thiefCrouching = (crouchingEnable || dist <= SPEED_STAY_CROUCH[1]) ? 1 : 0; // autocrouching if close enough

    boolean outOfBounds = (thief.x<0 || thief.x>=SIZE) || (thief.y<0 || thief.y>=SIZE);
    unspotted = true;
    subduedNow = -1;

    // guards move
    if (moveGuards) {
      for (int i = 0; i< G; i++) { if (true || guardActive[i]) guardsPositions[i] = ((guardsPositions[i]+1) % guardRoutes[i].size());}
    }
    // guards subduing
    for (int i = 0; i< G; i++) {
      if (!guardActive[i]) continue;

      if (guardRoutes[i].get(guardsPositions[i]).x == thief.x && guardRoutes[i].get(guardsPositions[i]).y == thief.y) {
        guardActive[i] = false;
        subdued++;
        subduedNow = i;
        thiefCrouching = 0; // NOT CROUCHING if ATTACKING A GUARD
        score += SCORE_BRIBE_PENALTY_MULT * B;
        continue;
      }
    }

    int collectedVal=-1;
    if (outOfBounds) {
      score -= SPOTTED_PENALTY;
    } else {
      for (int i = 0; i< G; i++)
      {
        if (outOfBounds) continue;
        if (!guardActive[i]) continue;

        guardSpotted[i]=false;
        if (isPointInsideTriangle(thief, thiefCrouching==1?guardsConeOfViewCrouch[i].get(guardsPositions[i]):guardsConeOfViewStay[i].get(guardsPositions[i])))
        {
          unspotted=false;
          guardSpotted[i]=true;
          // no break because we want to visualize
        }
      }

      if (unspotted) {
        for (int i = 0; i < C; i++) {
          if (valuables[i] == null) continue;
          if (valuables[i].x != thief.x || valuables[i].y != thief.y) continue;
          score += turn - SCORE_VALUABLE_BASE;
          collected++;
          valuables[i] = null;
          collectedVal = i;
        }
      }
    }
    if (debug)
    {
      System.out.println("Turn "+turn);
      System.out.println("Requested position "+attemptedThief.niceStr());
      System.out.println("Actual position "+thief.niceStr());
      System.out.println("Height "+ (thiefCrouching==1?"crouching":"standing"));
      System.out.println("Collected valuable "+(collectedVal==-1?"none":collectedVal));
      System.out.println("Subdued guard "+(subduedNow==-1?"none":subduedNow));
      System.out.println("Spotted " + (unspotted?"no":"yes"));
      System.out.println("score is "+score);
      if (outOfBounds) System.out.println("Escaped.");
      System.out.println();
    }
    if (!unspotted || outOfBounds || turn >= MAX_TURNS) {
      gameOver = true;
      return true;
    }

    return false;
  }

  private double callSolution() throws Exception
  {
    writeLine(""+ C);
    writeLine(""+ G);
    writeLine(""+ B);
    for (Point p : valuables) writeLine(""+p.x+" "+p.y);
    for (int i = 0; i< G; i++)
    {
      writeLine(""+ guardRoutes[i].size());
      //for (Point p : guardRoutes[i]) writeLine(""+p.x+" "+p.y);

      for (int k=0; k < guardRoutes[i].size(); k++) {
        writeLine(""+guardRoutes[i].get(k).x+" "+guardRoutes[i].get(k).y+ " "
        + guardsConeOfViewCrouch[i].get(k).get(1).x+" "+guardsConeOfViewCrouch[i].get(k).get(1).y+ " "
        + guardsConeOfViewCrouch[i].get(k).get(2).x+" "+guardsConeOfViewCrouch[i].get(k).get(2).y+ " "
        + guardsConeOfViewStay[i].get(k).get(1).x+" "+guardsConeOfViewStay[i].get(k).get(1).y+ " "
        + guardsConeOfViewStay[i].get(k).get(2).x+" "+guardsConeOfViewStay[i].get(k).get(2).y+ " ");
      }
    }
    writeLine(""+ thief.x+" "+ thief.y);

    flush();
    if (!isReadActive()) return -1;

    updateState();

    try
    {
      String[] inputLines = new String[MAX_TURNS +1];

      startTime();
      int PLAYERTURNS = Integer.parseInt(readLine());
      if (PLAYERTURNS<1 || PLAYERTURNS>1000) return fatalError("Illegal number of moves: "+PLAYERTURNS);
      for (turn=1; turn<= PLAYERTURNS; turn++) inputLines[turn]=readLine();
      stopTime();

      if (debug) System.out.println("Turn: " + PLAYERTURNS);
      for (turn=1; turn<= PLAYERTURNS; turn++)
      {
        String[] temp=inputLines[turn].split(" ", 3);
        if (temp.length<2) return fatalError("Illegal move format: "+inputLines[turn]);
        msgHandler.update(temp, 2);

        int atX = Integer.parseInt(temp[0]);
        int atY = Integer.parseInt(temp[1]);

        if (makeMove(atX, atY, true)) break;
        if (!parameters.isDefined("noanimate")) updateState();
      }
      updateState();
      return score; // not escaped in time
    }
    catch (Exception e) {
      if (debug) System.out.println(e.toString());
      return fatalError("Cannot parse your output");
    }

    //return score;
  }


/////////////////////////////////


  protected void paintContent(Graphics2D g)
  {
    Stroke dashed = new BasicStroke(20f, BasicStroke.CAP_BUTT, BasicStroke.JOIN_BEVEL, 0, new float[]{40}, 0);
    Stroke dashed2 = new BasicStroke(20f, BasicStroke.CAP_BUTT, BasicStroke.JOIN_BEVEL, 0, new float[]{40}, 40);
    Stroke normal = new BasicStroke(20f, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND);
    Stroke thin = new BasicStroke(10f, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND);

    //g.setStroke(new BasicStroke(0.005f, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND));
    adjustFont(g, Font.SANS_SERIF, Font.BOLD, String.valueOf("10"), new Rectangle2D.Double(0, 0, 2* valuableVisRadius, 2* valuableVisRadius));

    //g.setColor(new Color(129,245,66));   //light green
    g.setColor(Color.lightGray);
    g.fillRect(0,0, SIZE, SIZE);
    g.setStroke(normal);
    g.setColor(Color.black);
    g.drawRect(0,0, SIZE, SIZE);

    //draw guard routes
    //g.setStroke(thin);
    if (!parameters.isDefined("hideRoutes")) for (int i = 0; i< G; i++) paintPolygon(g, guardRoutes[i], null, Color.gray);
    g.setStroke(dashed);
    for (int i = 0; i< G; i++) paintLine(g, guardRoutes[i].get(guardsPositions[i]), guardRoutes[i].get((guardRoutes[i].size()+guardsPositions[i]-1)% guardRoutes[i].size()), Color.gray.darker());
    for (int i = 0; i< G; i++) paintLine(g, guardRoutes[i].get((guardRoutes[i].size()+guardsPositions[i]-1)% guardRoutes[i].size()), guardRoutes[i].get((guardRoutes[i].size()+guardsPositions[i]-2)% guardRoutes[i].size()), Color.gray);
    g.setStroke(normal);

    //draw valuables
    g.setStroke(thin);
    adjustFont(g, Font.SANS_SERIF, Font.BOLD, String.valueOf("00"), new Rectangle2D.Double(0, 0, 2* valuableVisRadius-40, 2* valuableVisRadius-40));
    for (int i = 0; i< C; i++)
    {
      if (valuables[i]==null) continue;
      paintPointCircle(g, valuables[i], valuableVisRadius, collectablePreview == i ? Color.yellow : Color.yellow.darker(),
                       Color.black, ""+i, Color.black);
    }
    g.setStroke(normal);

    adjustFont(g, Font.SANS_SERIF, Font.BOLD, String.valueOf("10"), new Rectangle2D.Double(0, 0, 2* valuableVisRadius, 2* valuableVisRadius));
    //draw guards
    for (int i=0; i<G; i++)
    {
      int k=guardsPositions[i];
      if (!guardActive[i])
      {
        paintPointCircle(g, guardsConeOfViewStay[i].get(k).get(0), guardVisRadius, Color.lightGray, Color.black, ""+i, Color.darkGray);
        continue;
      }

      if (!parameters.isDefined("selectiveViewcones") || guardSpotted[i] || distPoint2Poly(thief, guardsConeOfViewStay[i].get(k)) <= selectiveViewconesDistance)
      {
        Color cfillc = guardSpotted[i]?new Color(225, 85, 31, preview ? 32 : 70):new Color(129,245,66, preview ? 32 : 70);
        Color cfills = guardSpotted[i]?new Color(178, 20, 44, preview ? 32 : 70):new Color(29, 168, 80, preview ? 32 : 70);
        Color cbord = guardSpotted[i]?Color.orange.darker():Color.GREEN.darker();
        paintPolygon(g, capTriangle(guardsConeOfViewStay[i].get(k)), cfills, cfills);
        paintPolygon(g, capTriangle(guardsConeOfViewCrouch[i].get(k)), cfillc, null);
      }

      paintPointCircle(g, guardsConeOfViewStay[i].get(k).get(0), guardVisRadius, Color.blue, Color.black, ""+i, Color.white);
    }

    //draw thief
    paintPointCircle(g, thief, thiefVisRadius, Color.black, subduedNow!=-1?Color.red:Color.black, thiefCrouching==1?"C":"S",thiefCrouching==1?Color.gray:Color.white);
    if (preview) {
      paintPointCircle(g, thiefPreview, thiefVisRadius, Color.gray.darker(), subduedNowPreview!=-1?Color.red:Color.black,
                       thiefCrouchingPreview==1?"C":"S",thiefCrouchingPreview==1?Color.gray:Color.white.darker());
    }

    g.setStroke(dashed);
    if (oldThief!=null) paintLine(g, oldThief, thief, Color.gray);
    g.setStroke(normal);

    if (parameters.isDefined("showAttempt")) {
      g.setStroke(dashed2);
      if (attemptedThief!= null) paintLine(g, oldThief, attemptedThief, Color.black);
      g.setStroke(normal);
    }

    //  in manual mode
    if (parameters.isDefined("manual"))
    {
      g.setStroke(dashed);
      if (attemptedThief!= null) paintLine(g, thief, attemptedThief, Color.black);
      g.setStroke(normal);
    }
  }

  //region <PAINT METHODS>

  private void paintPointCircle(Graphics2D g, Point p, int radius, Color fillcol, Color bordercol)
  {
    g.setColor(fillcol);
    g.fillOval(p.x-radius, p.y-radius, 2*radius, 2*radius);
    g.setColor(bordercol);
    g.drawOval(p.x-radius, p.y-radius, 2*radius, 2*radius);
  }

  private void paintPointCircle(Graphics2D g, Point p, int radius, Color fillcol, Color bordercol, String text, Color textcol)
  {
    g.setColor(fillcol);
    g.fillOval(p.x-radius, p.y-radius, 2*radius, 2*radius);
    g.setColor(bordercol);
    g.drawOval(p.x-radius, p.y-radius, 2*radius, 2*radius);
    g.setColor(textcol);
    drawString(g, text, new Rectangle2D.Double(p.x, p.y, 0, 0));
  }

  private void paintLine(Graphics2D g, Point p1, Point p2, Color color)
  {
    g.setColor(color);
    g.drawLine(p1.x, p1.y, p2.x, p2.y);
  }

  private void paintPolygon(Graphics2D g, List<Point> poly, Color fillcolor, Color bordercol)
  {
    GeneralPath gp = new GeneralPath();
    Point p= poly.get(0);
    gp.moveTo(p.x, p.y);

    for (int k = 1; k< poly.size(); k++)
    {
      Point p2= poly.get(k);
      gp.lineTo(p2.x, p2.y);
    }
    gp.lineTo(p.x, p.y);    //close path
    if (fillcolor != null) {g.setColor(fillcolor); g.fill(gp);}
    if (bordercol != null) {g.setColor(bordercol); g.draw(gp);}
  }

  private boolean isInside(Point p) {
    return p.x >= 0 && p.y >= 0 && p.x <= SIZE && p.y <= SIZE;
  }

  private Point onEdge(Point a, Point b) {
    double dx = b.x - a.x;
    double dy = b.y - a.y;
    double f = 1.0;
    if (b.x < 0) {
      f = Math.min(f, a.x / -dx);
    }
    if (b.x > SIZE) {
      f = Math.min(f, (SIZE - a.x) / dx);
    }
    if (b.y < 0) {
      f = Math.min(f, a.y / -dy);
    }
    if (b.y > SIZE) {
      f = Math.min(f, (SIZE - a.y) / dy);
    }
    return new Point((int)(a.x + f * dx), (int)(a.y + f * dy));
  }

  private List<Point> capTriangle(List<Point> triangle) {
    Point p1 = triangle.get(0);
    Point p2 = triangle.get(1);
    Point p3 = triangle.get(2);
    if (isInside(p2) && isInside(p3)) return triangle;
    List<Point> ans = new ArrayList<Point>();
    ans.add(p1);
    if (isInside(p2)) {
      ans.add(p2);
      ans.add(onEdge(p2, p3));
      ans.add(onEdge(p1, p3));
    } else if (isInside(p3)) {
      ans.add(onEdge(p1, p2));
      ans.add(onEdge(p3, p2));
      ans.add(p3);
    } else {
      Point e2 = onEdge(p1, p2);
      Point e3 = onEdge(p1, p3);
      if (e2.x == e3.x || e2.y == e3.y) {
        ans.add(e2);
        ans.add(e3);
      } else {
        int x = (e2.x == 0 || e3.x==0) ? 0 : SIZE;
        int y = (e2.y == 0 || e3.y==0) ? 0 : SIZE;
        Point corner = new Point(x, y);
        if (isPointInsideTriangle(corner, triangle)) {
          ans.add(e2);
          ans.add(corner);
          ans.add(e3);
        } else {
          ans.add(e2);
          ans.add(onEdge(p3, p2));
          ans.add(onEdge(p2, p3));
          ans.add(e3);
        }
      }
    }
    return ans;
  }

  // endregion

  //region <MATH METHODS>

  private double shorten(double a)
  {
    return (double)Math.round(a * 1000.0) / 1000.0;
  }

  //generates a normally distributed random variable with mean 0 and standard deviation 1
  //based on https://docs.oracle.com/javase/8/docs/api/java/util/Random.html#nextGaussian--
  //which is based on Box-Muller
  private double randomGaussian()
  {
    double v1,v2,s;
    do
    {
      v1 = randomDouble(-1,+1);
      v2 = randomDouble(-1,+1);
      s = v1 * v1 + v2 * v2;
    }
    while (s >= 1 || s == 0);

    //I am throwing away the v2 random, but it's ok
    return v1 * Math.sqrt(-2 * Math.log(s)/s);
  }


  //endregion

  //region <GEOMETRY METHODS>

  private double distSegment2Segment(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
  {
    if (linesIntersect(x1,y1,x2,y2,x3,y3,x4,y4)) return 0;

    double d1=distPoint2Line(new Point(x1,y1),x3,y3,x4,y4);
    double d2=distPoint2Line(new Point(x2,y2),x3,y3,x4,y4);
    double d3=distPoint2Line(new Point(x3,y3),x1,y1,x2,y2);
    double d4=distPoint2Line(new Point(x4,y4),x1,y1,x2,y2);
    double[] a={d1,d2,d3,d4};
    Arrays.sort(a);
    return a[0];
  }

  // Checks whether segments (x1,y1)-(x2,y2) and (x3,y3)-(x4,y4) intersect or touch
  // Modified Java's Line2D implementation to use integers
  // https://github.com/srisatish/openjdk/blob/master/jdk/src/share/classes/java/awt/geom/Line2D.java
  private boolean linesIntersect(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
  {
    return ((relativeCCW(x1, y1, x2, y2, x3, y3) *
            relativeCCW(x1, y1, x2, y2, x4, y4) <= 0)
            && (relativeCCW(x3, y3, x4, y4, x1, y1) *
            relativeCCW(x3, y3, x4, y4, x2, y2) <= 0));
  }

  private int relativeCCW(int x1, int y1, int x2, int y2, int px, int py)
  {
    x2 -= x1;
    y2 -= y1;
    px -= x1;
    py -= y1;
    long ccw = px * y2 - py * x2;
    if (ccw == 0) {
      ccw = px * x2 + py * y2;
      if (ccw > 0) {
        px -= x2;
        py -= y2;
        ccw = px * x2 + py * y2;
        if (ccw < 0) ccw = 0;
      }
    }
    return (ccw < 0) ? -1 : ((ccw > 0) ? 1 : 0);
  }

  private boolean isPointInsideTriangle(Point p, List<Point> triangle) {
    if (triangle.size() != 3) return false;

    Point p1 = triangle.get(0);
    Point p2 = triangle.get(1);
    Point p3 = triangle.get(2);

    // Check if point p is on the same side of all three edges
    int ccw1 = relativeCCW(p1.x, p1.y, p2.x, p2.y, p.x, p.y);
    int ccw2 = relativeCCW(p2.x, p2.y, p3.x, p3.y, p.x, p.y);
    int ccw3 = relativeCCW(p3.x, p3.y, p1.x, p1.y, p.x, p.y);

    return (ccw1 >= 0 && ccw2 >= 0 && ccw3 >= 0) || (ccw1 <= 0 && ccw2 <= 0 && ccw3 <= 0);
  }

  //from https://stackoverflow.com/questions/217578/how-can-i-determine-whether-a-2d-point-is-within-a-polygon
  private boolean isPointInsidePoly(Point p, List<Point> poly)
  {
    boolean inside=false;
    for (int i = 0, j = poly.size()-1; i < poly.size(); j = i++)
    {
      Point p1=poly.get(i);
      Point p2=poly.get(j);
      if ( ((p1.y>p.y) != (p2.y>p.y)) &&
              (p.x < (p2.x-p1.x) * (p.y-p1.y) * 1.0 / (p2.y-p1.y) + p1.x) )
        inside = !inside;
    }
    return inside;
  }

  private double distPoint2Point(Point p1, Point p2)
  {
    return Math.sqrt(sq(p1.x-p2.x) + sq(p1.y-p2.y));
  }

  //minimum distance from a point to a polygon
  private double distPoint2Poly(Point p, List<Point> poly)
  {
    double min=Double.MAX_VALUE;

    for (int i=0; i<poly.size(); i++)
    {
      Point p1=poly.get(i);
      Point p2=poly.get((i+1)%poly.size());
      min=Math.min(min,distPoint2Line(p,p1.x,p1.y,p2.x,p2.y));
    }

    return min;
  }

  //from https://stackoverflow.com/questions/849211/shortest-distance-between-a-point-and-a-line-segment
  private double distPoint2Line(Point p, int x1, int y1, int x2, int y2)
  {
    int x=p.x;
    int y=p.y;
    int A = x - x1;
    int B = y - y1;
    int C = x2 - x1;
    int D = y2 - y1;

    int dot = A * C + B * D;
    int len_sq = C * C + D * D;
    double param = -1;
    if (len_sq != 0) //in case of 0 length line
      param = dot * 1.0 / len_sq;

    double xx, yy;

    if (param < 0) {
      xx = x1;
      yy = y1;
    }
    else if (param > 1) {
      xx = x2;
      yy = y2;
    }
    else {
      xx = x1 + param * C;
      yy = y1 + param * D;
    }

    double dx = x - xx;
    double dy = y - yy;
    return Math.sqrt(dx * dx + dy * dy);
  }

  private double areaOfPolygon(List<Point> poly)
  {
    double t=0;

    for (int i=0; i<poly.size(); i++)
    {
      Point p1=poly.get(i);
      Point p2=poly.get((i+1)%poly.size());
      t+=p1.x*p2.y-p2.x*p1.y;
    }

    return t/2;
  }

  private int sq(int a)
  {
    return a*a;
  }
  //endregion

  //region <INFO PANEL>

  private void init()
  {
    if (hasVis())
    {
      setDefaultDelay(1000);    //this needs to be first

      setContentRect(0, 0, SIZE, SIZE);
      setInfoMaxDimension(5, 25);

      addInfo("Seed", seed);
      addInfo("C", C);
      addInfo("G", G);
      addInfo("B", B);
      addInfoBreak();
      addInfo("Time", "-");
      addInfo("Turns", "-");
      addInfo("Spotted", "-");
      addInfo("Collected", "-");
      addInfo("Subdued", "-");
      addInfo("Score", "-");
      addInfoBreak();
      addInfo("Thief position", null);
      addInfo("Current", "-");
      addInfo("Attempted", "-");
      addInfo("Previous", "-");
      addInfoBreak();
      msgHandler.addToInfo();
      update();
    }
  }

  protected void updateState()
  {
    if (hasVis())
    {
      synchronized (updateLock) {
        addInfo("Time", getRunTime());
        addInfo("Turns", turn);
        addInfo("Spotted", unspotted?"no":"yes");
        addInfo("Collected", collected);
        addInfo("Subdued", subdued);
        addInfo("Score", shorten(score));
        addInfo("Current", (thief.x<0 || thief.x>=SIZE) || (thief.y<0 || thief.y>=SIZE) ? "ESCAPED" : thief.niceStr());
        if (attemptedThief!=null) addInfo("Attempted", attemptedThief.niceStr());
        if (oldThief!=null) addInfo("Previous", oldThief.niceStr());
        msgHandler.addToInfo();
      }
      updateDelay();
    }
  }

  //endregion

  class Point
  {
    int x;
    int y;

    public Point(int x2, int y2)
    {
      x=x2;
      y=y2;
    }

    public String niceStr() {
      return "("+x+","+y+")";
    }
  }

  class MessageHandler {
    public String[] lines;
    private int maxLines=0;

    public MessageHandler() {
      lines=new String[0];
      maxLines=0;
    }

    public void update(String[] command, int msgIndex) {
      if (command.length<msgIndex+1) lines=new String[0];
      else lines=command[msgIndex].trim().replace("\\n", "\n").split("\n");
      maxLines=Math.max(maxLines, lines.length);
    }

    public void addToInfo() {
      addInfo("Message", null);
      for (int i=0; i<maxLines; i++) {addInfo("$"+i, i<lines.length?lines[i]:"");}
    }
  }

  //region <DEFAULT STUFF>

  protected boolean isMaximize() {
    return false;
  }

  protected double run() throws Exception
  {
    init();

    if (parameters.isDefined("manual"))
    {
      setDefaultDelay(0);
      updateState();
      return 0;
    }
    else return runAuto();
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

  protected void timeout() {
    addInfo("Time", getRunTime());
    update();
  }

  public static void main(String[] args) {
      new MarathonController().run(args);
  }
  //endregion

}