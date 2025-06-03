package com.topcoder.marathon;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.io.StringWriter;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.TimeUnit;

/**
 * Base class for Topcoder Marathon testers. Should be extended directly for
 * problems with no visualization. 
 * 
 * Updates: 
 *      2022/01/14 - Fix: timeout control was adding a noticeable overhead to 
 *                   startTime() and stopTime() methods.             
 */
public abstract class MarathonTester {
    protected Parameters parameters;
    protected boolean debug;
    protected long seed;
    protected SecureRandom rnd;
    protected boolean ending;

    private long elapsedTime, timeLimit, lastStart;
    private final Object timeLock = new Object();
    private final List<BufferedWriter> solInputWriters = new ArrayList<BufferedWriter>();
    private BufferedWriter solOutputWriter;
    private BufferedWriter solErrorWriter;
    private BufferedReader solOutputReader;
    private ErrorReader solErrorReader;
    private Process process;
    private String solutionError = "";
    private String errorMessage = "";
    private String lastLine = "";
    private StringBuilder executionErrors = new StringBuilder();
    private boolean timeout;
    private boolean readFailed;
    private Thread lastTimeoutThread;

    public void setParameters(Parameters parameters) {
        this.parameters = parameters;
        debug = parameters.isDefined(Parameters.debug);
    }

    public void setTimeLimit(long timeLimitInMillis) {
        this.timeLimit = timeLimitInMillis * 1_000_000;
    }

    public void setSeed(long seed) {
        this.seed = seed;
        try {
            rnd = SecureRandom.getInstance("SHA1PRNG");
            rnd.setSeed(seed);
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
            System.exit(-1);
        }
    }

    /**
     * Concrete MarathonTester implementations may override this value.
     */
    public int getErrorScore() {
        return -1;
    }

    /**
     * Concrete implementations may override this method to be notified about
     * timeout. It usually makes sense when it is necessary to update the
     * visualizer after a timeout, as the normal actions (like returning the
     * error score, interrupting the solution) is automatically handled.
     */
    protected void timeout() {
    }

    protected abstract void generate();

    protected abstract boolean isMaximize();

    protected abstract double run() throws Exception;

    public final long getRunTime() {
        return elapsedTime / 1_000_000;
    }

    public final boolean isTimeout() {
        return timeout;
    }

    protected final void startTime() {
        synchronized (timeLock) {
            if (lastStart != 0) {
                System.out.println("ERROR startTime() was called again, before endTime() closed the first one.");
                System.exit(-1);
            }
            if (timeLimit > 0) {
                lastTimeoutThread = new Thread() {
                    public void run() {
                        try {
                            boolean finished = process.waitFor(timeLimit - elapsedTime, TimeUnit.NANOSECONDS);
                            if (!finished) {
                                synchronized (timeLock) {
                                    if (lastStart > 0) elapsedTime += System.nanoTime() - lastStart;
                                    lastStart = 0;
                                    if (process != null) process.destroy();
                                    if (!timeout) {
                                        timeout = true;
                                        timeout();
                                    }
                                }
                            }
                        } catch (Exception e) {
                        }
                    }
                };
                lastTimeoutThread.start();
            }
            lastStart = System.nanoTime();
        }
    }

    protected final void stopTime() {
        synchronized (timeLock) {
            if (lastStart > 0) elapsedTime += System.nanoTime() - lastStart;
            lastStart = 0;
            try {
                if (lastTimeoutThread != null && lastTimeoutThread.isAlive()) {
                    lastTimeoutThread.interrupt();
                    lastTimeoutThread = null;
                }
            } catch (Exception e) {
            }
        }
    }

    public final double runTest() {
        double score = getErrorScore();
        try {
            generate();
            start();
            score = getErrorScore();
            score = run();
            if (timeLimit > 0 && getRunTime() > timeLimit) {
                synchronized (timeLock) {
                    if (!timeout) {
                        timeout = true;
                        timeout();
                    }
                }
            }
            end();
        } catch (Exception e) {
            stopTime();
            if (!timeout && !ending) {
                String msg = "";
                if (readFailed) {
                    msg = "ERROR! " + e.getMessage();
                } else {
                    StringWriter errors = new StringWriter();
                    e.printStackTrace(new PrintWriter(errors));
                    msg = "UNEXPECTED ERROR!\n" + errors;
                }
                System.out.println(msg);
                executionErrors.append(msg).append("\n");
            }
        }
        if (timeout) {
            String msg = "TIMEOUT! Time limit of " + timeLimit / 1_000_000 + " ms exceeded.";
            System.out.println(msg);
            executionErrors.append(msg).append("\n");
            score = getErrorScore();
        }
        return score;
    }

    protected final void writeLine(int v) throws Exception {
        writeLine(String.valueOf(v));
    }

    protected final void writeLine(String str) throws Exception {
        for (BufferedWriter out : solInputWriters) {
            out.write(str);
            out.newLine();
        }
    }

    protected final void flush() throws Exception {
        for (BufferedWriter out : solInputWriters) {
            out.flush();
        }
    }

    protected final int readLineToInt() throws Exception {
        return Integer.parseInt(readLine());
    }

    protected final int readLineToInt(int invalid) throws Exception {
        try {
            String line = readLine();
            return Integer.parseInt(line);
        } catch (NumberFormatException e) {
            return invalid;
        }
    }

    protected final int[] readLineToIntArr() throws Exception {
        String line = readLine();
        String[] s = line.split(" ");
        int[] arr = new int[s.length];
        for (int i = 0; i < arr.length; i++) {
            arr[i] = Integer.parseInt(s[i]);
        }
        return arr;
    }

    protected final String getLastLineRead() {
        return lastLine;
    }

    protected final String readLine() throws Exception {
        lastLine = solOutputReader.readLine();
        if (lastLine == null) {
            readFailed = true;
            if (parameters.isDefined(Parameters.loadSolOutput)) {
                throw new RuntimeException("Solution file unexpected end.");
            }
            if (process == null || !process.isAlive()) {
                throw new RuntimeException("Solution process terminated before outputting the expected data.");
            }
            throw new RuntimeException("Failed to read output from solution.");
        }
        if (solOutputWriter != null) {
            solOutputWriter.write(lastLine);
            solOutputWriter.newLine();
        }
        return lastLine;
    }

    protected final boolean isReadActive() {
        return solOutputReader != null;
    }

    protected final void setErrorMessage(String msg) {
        errorMessage = msg;
    }

    protected final double fatalError() {
        System.out.println(errorMessage);
        executionErrors.append(errorMessage).append("\n");
        return getErrorScore();
    }

    protected final double fatalError(String msg) {
        System.out.println(msg);
        executionErrors.append(msg).append("\n");
        return getErrorScore();
    }

    private final void start() throws Exception {
        if (parameters.isDefined(Parameters.saveSolInput)) {
            String s = parameters.getStringNull(Parameters.saveSolInput);
            File folder = new File(s == null ? "." : s);
            if (!folder.exists()) folder.mkdirs();
            BufferedWriter out = new BufferedWriter(new FileWriter(new File(folder, seed + ".in")));
            solInputWriters.add(out);
        }
        if (parameters.isDefined(Parameters.saveSolOutput)) {
            String s = parameters.getStringNull(Parameters.saveSolOutput);
            File folder = new File(s == null ? "." : s);
            if (!folder.exists()) folder.mkdirs();
            solOutputWriter = new BufferedWriter(new FileWriter(new File(folder, seed + ".out")));
        }
        if (parameters.isDefined(Parameters.saveSolError)) {
            String s = parameters.getStringNull(Parameters.saveSolError);
            File folder = new File(s == null ? "." : s);
            if (!folder.exists()) folder.mkdirs();
            solErrorWriter = new BufferedWriter(new FileWriter(new File(folder, seed + ".err")));
        }
        if (parameters.isDefined(Parameters.exec)) {
            String cmd = parameters.getString(Parameters.exec);
            if (cmd != null) {
                try {
                    boolean printMessages = true;
                    if (parameters.isDefined(Parameters.noOutput)) printMessages = false;
                    process = Runtime.getRuntime().exec(cmd);
                    solErrorReader = new ErrorReader(process.getErrorStream(), printMessages, solErrorWriter);
                    solErrorReader.start();
                    solOutputReader = new BufferedReader(new InputStreamReader(process.getInputStream()));
                    BufferedWriter out = new BufferedWriter(new OutputStreamWriter(process.getOutputStream()));
                    solInputWriters.add(out);
                } catch (Exception e) {
                    e.printStackTrace();
                    System.exit(-1);
                }
            }
        } else if (parameters.isDefined(Parameters.loadSolOutput)) {
            String s = parameters.getStringNull(Parameters.loadSolOutput);
            File folder = new File(s == null ? "." : s);
            if (!folder.exists()) {
                System.out.println("ERROR can't find folder " + folder);
                System.exit(-1);
            }
            File loadFile = new File(folder, seed + ".out");
            if (!loadFile.exists()) {
                System.out.println("ERROR can't find file " + loadFile.getPath());
                System.exit(-1);
            }
            solOutputReader = new BufferedReader(new FileReader(loadFile));
        }
    }

    protected void end() {
        if (ending) return;
        ending = true;
        for (BufferedWriter out : solInputWriters) {
            try {
                out.close();
            } catch (Exception e) {
            }
        }
        if (solOutputReader != null) {
            try {
                solOutputReader.close();
            } catch (Exception e) {
            }
        }
        if (solOutputWriter != null) {
            try {
                solOutputWriter.close();
            } catch (Exception e) {
            }
        }
        if (solErrorWriter != null) {
            try {
                solErrorWriter.close();
            } catch (Exception e) {
            }
        }
        if (solErrorReader != null) {
            solErrorReader.close();
            solutionError = solErrorReader.getOutput();
        }
        if (process != null) {
            try {
                process.destroy();
            } catch (Exception e) {
            }
        }
    }

    public final String getSolutionError() {
        return solutionError;
    }

    public final String getExecutionsErrors() {
        return executionErrors.toString();
    }

    protected final int randomInt(int origin, int boundInclusive) {
        if (boundInclusive <= origin) return origin;
        return rnd.nextInt(boundInclusive - origin + 1) + origin;
    }

    protected final int randomInt(int[] range, int minRange, int maxRange) {
        int origin = range[0];
        int boundInclusive = range[1];
        if (origin < minRange) origin = minRange;
        if (origin > maxRange) origin = maxRange;
        if (boundInclusive > maxRange) boundInclusive = maxRange;
        if (boundInclusive < minRange) boundInclusive = minRange;
        return randomInt(origin, boundInclusive);
    }

    protected final int randomInt(int[] range) {
        return randomInt(range[0], range[1]);
    }

    protected final double randomDouble(double[] range) {
        return randomDouble(range[0], range[1]);
    }

    protected final double randomDouble(double origin, double bound) {
        if (bound <= origin) return origin;
        double r = (rnd.nextLong() >>> 11) * 0x1.0p-53;
        if (origin < bound) {
            r = r * (bound - origin) + origin;
            if (r >= bound) r = Double.longBitsToDouble(Double.doubleToLongBits(bound) - 1);
        }
        return r;
    }

    protected final double randomDouble(double[] range, double minRange, double maxRange) {
        double origin = range[0];
        double bound = range[1];
        if (origin < minRange) origin = minRange;
        if (origin > maxRange) origin = maxRange;
        if (bound > maxRange) bound = maxRange;
        if (bound < minRange) bound = minRange;
        return randomDouble(origin, bound);
    }
}