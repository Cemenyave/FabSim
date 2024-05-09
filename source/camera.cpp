#include "camera.h"
#include "glm/glm/common.hpp"
#include "glm/glm/ext/matrix_clip_space.hpp"
#include "glm/glm/ext/matrix_float4x4.hpp"
#include "glm/glm/ext/scalar_constants.hpp"
#include "glm/glm/ext/vector_float3.hpp"
#include "glm/glm/matrix.hpp"
#include "glm/glm/trigonometric.hpp"

#include "debug_print.h"

glm::mat4x4 Camera::getToCameraMatrix() const
{
  return glm::inverse(m_transform);
}

glm::mat4x4 Camera::getCamereraProjectionMatrix() const
{
  glm::mat4x4 res = glm::perspective(glm::radians(110.f), 800.f/600.f, 0.5f, 100.f);
  return res;
}

void Camera::updateTransform()
{
  const float sinPitch = glm::sin(m_pitch);
  const float cosPitch = glm::cos(m_pitch);
  const float sinYaw = glm::sin(m_yaw);
  const float cosYaw = glm::cos(m_yaw);

  m_transform = glm::mat4x4{
    {cosYaw, 0.f, sinYaw, 0.f},
    {sinYaw * sinPitch, cosPitch, -sinPitch*cosYaw,         0.f},
    {-sinYaw * cosPitch, sinPitch, cosPitch * cosYaw, 0.f},
    { m_position, 1.f}
  };
}

void Camera::addPosition(glm::vec3 posDiff)
{
  m_position += posDiff.x * getRight();
  m_position += posDiff.y * getUp();
  m_position += posDiff.z * -getForward();
  updateTransform();
}

void Camera::setPosition(glm::vec3 newPos)
{
  m_position = newPos;
  updateTransform();
}

glm::vec3 Camera::getForward() const
{
  return {-m_transform[2][0], -m_transform[2][1], -m_transform[2][2]};
}

glm::vec3 Camera::getUp() const
{
  return {m_transform[1][0], m_transform[1][1], m_transform[1][2]};
}

glm::vec3 Camera::getRight() const
{
  return {m_transform[0][0], m_transform[0][1], m_transform[0][2]};
}

constexpr float normalizePitch(float pitch)
{
  constexpr float halfpi = glm::pi<float>() * 0.5f;

  //pitch should be in range [-pi/2, pi/2]
  return glm::clamp(pitch, -halfpi, halfpi);
}

constexpr float noralizeYaw(float yaw)
{
  constexpr float twopi = 2.f * glm::pi<float>();

  //make sure that we store yaw within [0, 2pi]
  yaw = yaw > twopi ? yaw - twopi :
    yaw < 0.f ? yaw + twopi : 
    yaw;

  return yaw;
}

void Camera::addRotation(float dyaw, float dpitch)
{
  m_yaw = noralizeYaw(m_yaw + dyaw);
  m_pitch = normalizePitch(m_pitch + dpitch);
  updateTransform();
}

void Camera::setRotation(float yaw, float pitch)
{
  m_yaw = noralizeYaw(yaw);
  m_pitch = normalizePitch(pitch);
  updateTransform();
}
