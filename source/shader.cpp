#include "shader.h"
#include "glad/glad.h"
#include "glm/glm/mat4x4.hpp"

#include "iostream"
#include <stdint.h>
#include <assert.h>

static bool compileShaders(uint64_t& shader, const char* shaderPath, GLenum shaderType)
{
  FILE* shaderFile;
  errno_t error = 0;
  error = fopen_s(&shaderFile, shaderPath, "rb");
  if (error != 0)
  {
    std::cout << "Failed to open shader file \"" << shaderPath << "\" , error code " << error;
    return false;
  }

  fseek(shaderFile, 0, SEEK_END);
  int64_t fileSize = ftell(shaderFile);
  char *shaderBuffer = new char[fileSize + 1];
  rewind(shaderFile);
  fread(shaderBuffer, sizeof(char), fileSize, shaderFile);
  shaderBuffer[fileSize] = '\0';

  shader = glCreateShader(shaderType);
  glShaderSource(shader, 1, &shaderBuffer, nullptr);
  glCompileShader(shader);

  GLint success;
  char log[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    std::cout << "FAILURE!: " << shaderPath << " shader compilation failed. Error log:" << std::endl;
    glGetShaderInfoLog(shader, 512, nullptr, log);
    std::cout << log << std::endl;
  }
  else
  {
    std::cout << "SUCCESS " << shaderPath << " shader compilde" << std::endl;
  }

  fclose(shaderFile);
  delete[] shaderBuffer;

  return success;
}

bool Shader::init(const char* vetexShaderFName, const char* fragmentShaderFName)
{
  // load and compile shaders from source
  uint64_t vertexShader;
  uint64_t fragmentShader;
  if (!compileShaders(vertexShader,   vetexShaderFName,    GL_VERTEX_SHADER))
  {
    return false;
  }

  if (!compileShaders(fragmentShader, fragmentShaderFName, GL_FRAGMENT_SHADER))
  {
    return false;
  }

  // link shader program
  m_programHandle = glCreateProgram();
  glAttachShader(m_programHandle, vertexShader);
  glAttachShader(m_programHandle, fragmentShader);
  glLinkProgram(m_programHandle);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // Check shader program status
  GLint success;
  char log[512];
  glGetProgramiv(m_programHandle, GL_LINK_STATUS, &success);
  if (!success)
  {
    std::cout << "FAILURE!: shader program linking failed. Error log:" << std::endl;
    glGetProgramInfoLog(m_programHandle, 512, nullptr, log);
    std::cout << log << std::endl;
  }
  else
  {
    std::cout << "SUCCESS shader linkage" << std::endl;
  }

  m_ready = success;
  return m_ready;
}

void Shader::SetUniformMat4x4(const char* uniformName, const glm::mat4x4& value)
{
 GLint UniformLocation = glGetUniformLocation(m_programHandle, uniformName);
 glUniformMatrix4fv(UniformLocation, 1, GL_FALSE, &value[0][0]);
}

void Shader::use()
{
  if (!m_ready)
  {
    std::cout << "Attempt to use bad shader" << std::endl;
    return;
  }
  assert(m_ready);
  glUseProgram(m_programHandle);
}
