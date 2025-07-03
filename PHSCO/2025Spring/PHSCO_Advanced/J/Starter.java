import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class Starter {
    static BufferedImage input, output;
    static File inputFile, outputFile;

    static final String INPUT_PATH = "casinofiles_std/barcodes.png";
    static final String OUTPUT_PATH = "casinofiles_std/output.png";

    public static void initIO() throws IOException {
        inputFile = new File(INPUT_PATH);
        outputFile = new File(OUTPUT_PATH);
        input = ImageIO.read(inputFile);
        output = new BufferedImage(input.getWidth(), input.getHeight(), BufferedImage.TYPE_INT_RGB);
    }

    public static int[] getPixel(int r, int c) {
        int rgb = input.getRGB(c, r);
        return new int[]{(rgb >> 16) & 255, (rgb >> 8) & 255, rgb & 255};
    }

    public static void setPixel(int r, int c, int[] rgb) {
        int val = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
        output.setRGB(c, r, val);
    }

    public static void writeOutput() throws IOException {
        ImageIO.write(output, "png", outputFile);
    }

    public static void main(String[] args) throws IOException {
        initIO();
        int h = input.getHeight(), w = input.getWidth();

        for (int r = 0; r < h; ++r)
            for (int c = 0; c < w; ++c)
                setPixel(r, c, getPixel(r, c));

        writeOutput();
    }
}
