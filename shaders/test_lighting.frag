#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 VertexWorldPos;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - VertexWorldPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diff * lightColor;

	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;
	vec3 result = ( ambient + diffuse )* objectColor;
    
	FragColor = vec4(result, 1.0f);
} 