package com.topcoder.marathon;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Font;
import java.awt.FontMetrics;
import java.awt.Graphics2D;
import java.awt.Stroke;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionListener;
import java.awt.geom.Ellipse2D;
import java.awt.geom.GeneralPath;
import java.awt.geom.Line2D;
import java.awt.geom.Rectangle2D;
import java.awt.geom.RoundRectangle2D;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.atomic.AtomicInteger;

import javax.swing.JComponent;
import javax.swing.SwingUtilities;

/**
 * Base class for Topcoder Marathon testers with animation, i.e.
 * intermediate states are displayed in the visualizer.
 * 
 * Updates: 
 *      2022/01/01 - Add the "replay" mode and review pause control.
 *      2021/02/03 - Keep the delay setting after end(), to allow pauses after the solution is over, 
 *                   in a manual mode or some kind of animation of the final state.
 */
public abstract class MarathonAnimatedVis extends MarathonVis {
    private int delay = -1;
    private final Object animLock = new Object();
    private boolean animInit, paused, ended, keyPressed, replayEnabled;
    private int solFrame = -1, paintFrame;

    private final Map<Object, Integer> replayDict = new HashMap<Object, Integer>();
    private final Map<Integer, Object> replayRev = new HashMap<Integer, Object>();
    private final Map<Integer, int[]> replaySequences = new HashMap<Integer, int[]>();
    private final Map<Integer, Map<Object, Object>> replayInfo = new HashMap<Integer, Map<Object, Object>>();
    private final AtomicInteger replayUid = new AtomicInteger();

    private final Color btBack = new Color(248, 248, 252);
    private final Color btFront = new Color(64, 64, 70);

    private final Stroke stroke1 = new BasicStroke(0.25f);
    private final Stroke stroke2 = new BasicStroke(1.0f);
    private final Color sliderFill1 = new Color(100, 100, 250);
    private final Color sliderFill2 = new Color(100, 200, 100);
    private final Color sliderBack1 = new Color(230, 230, 255);
    private final Color sliderBack2 = new Color(230, 245, 230);
    private final Rectangle2D[] rcControls = new Rectangle2D[8];
    private Rectangle2D rcMouse = null;
    private int[] delays = new int[] {1,2,4,7,10,15,20,25,30,40,50,60,80,100,120,150,200,250,300,400,500,600,800,1000,1500,2000};

    public void setParameters(Parameters parameters) {
        super.setParameters(parameters);
        if (parameters.isDefined(Parameters.delay)) delay = parameters.getIntValue(Parameters.delay);
        if (parameters.isDefined(Parameters.startPaused)) paused = true;
        if (!parameters.isDefined(Parameters.noReplay)) setReplayEnabled(true);
    }

    protected final void setReplayEnabled(boolean enabled) {
        replayEnabled = enabled;
    }

    protected void setInfoMaxDimension(int infoColumns, int infoLines) {
        super.setInfoMaxDimension(replayEnabled ? Math.max(20, infoColumns) : infoColumns, infoLines + (replayEnabled ? 5 : 0));
    }

    protected int paintInfo(Graphics2D g, int w, boolean isSave) {
        int y = 0;
        if (isSave || solFrame < 0 || !replayEnabled || !hasDelay()) y = super.paintInfo(g, w, isSave);
        else {
            boolean record = false;
            boolean replay = false;
            synchronized (animLock) {
                replay = paintFrame < solFrame;
                record = !replayInfo.containsKey(solFrame);
            }
            if (record) {
                synchronized (animLock) {
                    replayInfo.put(solFrame, getInfoMapCopy());
                }
                y = super.paintInfo(g, w, isSave);
            } else if (replay) {
                Map<Object, Object> map = replayInfo.get(paintFrame);
                if (map != null) y = super.paintInfo(g, w, map);
            } else {
                y = super.paintInfo(g, w, isSave);
            }
        }
        if (!isSave && y > 0) y = paintAnimControls(g, w, y);
        return y;
    }

    private int paintAnimControls(Graphics2D g, int w, int y) {
        if (!hasDelay() || !replayEnabled) return y;

        int x = w - infoFontWidth * infoColumns - border;
        int width = infoFontWidth * infoColumns;
        int lineHeight = (int) (lineSpacing * infoFontHeight);
        y += lineHeight;
        Rectangle2D rcTot = rcControls[7] = new Rectangle2D.Double(x, y, width, lineHeight);
        double r = lineHeight / 3.0;
        RoundRectangle2D rc1 = new RoundRectangle2D.Double(x, y + r, width, lineHeight - 2 * r, r, r);
        double wp = 0;
        if (solFrame > 0) {
            g.setColor(ended ? sliderBack2 : sliderBack1);
            g.fill(rc1);
            wp = width * paintFrame / (double) solFrame;
            RoundRectangle2D rc2 = new RoundRectangle2D.Double(x, y + r, wp, lineHeight - 2 * r, r, r);
            g.setColor(ended ? sliderFill2 : sliderFill1);
            g.fill(rc2);
        }
        Boolean isSel = rcTot.equals(rcMouse);
        if (solFrame > 0) {
            g.setColor(Color.GRAY);
            int step1 = solFrame <= 100 ? 10 : solFrame <= 1000 ? 100 : 250;
            int step2 = solFrame <= 100 ? 2 : solFrame <= 1000 ? 20 : 50;
            for (int i = 0; i < solFrame; i += step2) {
                double xt = x + width * i / (double) solFrame;
                g.draw(new Line2D.Double(xt, y + lineHeight - r * (i % step1 == 0 ? 0.1 : 0.5), xt, y + lineHeight - r * 0.7));
            }
        }
        g.setColor(isSel ? Color.BLACK : btFront);
        g.setStroke(isSel ? stroke2 : stroke1);
        g.draw(rc1);
        if (solFrame > 0) {
            r = lineHeight / 3.0;
            Ellipse2D e = new Ellipse2D.Double(x + wp - r, y + lineHeight * 0.5 - r, 2 * r, 2 * r);
            g.setColor(ended ? sliderFill2 : sliderFill1);
            g.fill(e);
            g.setColor(isSel ? Color.BLACK : btFront);
            g.draw(e);
        }
        g.setStroke(stroke1);
        y += lineHeight + lineHeight / 5;

        double xb = x;
        double wb = (width - 8) / 5.0;
        for (int i = 0; i <= 4; i++) {
            Rectangle2D rb = rcControls[i] = new Rectangle2D.Double(xb, y, wb, lineHeight);
            int icon = i;
            if (paused && i == 2) icon = 7;
            paintButton(g, rb, rb.equals(rcMouse), icon);
            xb += wb + 2;
        }
        xb = x;
        y += lineHeight + lineHeight / 5;
        Font f = g.getFont();
        g.setFont(f.deriveFont(f.getSize2D() * 0.8f));
        FontMetrics metrics = g.getFontMetrics();
        String s = "Delay: " + delay + " ms";
        Rectangle2D rect = metrics.getStringBounds(s, g);
        int xs = (int) (x + (width - rect.getWidth()) / 2);
        int ys = y + (lineHeight + metrics.getAscent()) / 2;
        g.setColor(Color.BLACK);
        g.drawString(s, xs, ys);
        int yl = lineHeight / 2 + 2 + y;
        g.setColor(Color.GRAY);
        g.drawLine((int) (xb + wb), yl, xs - 2, yl);
        g.drawLine((int) (xb + width - wb), yl, xs + (int) rect.getWidth() + 2, yl);
        for (int i = 5; i <= 6; i++) {
            Rectangle2D rb = rcControls[i] = new Rectangle2D.Double(xb, y, wb, lineHeight);
            paintButton(g, rb, rb.equals(rcMouse), i);
            xb += 4 * (wb + 2);
        }
        g.setFont(f);
        return y;
    }

    private void paintButton(Graphics2D g, Rectangle2D rb, boolean isSel, int iconIdx) {
        g.setColor(isSel ? Color.WHITE : btBack);
        g.fill(rb);

        double s = Math.min(rb.getWidth() * 0.75, rb.getHeight()) * 0.3;
        double x = Math.round(rb.getCenterX());
        double y = Math.round(rb.getCenterY());
        GeneralPath gp = new GeneralPath(GeneralPath.WIND_NON_ZERO);
        switch (iconIdx) {
        case 0:
            gp.moveTo(x + s * 1.5, y - s);
            gp.lineTo(x + s * 1.5, y + s);
            gp.lineTo(x + s * 0.1, y);
            gp.closePath();
            gp.moveTo(x + s * 0.4, y - s);
            gp.lineTo(x + s * 0.4, y + s);
            gp.lineTo(x - s * 1.0, y);
            gp.closePath();
            gp.moveTo(x - s * 1.4, y - s);
            gp.lineTo(x - s * 1.4, y + s);
            gp.lineTo(x - s * 1.0, y + s);
            gp.lineTo(x - s * 1.0, y - s);
            gp.closePath();
            break;

        case 1:
            gp.moveTo(x + s * 0.9, y - s);
            gp.lineTo(x + s * 0.9, y + s);
            gp.lineTo(x - s * 0.5, y);
            gp.closePath();
            gp.moveTo(x - s * 0.9, y - s);
            gp.lineTo(x - s * 0.9, y + s);
            gp.lineTo(x - s * 0.5, y + s);
            gp.lineTo(x - s * 0.5, y - s);
            gp.closePath();
            break;

        case 7:
            gp.moveTo(x - s * 0.9, y - s * 1.1);
            gp.lineTo(x - s * 0.9, y + s * 1.1);
            gp.lineTo(x + s * 0.9, y);
            gp.closePath();
            break;

        case 2:
            gp.moveTo(x - s * 0.8, y - s * 1.1);
            gp.lineTo(x - s * 0.8, y + s * 1.1);
            gp.lineTo(x - s * 0.25, y + s * 1.1);
            gp.lineTo(x - s * 0.25, y - s * 1.1);
            gp.moveTo(x + s * 0.8, y - s * 1.1);
            gp.lineTo(x + s * 0.8, y + s * 1.1);
            gp.lineTo(x + s * 0.25, y + s * 1.1);
            gp.lineTo(x + s * 0.25, y - s * 1.1);
            gp.closePath();
            break;

        case 3:
            gp.moveTo(x - s * 0.9, y - s);
            gp.lineTo(x - s * 0.9, y + s);
            gp.lineTo(x + s * 0.5, y);
            gp.closePath();
            gp.moveTo(x + s * 0.9, y - s);
            gp.lineTo(x + s * 0.9, y + s);
            gp.lineTo(x + s * 0.5, y + s);
            gp.lineTo(x + s * 0.5, y - s);
            gp.closePath();
            break;

        case 4:
            gp.moveTo(x - s * 1.5, y - s);
            gp.lineTo(x - s * 1.5, y + s);
            gp.lineTo(x - s * 0.1, y);
            gp.closePath();
            gp.moveTo(x - s * 0.4, y - s);
            gp.lineTo(x - s * 0.4, y + s);
            gp.lineTo(x + s * 1.0, y);
            gp.closePath();
            gp.moveTo(x + s * 1.4, y - s);
            gp.lineTo(x + s * 1.4, y + s);
            gp.lineTo(x + s * 1.0, y + s);
            gp.lineTo(x + s * 1.0, y - s);
            gp.closePath();
            break;

        case 5:
            gp.moveTo(x - s, y + s * 0.2);
            gp.lineTo(x - s, y - s * 0.2);
            gp.lineTo(x + s, y - s * 0.2);
            gp.lineTo(x + s, y + s * 0.2);
            gp.closePath();
            break;

        case 6:
            gp.moveTo(x + s * 0.2, y - s);
            gp.lineTo(x - s * 0.2, y - s);
            gp.lineTo(x - s * 0.2, y + s);
            gp.lineTo(x + s * 0.2, y + s);
            gp.closePath();
            gp.moveTo(x - s, y + s * 0.2);
            gp.lineTo(x + s, y + s * 0.2);
            gp.lineTo(x + s, y - s * 0.2);
            gp.lineTo(x - s, y - s * 0.2);
            gp.closePath();
            break;
        }
        g.setColor(isSel ? Color.BLACK : btFront);
        g.fill(gp);
        if (isSel) {
            g.setStroke(stroke2);
            g.draw(rb);
            g.setStroke(stroke1);
        } else {
            g.setStroke(stroke1);
            g.draw(rb);
        }
    }

    protected void handleMousePressed(MouseEvent e) {
        super.handleMousePressed(e);
        if (e.isConsumed() || !replayEnabled) return;
        for (int i = 0; i < rcControls.length; i++) {
            Rectangle2D rc = rcControls[i];
            if (rc != null && rc.contains(e.getPoint())) {
                e.consume();
                switch (i) {
                case 0:
                    first();
                    break;

                case 1:
                    prev();
                    break;

                case 2:
                    togglePause();
                    break;

                case 3:
                    next();
                    break;

                case 4:
                    last();
                    break;

                case 5:
                    adjustDelay(-1);
                    break;

                case 6:
                    adjustDelay(1);
                    break;

                case 7:
                    int to = (int) Math.round((e.getPoint().getX() - rc.getX()) / rc.getWidth() * solFrame);
                    moveTo(to);
                    break;
                }
            }
        }
    }

    private void adjustDelay(int dir) {
        boolean repaint = false;
        synchronized (animLock) {
            int idx = Arrays.binarySearch(delays, delay);
            if (idx < 0) {
                delays = Arrays.copyOf(delays, delays.length + 1);
                delays[delays.length - 1] = delay;
                Arrays.sort(delays);
                idx = Arrays.binarySearch(delays, delay);
            }
            idx += dir;
            if (idx >= 0 && idx < delays.length) {
                delay = delays[idx];
                repaint = true;
            }
        }
        if (repaint) frame.getContentPane().repaint();
    }

    protected void paintContent(Graphics2D g, boolean isSave) {
        if (isSave || solFrame < 0 || !replayEnabled || !hasDelay()) super.paintContent(g, isSave);
        else {
            boolean record = false;
            boolean replay = false;
            synchronized (animLock) {
                replay = paintFrame < solFrame;
                record = !replaySequences.containsKey(solFrame);
            }
            if (record) {
                RecordableGraphics rg = new RecordableGraphics(g, replayDict, replayRev, replayUid);
                paintContent(rg);
                int[] seq = rg.getReplaySequence();
                synchronized (animLock) {
                    replaySequences.put(solFrame, seq);
                }
            } else if (replay) {
                int[] seq = replaySequences.get(paintFrame);
                if (seq != null) {
                    RecordableGraphics rg = new RecordableGraphics(g, replayRev);
                    rg.replay(seq);
                }
            } else {
                super.paintContent(g, isSave);
            }
        }
    }

    protected final boolean hasDelay() {
        return delay > 0;
    }

    protected final int getDelay() {
        return delay;
    }

    protected void end() {
        synchronized (animLock) {
            ended = true;
            paused = true;
            animLock.notifyAll();
        }
        super.end();
        frame.getContentPane().repaint();
    }

    protected final void setDefaultDelay(int defaultDelay) {
        if (delay == -1) delay = defaultDelay;
    }

    protected void handleKeyPressed(KeyEvent e) {
    }

    private final void initAnim() {
        frame.addKeyListener(new KeyAdapter() {
            public void keyPressed(KeyEvent e) {
                handleKeyPressed(e);
                if (e.isConsumed()) return;
                if (e.getKeyCode() == KeyEvent.VK_SPACE) {
                    e.consume();
                    togglePause();
                } else if (e.getKeyCode() == KeyEvent.VK_RIGHT) {
                    e.consume();
                    next();
                } else if (e.getKeyCode() == KeyEvent.VK_LEFT) {
                    if (replayEnabled && hasDelay()) {
                        e.consume();
                        prev();
                    }
                } else if (e.getKeyCode() == KeyEvent.VK_UP) {
                    if (replayEnabled && hasDelay()) {
                        e.consume();
                        moveTo(Math.max(0, paintFrame + 10));
                    }
                } else if (e.getKeyCode() == KeyEvent.VK_DOWN) {
                    if (replayEnabled && hasDelay()) {
                        e.consume();
                        moveTo(Math.min(solFrame, paintFrame - 10));
                    }
                } else if (e.getKeyCode() == KeyEvent.VK_HOME) {
                    if (replayEnabled && hasDelay()) {
                        e.consume();
                        first();
                    }
                } else if (e.getKeyCode() == KeyEvent.VK_END) {
                    if (replayEnabled && hasDelay()) {
                        e.consume();
                        last();
                    }
                }
            }
        });

        if (replayEnabled && hasDelay()) {
            Thread animThread = new Thread() {
                public void run() {
                    while (true) {
                        boolean sleep = true;
                        boolean repaint = false;
                        synchronized (animLock) {
                            while (paused) {
                                sleep = false;
                                try {
                                    animLock.wait();
                                } catch (InterruptedException e) {
                                }
                            }
                            if (paintFrame < solFrame) {
                                paintFrame++;
                                repaint = true;
                            } else if (ended) {
                                paused = true;
                            }
                            animLock.notifyAll();
                        }
                        if (repaint) {
                            try {
                                SwingUtilities.invokeAndWait(new Runnable() {
                                    public void run() {
                                        JComponent c = (JComponent) frame.getContentPane();
                                        c.paintImmediately(0, 0, c.getWidth(), c.getHeight());
                                    }
                                });
                            } catch (Exception e) {
                            }
                        }
                        if (sleep) {
                            try {
                                Thread.sleep(delay);
                            } catch (Exception e) {
                            }
                        }
                    }
                }
            };
            animThread.setDaemon(true);
            animThread.start();

            frame.getContentPane().addMouseMotionListener(new MouseMotionListener() {
                public void mouseMoved(MouseEvent e) {
                    if (e.isConsumed()) return;
                    if (rcMouse != null && rcMouse.contains(e.getPoint())) return;
                    Rectangle2D r = null;
                    for (Rectangle2D rc : rcControls) {
                        if (rc.contains(e.getPoint())) {
                            r = rc;
                            break;
                        }
                    }
                    if (r == null && rcMouse == null) return;
                    e.consume();
                    rcMouse = r;
                    frame.getContentPane().repaint();
                }

                public void mouseDragged(MouseEvent e) {
                    if (e.isConsumed()) return;
                    Rectangle2D rc = rcControls[7];
                    if (rc.contains(e.getPoint())) {
                        e.consume();
                        int to = (int) Math.round((e.getPoint().getX() - rc.getX()) / rc.getWidth() * solFrame);
                        moveTo(to);
                    }
                }
            });
        }
    }

    private void togglePause() {
        synchronized (animLock) {
            keyPressed = true;
            paused = !paused;
            animLock.notifyAll();
        }
        frame.getContentPane().repaint();
    }

    private void moveTo(int to) {
        boolean repaint = false;
        synchronized (animLock) {
            if (!paused) paused = true;
            if (to >= 0 && to <= solFrame && to != paintFrame) {
                paintFrame = to;
                repaint = true;
            }
            animLock.notifyAll();
        }
        if (repaint) frame.getContentPane().repaint();
    }

    private void first() {
        boolean repaint = false;
        synchronized (animLock) {
            if (!paused) paused = true;
            if (paintFrame > 0) {
                paintFrame = 0;
                repaint = true;
            }
            animLock.notifyAll();
        }
        if (repaint) frame.getContentPane().repaint();
    }

    private void last() {
        boolean repaint = false;
        synchronized (animLock) {
            if (!paused) paused = true;
            if (paintFrame < solFrame) {
                paintFrame = solFrame;
                repaint = true;
            }
            animLock.notifyAll();
        }
        if (repaint) frame.getContentPane().repaint();
    }

    private void prev() {
        boolean repaint = false;
        synchronized (animLock) {
            if (!paused) paused = true;
            if (paintFrame > 0) {
                paintFrame--;
                repaint = true;
            }
            animLock.notifyAll();
        }
        if (repaint) frame.getContentPane().repaint();
    }

    private void next() {
        boolean repaint = false;
        synchronized (animLock) {
            if (!paused) paused = true;
            if (paintFrame == solFrame) keyPressed = true;
            else {
                paintFrame++;
                repaint = true;
            }
            animLock.notifyAll();
        }
        if (repaint) frame.getContentPane().repaint();
    }

    protected void updateDelay() {
        if (!hasVis()) return;
        synchronized (animLock) {
            while (!ended && paintFrame < solFrame) {
                try {
                    animLock.wait();
                } catch (InterruptedException e) {
                }
            }
            paintFrame = ++solFrame;
        }
        update();
        if (!hasDelay()) return;
        synchronized (updateLock) {
            if (!animInit) {
                initAnim();
                animInit = true;
            }
        }
        boolean sleep = !ended;
        synchronized (animLock) {
            while (!ended && ((paused && !keyPressed) || paintFrame < solFrame)) {
                try {
                    animLock.wait();
                } catch (InterruptedException e) {
                }
            }
            if (keyPressed) {
                sleep = false;
                keyPressed = false;
            }
        }
        if (sleep) {
            try {
                Thread.sleep(delay);
            } catch (Exception e) {
            }
        }
    }
}