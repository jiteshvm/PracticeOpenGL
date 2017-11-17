#version 330 core
out vec4 FragColor;
  
in vec4 vertexColor; // the input variable from the vertex shader (same name and same type)  
in vec3 vertexPosition;
uniform vec4 uniformColor;

void main()
{
    //FragColor = vertexColor;
    //FragColor = uniformColor;
    FragColor = vec4(vertexPosition, 1.0);
} 