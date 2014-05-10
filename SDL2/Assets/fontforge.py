# -*- encoding: utf8 -*-
import PIL
from PIL import ImageFont
from PIL import Image
from PIL import ImageDraw


letters = '1234567890,.qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM'
font = ImageFont.truetype("DroidSans.ttf", 52)


for letter in letters:
	image = Image.new("RGBA", (64, 64), (0, 0, 0, 0))
	canvas = ImageDraw.Draw(image)
	(width, height) = canvas.textsize(letter, font=font)
	canvas.text((0, 0), letter, (20, 255, 20, 255), font=font)
	image.save("SpriteSheetContent/" + letter + ".png", format="png")
