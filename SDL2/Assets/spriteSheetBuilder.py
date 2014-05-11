import PIL
import math
from PIL import Image
from PIL import ImageDraw
from os import listdir
from os.path import isfile, join

target = 'spritesheet'
source = 'SpriteSheetContent/'
spriteSize = 64

sourceFiles = [f for f in listdir(source) if isfile(join(source, f))]
spritesheetSize = pow(2, math.ceil(math.log(len(sourceFiles)**0.5) / math.log(2)))
print(sourceFiles)

'''
for letter in letters:
	image = Image.new("RGBA", (64, 64), (0, 0, 0, 0))
	canvas = ImageDraw.Draw(image)
	(width, height) = canvas.textsize(letter, font=font)
	canvas.text((0, 0), letter, (20, 255, 20, 255), font=font)
	image.save("SpriteSheetContent/" + letter + ".png", format="png")
'''