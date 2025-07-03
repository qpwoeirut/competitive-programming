package com.topcoder.marathon;

import java.awt.Color;
import java.awt.Composite;
import java.awt.Font;
import java.awt.FontMetrics;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.GraphicsConfiguration;
import java.awt.Image;
import java.awt.Paint;
import java.awt.Rectangle;
import java.awt.RenderingHints;
import java.awt.RenderingHints.Key;
import java.awt.Shape;
import java.awt.Stroke;
import java.awt.font.FontRenderContext;
import java.awt.font.GlyphVector;
import java.awt.geom.AffineTransform;
import java.awt.image.BufferedImage;
import java.awt.image.BufferedImageOp;
import java.awt.image.ImageObserver;
import java.awt.image.RenderedImage;
import java.awt.image.renderable.RenderableImage;
import java.text.AttributedCharacterIterator;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.concurrent.atomic.AtomicInteger;

public class RecordableGraphics extends Graphics2D {
    private final Graphics2D g;
    private final Map<Object, Integer> dict;
    private final Map<Integer, Object> rev;
    private final AtomicInteger uid;
    private final List<Integer> replaySeq;

    private static final int SET_COLOR = 1;
    private static final int FILL_RECT = 2;
    private static final int SET_RENDERING_HINTS1 = 3;
    private static final int DRAW = 4;
    private static final int DRAW_IMAGE1 = 5;
    private static final int DRAW_IMAGE2 = 6;
    private static final int DRAW_RENDERED_IMAGE = 7;
    private static final int DRAW_RENDERABLE_IMAGE = 8;
    private static final int DRAW_STRING1 = 9;
    private static final int DRAW_STRING2 = 10;
    private static final int DRAW_STRING3 = 11;
    private static final int DRAW_STRING4 = 12;
    private static final int DRAW_GLYPH_VECTOR = 13;
    private static final int FILL = 14;
    private static final int HIT = 15;
    private static final int SET_COMPOSITE = 16;
    private static final int SET_PAINT = 17;
    private static final int SET_STROKE = 18;
    private static final int SET_RENDERING_HINT = 19;
    private static final int SET_RENDERING_HINTS2 = 20;
    private static final int ADD_RENDERING_HINTS = 21;
    private static final int TRANSLATE1 = 22;
    private static final int TRANSLATE2 = 23;
    private static final int ROTATE1 = 24;
    private static final int ROTATE2 = 25;
    private static final int SCALE = 26;
    private static final int SHEAR = 27;
    private static final int TRANSFORM = 28;
    private static final int SET_TRANSFORM = 29;
    private static final int SET_BACKGROUND = 30;
    private static final int CLIP = 31;
    private static final int SET_PAINT_MODE = 32;
    private static final int SET_XOR_MODE = 33;
    private static final int SET_FONT = 34;
    private static final int CLIP_RECT = 35;
    private static final int SET_CLIP1 = 36;
    private static final int SET_CLIP2 = 37;
    private static final int COPY_AREA = 38;
    private static final int DRAW_LINE = 39;
    private static final int CLEAR_RECT = 40;
    private static final int DRAW_ROUND_RECT = 41;
    private static final int FILL_ROUND_RECT = 42;
    private static final int DRAW_OVAL = 43;
    private static final int FILL_OVAL = 44;
    private static final int DRAW_ARC = 45;
    private static final int FILL_ARC = 46;
    private static final int DRAW_POLYLINE = 47;
    private static final int DRAW_POLYGON = 48;
    private static final int FILL_POLYGON = 49;
    private static final int DRAW_IMAGE3 = 50;
    private static final int DRAW_IMAGE4 = 51;
    private static final int DRAW_IMAGE5 = 52;
    private static final int DRAW_IMAGE6 = 53;
    private static final int DRAW_IMAGE7 = 54;
    private static final int DRAW_IMAGE8 = 55;
    private static final int DRAW_RECT = 56;

    public RecordableGraphics(Graphics2D g, Map<Object, Integer> dict, Map<Integer, Object> rev, AtomicInteger uid) {
        this.g = g;
        this.dict = dict;
        this.rev = rev;
        this.uid = uid;
        this.replaySeq = new ArrayList<Integer>();
    }

    public RecordableGraphics(Graphics2D g, Map<Integer, Object> rev) {
        this.g = g;
        this.dict = null;
        this.rev = rev;
        this.uid = null;
        this.replaySeq = null;
    }

    public void replay(int[] seq) {
        for (int i = 0; i < seq.length; i++) {
            int cmd = seq[i];
            switch (cmd) {
            case SET_COLOR:
                g.setColor((Color) p(seq[++i]));
                break;

            case FILL_RECT:
                g.fillRect((Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]));
                break;

            case SET_RENDERING_HINTS1:
                g.setRenderingHints((RenderingHints) p(seq[++i]));
                break;

            case DRAW:
                g.draw((Shape) p(seq[++i]));
                break;

            case DRAW_IMAGE1:
                g.drawImage((Image) p(seq[++i]), (AffineTransform) p(seq[++i]), (ImageObserver) p(seq[++i]));
                break;

            case DRAW_IMAGE2:
                g.drawImage((BufferedImage) p(seq[++i]), (BufferedImageOp) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]));
                break;

            case DRAW_RENDERED_IMAGE:
                g.drawRenderedImage((RenderedImage) p(seq[++i]), (AffineTransform) p(seq[++i]));
                break;

            case DRAW_RENDERABLE_IMAGE:
                g.drawRenderableImage((RenderableImage) p(seq[++i]), (AffineTransform) p(seq[++i]));
                break;

            case DRAW_STRING1:
                g.drawString((String) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]));
                break;

            case DRAW_STRING2:
                g.drawString((String) p(seq[++i]), (Float) p(seq[++i]), (Float) p(seq[++i]));
                break;

            case DRAW_STRING3:
                g.drawString((AttributedCharacterIterator) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]));
                break;

            case DRAW_STRING4:
                g.drawString((AttributedCharacterIterator) p(seq[++i]), (Float) p(seq[++i]), (Float) p(seq[++i]));
                break;

            case DRAW_GLYPH_VECTOR:
                g.drawGlyphVector((GlyphVector) p(seq[++i]), (Float) p(seq[++i]), (Float) p(seq[++i]));
                break;

            case FILL:
                g.fill((Shape) p(seq[++i]));
                break;

            case HIT:
                g.hit((Rectangle) p(seq[++i]), (Shape) p(seq[++i]), (boolean) p(seq[++i]));
                break;

            case SET_COMPOSITE:
                g.setComposite((Composite) p(seq[++i]));
                break;

            case SET_PAINT:
                g.setPaint((Paint) p(seq[++i]));
                break;

            case SET_STROKE:
                g.setStroke((Stroke) p(seq[++i]));
                break;

            case SET_RENDERING_HINT:
                g.setRenderingHint((Key) p(seq[++i]), (Object) p(seq[++i]));
                break;

            case SET_RENDERING_HINTS2:
                g.setRenderingHints((Map<?, ?>) p(seq[++i]));
                break;

            case ADD_RENDERING_HINTS:
                g.addRenderingHints((Map<?, ?>) p(seq[++i]));
                break;

            case TRANSLATE1:
                g.translate((Integer) p(seq[++i]), (Integer) p(seq[++i]));
                break;

            case TRANSLATE2:
                g.translate((Double) p(seq[++i]), (Double) p(seq[++i]));
                break;

            case ROTATE1:
                g.rotate((Double) p(seq[++i]));
                break;

            case ROTATE2:
                g.rotate((Double) p(seq[++i]), (Double) p(seq[++i]), (Double) p(seq[++i]));
                break;

            case SCALE:
                g.scale((Double) p(seq[++i]), (Double) p(seq[++i]));
                break;

            case SHEAR:
                g.shear((Double) p(seq[++i]), (Double) p(seq[++i]));
                break;

            case TRANSFORM:
                g.transform((AffineTransform) p(seq[++i]));
                break;

            case SET_TRANSFORM:
                g.setTransform((AffineTransform) p(seq[++i]));
                break;

            case SET_BACKGROUND:
                g.setBackground((Color) p(seq[++i]));
                break;

            case CLIP:
                g.clip((Shape) p(seq[++i]));
                break;

            case SET_PAINT_MODE:
                g.setPaintMode();
                break;

            case SET_XOR_MODE:
                g.setXORMode((Color) p(seq[++i]));
                break;

            case SET_FONT:
                g.setFont((Font) p(seq[++i]));
                break;

            case CLIP_RECT:
                g.clipRect((Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]));
                break;

            case SET_CLIP1:
                g.setClip((Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]));
                break;

            case SET_CLIP2:
                g.setClip((Shape) p(seq[++i]));
                break;

            case COPY_AREA:
                g.copyArea((Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]));
                break;

            case DRAW_LINE:
                g.drawLine((Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]));
                break;

            case CLEAR_RECT:
                g.clearRect((Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]));
                break;

            case DRAW_ROUND_RECT:
                g.drawRoundRect((Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]));
                break;

            case FILL_ROUND_RECT:
                g.fillRoundRect((Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]));
                break;

            case DRAW_OVAL:
                g.drawOval((Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]));
                break;

            case FILL_OVAL:
                g.fillOval((Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]));
                break;

            case DRAW_ARC:
                g.drawArc((Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]));
                break;

            case FILL_ARC:
                g.fillArc((Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]));
                break;

            case DRAW_POLYLINE:
                g.drawPolyline((int[]) p(seq[++i]), (int[]) p(seq[++i]), (Integer) p(seq[++i]));
                break;

            case DRAW_POLYGON:
                g.drawPolygon((int[]) p(seq[++i]), (int[]) p(seq[++i]), (Integer) p(seq[++i]));
                break;

            case FILL_POLYGON:
                g.fillPolygon((int[]) p(seq[++i]), (int[]) p(seq[++i]), (Integer) p(seq[++i]));
                break;

            case DRAW_IMAGE3:
                g.drawImage((Image) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]), (ImageObserver) p(seq[++i]));
                break;

            case DRAW_IMAGE4:
                g.drawImage((Image) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]), (ImageObserver) p(seq[++i]));
                break;

            case DRAW_IMAGE5:
                g.drawImage((Image) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]), (Color) p(seq[++i]), (ImageObserver) p(seq[++i]));
                break;

            case DRAW_IMAGE6:
                g.drawImage((Image) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]), (Color) p(seq[++i]), (ImageObserver) p(seq[++i]));
                break;

            case DRAW_IMAGE7:
                g.drawImage((Image) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]),
                        (Integer) p(seq[++i]), (Integer) p(seq[++i]), (ImageObserver) p(seq[++i]));
                break;

            case DRAW_IMAGE8:
                g.drawImage((Image) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]),
                        (Integer) p(seq[++i]), (Integer) p(seq[++i]), (Color) p(seq[++i]), (ImageObserver) p(seq[++i]));
                break;

            case DRAW_RECT:
                g.drawRect((Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]), (Integer) p(seq[++i]));
                break;

            default:
                throw new UnsupportedOperationException("Command ID = " + cmd);
            }
        }
    }

    public Object p(int key) {
        return rev.get(key);
    }

    public int[] getReplaySequence() {
        int[] ret = new int[replaySeq.size()];
        for (int i = 0; i < ret.length; i++) {
            ret[i] = replaySeq.get(i);
        }
        return ret;
    }

    private int getUid(Object o) {
        Integer v = dict.get(o);
        if (v == null) {
            v = uid.incrementAndGet();
            dict.put(o, v);
            rev.put(v, o);
        }
        return v;
    }

    private void addToReplay(int cmdId, Object... params) {
        replaySeq.add(cmdId);
        for (Object param : params) {
            replaySeq.add(getUid(param));
        }
    }

    public void setColor(Color color) {
        if (color.equals(getColor())) return;
        addToReplay(SET_COLOR, color);
        g.setColor(color);
    }

    public void fillRect(int x, int y, int w, int h) {
        addToReplay(FILL_RECT, x, y, w, h);
        g.fillRect(x, y, w, h);
    }

    public void setRenderingHints(RenderingHints hints) {
        addToReplay(SET_RENDERING_HINTS1, hints);
        g.setRenderingHints(hints);
    }

    public void draw(Shape s) {
        addToReplay(DRAW, s);
        g.draw(s);
    }

    public boolean drawImage(Image img, AffineTransform xform, ImageObserver obs) {
        addToReplay(DRAW_IMAGE1, img, xform, obs);
        return g.drawImage(img, xform, obs);
    }

    public void drawImage(BufferedImage img, BufferedImageOp op, int x, int y) {
        addToReplay(DRAW_IMAGE2, img, op, x, y);
        g.drawImage(img, op, x, y);
    }

    public void drawRenderedImage(RenderedImage img, AffineTransform xform) {
        addToReplay(DRAW_RENDERED_IMAGE, img, xform);
        g.drawRenderedImage(img, xform);
    }

    public void drawRenderableImage(RenderableImage img, AffineTransform xform) {
        addToReplay(DRAW_RENDERABLE_IMAGE, img, xform);
        g.drawRenderableImage(img, xform);
    }

    public void drawString(String str, int x, int y) {
        addToReplay(DRAW_STRING1, str, x, y);
        g.drawString(str, x, y);
    }

    public void drawString(String str, float x, float y) {
        addToReplay(DRAW_STRING2, str, x, y);
        g.drawString(str, x, y);
    }

    public void drawString(AttributedCharacterIterator iterator, int x, int y) {
        addToReplay(DRAW_STRING3, iterator, x, y);
        g.drawString(iterator, x, y);
    }

    public void drawString(AttributedCharacterIterator iterator, float x, float y) {
        addToReplay(DRAW_STRING4, iterator, x, y);
        g.drawString(iterator, x, y);
    }

    public void drawGlyphVector(GlyphVector gv, float x, float y) {
        addToReplay(DRAW_GLYPH_VECTOR, gv, x, y);
        g.drawGlyphVector(gv, x, y);
    }

    public void fill(Shape s) {
        addToReplay(FILL, s);
        g.fill(s);
    }

    public boolean hit(Rectangle rect, Shape s, boolean onStroke) {
        addToReplay(HIT, rect, s, onStroke);
        return g.hit(rect, s, onStroke);
    }

    public GraphicsConfiguration getDeviceConfiguration() {
        return g.getDeviceConfiguration();
    }

    public void setComposite(Composite comp) {
        addToReplay(SET_COMPOSITE, comp);
        g.setComposite(comp);

    }

    public void setPaint(Paint paint) {
        addToReplay(SET_PAINT, paint);
        g.setPaint(paint);
    }

    public void setStroke(Stroke s) {
        if (s.equals(getStroke())) return;
        addToReplay(SET_STROKE, s);
        g.setStroke(s);
    }

    public void setRenderingHint(Key hintKey, Object hintValue) {
        addToReplay(SET_RENDERING_HINT, hintKey, hintValue);
        g.setRenderingHint(hintKey, hintValue);
    }

    public Object getRenderingHint(Key hintKey) {
        return g.getRenderingHint(hintKey);
    }

    public void setRenderingHints(Map<?, ?> hints) {
        addToReplay(SET_RENDERING_HINTS2, hints);
        g.setRenderingHints(hints);
    }

    public void addRenderingHints(Map<?, ?> hints) {
        addToReplay(ADD_RENDERING_HINTS, hints);
        g.addRenderingHints(hints);
    }

    public RenderingHints getRenderingHints() {
        return g.getRenderingHints();
    }

    public void translate(int x, int y) {
        addToReplay(TRANSLATE1, x, y);
        g.translate(x, y);
    }

    public void translate(double tx, double ty) {
        addToReplay(TRANSLATE2, tx, ty);
        g.translate(tx, ty);
    }

    public void rotate(double theta) {
        addToReplay(ROTATE1, theta);
        g.rotate(theta);
    }

    public void rotate(double theta, double x, double y) {
        addToReplay(ROTATE2, theta, x, y);
        g.rotate(theta, x, y);
    }

    public void scale(double sx, double sy) {
        addToReplay(SCALE, sx, sy);
        g.scale(sx, sy);
    }

    public void shear(double shx, double shy) {
        addToReplay(SHEAR, shx, shy);
        g.shear(shx, shy);
    }

    public void transform(AffineTransform Tx) {
        addToReplay(TRANSFORM, Tx);
        g.transform(Tx);
    }

    public void setTransform(AffineTransform Tx) {
        addToReplay(SET_TRANSFORM, Tx);
        g.setTransform(Tx);
    }

    public AffineTransform getTransform() {
        return g.getTransform();
    }

    public Paint getPaint() {
        return g.getPaint();
    }

    public Composite getComposite() {
        return g.getComposite();
    }

    public void setBackground(Color color) {
        addToReplay(SET_BACKGROUND, color);
        g.setBackground(color);
    }

    public Color getBackground() {
        return g.getBackground();
    }

    public Stroke getStroke() {
        return g.getStroke();
    }

    public void clip(Shape s) {
        addToReplay(CLIP, s);
        g.clip(s);
    }

    public FontRenderContext getFontRenderContext() {
        return g.getFontRenderContext();
    }

    public Graphics create() {
        return g.create();
    }

    public Color getColor() {
        return g.getColor();
    }

    public void setPaintMode() {
        addToReplay(SET_PAINT_MODE);
        g.setPaintMode();
    }

    public void setXORMode(Color c1) {
        addToReplay(SET_XOR_MODE, c1);
        g.setXORMode(c1);
    }

    public Font getFont() {
        return g.getFont();
    }

    public void setFont(Font font) {
        if (font.equals(getFont())) return;
        addToReplay(SET_FONT, font);
        g.setFont(font);
    }

    public FontMetrics getFontMetrics(Font f) {
        return g.getFontMetrics(f);
    }

    public Rectangle getClipBounds() {
        return g.getClipBounds();
    }

    public void clipRect(int x, int y, int width, int height) {
        addToReplay(CLIP_RECT, x, y, width, height);
        g.clipRect(x, y, width, height);
    }

    public void setClip(int x, int y, int width, int height) {
        addToReplay(SET_CLIP1, x, y, width, height);
        g.setClip(x, y, width, height);
    }

    public Shape getClip() {
        return g.getClip();
    }

    public void setClip(Shape clip) {
        addToReplay(SET_CLIP2, clip);
        g.setClip(clip);
    }

    public void copyArea(int x, int y, int width, int height, int dx, int dy) {
        addToReplay(COPY_AREA, x, y, width, height, dx, dy);
        g.copyArea(x, y, width, height, dx, dy);
    }

    public void drawLine(int x1, int y1, int x2, int y2) {
        addToReplay(DRAW_LINE, x1, y1, x2, y2);
        g.drawLine(x1, y1, x2, y2);
    }

    public void clearRect(int x, int y, int width, int height) {
        addToReplay(CLEAR_RECT, x, y, width, height);
        g.clearRect(x, y, width, height);
    }

    public void drawRoundRect(int x, int y, int width, int height, int arcWidth, int arcHeight) {
        addToReplay(DRAW_ROUND_RECT, x, y, width, height, arcWidth, arcHeight);
        g.drawRoundRect(x, y, width, height, arcWidth, arcHeight);
    }

    public void fillRoundRect(int x, int y, int width, int height, int arcWidth, int arcHeight) {
        addToReplay(FILL_ROUND_RECT, x, y, width, height, arcWidth, arcHeight);
        g.fillRoundRect(x, y, width, height, arcWidth, arcHeight);
    }

    public void drawOval(int x, int y, int width, int height) {
        addToReplay(DRAW_OVAL, x, y, width, height);
        g.drawOval(x, y, width, height);
    }

    public void fillOval(int x, int y, int width, int height) {
        addToReplay(FILL_OVAL, x, y, width, height);
        g.fillOval(x, y, width, height);
    }

    public void drawArc(int x, int y, int width, int height, int startAngle, int arcAngle) {
        addToReplay(DRAW_ARC, x, y, width, height, startAngle, arcAngle);
        g.drawArc(x, y, width, height, startAngle, arcAngle);
    }

    public void fillArc(int x, int y, int width, int height, int startAngle, int arcAngle) {
        addToReplay(FILL_ARC, x, y, width, height, startAngle, arcAngle);
        g.fillArc(x, y, width, height, startAngle, arcAngle);
    }

    public void drawPolyline(int[] xPoints, int[] yPoints, int nPoints) {
        addToReplay(DRAW_POLYLINE, xPoints, yPoints, nPoints);
        g.drawPolyline(xPoints, yPoints, nPoints);
    }

    public void drawPolygon(int[] xPoints, int[] yPoints, int nPoints) {
        addToReplay(DRAW_POLYGON, xPoints, yPoints, nPoints);
        g.drawPolygon(xPoints, yPoints, nPoints);
    }

    public void fillPolygon(int[] xPoints, int[] yPoints, int nPoints) {
        addToReplay(FILL_POLYGON, xPoints, yPoints, nPoints);
        g.fillPolygon(xPoints, yPoints, nPoints);
    }

    public boolean drawImage(Image img, int x, int y, ImageObserver observer) {
        addToReplay(DRAW_IMAGE3, img, x, y, observer);
        return g.drawImage(img, x, y, observer);
    }

    public boolean drawImage(Image img, int x, int y, int width, int height, ImageObserver observer) {
        addToReplay(DRAW_IMAGE4, img, x, y, width, height, observer);
        return g.drawImage(img, x, y, width, height, observer);
    }

    public boolean drawImage(Image img, int x, int y, Color bgcolor, ImageObserver observer) {
        addToReplay(DRAW_IMAGE5, img, x, y, bgcolor, observer);
        return g.drawImage(img, x, y, bgcolor, observer);
    }

    public boolean drawImage(Image img, int x, int y, int width, int height, Color bgcolor, ImageObserver observer) {
        addToReplay(DRAW_IMAGE6, img, x, y, width, height, bgcolor, observer);
        return g.drawImage(img, x, y, width, height, bgcolor, observer);
    }

    public boolean drawImage(Image img, int dx1, int dy1, int dx2, int dy2, int sx1, int sy1, int sx2, int sy2, ImageObserver observer) {
        addToReplay(DRAW_IMAGE7, img, dx1, dy1, dx2, dy2, sx1, sy1, sx2, sy2, observer);
        return g.drawImage(img, dx1, dy1, dx2, dy2, sx1, sy1, sx2, sy2, observer);
    }

    public boolean drawImage(Image img, int dx1, int dy1, int dx2, int dy2, int sx1, int sy1, int sx2, int sy2, Color bgcolor, ImageObserver observer) {
        addToReplay(DRAW_IMAGE8, img, dx1, dy1, dx2, dy2, sx1, sy1, sx2, sy2, bgcolor, observer);
        return g.drawImage(img, dx1, dy1, dx2, dy2, sx1, sy1, sx2, sy2, bgcolor, observer);
    }

    public void drawRect(int x, int y, int w, int h) {
        addToReplay(DRAW_RECT, x, y, w, h);
        g.drawRect(x, y, w, h);
    }

    public void dispose() {
        g.dispose();
    }
}
