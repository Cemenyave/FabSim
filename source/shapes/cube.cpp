#include "cube.h"
#include "glm/glm/ext/vector_float3.hpp"
#include <glm/glm/geometric.hpp>

//  
//     5      6
//     ______
//    /____/\
//  1\ \  \2\
//   \8\__\_\ 7
//   \/   \/
//  4----- 3

Mesh makeCube()
{
  glm::vec3 pos1{-0.5f,  0.5f,  0.5f};
  glm::vec3 pos2{ 0.5f,  0.5f,  0.5f};
  glm::vec3 pos3{ 0.5f, -0.5f,  0.5f};
  glm::vec3 pos4{-0.5f, -0.5f,  0.5f};
  glm::vec3 pos5{-0.5f,  0.5f, -0.5f};
  glm::vec3 pos6{ 0.5f,  0.5f, -0.5f};
  glm::vec3 pos7{ 0.5f, -0.5f, -0.5f};
  glm::vec3 pos8{-0.5f, -0.5f, -0.5f};
  glm::vec3 norm1 = glm::normalize(pos1);
  glm::vec3 norm2 = glm::normalize(pos2);
  glm::vec3 norm3 = glm::normalize(pos3);
  glm::vec3 norm4 = glm::normalize(pos4);
  glm::vec3 norm5 = glm::normalize(pos5);
  glm::vec3 norm6 = glm::normalize(pos6);
  glm::vec3 norm7 = glm::normalize(pos7);
  glm::vec3 norm8 = glm::normalize(pos8);
  Mesh cube;
  cube.setVertices(
    {
     //position                normal                     R    G    B    A
      {pos1.x, pos1.y, pos1.z, norm1.x, norm1.y, norm1.z, 0.f, 1.f, 0.f, 0.f},
      {pos2.x, pos2.y, pos2.z, norm2.x, norm2.y, norm2.z, 0.f, 1.f, 0.f, 0.f},
      {pos3.x, pos3.y, pos3.z, norm3.x, norm3.y, norm3.z, 0.f, 1.f, 0.f, 0.f},
      {pos4.x, pos4.y, pos4.z, norm4.x, norm4.y, norm4.z, 0.f, 1.f, 0.f, 0.f},
      {pos5.x, pos5.y, pos5.z, norm5.x, norm5.y, norm5.z, 1.f, 1.f, 1.f, 0.f},
      {pos6.x, pos6.y, pos6.z, norm6.x, norm6.y, norm6.z, 1.f, 1.f, 1.f, 0.f},
      {pos7.x, pos7.y, pos7.z, norm7.x, norm7.y, norm7.z, 1.f, 1.f, 1.f, 0.f},
      {pos8.x, pos8.y, pos8.z, norm8.x, norm8.y, norm8.z, 1.f, 1.f, 1.f, 0.f},
    },

    {
      5,4,6,
      4,7,6,

      1,5,6,
      6,2,1,

      0,4,5,
      5,1,0,

      3,7,6,
      6,2,3,

      4,0,7,
      0,3,7,

      0,1,3,
      3,1,2,
     }
  );
  cube.init();
  return cube;
}
