#include "Includes.h"
#include "SpriteRenderer.h"
#include "GLHelper.h"


SpriteRenderer::SpriteRenderer()
{
	Shader.init();
	texture = GLHelper::LoadTexture("Assets/font_0.png");
	glGenBuffers(2, buffers);

	// Who needs parsers.letters[32] = Glyph(1013, 0, 3, 1, -1, 99, 52);
	
letters[32] = Glyph(0, 500, 12, 63, 20, 17, 52);
letters[33] = Glyph(1000, 0, 12, 63, 20, 17, 52);
letters[34] = Glyph(636, 194, 34, 23, 9, 17, 52);
letters[35] = Glyph(611, 131, 53, 62, -1, 18, 52);
letters[36] = Glyph(122, 0, 41, 78, 6, 15, 52);
letters[37] = Glyph(665, 131, 51, 60, 1, 20, 52);
letters[38] = Glyph(717, 0, 51, 65, 1, 16, 52);
letters[39] = Glyph(671, 192, 12, 23, 20, 17, 52);
letters[40] = Glyph(164, 0, 24, 77, 15, 15, 52);
letters[41] = Glyph(189, 0, 24, 77, 12, 15, 52);
letters[42] = Glyph(477, 201, 43, 40, 4, 16, 52);
letters[43] = Glyph(317, 207, 48, 46, 2, 30, 52);
letters[44] = Glyph(568, 196, 18, 27, 15, 65, 52);
letters[45] = Glyph(774, 180, 28, 12, 12, 49, 52);
letters[46] = Glyph(710, 192, 16, 15, 18, 65, 52);
letters[47] = Glyph(405, 0, 44, 71, 4, 17, 52);
letters[48] = Glyph(88, 80, 43, 65, 4, 16, 52);
letters[49] = Glyph(362, 139, 42, 63, 7, 17, 52);
letters[50] = Glyph(472, 71, 41, 64, 4, 16, 52);
letters[51] = Glyph(132, 79, 43, 65, 4, 16, 52);
letters[52] = Glyph(140, 145, 45, 63, 4, 17, 52);
letters[53] = Glyph(429, 72, 42, 64, 5, 17, 52);
letters[54] = Glyph(44, 80, 43, 65, 5, 16, 52);
letters[55] = Glyph(447, 137, 41, 63, 5, 17, 52);
letters[56] = Glyph(176, 78, 42, 65, 5, 16, 52);
letters[57] = Glyph(0, 89, 43, 65, 4, 16, 52);
letters[58] = Glyph(460, 201, 16, 45, 18, 35, 52);
letters[59] = Glyph(995, 66, 19, 57, 15, 35, 52);
letters[60] = Glyph(413, 201, 46, 45, 3, 31, 52);
letters[61] = Glyph(521, 200, 46, 29, 3, 39, 52);
letters[62] = Glyph(366, 203, 46, 45, 3, 31, 52);
letters[63] = Glyph(554, 67, 37, 64, 9, 16, 52);
letters[64] = Glyph(309, 0, 50, 72, 0, 21, 52);
letters[65] = Glyph(751, 66, 50, 63, 1, 17, 52);
letters[66] = Glyph(0, 155, 46, 63, 4, 17, 52);
letters[67] = Glyph(262, 77, 40, 65, 6, 16, 52);
letters[68] = Glyph(186, 144, 44, 63, 5, 17, 52);
letters[69] = Glyph(405, 137, 41, 63, 6, 17, 52);
letters[70] = Glyph(489, 136, 40, 63, 7, 17, 52);
letters[71] = Glyph(910, 0, 44, 65, 4, 16, 52);
letters[72] = Glyph(319, 143, 42, 63, 5, 17, 52);
letters[73] = Glyph(571, 132, 39, 63, 6, 17, 52);
letters[74] = Glyph(514, 67, 39, 64, 4, 17, 52);
letters[75] = Glyph(802, 66, 48, 63, 4, 17, 52);
letters[76] = Glyph(530, 132, 40, 63, 9, 17, 52);
letters[77] = Glyph(94, 146, 45, 63, 3, 17, 52);
letters[78] = Glyph(231, 144, 43, 63, 4, 17, 52);
letters[79] = Glyph(818, 0, 46, 65, 3, 16, 52);
letters[80] = Glyph(275, 143, 43, 63, 6, 17, 52);
letters[81] = Glyph(262, 0, 46, 76, 3, 16, 52);
letters[82] = Glyph(900, 66, 47, 63, 5, 17, 52);
letters[83] = Glyph(219, 78, 42, 65, 5, 16, 52);
letters[84] = Glyph(47, 146, 46, 63, 3, 17, 52);
letters[85] = Glyph(384, 72, 44, 64, 4, 17, 52);
letters[86] = Glyph(851, 66, 48, 63, 2, 17, 52);
letters[87] = Glyph(592, 67, 54, 63, -1, 17, 52);
letters[88] = Glyph(700, 67, 50, 63, 1, 17, 52);
letters[89] = Glyph(647, 67, 52, 63, 0, 17, 52);
letters[90] = Glyph(948, 66, 46, 63, 4, 17, 52);
letters[91] = Glyph(238, 0, 23, 77, 17, 15, 52);
letters[92] = Glyph(360, 0, 44, 71, 4, 17, 52);
letters[93] = Glyph(214, 0, 23, 77, 12, 15, 52);
letters[94] = Glyph(587, 196, 48, 23, 2, 17, 52);
letters[95] = Glyph(803, 180, 54, 8, -1, 92, 52);
letters[96] = Glyph(684, 192, 25, 16, 8, 11, 52);
letters[97] = Glyph(853, 130, 44, 49, 3, 32, 52);
letters[98] = Glyph(541, 0, 43, 66, 6, 15, 52);
letters[99] = Glyph(898, 130, 39, 49, 6, 32, 52);
letters[100] = Glyph(585, 0, 43, 66, 3, 15, 52);
letters[101] = Glyph(760, 130, 46, 49, 3, 32, 52);
letters[102] = Glyph(344, 73, 39, 65, 7, 15, 52);
letters[103] = Glyph(496, 0, 44, 66, 3, 32, 52);
letters[104] = Glyph(303, 77, 40, 65, 6, 15, 52);
letters[105] = Glyph(450, 0, 45, 70, 5, 10, 52);
letters[106] = Glyph(0, 0, 31, 88, 5, 10, 52);
letters[107] = Glyph(955, 0, 44, 65, 7, 15, 52);
letters[108] = Glyph(865, 0, 44, 65, 3, 15, 52);
letters[109] = Glyph(0, 219, 46, 48, 3, 32, 52);
letters[110] = Glyph(978, 130, 40, 48, 6, 32, 52);
letters[111] = Glyph(807, 130, 45, 49, 3, 32, 52);
letters[112] = Glyph(673, 0, 43, 66, 6, 32, 52);
letters[113] = Glyph(629, 0, 43, 66, 3, 32, 52);
letters[114] = Glyph(87, 210, 38, 48, 11, 32, 52);
letters[115] = Glyph(938, 130, 39, 49, 7, 32, 52);
letters[116] = Glyph(717, 131, 42, 60, 4, 20, 52);
letters[117] = Glyph(47, 210, 39, 48, 6, 33, 52);
letters[118] = Glyph(229, 208, 46, 47, 3, 33, 52);
letters[119] = Glyph(126, 210, 53, 47, -1, 33, 52);
letters[120] = Glyph(180, 209, 48, 47, 2, 33, 52);
letters[121] = Glyph(769, 0, 48, 65, 2, 33, 52);
letters[122] = Glyph(276, 207, 40, 47, 6, 33, 52);
letters[123] = Glyph(44, 0, 38, 79, 7, 15, 52);
letters[124] = Glyph(32, 0, 11, 85, 20, 15, 52);
letters[125] = Glyph(83, 0, 38, 79, 7, 15, 52);
letters[126] = Glyph(727, 192, 46, 14, 3, 46, 52);



}


void SpriteRenderer::Render(glm::vec2 position, float size, int texturePosition)
{
	Render(position.x, position.y, size, texturePosition);
}

void SpriteRenderer::Render(float x, float y, float size, int texturePosition)
{
	this->InsertTextureCoordinates(texturePosition);
	this->InsertCoordinates(x, y, size);
}

void SpriteRenderer::Flip(glm::mat4 Projection, glm::mat4 View)
{
	if(CoordinateBuffer.size() > 0) 
	{
	
		//Fill buffers
		
		glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * CoordinateBuffer.size(), &CoordinateBuffer[0], GL_STREAM_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

		glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * TextureBuffer.size(), &TextureBuffer[0], GL_STREAM_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture);

		Shader.begin();
		Shader.setModel(glm::mat4());
		Shader.setProjection(Projection);	
		Shader.setView(View);
		Shader.setTexture(1);

		glDrawArrays(GL_TRIANGLES, 0, TextureBuffer.size());

		TextureBuffer.clear();
		CoordinateBuffer.clear();
	}
}

SpriteRenderer::~SpriteRenderer()
{
	glDeleteBuffers(2, buffers);
}

void SpriteRenderer::RenderText(float x, float y, string text)
{
	const char* cstring = text.c_str();
	int letterCount = text.size();
	
	float cursor_x = x;
	float cursor_y = y;

	for(int i = 0; i < letterCount; i++)
	{
		Glyph glyph = letters[cstring[i]];
		InsertTextureCoordinates(glyph.x, glyph.y, glyph.width, glyph.height);
		float scale = 300;
		InsertCoordinates(
			cursor_x + glyph.xoffset * scale,
			cursor_x + (glyph.xoffset + glyph.width) * scale,
			cursor_y - (glyph.height + glyph.yoffset) * scale,
			cursor_y - (glyph.yoffset) * scale);
		cursor_x += glyph.xadvance * scale;
	}

}

void SpriteRenderer::InsertTextureCoordinates(float x, float y, float width, float height)
{
	TextureBuffer.emplace_back(x + width);
	TextureBuffer.emplace_back(y + height);
	TextureBuffer.emplace_back(x);
	TextureBuffer.emplace_back(y + height);
	TextureBuffer.emplace_back(x);
	TextureBuffer.emplace_back(y);

	TextureBuffer.emplace_back(x + width);
	TextureBuffer.emplace_back(y + height);
	TextureBuffer.emplace_back(x);
	TextureBuffer.emplace_back(y);
	TextureBuffer.emplace_back(x + width);
	TextureBuffer.emplace_back(y);


}

void SpriteRenderer::InsertCoordinates(float left, float right, float bottom, float top)
{
	CoordinateBuffer.emplace_back(right);
	CoordinateBuffer.emplace_back(bottom);
	CoordinateBuffer.emplace_back(0.0f);
	CoordinateBuffer.emplace_back(left);
	CoordinateBuffer.emplace_back(bottom);
	CoordinateBuffer.emplace_back(0.0f);
	CoordinateBuffer.emplace_back(left);
	CoordinateBuffer.emplace_back(top);
	CoordinateBuffer.emplace_back(0.0f);

	CoordinateBuffer.emplace_back(right);
	CoordinateBuffer.emplace_back(bottom);
	CoordinateBuffer.emplace_back(0.0f);
	CoordinateBuffer.emplace_back(left);
	CoordinateBuffer.emplace_back(top);
	CoordinateBuffer.emplace_back(0.0f);
	CoordinateBuffer.emplace_back(right);
	CoordinateBuffer.emplace_back(top);
	CoordinateBuffer.emplace_back(0.0f);


}

void SpriteRenderer::InsertTextureCoordinates(int texturePosition)
{
	assert(texturePosition < ROW_COUNT * COLLUMN_COUNT);
	int collumn = texturePosition % ROW_COUNT;
	int row = texturePosition / COLLUMN_COUNT;
	float height = 1.0f / ROW_COUNT;
	float width = 1.0f / COLLUMN_COUNT;

	float x = collumn * width;
	float y = row * height;

	/*
	float UV[] = {
		x + width, y + height,
		x + 0.0f,  y + 0.0f,
		x + width, y + 0.0f,
		x + width, y + height,
		x + 0.0f,  y + height,
		x + 0.0f,  y + 0.0f,
	};
	*/
	InsertTextureCoordinates(x, y, width, height);
}

void SpriteRenderer::InsertCoordinates(float x, float y, float size)
{
	/*
	float SquareCoordinateArray[] = {
		0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
	};
	*/
	float left = x - size / 2;
	float right = x + size / 2;
	float top = y - size / 2;
	float bottom = y + size / 2; 

	InsertCoordinates(left, right, bottom, top);
}