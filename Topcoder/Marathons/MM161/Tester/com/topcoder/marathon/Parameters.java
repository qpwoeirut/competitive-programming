package com.topcoder.marathon;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 *  Updates: 
 *      2022/01/01 - Add "noReplay"/"nr" option. 
 *      2021/09/13 - Fix "ns" assignment to "noSummary".
 */
public class Parameters {
    public static final String controlBests = "bests";
    public static final String debug = "debug";
    public static final String delay = "delay";
    public static final String exec = "exec";
    public static final String infoScale = "infoScale";
    public static final String loadSolOutput = "loadSolOutput";
    public static final String noAntialiasing = "noAntialiasing";
    public static final String noOutput = "noOutput";
    public static final String noReplay = "noReplay";
    public static final String noSummary = "noSummary";
    public static final String noVis = "novis";
    public static final String paintInfo = "paintInfo";
    public static final String printRuntime = "printRuntime";
    public static final String saveAll = "saveAll";
    public static final String saveScores = "saveScores";
    public static final String saveSolError = "saveSolError";
    public static final String saveSolInput = "saveSolInput";
    public static final String saveSolOutput = "saveSolOutput";
    public static final String saveVis = "saveVis";
    public static final String screen = "screen";
    public static final String seed = "seed";
    public static final String size = "size";
    public static final String startPaused = "pause";
    public static final String windowPosition = "windowPos";
    public static final String threads = "threads";
    public static final String timeLimit = "timeLimit";

    public static final int maxListLen = 1_000_000;

    private static final Map<String, String> equivalentParams = new HashMap<String, String>();

    static {
        equivalentParams.put("bs", controlBests);
        equivalentParams.put("db", debug);
        equivalentParams.put("dl", delay);
        equivalentParams.put("ex", exec);
        equivalentParams.put("is", infoScale);
        equivalentParams.put("lo", loadSolOutput);
        equivalentParams.put("na", noAntialiasing);
        equivalentParams.put("no", noOutput);
        equivalentParams.put("nr", noReplay);
        equivalentParams.put("ns", noSummary);
        equivalentParams.put("nv", noVis);
        equivalentParams.put("pi", paintInfo);
        equivalentParams.put("pr", printRuntime);
        equivalentParams.put("ps", startPaused);
        equivalentParams.put("sa", saveAll);
        equivalentParams.put("sc", screen);
        equivalentParams.put("sd", seed);
        equivalentParams.put("se", saveSolError);
        equivalentParams.put("si", saveSolInput);
        equivalentParams.put("so", saveSolOutput);
        equivalentParams.put("ss", saveScores);
        equivalentParams.put("sv", saveVis);
        equivalentParams.put("sz", size);
        equivalentParams.put("th", threads);
        equivalentParams.put("tl", timeLimit);
        equivalentParams.put("wp", windowPosition);
    }

    private final Map<String, String> params = new HashMap<String, String>();

    public String toString() {
        return params.toString();
    }

    public void put(String key, String value) {
        if (equivalentParams.containsKey(key)) key = equivalentParams.get(key);
        params.put(normalize(key), value);
    }

    public boolean isList(String key) {
        String val = params.get(normalize(key));
        if (val == null) return false;
        int pos = val.indexOf("*");
        if (pos > 0 && pos < val.length() - 1) return true;
        return val.startsWith("{") && val.endsWith("}");
    }

    public List<Long> getLongList(String key) {
        String val = params.get(normalize(key));
        if (val == null) return null;
        try {
            List<Long> l = new ArrayList<Long>();
            int pos = val.indexOf("*");
            int mult = 1;
            if (pos > 0 && pos < val.length() - 1) mult = Integer.parseInt(val.substring(pos + 1));
            if (val.startsWith("{")) {
                int close = val.indexOf("}");
                if (close < 0) return null;
                String[] s = val.substring(1, close).trim().split(",");
                for (int i = 0; i < s.length; i++) {
                    l.add(Long.parseLong(s[i].trim()));
                }
            } else if (pos > 0) {
                long[] range = getLongRangeFromValue(val.substring(0, pos));
                long start = range[0];
                long end = range[1];
                if (end > maxListLen + start) end = maxListLen + start;
                for (long i = start; i <= end; i++) {
                    l.add(i);
                }
            } else {
                return null;
            }
            if (mult > 1) {
                List<Long> aux = new ArrayList<Long>(l);
                for (int i = 1; i < mult && l.size() < maxListLen; i++) {
                    l.addAll(aux);
                }
                if (l.size() > maxListLen) l.subList(maxListLen, l.size()).clear();
            }
            return l;
        } catch (Exception e) {
            error("ERROR getting parameter long value/range/list!", e, key, val);
        }
        return null;
    }

    public boolean isDefined(String key) {
        return params.containsKey(normalize(key));
    }

    public void remove(String key) {
        params.remove(normalize(key));
    }

    public long[] getLongRange(String key) {
        String value = params.get(normalize(key));
        try {
            return getLongRangeFromValue(value);
        } catch (Exception e) {
            error("ERROR getting parameter long value/range!", e, key, value);
        }
        return null;
    }

    private long[] getLongRangeFromValue(String value) throws Exception {
        long[] ret = new long[2];
        boolean plus = value.indexOf('+') > 0;
        String[] s = value.split(plus ? "\\+" : ",");
        ret[0] = Long.parseLong(s[0]);
        ret[1] = Long.parseLong(s[s.length - 1]);
        if (plus) ret[1] += ret[0] - 1;
        return ret;
    }

    public double[] getDoubleRange(String key) {
        String value = params.get(normalize(key));
        double[] ret = new double[2];
        try {
            boolean plus = value.indexOf('+') > 0;
            String[] s = value.split(plus ? "\\+" : ",");
            ret[0] = Double.parseDouble(s[0]);
            ret[1] = Double.parseDouble(s[s.length - 1]);
            if (plus) ret[1] += ret[0] - 1;
        } catch (Exception e) {
            error("ERROR getting parameter double value/range!", e, key, value);
        }
        return ret;
    }

    public int[] getIntRange(String key) {
        String value = params.get(normalize(key));
        int[] ret = new int[2];
        try {
            boolean plus = value.indexOf('+') > 0;
            String[] s = value.split(plus ? "\\+" : ",");
            ret[0] = Integer.parseInt(s[0]);
            ret[1] = Integer.parseInt(s[s.length - 1]);
            if (plus) ret[1] += ret[0] - 1;
        } catch (Exception e) {
            error("ERROR getting parameter int value/range!", e, key, value);
        }
        return ret;
    }

    public int getIntValue(String key) {
        String value = params.get(key.toLowerCase());
        int ret = 0;
        try {
            ret = Integer.parseInt(value);
        } catch (Exception e) {
            error("ERROR getting parameter integer value!", e, key, value);
        }
        return ret;
    }

    public long getLongValue(String key) {
        String value = params.get(key.toLowerCase());
        long ret = 0;
        try {
            ret = Long.parseLong(value);
        } catch (Exception e) {
            error("ERROR getting parameter long value!", e, key, value);
        }
        return ret;
    }

    public double getDoubleValue(String key) {
        String value = params.get(key.toLowerCase());
        double ret = 0;
        try {
            ret = Double.parseDouble(value);
        } catch (Exception e) {
            error("ERROR getting parameter double value!", e, key, value);
        }
        return ret;
    }

    public String getString(String key) {
        String value = params.get(key.toLowerCase());
        if (value == null) {
            error("ERROR getting parameter string value!", null, key, value);
        }
        return value;
    }

    public String getStringNull(String key) {
        return params.get(key.toLowerCase());
    }

    private void error(String msg, Exception e, String key, String value) {
        System.err.println(msg + "\n    key = " + key + "\n    value = " + value);
        if (e != null) e.printStackTrace();
        System.exit(-1);
    }

    private static String normalize(String key) {
        return key.toLowerCase();
    }
}