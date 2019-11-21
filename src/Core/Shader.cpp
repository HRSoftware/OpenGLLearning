
#include "../../include/Core/Shader.h"

Shader::Shader(std::string filename, bool bCore )
{
	if (bCore)
		filename = "core/" + filename;
	std::string filePath = "./Shaders/" + filename;
	std::string vertexCode;
	std::string fragCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{

		if (!vShaderFile.good())
		{
			std::cout << "ERROR::SHADER::VERTEX_FILE_NOT_SUCCESFULLY_READ --> " << filename << std::endl;
		}

		if (!fShaderFile.good())
		{
			std::cout << "ERROR::SHADER::FRAGMENT_FILE_NOT_SUCCESFULLY_READ --> " << filename << std::endl;
		}

		vShaderFile.open(filePath + ".vert");
		fShaderFile.open(filePath + ".frag");

		std::stringstream vShaderStream, fShaderStream;


		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ --> " << filename << std::endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragCode.c_str();

	unsigned int vertex, frag;
	int success;
	char infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\t" << filename << "\n\t" << infoLog << std::endl;
	};

	frag = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frag, 1, &fShaderCode, NULL);
	glCompileShader(frag);
	glGetShaderiv(frag, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(frag, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAG::COMPILATION_FAILED\t" << filename << "\n\t" << infoLog << std::endl;
	};


	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, frag);
	glLinkProgram(ID);

	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\t" << filename << "\n\t" << infoLog << std::endl;
	}

	findUniformLocations();
	_shaderName = filename;
	glDeleteShader(vertex);
	glDeleteShader(frag);
}

void Shader::reloadShaderFromFile(const char* fileName, bool isCoreShader = false)
{
	assert(fileName);
	GLuint reloadedProgram = Shader(fileName, isCoreShader).ID;

	if (reloadedProgram) {
		glDeleteProgram(ID);
		ID = reloadedProgram;
	}
}

void Shader::findUniformLocations()
{
	_uniformLocations.clear();

	GLint numUniforms = 0;
#ifdef __APPLE__
	// For OpenGL 4.1, use glGetActiveUniform
	GLint maxLen;
	GLchar *name;

	glGetProgramiv(handle, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLen);
	glGetProgramiv(handle, GL_ACTIVE_UNIFORMS, &numUniforms);

	name = new GLchar[maxLen];
	for (GLuint i = 0; i < numUniforms; ++i) {
		GLint size;
		GLenum type;
		GLsizei written;
		glGetActiveUniform(handle, i, maxLen, &written, &size, &type, name);
		GLint location = glGetUniformLocation(handle, name);
		uniformLocations[name] = glGetUniformLocation(handle, name);
	}
	delete[] name;
#else
	// For OpenGL 4.3 and above, use glGetProgramResource
	glGetProgramInterfaceiv( ID, GL_UNIFORM, GL_ACTIVE_RESOURCES, &numUniforms);

	GLenum properties[] = {GL_NAME_LENGTH, GL_TYPE, GL_LOCATION, GL_BLOCK_INDEX};

	for( GLint i = 0; i < numUniforms; ++i ) {
		GLint results[4];
		glGetProgramResourceiv(ID, GL_UNIFORM, i, 4, properties, 4, NULL, results);

		if( results[3] != -1 ) continue;  // Skip uniforms in blocks
		GLint nameBufSize = results[0] + 1;
		char * name = new char[nameBufSize];
		glGetProgramResourceName(ID, GL_UNIFORM, i, nameBufSize, NULL, name);
		_uniformLocations[name] = results[2];
		delete [] name;
	}
#endif
}

GLint Shader::getLocation(const std::string& name) const
{
	if(_uniformLocations.find(name) == _uniformLocations.end() )
	{
		std::cout << "Shader Attribute '" << name << "' not found in " << _shaderName << std::endl;
		return -1;
	}
	return  _uniformLocations.at(name);
}

