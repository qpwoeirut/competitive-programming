package com.topcoder.marathon;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.nio.file.Files;
import java.nio.file.StandardCopyOption;
import java.text.DecimalFormat;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

/**
 * Main entry point of the Marathon tester. It handles parameter and calls the solution.
 *   
 * Updates: 
 *      2021/02/04 - Allow easy repetition of a single seed, a range or a list,
 *                   using suffix "*N", like -sd 1*5 or -sd 1,50*5 or -sd {1,9,72,99}*5.
 *      2020/12/28 - Handle a list of seeds, like -sd {1,9,72,909}.
 */
public class MarathonController {
    private final Object statsLock = new Object();
    private long maxRunTime, avgRunTime;
    private int numFails, numCases, numImproved, numTied, numNew;
    private double prevTotScore, currTotScore;
    private static final double eps = 1e-9;

    private Parameters parseArgs(String[] args) {
        Parameters parameters = new Parameters();
        String last = null;
        for (String s : args) {
            if (!s.startsWith("-")) {
                if (last == null) {
                    System.out.println("ERROR: Invalid command line parameters!");
                    System.out.println("It should contain one or more a sequence of ");
                    System.out.println("    -key value     (a single value)");
                    System.out.println("    -key start,end (a range, from start to end, inclusive)");
                    System.out.println("    -flag          (enable a flag)");
                    System.exit(-1);
                }
                parameters.put(last, s);
                last = null;
            } else {
                if (last != null) parameters.put(last, null);
                last = s.substring(1);
                if (last.isEmpty()) last = null;
            }
        }
        if (last != null) parameters.put(last, null);
        return parameters;
    }

    private synchronized Double checkBest(File bestsFile, boolean isMaximize, double errorScore, long seed, double score) {
        if (bestsFile == null) return null;
        Double best = null;
        try {
            Map<Long, Double> bests = new TreeMap<Long, Double>();
            if (bestsFile.exists()) {
                BufferedReader in = new BufferedReader(new FileReader(bestsFile));
                String line = null;
                while ((line = in.readLine()) != null) {
                    String[] s = line.split("=");
                    bests.put(Long.parseLong(s[0]), Double.parseDouble(s[1]));
                }
                in.close();
            }
            best = bests.get(seed);
            if (score != errorScore) {
                if (best == null || (isMaximize && score > best) || (!isMaximize && score < best)) {
                    bests.put(seed, score);
                    File tmpFile = new File(bestsFile.getPath() + ".tmp");
                    BufferedWriter out = new BufferedWriter(new FileWriter(tmpFile));
                    StringBuilder sb = new StringBuilder();
                    for (long a : bests.keySet()) {
                        sb.delete(0, sb.length());
                        sb.append(a).append('=').append(bests.get(a));
                        out.write(sb.toString());
                        out.newLine();
                    }
                    out.close();
                    Files.move(tmpFile.toPath(), bestsFile.toPath(), StandardCopyOption.REPLACE_EXISTING, StandardCopyOption.ATOMIC_MOVE);
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return best;
    }

    private void saveScores(File scoresFile, Map<Long, Double> currentScores) {
        try {
            BufferedWriter out = new BufferedWriter(new FileWriter(scoresFile));
            StringBuilder sb = new StringBuilder();
            for (long a : currentScores.keySet()) {
                sb.delete(0, sb.length());
                sb.append(a).append('=').append(currentScores.get(a));
                out.write(sb.toString());
                out.newLine();
            }
            out.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    //Called by server tester using a direct call
    public MarathonTestResult run(String className, long seed, String exec, int timeLimit) {
        MarathonTestResult result = new MarathonTestResult();
        MarathonTester tester = null;
        Constructor<?> constructor = null;
        try {
            Class<?> c = Class.forName(className);
            constructor = c.getConstructors()[0];
            tester = (MarathonTester) constructor.newInstance();
        } catch (Exception e) {
            result.setError("ERROR finding class " + className + ": " + e.getMessage());
            return result;
        }
        try {
            Parameters parameters = new Parameters();
            if (exec != null) parameters.put(Parameters.exec, exec);
            parameters.put(Parameters.noVis, null);
            parameters.put(Parameters.noOutput, null);

            result.setScore(tester.getErrorScore());
            result.setMaximize(tester.isMaximize());
            tester.setParameters(parameters);
            tester.setSeed(seed);
            tester.setTimeLimit(timeLimit);

            double score = tester.runTest();

            result.setScore(score);
            result.setRunTime(tester.getRunTime());
            result.setOutput(tester.getSolutionError());
            result.setError(tester.getExecutionsErrors());
        } catch (Exception e) {
            result.setError("ERROR calling tester " + className + ": " + e.getMessage());
        }
        return result;
    }

    //Called by local tester, passing command line parameters
    public final void run(String[] args) {
        //Find the name of the concrete class (actual MarathonTester) to be called using reflection
        String className = new Exception().getStackTrace()[1].getClassName();

        //Parse command line parameters
        Parameters parameters = parseArgs(args);

        //Seeds queue
        LinkedList<Long> seeds = new LinkedList<Long>();

        //Get seeds range (default is seed=1)
        String seedsProcessed = "";
        if (parameters.isDefined(Parameters.seed)) {
            if (parameters.isList(Parameters.seed)) {
                List<Long> l = parameters.getLongList(Parameters.seed);
                seeds.addAll(l);
                StringBuilder sb = new StringBuilder();
                sb.append("{");
                for (int i = 0; i < l.size(); i++) {
                    if (i > 0) sb.append(",");
                    sb.append(l.get(i));
                    if (i == 10 && l.size() > 15) {
                        i = l.size() - 2;
                        sb.append(",...");
                    }
                }
                sb.append("}");
                seedsProcessed = sb.toString();
            } else {
                long[] seedRange = parameters.getLongRange(Parameters.seed);
                long startSeed = seedRange[0];
                long endSeed = Math.min(seedRange[1], Parameters.maxListLen + startSeed);
                seedsProcessed = startSeed + " to " + endSeed;
                for (long seed = startSeed; seed <= endSeed; seed++) {
                    seeds.add(seed);
                }
            }
            parameters.remove(Parameters.seed);
        } else {
            seeds.add(1L);
            seedsProcessed = "1";
        }

        //Multiple seeds?
        boolean multipleSeeds = seeds.size() > 1;

        //Check and expand saveAll parameter
        if (parameters.isDefined(Parameters.saveAll)) {
            if (parameters.isDefined(Parameters.saveSolInput)) {
                System.out.println("ERROR: Parameters " + Parameters.saveAll + " and " + Parameters.saveSolInput + " can't be used together.");
                return;
            }
            if (parameters.isDefined(Parameters.saveSolOutput)) {
                System.out.println("ERROR: Parameters " + Parameters.saveAll + " and " + Parameters.saveSolOutput + " can't be used together.");
                return;
            }
            if (parameters.isDefined(Parameters.saveSolError)) {
                System.out.println("ERROR: Parameters " + Parameters.saveAll + " and " + Parameters.saveSolError + " can't be used together.");
                return;
            }
            String folder = parameters.getStringNull(Parameters.saveAll);
            parameters.remove(Parameters.saveAll);
            parameters.put(Parameters.saveSolInput, folder);
            parameters.put(Parameters.saveSolOutput, folder);
            parameters.put(Parameters.saveSolError, folder);
        }

        //Check invalid combinations with loadSolOutput parameter
        if (parameters.isDefined(Parameters.loadSolOutput)) {
            if (parameters.isDefined(Parameters.exec)) {
                System.out.println("ERROR: Parameters " + Parameters.loadSolOutput + " and " + Parameters.exec + " can't be used together.");
                return;
            }
            if (parameters.isDefined(Parameters.saveSolOutput)) {
                System.out.println("ERROR: Parameters " + Parameters.loadSolOutput + " and " + Parameters.saveSolOutput + " can't be used together.");
                return;
            }
            if (parameters.isDefined(Parameters.saveSolError)) {
                System.out.println("ERROR: Parameters " + Parameters.loadSolOutput + " and " + Parameters.saveSolError + " can't be used together.");
                return;
            }
        }

        //Number of threads for simultaneous test execution (default is a single thread) 
        int numThreads = 1;
        if (parameters.isDefined(Parameters.threads)) {
            numThreads = parameters.getIntValue(Parameters.threads);
            numThreads = Math.max(numThreads, 1);
            numThreads = Math.min(numThreads, Runtime.getRuntime().availableProcessors());
            int numSeeds = seeds.size();
            if (numSeeds < numThreads) numThreads = numSeeds;
            parameters.remove(Parameters.threads);
        }

        //Check if controlling bests is defined (default is turned off)
        File bf = null;
        if (parameters.isDefined(Parameters.controlBests)) {
            bf = new File(parameters.getString(Parameters.controlBests));
            if (bf.getParentFile() != null && !bf.getParentFile().exists()) {
                bf.getParentFile().mkdirs();
            }
        }
        File bestsFile = bf;

        //Save current scores to a file if enabled
        Map<Long, Double> currentScores = new TreeMap<Long, Double>();
        File scoresFile = null;
        if (parameters.isDefined(Parameters.saveScores)) {
            scoresFile = new File(parameters.getString(Parameters.saveScores));
        }

        //Instantiate the concrete class (actual MarathonTester) 
        Class<?> c = null;
        Constructor<?> ct = null;
        double es = -1;
        boolean im = true;
        try {
            c = Class.forName(className);
            ct = c.getConstructors()[0];
            //Create an instance to check it is accessible and get its configuration 
            MarathonTester tester = (MarathonTester) ct.newInstance();
            es = tester.getErrorScore();
            im = tester.isMaximize();
        } catch (Exception e) {
            System.out.println("ERROR finding class " + className);
            e.printStackTrace();
            System.exit(-1);
        }
        Constructor<?> constructor = ct;
        double errorScore = es;
        boolean isMaximize = im;

        //Check if showing runtime is enabled  (default is turned off)
        boolean printRuntime = parameters.isDefined(Parameters.printRuntime);

        //Get time limit, in milliseconds (default is no time limit control, timeLimit = 0)
        long tl = 0;
        if (parameters.isDefined(Parameters.timeLimit)) tl = parameters.getLongValue(Parameters.timeLimit);
        long timeLimit = tl;

        //Run tests
        Thread[] threads = new Thread[numThreads];
        for (int i = 0; i < numThreads; i++) {
            (threads[i] = new Thread() {
                public void run() {
                    StringBuilder sb = new StringBuilder();
                    while (true) {
                        long seed = 0;
                        synchronized (seeds) {
                            if (seeds.isEmpty()) break;
                            seed = seeds.removeFirst();
                        }
                        try {
                            MarathonTester tester = (MarathonTester) constructor.newInstance();
                            tester.setParameters(parameters);
                            tester.setSeed(seed);
                            if (timeLimit != 0) tester.setTimeLimit(timeLimit);

                            double score = tester.runTest();
                            long runTime = tester.getRunTime();

                            sb.delete(0, sb.length());
                            if (multipleSeeds) sb.append("Seed = ").append(seed).append(", ");
                            sb.append("Score = ").append(score);
                            Double best = checkBest(bestsFile, isMaximize, errorScore, seed, score);
                            if (best != null) sb.append(", PreviousBest = ").append(best);
                            if (printRuntime) sb.append(", RunTime = ").append(runTime).append(" ms");
                            System.out.println(sb.toString());
                            System.out.flush();

                            synchronized (statsLock) {
                                numCases++;
                                if (score == tester.getErrorScore()) numFails++;
                                avgRunTime += runTime;
                                maxRunTime = Math.max(maxRunTime, runTime);
                                currentScores.put(seed, score);
                                if (bestsFile != null) {
                                    if (best == null) {
                                        numNew++;
                                        if (score != tester.getErrorScore()) {
                                            currTotScore++;
                                        }
                                    } else if (score != tester.getErrorScore()) {
                                        double newBest = best;
                                        if ((isMaximize && score > best + eps) || (!isMaximize && score < best - eps)) {
                                            numImproved++;
                                            newBest = score;
                                        } else if (Math.abs(score - best) < eps) numTied++;
                                        currTotScore += isMaximize ? (newBest <= 0 ? 0 : score / newBest) : (score <= 0 ? 0 : newBest / score);
                                        prevTotScore += isMaximize ? (newBest <= 0 ? 0 : best / newBest) : (best <= 0 ? 0 : newBest / best);
                                    }
                                }
                            }
                        } catch (Exception e) {
                            System.out.println("ERROR calling tester " + className);
                            e.printStackTrace();
                            System.exit(-1);
                        }
                    }
                }
            }).start();
        }
        for (int i = 0; i < numThreads; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
            }
        }
        if (scoresFile != null) {
            saveScores(scoresFile, currentScores);
        }
        if (multipleSeeds && !parameters.isDefined(Parameters.noSummary)) {
            avgRunTime /= numCases;
            System.out.println();
            System.out.println("            Seeds: " + seedsProcessed);
            System.out.println("   Executed Cases: " + numCases);
            System.out.println("     Failed Cases: " + numFails);
            System.out.println("    Avg. Run Time: " + avgRunTime + " ms");
            System.out.println("    Max. Run Time: " + maxRunTime + " ms");
            if (bestsFile != null) {
                DecimalFormat df = new DecimalFormat("0.00000");
                System.out.println();
                if (numImproved > 0) System.out.println("   Improved Bests: " + numImproved);
                if (numTied > 0) System.out.println("       Tied Cases: " + numTied);
                if (numNew > 0) System.out.println("        New Cases: " + numNew);
                if (numCases - numNew > 0) {
                    prevTotScore /= numCases - numNew;
                    System.out.println("Prev. Bests Score: " + df.format(prevTotScore * 100));
                }
                currTotScore /= numCases;
                System.out.println("    Current Score: " + df.format(currTotScore * 100));
            }
        }
    }
}