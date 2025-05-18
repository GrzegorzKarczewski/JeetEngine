#version 330 core
in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform sampler2D texture_diffuse1;

// Light properties
uniform vec3 lightPos;
uniform vec3 lightColor;

// View position
uniform vec3 viewPos;

void main()
{
    // Ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 lighting = (ambient + diffuse + specular);
    vec3 textureColor = texture(texture_diffuse1, TexCoords).rgb;

    FragColor = vec4(lighting * textureColor, 1.0);
}
