#include "../../include/Builders/ShaderBuilder.h"


ShaderBuilder& ShaderBuilder::createShader(int id, std::string refName , std::string fileName, bool core)
{
    resID = id;
    shaderFileName = fileName;
    shaderProgramName = refName;
    programID = 0;
    _uniformLocations.clear();
    shadersIDs.clear();
    return *this;
}

ShaderBuilder& ShaderBuilder::addShader(ShaderType shaderType, std::string fileName)
{
    std::string shaderRAWCode;
    std::ifstream shaderFile;
    //fileName = shaderFileName.empty() ? shaderProgramName : shaderFileName;
    

    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        if (!shaderFile.good())
            std::cout << "ERROR::SHADER::INPUTFILE_NOT_SUCCESFULLY_READ --> " << fileName << std::endl;

        std::string fileEXT;
        switch ( shaderType )
        {
        case ShaderType::VERTEX:
            fileEXT = ".vert";
            break;
        case ShaderType::FRAGMENT:
            fileEXT = ".frag";
            break;
        case ShaderType::GEOMETRY:
            fileEXT = ".geo";
            break;
        case ShaderType::COMPUTE:
            fileEXT = ".comp";
            break;
        case ShaderType::TESS_CONTROL:
            fileEXT = ".tesc";
            break;
        case ShaderType::TESS_EVAL:
            fileEXT = ".tesa";
            break;
        default:
            break;
        }

    std::filesystem::path filePath( fileName + fileEXT);
    std::filesystem::path fullbackfilePath( fileName + fileEXT);

        if (exists(filePath))
            shaderFile.open(filePath);
        else
            shaderFile.open(fullbackfilePath);

        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderRAWCode = shaderStream.str();
        shaderFile.close();
    }
    catch ( std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ --> " << fileName << std::endl;
    }

    const char* shaderCode = shaderRAWCode.c_str();
    unsigned int shaderID = glCreateShader(shaderType);
    int success;
    char infoLog[512];

    glShaderSource(shaderID, 1, &shaderCode, NULL);
    glCompileShader(shaderID);
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\t" << fileName << "\n\t" << infoLog << std::endl;
    }

    shadersIDs.push_back(shaderID);


    return *this;
}

Shader ShaderBuilder::build()
{
    int success;
    char infoLog[512];
    std::map<std::string, int> uniforms;

    programID = glCreateProgram();
    for ( auto shaderID : shadersIDs )
    {
        glAttachShader(programID, shaderID);
    }
    glLinkProgram(programID);

    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(programID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\t" << shaderProgramName << "\n\t" << infoLog << std::endl;
    }

    uniforms = findUniformLocations();
    for ( auto shaderID : shadersIDs )
    {
        glDeleteShader(shaderID);
    }
    
    return Shader(programID, shaderProgramName, uniforms);
}

std::map<std::string, int> ShaderBuilder::findUniformLocations()
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
    glGetProgramInterfaceiv( programID, GL_UNIFORM, GL_ACTIVE_RESOURCES, &numUniforms);

    GLenum properties[] = {GL_NAME_LENGTH, GL_TYPE, GL_LOCATION, GL_BLOCK_INDEX};

    for( GLint i = 0; i < numUniforms; ++i ) {
        GLint results[4];
        glGetProgramResourceiv(programID, GL_UNIFORM, i, 4, properties, 4, NULL, results);

        if( results[3] != -1 ) continue;  // Skip uniforms in blocks
        GLint nameBufSize = results[0] + 1;
        char * name = new char[nameBufSize];
        glGetProgramResourceName(programID, GL_UNIFORM, i, nameBufSize, NULL, name);
        _uniformLocations[name] = results[2];
        delete [] name;
    }
#endif

    return _uniformLocations;
}

