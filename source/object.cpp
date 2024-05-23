#include "object.h"
#include "mesh.h"
#include <cassert>


Object::Object(Mesh&& mesh) : m_mesh(std::move(mesh))
{}

void Object::setTransform(glm::mat4x4 transform)
{
  m_transform = transform;
}

void Object::setScalse(glm::vec3)
{
  assert(false && "not implemented yet");
}

void Object::setPosition(glm::vec3)
{
  assert(false && "not implemented yet");
}

const Mesh& Object::getMesh() const
{
  return m_mesh;
}

glm::mat4x4 Object::getTransform() const
{
  return m_transform;
}
