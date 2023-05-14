#include "iostream"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

static constexpr int window_height = 600;
static constexpr int window_width = 800;

bool g_shouldClose = false;


float vertices[] = {
  -0.5f, -0.5f, 0.0f,
   0.5f, -0.5f, 0.0f,
   0.0f,  0.5f, 0.0f,
};

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

  // Set up vertex buffer object
  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  while(true)
  {
    if (g_shouldClose)
    {
      break;
    }

    glfwPollEvents();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
  }

  glfwTerminate();
  return 0;
}
