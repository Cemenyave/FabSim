#pragma once

#include "glm/glm/ext/matrix_float4x4.hpp"
#include <iostream>
inline void print_mat(const glm::mat4& mat)
{
  std::cout << mat[0][0] << " " << mat[1][0] << " " << mat[2][0] << " " << mat[3][0] << std::endl <<
  mat[0][1] << " " << mat[1][1] << " " << mat[2][1] << " " << mat[3][1] << std::endl <<
  mat[0][2] << " " << mat[1][2] << " " << mat[2][2] << " " << mat[3][2] << std::endl <<
  mat[0][3] << " " << mat[1][3] << " " << mat[2][3] << " " << mat[3][3] << std::endl;
}
