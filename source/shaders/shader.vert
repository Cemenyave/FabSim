#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec4 aColor;

uniform mat4x4 View;
uniform mat4x4 World;
uniform mat4x4 Projection;

out vec4 VertexColor;

void main()
{
  gl_Position = Projection * View * World * vec4(aPos, 1.0);
  VertexColor = aColor;
}
