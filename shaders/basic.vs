#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec4 vertexColor; // specify a color output to the fragment shader
out vec3 vertexPosition;
out vec2 TexCoord;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(aPos, 1.0);
    vertexColor = vec4(aColor, 1.0);
    vertexPosition = aPos;
    TexCoord = aTexCoord;
    //vertexColor = vec4(0.5, 0.0, 0.0, 1.0);
}