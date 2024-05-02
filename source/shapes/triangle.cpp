#include "triangle.h"

Mesh makeTriangle()
{
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
  return triangle;
}
