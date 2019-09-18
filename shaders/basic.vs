#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec3 vertexPosition;
out vec2 TexCoord;

uniform mat4 transform;
uniform mat4 mvp_mat;
void main()
{
    gl_Position = mvp_mat * vec4(aPos, 1.0);
    vertexPosition = aPos;
    TexCoord = aTexCoord;
}