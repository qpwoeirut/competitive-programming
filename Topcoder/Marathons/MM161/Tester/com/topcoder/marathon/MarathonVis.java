package com.topcoder.marathon;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.FontMetrics;
import java.awt.GradientPaint;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.GraphicsConfiguration;
import java.awt.GraphicsDevice;
import java.awt.GraphicsEnvironment;
import java.awt.Insets;
import java.awt.Rectangle;
import java.awt.RenderingHints;
import java.awt.Shape;
import java.awt.Toolkit;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.font.FontRenderContext;
import java.awt.font.GlyphVector;
import java.awt.geom.AffineTransform;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Line2D;
import java.awt.geom.Rectangle2D;
import java.awt.image.BufferedImage;
import java.awt.image.BufferedImageOp;
import java.awt.image.ConvolveOp;
import java.awt.image.Kernel;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import javax.imageio.ImageIO;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

/**
 * Base class for Topcoder Marathon testers with visualization. 
 * Should be extended directly for problems with a visual representation, but no animation,
 * i.e. only a single (final) state is shown.
 * 
 * Updates: 
 *      2021/09/13 - Small change in the way the frame is created (waiting, instead of doing
 *                   it in the background).             
 *      2021/02/05 - Move mouse click events to another (not AWT) thread, to avoid painting/  
 *                   delay issues after an user action.
 *                 - Override paint() instead of paintComponent().
 *                 - Use mousePress() event instead of mountClick() for better responsiveness.
 *                 - Add -saveVis parameter to allow saving the visualizer content, after 
 *                   each update.
 *                 - Add -infoScale parameter to allow increase/decrease the font used in the 
 *                   info panel (right side of visualizer). The panel is not displayed if 
 *                   infoScale is 0 (which may be useful if the user wants to see only the 
 *                   main content, possibly together with -saveVis parameter). 
 *      2020/11/19 - Handle -windowPos and -screen parameters.
 */
public abstract class MarathonVis extends MarathonTester {
    protected final Object updateLock = new Object();
    protected JFrame frame;
    private boolean vis = true;
    private JPanel panel;
    private Font infoFontPlain, infoFontBold;
    private final Map<Object, Object> infoMap = new HashMap<Object, Object>();
    private final Map<Object, Boolean> infoChecked = new HashMap<Object, Boolean>();
    private final Map<Object, Rectangle2D> infoRects = new HashMap<Object, Rectangle2D>();
    private final List<Object> infoSequence = new ArrayList<Object>();
    protected int border, infoFontWidth, infoFontHeight, infoColumns, infoLines;
    private double size = -1;
    private Rectangle2D contentRect = new Rectangle2D.Double(0, 0, 100, 100);
    private Rectangle2D contentScreen = new Rectangle2D.Double();
    protected static final double lineSpacing = 1.25;
    private RenderingHints hints;
    private long paintTime;
    private int paintCnt;
    private int saveVisSeq;
    private BufferedImage lastSavedImage;

    protected abstract void paintContent(Graphics2D g);

    static {
        System.setProperty("sun.java2d.uiScale", "1");
        System.setProperty("sun.java2d.dpiaware", "true");
    }

    public void setParameters(Parameters parameters) {
        super.setParameters(parameters);
        if (parameters.isDefined(Parameters.noVis)) {
            System.setProperty("java.awt.headless", "true");
            vis = false;
        }
        if (parameters.isDefined(Parameters.size)) size = parameters.getIntValue(Parameters.size);
    }

    protected void setInfoMaxDimension(int infoColumns, int infoLines) {
        if (!vis) return;
        this.infoColumns = infoColumns;
        this.infoLines = infoLines;
    }

    protected final void setContentRect(double xLeft, double yTop, double xRight, double yBottom) {
        if (!vis) return;
        contentRect.setRect(xLeft, yTop, xRight - xLeft, yBottom - yTop);
    }

    protected final void setDefaultSize(int size) {
        if (this.size == -1) this.size = size;
    }

    protected final boolean hasVis() {
        return vis;
    }

    protected void update() {
        if (!vis) return;
        synchronized (updateLock) {
            if (frame == null) {
                String className = getClass().getName();
                Map<RenderingHints.Key, Object> hintsMap = new HashMap<RenderingHints.Key, Object>();
                hintsMap.put(RenderingHints.KEY_FRACTIONALMETRICS, RenderingHints.VALUE_FRACTIONALMETRICS_ON);
                hintsMap.put(RenderingHints.KEY_INTERPOLATION, RenderingHints.VALUE_INTERPOLATION_BILINEAR);
                hintsMap.put(RenderingHints.KEY_RENDERING, RenderingHints.VALUE_RENDER_SPEED);
                hintsMap.put(RenderingHints.KEY_COLOR_RENDERING, RenderingHints.VALUE_COLOR_RENDER_SPEED);
                if (parameters.isDefined(Parameters.noAntialiasing)) {
                    hintsMap.put(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_OFF);
                    hintsMap.put(RenderingHints.KEY_TEXT_ANTIALIASING, RenderingHints.VALUE_TEXT_ANTIALIAS_OFF);
                } else {
                    hintsMap.put(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
                    hintsMap.put(RenderingHints.KEY_TEXT_ANTIALIASING, RenderingHints.VALUE_TEXT_ANTIALIAS_ON);
                }
                hints = new RenderingHints(hintsMap);

                frame = new JFrame();
                frame.addWindowListener(new WindowAdapter() {
                    public void windowClosed(WindowEvent e) {
                        end();
                    }
                });

                panel = new JPanel() {
                    private static final long serialVersionUID = -1008231133177413855L;

                    public void paint(Graphics g) {
                        paintVis(g, getWidth(), getHeight(), false);
                    }
                };

                panel.addMouseListener(new MouseAdapter() {
                    public void mousePressed(MouseEvent e) {
                        if (e.isConsumed()) return;
                        if (contentScreen != null && contentScreen.contains(e.getPoint())) {
                            if (contentScreen.getWidth() > 0 && contentScreen.getHeight() > 0) {
                                double x = (e.getX() - contentScreen.getX()) / contentScreen.getWidth() * contentRect.getWidth() + contentRect.getX();
                                double y = (e.getY() - contentScreen.getY()) / contentScreen.getHeight() * contentRect.getHeight() + contentRect.getY();
                                new Thread() {
                                    public void run() {
                                        contentClicked(x, y, e.getButton(), e.getClickCount());
                                    }
                                }.start();
                                e.consume();
                            }
                            return;
                        }
                        handleMousePressed(e);
                    }
                });
                panel.addMouseMotionListener(new MouseAdapter() {
                    public void mouseMoved(MouseEvent e) {
                        if (e.isConsumed()) return;
                        if (contentScreen != null && contentScreen.contains(e.getPoint())) {
                            if (contentScreen.getWidth() > 0 && contentScreen.getHeight() > 0) {
                                double x = (e.getX() - contentScreen.getX()) / contentScreen.getWidth() * contentRect.getWidth() + contentRect.getX();
                                double y = (e.getY() - contentScreen.getY()) / contentScreen.getHeight() * contentRect.getHeight() + contentRect.getY();
                                new Thread() {
                                    public void run() {
                                        mouseMove(x, y);
                                    }
                                }.start();
                                e.consume();
                            }
                            return;
                        }
                    }
                });

                final int resolution = Toolkit.getDefaultToolkit().getScreenResolution();
                int infoScale = 100;
                if (parameters.isDefined(Parameters.infoScale)) infoScale = parameters.getIntValue(Parameters.infoScale);
                if (infoScale < 0) infoScale = 0;
                else if (infoScale > 400) infoScale = 400;
                if (infoScale != 0) {
                    infoFontPlain = new Font(Font.SANS_SERIF, Font.PLAIN, resolution * infoScale / 800);
                    infoFontBold = new Font(Font.SANS_SERIF, Font.BOLD, infoFontPlain.getSize());
                }

                try {
                    SwingUtilities.invokeAndWait(new Runnable() {
                        public void run() {
                            frame.setSize(1000, 800);
                            frame.setTitle(className + " - Seed: " + seed);
                            frame.setIconImage(getIcon());
                            frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

                            frame.setContentPane(panel);

                            if (infoFontPlain != null) {
                                FontRenderContext frc = new FontRenderContext(null, true, true);
                                Rectangle2D rc = infoFontBold.getStringBounds("0", frc);
                                infoFontWidth = (int) Math.ceil(rc.getWidth());
                                infoFontHeight = (int) Math.ceil(rc.getHeight());
                            }

                            border = resolution / 8;
                            showAndAdjustWindowBounds();
                        }
                    });
                } catch (Exception e) {
                }
            }
        }
        if (parameters.isDefined(Parameters.saveVis)) saveVis();
        try {
            SwingUtilities.invokeAndWait(new Runnable() {
                public void run() {
                    panel.paintImmediately(0, 0, panel.getWidth(), panel.getHeight());
                }
            });
        } catch (Exception e) {
        }
    }

    protected void handleMousePressed(MouseEvent e) {
        if (e.isConsumed()) return;
        for (Object key : infoRects.keySet()) {
            Rectangle2D rc = infoRects.get(key);
            if (rc != null && rc.contains(e.getPoint())) {
                Boolean checked = infoChecked.get(key);
                if (checked != null) {
                    infoChecked.put(key, !checked);
                    new Thread() {
                        public void run() {
                            checkChanged(key, !checked);
                        }
                    }.start();
                    e.consume();
                }
                break;
            }
        }
    }
    
    protected Map<Object, Object> getInfoMapCopy() {
        return new HashMap<Object, Object>(infoMap);
    }

    private void saveVis() {
        int w = panel.getWidth();
        if (w > 0) {
            int h = panel.getHeight();
            String s = parameters.getStringNull(Parameters.saveVis);
            File folder = new File(s == null ? "." : s);
            if (!folder.exists()) folder.mkdirs();
            BufferedImage img = new BufferedImage(w, h, BufferedImage.TYPE_INT_BGR);
            Graphics2D g = img.createGraphics();
            paintVis(g, w, h, true);
            g.dispose();
            try {
                synchronized (updateLock) {
                    boolean eq = false;
                    if (lastSavedImage != null && lastSavedImage.getWidth() == w && lastSavedImage.getHeight() == h) {
                        int[] curr = img.getRGB(0, 0, w, h, null, 0, w);
                        int[] prev = lastSavedImage.getRGB(0, 0, w, h, null, 0, w);
                        eq = curr.length == prev.length;
                        if (eq) {
                            OUT: for (int i = 0; i < 256; i++) {
                                for (int j = i; j < curr.length; j += 256) {
                                    if (curr[j] != prev[j]) {
                                        eq = false;
                                        break OUT;
                                    }
                                }
                            }
                        }
                    }
                    if (!eq) {
                        File file = new File(folder, String.format("%d-%05d.png", seed, ++saveVisSeq));
                        ImageIO.write(img, "png", file);
                        lastSavedImage = img;
                    }
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    private void showAndAdjustWindowBounds() {
        Rectangle screenBounds = null;
        Insets screenInsets = null;
        int screen = 1;
        if (parameters.isDefined(Parameters.screen)) {
            try {
                screen = Integer.parseInt(parameters.getString(Parameters.screen));
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        try {
            GraphicsDevice[] graphicsDevices = GraphicsEnvironment.getLocalGraphicsEnvironment().getScreenDevices();
            int numScreen = 0;
            for (GraphicsDevice gd : graphicsDevices) {
                numScreen++;
                if (numScreen == 1 || numScreen == screen) {
                    GraphicsConfiguration gc = gd.getDefaultConfiguration();
                    screenBounds = new Rectangle(gc.getBounds());
                    screenInsets = Toolkit.getDefaultToolkit().getScreenInsets(gc);
                }
            }
        } catch (Throwable t) {
            t.printStackTrace();
        }
        int x = Integer.MIN_VALUE, y = Integer.MIN_VALUE, w = Integer.MIN_VALUE, h = Integer.MIN_VALUE;
        if (parameters.isDefined(Parameters.windowPosition)) {
            String[] v = parameters.getString(Parameters.windowPosition).split(",");
            boolean ok = v.length == 2 || v.length == 4;
            if (ok) {
                try {
                    x = Integer.parseInt(v[0]);
                    y = Integer.parseInt(v[1]);
                    if (screenBounds != null) {
                        x += screenBounds.x;
                        y += screenBounds.y;
                    }
                    if (screenInsets != null) {
                        x += screenInsets.left;
                        y += screenInsets.top;
                    }
                    if (v.length > 2) {
                        w = Integer.parseInt(v[2]);
                        h = Integer.parseInt(v[3]);
                        if (w > 0 && h > 0) {
                            frame.setVisible(true);
                            frame.setBounds(x, y, w, h);
                        } else {
                            ok = false;
                        }
                    }
                } catch (Exception e) {
                    ok = false;
                }
            }
            if (!ok) {
                System.err.println("Parameter -" + Parameters.windowPosition + " should be followed by 2 or 4 integers: x,y[,width,height] of desired window position.");
                System.exit(0);
            }
        }
        if (w == Integer.MIN_VALUE || h == Integer.MIN_VALUE) {
            frame.setVisible(true);
            if (x != Integer.MIN_VALUE && y != Integer.MIN_VALUE) {
                frame.setLocation(x, y);
            } else if (screenBounds != null) {
                int xf = screenBounds.x;
                int yf = screenBounds.y;
                if (screenInsets != null) {
                    xf += screenInsets.left;
                    yf += screenInsets.top;
                }
                frame.setLocation(xf, yf);
            } else {
                frame.setLocation(0, 0);
            }
            if (size <= 0 && screenBounds != null) {
                Rectangle bounds = new Rectangle(screenBounds);
                if (x != Integer.MIN_VALUE && y != Integer.MIN_VALUE) {
                    bounds.x = x;
                    bounds.y = y;
                }
                if (screenInsets != null) {
                    int dx = 0;
                    int dy = 0;
                    if (bounds.x - screenBounds.x < screenInsets.left) dx = screenInsets.left - bounds.x;
                    if (bounds.y - screenBounds.y < screenInsets.top) dy = screenInsets.top - bounds.y;
                    bounds.x += dx;
                    bounds.y += dy;
                    if (bounds.x >= screenBounds.x && bounds.x < screenBounds.x + screenBounds.width) {
                        bounds.width -= Math.max(0, bounds.x - screenBounds.x + bounds.width - (screenBounds.width - screenInsets.right));
                    }
                    if (bounds.y >= screenBounds.y && bounds.y < screenBounds.y + screenBounds.height) {
                        bounds.height -= Math.max(0, bounds.y - screenBounds.y + bounds.height - (screenBounds.height - screenInsets.bottom));
                    }
                }
                Insets fi = frame.getInsets();
                int fw = bounds.width - fi.left - fi.right;
                int fh = bounds.height - fi.top - fi.bottom;
                double sw = (fw - 3 * border - infoColumns * infoFontWidth) / contentRect.getWidth();
                double sh = (fh - 2 * border) / contentRect.getHeight();
                size = Math.min(sw, sh);
            }
            int width = 2 * border + (int) (contentRect.getWidth() * size);
            if (infoFontWidth > 0) width += border + infoColumns * infoFontWidth;
            int height = 2 * border + (int) Math.max(infoLines * infoFontHeight * lineSpacing, contentRect.getHeight() * size);
            panel.setPreferredSize(new Dimension(width, height));
            frame.pack();
        }
    }

    protected void checkChanged(Object key, boolean newValue) {
        panel.repaint();
    }

    protected void contentClicked(double x, double y, int mouseButton, int clickCount) {
    }
    protected void mouseMove(double x, double y) {
    }

    protected void end() {
        if (ending) return;
        if (paintCnt > 0 && parameters.isDefined(Parameters.paintInfo)) {
            System.out.println("    Paint Count: " + paintCnt);
            System.out.println("Paint Avg. Time: " + paintTime / paintCnt + " ms");
        }
        super.end();
    }

    protected final void addInfo(Object key, Object value) {
        if (!vis) return;
        if (!infoMap.containsKey(key)) infoSequence.add(key);
        infoMap.put(key, value);
    }

    protected final void addInfo(Object key) {
        if (!vis) return;
        if (!infoMap.containsKey(key)) infoSequence.add(key);
        infoMap.put(key, null);
    }

    protected final void addInfo(Object key, Object value, boolean checked) {
        if (!vis) return;
        if (!infoMap.containsKey(key)) infoSequence.add(key);
        infoMap.put(key, value);
        infoChecked.put(key, checked);
    }

    protected final void addInfo(Object key, boolean checked) {
        if (!vis) return;
        if (!infoMap.containsKey(key)) infoSequence.add(key);
        infoMap.put(key, null);
        infoChecked.put(key, checked);
    }

    protected final void addInfoBreak() {
        if (!vis) return;
        infoSequence.add(null);
    }

    protected final boolean isInfoChecked(Object key) {
        Boolean checked = infoChecked.get(key);
        if (checked != null) return checked.booleanValue();
        return false;
    }

    protected final Rectangle2D getPaintRect() {
        return contentRect;
    }

    private void paintVis(Graphics g, int w, int h, boolean isSave) {
        long t = System.currentTimeMillis();
        Graphics2D g2 = (Graphics2D) g;
        g2.setColor(new Color(230, 230, 232));
        g2.fillRect(0, 0, w, h);
        g2.setRenderingHints(hints);
        synchronized (updateLock) {
            if (infoColumns > 0 && infoFontWidth > 0) paintInfo(g2, w, isSave);
            paintCenter(g2, infoFontWidth == 0 ? w : w - infoFontWidth * infoColumns - border, h, isSave);
            paintTime += System.currentTimeMillis() - t;
            paintCnt++;
        }
    }

    private void paintCenter(Graphics2D g, int w, int h, boolean isSave) {
        int pw = w - 2 * border;
        int ph = h - 2 * border;
        if (pw <= 0 || ph <= 0) return;
        int px = border;
        int py = border;
        if (contentRect.getWidth() * ph > contentRect.getHeight() * pw) {
            ph = (int) (contentRect.getHeight() * pw / contentRect.getWidth());
        } else {
            int nw = (int) (contentRect.getWidth() * ph / contentRect.getHeight());
            px += (pw - nw) / 2;
            pw = nw;
        }
        AffineTransform nt = new AffineTransform();
        nt.translate(px, py);
        nt.scale(pw / contentRect.getWidth(), ph / contentRect.getHeight());
        nt.translate(-contentRect.getX(), -contentRect.getY());
        AffineTransform ct = g.getTransform();
        contentScreen.setRect(px, py, pw, ph);
        g.setTransform(nt);
        paintContent(g, isSave);
        g.setTransform(ct);
    }

    protected void paintContent(Graphics2D g, boolean isSave) {
        paintContent(g);
    }

    protected int paintInfo(Graphics2D g, int w, boolean isSave) {
        return paintInfo(g, w, infoMap);    
    }
    
    protected int paintInfo(Graphics2D g, int w, Map<Object, Object> map) {
        int x = w - infoFontWidth * infoColumns - border;
        int y = border;
        int maxKey = 0;
        g.setFont(infoFontBold);
        FontMetrics metrics = g.getFontMetrics();
        for (Object key : infoSequence) {
            if (key != null) {
                String s = "";
                if (key instanceof Color) {
                    s = "##";
                } else {
                    s = key.toString();
                }
                boolean hasValue = map.get(key) != null;
                if (hasValue) s += ": ";
                if (infoChecked.get(key) != null) s += "##";
                Rectangle2D rect = metrics.getStringBounds(s, g);
                int width = (int) rect.getWidth();
                if (!hasValue) width /= 2;
                maxKey = Math.max(maxKey, width);
            }
        }

        int lineHeight = (int) (lineSpacing * infoFontHeight);
        g.setStroke(new BasicStroke(1f, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND));
        g.setColor(Color.black);
        for (Object key : infoSequence) {
            if (key != null) {
                Object value = map.get(key);
                g.setFont(infoFontBold);
                int xc = 0;
                if (value == null) {
                    xc = drawString(g, key.toString(), x + maxKey, y, 0);
                } else {
                    if (key instanceof Color) {
                        xc = drawColor(g, (Color) key, x + maxKey, y);
                    } else {
                        xc = drawString(g, key + ": ", x + maxKey, y, -1);
                    }
                    g.setFont(infoFontPlain);
                    drawString(g, value.toString(), x + maxKey, y, 1);
                }
                Boolean checked = infoChecked.get(key);
                if (checked != null) drawChecked(g, key, checked, xc, y);
            }
            y += lineHeight;
        }
        return y;
    }

    private int drawColor(Graphics2D g, Color color, int x, int y) {
        FontMetrics metrics = g.getFontMetrics();
        int size = metrics.getHeight() - metrics.getDescent();
        g.setColor(color);
        Rectangle2D rc = new Rectangle2D.Double(x - size - infoFontWidth, y + metrics.getDescent() / 2, size, size);
        g.fill(rc);
        g.setColor(Color.black);
        g.draw(rc);
        return (int) rc.getMinX();
    }

    private void drawChecked(Graphics2D g, Object key, boolean checked, int x, int y) {
        FontMetrics metrics = g.getFontMetrics();
        int size = metrics.getHeight() - metrics.getDescent();
        Rectangle2D rc = new Rectangle2D.Double(x - size - infoFontWidth, y + metrics.getDescent() / 2, size, size);
        g.setColor(Color.black);
        g.draw(rc);
        synchronized (infoRects) {
            infoRects.put(key, rc);
        }
        if (checked) {
            g.draw(new Line2D.Double(rc.getMinX(), rc.getMinY(), rc.getMaxX(), rc.getMaxY()));
            g.draw(new Line2D.Double(rc.getMinX(), rc.getMaxY(), rc.getMaxX(), rc.getMinY()));
        }
    }

    private int drawString(Graphics2D g, String s, int x, int y, int align) {
        FontMetrics metrics = g.getFontMetrics();
        Rectangle2D rect = metrics.getStringBounds(s, g);
        if (align < 0) x -= (int) rect.getWidth();
        else if (align == 0) x -= (int) rect.getWidth() / 2;
        g.drawString(s, x, y + metrics.getAscent());
        return x;
    }

    protected void adjustFont(Graphics2D g, String fontName, int fontStyle, String largestStr, Rectangle2D rcToFit) {
        g.setFont(new Font(fontName, fontStyle, 32));
        Rectangle2D bounds = g.getFontMetrics().getStringBounds(largestStr, g);
        double f = Math.min(rcToFit.getWidth() / bounds.getWidth(), rcToFit.getHeight() / bounds.getHeight());
        AffineTransform transformation = AffineTransform.getScaleInstance(f, f);
        g.setFont(g.getFont().deriveFont(transformation));
    }

    protected void drawString(Graphics2D g, String str, Rectangle2D rc) {
        GlyphVector v = g.getFont().createGlyphVector(g.getFontRenderContext(), str);
        Shape s = v.getOutline();
        Rectangle2D rs = s.getBounds2D();
        double x = rc.getX() - rs.getX() + (rc.getWidth() - rs.getWidth()) / 2.0;
        double y = rc.getY() - rs.getY() + (rc.getHeight() - rs.getHeight()) / 2.0;
        s = AffineTransform.getTranslateInstance(x, y).createTransformedShape(s);
        g.fill(s);
    }

    private BufferedImage getIcon() {
        int size = 256;
        BufferedImage img = new BufferedImage(size, size, BufferedImage.TYPE_INT_ARGB);
        Graphics2D g = img.createGraphics();
        g.setRenderingHints(hints);
        AffineTransform nt = new AffineTransform();
        nt.scale(size, size);
        g.setTransform(nt);
        g.setStroke(new BasicStroke(0.06f, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND));
        GradientPaint gradient = new GradientPaint(0.5f, 0, new Color(150, 75, 200), 0.5f, 1, new Color(90, 160, 230));
        g.setPaint(gradient);
        Ellipse2D e0 = new Ellipse2D.Double(0, 0, 1, 1);
        g.fill(e0);
        Ellipse2D e1 = new Ellipse2D.Double(0.05, 0.45, 0.2, 0.2);
        Ellipse2D e2 = new Ellipse2D.Double(0.30, 0.05, 0.2, 0.2);
        Ellipse2D e3 = new Ellipse2D.Double(0.75, 0.25, 0.2, 0.2);
        Ellipse2D e4 = new Ellipse2D.Double(0.70, 0.60, 0.2, 0.2);
        Ellipse2D e5 = new Ellipse2D.Double(0.35, 0.75, 0.2, 0.2);
        g.setColor(Color.white);
        g.setStroke(new BasicStroke(0.06f, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND));
        g.draw(new Line2D.Double(e1.getCenterX(), e1.getCenterY(), e2.getCenterX(), e2.getCenterY()));
        g.draw(new Line2D.Double(e1.getCenterX(), e1.getCenterY(), e3.getCenterX(), e3.getCenterY()));
        g.draw(new Line2D.Double(e4.getCenterX(), e4.getCenterY(), e3.getCenterX(), e3.getCenterY()));
        g.draw(new Line2D.Double(e4.getCenterX(), e4.getCenterY(), e5.getCenterX(), e5.getCenterY()));
        g.draw(new Line2D.Double(e2.getCenterX(), e2.getCenterY(), e5.getCenterX(), e5.getCenterY()));
        g.draw(new Line2D.Double(e2.getCenterX(), e2.getCenterY(), e4.getCenterX(), e4.getCenterY()));
        g.setPaint(gradient);
        g.fill(e1);
        g.fill(e2);
        g.fill(e3);
        g.fill(e4);
        g.fill(e5);
        g.setColor(Color.white);
        g.draw(e1);
        g.draw(e2);
        g.draw(e3);
        g.draw(e4);
        g.draw(e5);
        g.dispose();
        float[] blurKernel = {0.1f,0.1f,0.1f,0.1f,0.2f,0.1f,0.1f,0.1f,0.1f};
        BufferedImageOp blurFilter = new ConvolveOp(new Kernel(3, 3, blurKernel), ConvolveOp.EDGE_NO_OP, hints);
        blurFilter.filter(img, null);
        return img;
    }
}
