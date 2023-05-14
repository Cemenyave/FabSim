#include "iostream"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <gl/gl.h>
#include <stdint.h>

#define __STDC_WANT_LIB_EXT1__ 1;
#include <stdio.h>
#include <assert.h>

static constexpr int window_height = 600;
static constexpr int window_width = 800;

bool g_shouldClose = false;


float vertices[] = {
  -0.5f, -0.5f, 0.0f,
   0.5f, -0.5f, 0.0f,
   0.0f,  0.5f, 0.0f,
};

void CompileShaders(uint64_t& shader, const char* shaderPath, GLenum shaderType);

void windowCloseCallback(GLFWwindow* window)
{
  g_shouldClose = true;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

}

int main(int argc, const char** argv)
{
  if (glfwInit() == GLFW_FALSE)
  {
    const char * error = nullptr;
    int errorNumber = GLFW_NO_ERROR;
    errorNumber = glfwGetError(&error);
    std::cout << "Failed to initialize GLFW ("<< errorNumber << "): "
      << error
      << std::endl;
    return 1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  GLFWwindow* window = nullptr;
  window = glfwCreateWindow(window_width, window_height, "Fabric Simulator", nullptr, nullptr);
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failded to initialize GLAD" << std::endl;
    return 1;
  }

  glViewport(0, 0, window_width, window_height);

  glfwSetWindowCloseCallback(window, windowCloseCallback);
  glfwSetKeyCallback(window, keyCallback);

  uint64_t vertexShader;
  uint64_t fragmentShader;
  CompileShaders(vertexShader,   "../source/shaders/shader.vert", GL_VERTEX_SHADER);
  CompileShaders(fragmentShader, "../source/shaders/shader.frag", GL_FRAGMENT_SHADER);

  uint64_t shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // Check shader program status
  {
    GLint success;
    char log[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
      std::cout << "FAILURE!: shader program linking failed. Error log:" << std::endl;
      glGetProgramInfoLog(shaderProgram, 512, nullptr, log);
      std::cout << log << std::endl;
    }
    else
    {
      std::cout << "SUCCESS shader linkage" << std::endl;
    }
  }

  // Set up vertex buffer object
  GLuint VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  GLuint VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
  glEnableVertexAttribArray(0);

  glUseProgram(shaderProgram);

  while(true)
  {
    if (g_shouldClose)
    {
      break;
    }

    glfwPollEvents();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glfwTerminate();
  return 0;
}

void CompileShaders(uint64_t& shader, const char* shaderPath, GLenum shaderType)
{
  FILE* shaderFile;
  errno_t error = 0;
  error = fopen_s(&shaderFile, shaderPath, "rb");
  if (error != 0)
  {
    std::cout << "Failed to open shader file \"" << shaderPath << "\" , error code " << error;
    return;
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
}
