# run `pip install Pillow` beforehand
from PIL import Image
import os

input_path = os.path.join(os.getcwd(), "casinofiles/barcodes.png")
output_path = os.path.join(os.getcwd(), "casinofiles/output.png")

_input = Image.open(input_path).convert("RGB")
_width, _height = _input.size
_output = Image.new("RGB", (_width, _height))

def get_pixel(r, c):
    return _input.getpixel((c, r))

def set_pixel(r, c, rgb):
    _output.putpixel((c, r), tuple(rgb))

def write_output():
    _output.save(output_path)


for r in range(_height):
    for c in range(_width):
        rgb = get_pixel(r, c)
        set_pixel(r, c, rgb)

write_output()
