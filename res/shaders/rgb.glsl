#shader vertex
#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec3 vertexColor;

out vec3 v_vertexColor;

void main()
{
   v_vertexColor = vertexColor;
   gl_Position = vec4(position, 0.0, 1.0);
};

#shader fragment
#version 330 core

in vec3 v_vertexColor;
layout(location = 0) out vec4 color;
uniform vec4 u_Color;

void main()
{
   color = vec4(v_vertexColor, 1.0);
};