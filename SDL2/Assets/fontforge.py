# -*- encoding: utf8 -*-
import PIL
from PIL import ImageFont
from PIL import Image
from PIL import ImageDraw


letters = ' 1234567890,.;:"\'qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM'
description = open('font_description.txt', 'w')
font = ImageFont.truetype("DroidSans.ttf", 32)
image = Image.new("RGBA", (2048, 64), (0, 0, 0, 0))
canvas = ImageDraw.Draw(image)
cursor = 0
total_width = 2048
description.write('[height]: {}\n'.format(32/total_width))

def describe(letter, start, end):
	start = start / total_width
	end = end / total_width
	description.write('[{}]: {} {}\n'.format(letter, start, end))

for letter in letters:
	(width, height) = canvas.textsize(letter, font=font)
	describe(letter, width, cursor + width)
	canvas.text((cursor, 0), letter, (255, 255, 255, 255), font=font)
	cursor = cursor + width

print(cursor)
image.save("DroidSans.png")
