#include "Includes.h"
#include "TextFactory.h"
#include <sstream>

pair<string, vector<float>> parse_line(string line);

TextFactory::TextFactory(void)
{

	//Load texture and save font description to TextureCoordinates
	ifstream description("Assets/font_description.txt");
	assert(description.is_open());
	string height_line;

	//Get font height	
	getline(description, height_line);
	auto height = parse_line(height_line);
	Height = height.second[0];

	string line;
	while(getline(description, line))
	{		
		auto token = parse_line(line);
		assert(token.first.length() == 1);
		assert(token.second.size() == 2);
		TextureCoordinates[token.first[0]] = pair<float, float>(token.second[0], token.second[1]);	
	}
	description.close();

	Texture = GLHelper::LoadTexture("Assets/droidsans.png");
	GLuint fragment_shader = GLHelper::LoadShader("Assets/FontFragmentShader.glsl", gl::FRAGMENT_SHADER);
	GLuint vertex_shader = GLHelper::LoadShader("Assets/FontVertexShader.glsl", gl::VERTEX_SHADER);
	Program = GLHelper::CreateProgram(fragment_shader, vertex_shader);

	XOffsetHandle = gl::GetUniformLocation(Program, "XOffset");
	YOffsetHandle = gl::GetUniformLocation(Program, "YOffset");
	ColorHandle = gl::GetUniformLocation(Program, "Color");
	TextureHandle = gl::GetUniformLocation(Program, "TextureSampler");
	CameraHandle = gl::GetUniformLocation(Program, "Camera");
	CheckGlErrors();
}

TextFactory::~TextFactory()
{
	FlushCache();
}

void TextFactory::FlushCache()
{
	gl::DeleteBuffers(buffers.size(), buffers.data());
	buffers.clear();

	for(auto &entry: Strings)
	{
		gl::DeleteVertexArrays(1, &entry.second);
	}
	Strings.clear();
}

pair<string, vector<float>> parse_line(string line)
{
	int token_starts = line.find_first_of('[') + 1;
	int token_ends = line.find_last_of(']') - 1;
	int values_start = line.find_last_of(':') + 2;

	string token = line.substr(token_starts, token_ends);
	string unsplitted_values = line.substr(values_start);
	istringstream values_stream(unsplitted_values);

	vector<float> values;
	float value;
	while(values_stream >> value)
	{
		values.emplace_back(value);
	}

	return pair<string, vector<float>>(token, values);
}

pair<float, float> TextFactory::Measure(string text)
{
	pair<float, float> dimensions(0.0f, Height);
	for(char& c : text)
	{
		auto location = TextureCoordinates[c];
		dimensions.first += location.second - location.first;
	}
	return dimensions;
}

void TextFactory::Prepare(string text)
{
	try
	{
		Strings.at(text);
	}
	catch(out_of_range&)
	{
		vector<float> uv_data;
		uv_data.reserve(text.length() * 6 * 2);
		vector<float> geometry_data;
		geometry_data.reserve(text.length() * 6 * 3);
		float cursor = 0;
		for(char& c: text)
		{
			auto uv = TextureCoordinates.at(c);
			//First triangle
			uv_data.emplace_back(uv.second);			uv_data.emplace_back(1.0f);
			uv_data.emplace_back(uv.first);			uv_data.emplace_back(0.0f);
			uv_data.emplace_back(uv.second);			uv_data.emplace_back(0.0f);
			//Second triangle
			uv_data.emplace_back(uv.second);			uv_data.emplace_back(1.0f);
			uv_data.emplace_back(uv.first);			uv_data.emplace_back(1.0f);
			uv_data.emplace_back(uv.first);			uv_data.emplace_back(0.0f);

			// geometry:
			float width = uv.second - uv.first;
			float left = cursor;
			float right = left + width;
			float bottom = 0;
			float top = 1;
			// first triangle
			geometry_data.emplace_back(right);			geometry_data.emplace_back(top);			geometry_data.emplace_back(0.0f);
			geometry_data.emplace_back(left);			geometry_data.emplace_back(bottom);			geometry_data.emplace_back(0.0f);
			geometry_data.emplace_back(right);			geometry_data.emplace_back(bottom);			geometry_data.emplace_back(0.0f);
			// second triangle
			geometry_data.emplace_back(right);			geometry_data.emplace_back(top);			geometry_data.emplace_back(0.0f);
			geometry_data.emplace_back(left);			geometry_data.emplace_back(top);			geometry_data.emplace_back(0.0f);
			geometry_data.emplace_back(left);			geometry_data.emplace_back(bottom);			geometry_data.emplace_back(0.0f);
			cursor += width;
		}
		for(auto &element : geometry_data)
		{
			element *= 500;
		}
		GLuint vao;
		GLuint vbouv;
		GLuint vbogeom;


		gl::GenVertexArrays(1, &vao);
		gl::BindVertexArray(vao);
		gl::GenBuffers(1, &vbouv);
		gl::BindBuffer(gl::ARRAY_BUFFER, vbouv);
		//Allocate memory
		gl::BufferData(gl::ARRAY_BUFFER, sizeof(float) * uv_data.size(), &uv_data[0], gl::STATIC_DRAW);
		gl::EnableVertexAttribArray(0);
		gl::VertexAttribPointer(0, 2, gl::FLOAT, gl::FALSE_, 0, 0);

		gl::GenBuffers(1, &vbogeom);
		gl::BufferData(gl::ARRAY_BUFFER, sizeof(float) * geometry_data.size(), &geometry_data[0], gl::STATIC_DRAW);

		gl::EnableVertexAttribArray(1);
		gl::VertexAttribPointer(1, 3, gl::FLOAT, gl::FALSE_, 0, 0);

		gl::BindVertexArray(0);
		buffers.emplace_back(vbouv);
		buffers.emplace_back(vbogeom);
		Strings[text] = vao;
	}
}

void TextFactory::RenderText(string text, float x, float y)
{
	DrawCall call = {text, x, y};
	drawCalls.emplace_back(call);
	Prepare(text);
}

void TextFactory::Render(glm::mat4 Camera)
{
	gl::UseProgram(Program);
	gl::ActiveTexture(gl::TEXTURE0);
	gl::BindTexture(gl::TEXTURE_2D, Texture);
	gl::Uniform1i(TextureHandle, 0);
	gl::Uniform3f(ColorHandle, 0.0f, 0.0f, 1.0f);
	gl::UniformMatrix4fv(CameraHandle, 1, 0, &Camera[0][0]);
	for(auto &call : drawCalls)
	{
		gl::Uniform1f(XOffsetHandle, call.x);
		gl::Uniform1f(YOffsetHandle, call.y);
		GLuint vao = Strings.at(call.text);
		gl::BindVertexArray(vao);		
		gl::DrawArrays(gl::TRIANGLES, 0, call.text.length() * 2 * 3);
		gl::BindVertexArray(0);
	}
	drawCalls.clear();
}