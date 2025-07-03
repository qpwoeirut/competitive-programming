package com.topcoder.marathon;

public class MarathonTestResult {
    private String error;
    private boolean isMaximize;
    private String output;
    private long runTime;
    private double score;

    public MarathonTestResult() {
        score = -1;
        output = "";
        error = "";
        runTime = 0;
        isMaximize = true;
    }

    public String getError() {
        return error;
    }

    public String getOutput() {
        return output;
    }

    public long getRunTime() {
        return runTime;
    }

    public double getScore() {
        return score;
    }

    public boolean isMaximize() {
        return isMaximize;
    }

    public void setError(String error) {
        this.error = error;
    }

    public void setMaximize(boolean isMaximize) {
        this.isMaximize = isMaximize;
    }

    public void setOutput(String output) {
        this.output = output;
    }

    public void setRunTime(long runTime) {
        this.runTime = runTime;
    }

    public void setScore(double score) {
        this.score = score;
    }
}
