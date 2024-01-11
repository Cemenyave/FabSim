#include "glm/glm/fwd.hpp"

class Shader
{
public:
  Shader() = default;
  bool init(const char* vetexShaderFName, const char* fragmentShaderFName);
  void use();
  void SetUniformMat4x4(const char* uniformName, const glm::mat4x4& value);

private:
  uint64_t m_programHandle = 0;
  bool m_ready = false;
};
