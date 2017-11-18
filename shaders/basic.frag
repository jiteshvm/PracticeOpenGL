#version 330 core
out vec4 FragColor;
  
in vec4 vertexColor; // the input variable from the vertex shader (same name and same type)  
in vec3 vertexPosition;
in vec2 TexCoord;
uniform vec4 uniformColor;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    //FragColor = vertexColor;
    //FragColor = uniformColor;
    //FragColor = vec4(vertexPosition, 1.0);
    FragColor = texture(texture2, TexCoord) * vec4(vertexPosition, 1.0);
} 