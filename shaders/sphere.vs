#version 410 core
layout (location = 0) in vec3 vertexPosition;
//layout (location = 1) in vec3 vertexNormal;
//layout (location = 2) in vec2 vertexTexCoord;

out vec3 vPos;
//out vec2 texCoord;

uniform mat4 mvp;

void main()
{
    gl_Position = mvp * vec4(vertexPosition, 1.0);
    vPos = vertexPosition;
    //texCoord = vertexTexCoord;
}