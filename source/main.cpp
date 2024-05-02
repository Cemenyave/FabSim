#include "glm/glm/ext/matrix_float4x4.hpp"
#include "glm/glm/ext/matrix_transform.hpp"
#include "glm/glm/ext/vector_float2.hpp"
#include "glm/glm/ext/vector_float3.hpp"
#include "glm/glm/geometric.hpp"
#include "iostream"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <gl/gl.h>

#include "shader.h"
#include "mesh.h"
#include "camera.h"

#include "debug_print.h"

#include <chrono>
#include <ostream>

static constexpr int window_height = 600;
static constexpr int window_width = 800;

bool g_shouldClose = false;


// OpenGL uses right-hand system in 3D space
//    y^
//     |
//     |
//     |
//     -------->
//    /        x
//   /
//  v x
//
// In 2D screen space left-hand system
//  y^
//   |  A Z
//   | /
//   |/
//   -------->
//            x
//


static void render(const Mesh& mesh, const glm::mat4x4& worldTransform, Shader& shader, Camera& camera)
{
  //In order to render a mesh we need to
  // 1. Set shader program
  // 2. Set unifomr values (camera transfrom matrix, etc.)
  // 3. Switch vertex array to meshes VAO
  // 4. And, finally, call glDrawArrays()

  shader.use();
  shader.SetUniformMat4x4("View", camera.getToCameraMatrix());
  shader.SetUniformMat4x4("Projection", camera.getCamereraProjectionMatrix());
  shader.SetUniformMat4x4("World", worldTransform);

  mesh.draw();
}

struct ControlState
{
  bool m_cam_move_up = false;
  bool m_cam_move_down = false;
  bool m_cam_move_left = false;
  bool m_cam_move_right = false;
  bool m_cam_move_forward = false;
  bool m_cam_move_back = false;
  glm::vec2 m_mouseDelta = {0.f, 0.f};
} static g_congrolState;

void windowCloseCallback(GLFWwindow* window)
{
  g_shouldClose = true;
}

static void windowCursorPosCallback(GLFWwindow* window, double xPos, double yPos)
{
  static glm::vec2 s_prevMousePos = {0.f, 0.f};
  glm::vec2 curMousePos = {xPos, yPos};
  g_congrolState.m_mouseDelta += curMousePos - s_prevMousePos;
  s_prevMousePos = curMousePos;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_W)
  {
    g_congrolState.m_cam_move_forward = action == GLFW_PRESS || action == GLFW_REPEAT;
  }

  if (key == GLFW_KEY_S)
  {
    g_congrolState.m_cam_move_back = action == GLFW_PRESS || action == GLFW_REPEAT;
  }

  if (key == GLFW_KEY_A)
  {
    g_congrolState.m_cam_move_left = action == GLFW_PRESS || action == GLFW_REPEAT;
  }

  if (key == GLFW_KEY_D)
  {
    g_congrolState.m_cam_move_right = action == GLFW_PRESS || action == GLFW_REPEAT;
  }

  if (key == GLFW_KEY_Q)
  {
    g_congrolState.m_cam_move_up = action == GLFW_PRESS || action == GLFW_REPEAT;
  }

  if (key == GLFW_KEY_E)
  {
    g_congrolState.m_cam_move_down = action == GLFW_PRESS || action == GLFW_REPEAT;
  }

  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    g_shouldClose = true;
  }
}

void mouseKeyCallback(GLFWwindow* window, int button, int action, int mods)
{
}

void updateCamera(float dt, Camera& camera)
{
  glm::vec3 inputDirection(0.0);
  if (g_congrolState.m_cam_move_up)
  {
    inputDirection.y += 1.0;
  }

  if (g_congrolState.m_cam_move_down)
  {
    inputDirection.y += -1.0;
  }

  if (g_congrolState.m_cam_move_left)
  {
    inputDirection.x += -1.0;
  }

  if (g_congrolState.m_cam_move_right)
  {
    inputDirection.x += 1.0;
  }

  if (g_congrolState.m_cam_move_forward)
  {
    inputDirection.z -= 1.0;
  }

  if (g_congrolState.m_cam_move_back)
  {
    inputDirection.z += 1.0;
  }

  glm::normalize(inputDirection);
  camera.addPosition(inputDirection * (dt * 0.3f));

  if (g_congrolState.m_mouseDelta.x != 0.f || g_congrolState.m_mouseDelta.y != 0.f)
  {
    const static glm::vec2 s_mouseSens = {0.01f , 0.01f};
    glm::vec2 inputRotation = g_congrolState.m_mouseDelta * s_mouseSens;
    camera.addRotation(inputRotation.x, inputRotation.y);
    g_congrolState.m_mouseDelta = {0.f, 0.f};
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

    // subscribe to event from window
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetWindowCloseCallback(window, windowCloseCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseKeyCallback);
    glfwSetCursorPosCallback(window, windowCursorPosCallback);

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
      std::cout << "Failded to initialize GLAD" << std::endl;
      return 1;
    }

    glViewport(0, 0, window_width, window_height);
    glEnable(GL_DEPTH_TEST);
  }

  Shader shader{};
  shader.init(
      "../source/shaders/shader.vert",
      "../source/shaders/shader.frag"
  );


  Mesh triangle;
  triangle.setVertices(
    {
       //position          normal         R    G    B    A
      {-0.5f, -0.5f, 0.0f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f},
      { 0.5f, -0.5f, 0.0f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f},
      { 0.0f,  0.5f, 0.0f, 0.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f},
    },
    {0, 1, 2}
  );

  triangle.init();

  print_mat(glm::mat4x4{1.f});
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

    updateCamera(dt, camera);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4x4 world{1.f};
    world = glm::translate(world, {0.f, 0.f, -1.f});
    render(triangle, world, shader, camera);

    glfwSwapBuffers(window);
  }

  glfwTerminate();
  return 0;
}
