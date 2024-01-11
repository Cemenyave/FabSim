#include "camera.h"
#include "glm/glm/ext/matrix_float4x4.hpp"
#include "glm/glm/ext/scalar_constants.hpp"
//#include "glm/glm/ext/vector_float4.hpp"
//#include "glm/glm/fwd.hpp"
#include "glm/glm/trigonometric.hpp"

glm::mat4x4 Camera::getToCameraMatrix() const
{
  const float sinPitch = glm::sin(m_pitch);
  const float cosPitch = glm::cos(m_pitch);
  const float sinYaw = glm::sin(m_yaw);
  const float cosYaw = glm::cos(m_yaw);

  return {
    {cosYaw, sinPitch * sinYaw, -cosPitch * sinYaw, 0},
    {0, cosPitch, sinPitch, 0},
    {sinYaw, -sinPitch*cosYaw, cosPitch, cosYaw},

    //set translation component
    //it's negative position vector because in order to
    //translate point from world space to 
    //another objects local space we should subtract
    { -m_position, 1.0 }
  };
}

void Camera::addPosition(glm::vec3 posDiff)
{
  m_position += posDiff;
}

void Camera::setPosition(glm::vec3 newPos)
{
  m_position = newPos;
}

constexpr float normalizePitch(float pitch)
{
  constexpr float pi = 2 * glm::pi<float>();

  //pitch should be in range [-pi, pi]
  return pitch > pi ? pi :
    pitch < -pi ? -pi :
    pitch;
}

constexpr float noralizeYaw(float yaw)
{
  constexpr float twopi = 2 * glm::pi<float>();

  //make sure that we store yaw within [-2pi, 2pi]
  yaw = yaw > twopi ? yaw - twopi :
    yaw < -twopi ? yaw + twopi : 
    yaw;

  //and count rotation only clockwise
  if (yaw < 0.f)
  {
    yaw = twopi - yaw;
  }

  return yaw;
}

void Camera::addRotation(float dyaw, float dpitch)
{
  m_yaw = noralizeYaw(m_yaw + dyaw);
  m_pitch = normalizePitch(m_pitch + dpitch);
}

void Camera::setRotation(float yaw, float pitch)
{
  m_yaw = noralizeYaw(yaw);
  m_pitch = normalizePitch(pitch);
}
