#include "glm/glm/ext/matrix_float4x4.hpp"
#include "glm/glm/ext/vector_float4.hpp"
#include "glm/glm/geometric.hpp"
#include "iostream"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <gl/gl.h>

#include "shader.h"
#include "mesh.h"
#include "camera.h"


#include <chrono>

static constexpr int window_height = 600;
static constexpr int window_width = 800;

bool g_shouldClose = false;


static void render(const Mesh& mesh, glm::mat4x4 worldTransform = {1.f}, Shader& shader, Camera& camera)
{
  //In order to render a mesh we need to
  // 1. Set shader program
  // 2. Set unifomr values (camera transfrom matrix, etc.)
  // 3. Switch vertex array to meshes VAO
  // 4. And, finally, call glDrawArrays()

  shader.use();
  shader.SetUniformMat4x4("View", camera.getToCameraMatrix());
  shader.SetUniformMat4x4("Porjection", glm::mat4x4(1.f));

  mesh.draw();
}


void windowCloseCallback(GLFWwindow* window)
{
  g_shouldClose = true;
}

void windowCursorPosCallback(GLFWwindow* window, double xPos, double yPos)
{
}

static bool g_camcontroll_move_up = false;
static bool g_camcontroll_move_down = false;
static bool g_camcontroll_move_left = false;
static bool g_camcontroll_move_right = false;


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_W)
  {
    g_camcontroll_move_up = action == GLFW_PRESS || action == GLFW_REPEAT;
  }

  if (key == GLFW_KEY_S)
  {
    g_camcontroll_move_down = action == GLFW_PRESS || action == GLFW_REPEAT;
  }

  if (key == GLFW_KEY_A)
  {
    g_camcontroll_move_left = action == GLFW_PRESS || action == GLFW_REPEAT;
  }

  if (key == GLFW_KEY_D)
  {
    g_camcontroll_move_right = action == GLFW_PRESS || action == GLFW_REPEAT;
  }

  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    g_shouldClose = true;
  }
}

int main(int argc, const char** argv)
{
  // init glfw
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
  }

  GLFWwindow* window = nullptr;

  // Create window
  {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(window_width, window_height, "Fabric Simulator", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
      std::cout << "Failded to initialize GLAD" << std::endl;
      return 1;
    }

    glViewport(0, 0, window_width, window_height);

    // subscribe to event from window
    glfwSetWindowCloseCallback(window, windowCloseCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetCursorPosCallback(window, windowCursorPosCallback);
  }

  Shader shader{};
  shader.init(
      "../source/shaders/shader.vert",
      "../source/shaders/shader.frag"
  );


  Mesh triangle;
  triangle.setVertices({
     //position          normal         R    G    B    A
    {-0.5f, -0.5f, 0.0f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f},
    { 0.5f, -0.5f, 0.0f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f},
    { 0.0f,  0.5f, 0.0f, 0.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f},
  });

  triangle.init();

  Camera camera;

  std::chrono::time_point<std::chrono::high_resolution_clock> currentTime = std::chrono::high_resolution_clock::now();

  while(true)
  {
    if (g_shouldClose)
    {
      break;
    }

    glfwPollEvents();

    std::chrono::time_point<std::chrono::high_resolution_clock> newTime = std::chrono::high_resolution_clock::now();

    //delta time in seconds
    float dt = std::chrono::duration<float>(newTime - currentTime).count();
    currentTime = newTime;

    // update
    {
      glm::vec3 inputDirection(0.0);
      if (g_camcontroll_move_up)
      {
        inputDirection.y += 1.0;
      }

      if (g_camcontroll_move_down)
      {
        inputDirection.y += -1.0;
      }

      if (g_camcontroll_move_left)
      {
        inputDirection.x += -1.0;
      }

      if (g_camcontroll_move_right)
      {
        inputDirection.x += 1.0;
      }

      glm::normalize(inputDirection);
      camera.addPosition(inputDirection * (dt * 0.3f));
    }

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    render(triangle, shader, camera);

    glfwSwapBuffers(window);
  }

  glfwTerminate();
  return 0;
}
