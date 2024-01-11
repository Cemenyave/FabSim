#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec4 aColor;

uniform mat4x4 View;

out vec4 VertexColor;

void main()
{
  gl_Position = View * vec4(aPos.x, aPos.y, aPos.z, 1.0);
  VertexColor = aColor;
}
