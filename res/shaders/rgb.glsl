#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertexColor;

out vec3 v_vertexColor;

uniform mat4 m_MVP;

void main()
{
   v_vertexColor = vertexColor;
   gl_Position = m_MVP * vec4(position, 1.0);
}

#shader fragment
#version 330 core

in vec3 v_vertexColor;
layout(location = 0) out vec4 color;
uniform vec4 u_Color;
uniform float u_Time;

void main()
{
   float r = (sin(u_Time) + 1) / 2 * v_vertexColor.r;
   float g = (sin(u_Time + 20) + 1) / 2 * v_vertexColor.g;
   float b = (sin(u_Time + 40) + 1) / 2 * v_vertexColor.b;
   color = vec4(r, g, b, 1.0);
}