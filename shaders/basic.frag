#version 330 core
out vec4 FragColor;
  
in vec3 vertexPosition;
in vec2 TexCoord;

uniform sampler2D mainTexture;

void main()
{
    FragColor = texture(mainTexture, TexCoord);
} 