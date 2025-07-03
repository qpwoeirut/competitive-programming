package com.topcoder.marathon;

import java.io.BufferedWriter;
import java.io.InputStream;

class ErrorReader extends Thread {
    private final InputStream errorStream;
    private final BufferedWriter errorWriter;
    private final StringBuilder sb = new StringBuilder();
    private final boolean printMessages;
    private static final int maxLength = 10_000_000;

    public ErrorReader(InputStream errorStream, boolean printMessages, BufferedWriter errorWriter) {
        this.errorStream = errorStream;
        this.printMessages = printMessages;
        this.errorWriter = errorWriter;
    }

    public void run() {
        StringBuilder buffer = new StringBuilder();
        try {
            byte[] ch = new byte[65536];
            int read;
            while ((read = errorStream.read(ch)) > 0) {
                String s = new String(ch, 0, read);
                buffer.append(s);
                if (errorStream.available() == 0) {
                    write(buffer.toString());
                    buffer.delete(0, buffer.length());
                }
            }
        } catch (Exception e) {
        }
        try {
            if (buffer.length() > 0) write(buffer.toString());
        } catch (Exception e) {
        }
    }

    private void write(String s) throws Exception {
        if (sb.length() < maxLength) sb.append(s);
        if (printMessages) {
            System.out.print(s);
            System.out.flush();
        }
        if (errorWriter != null) {
            errorWriter.write(s);
            errorWriter.flush();
        }
    }

    public String getOutput() {
        return sb.toString();
    }

    public void close() {
        try {
            if (errorStream != null) errorStream.close();
        } catch (Exception e) {
        }
        try {
            if (errorWriter != null) errorWriter.close();
        } catch (Exception e) {
        }
    }
}