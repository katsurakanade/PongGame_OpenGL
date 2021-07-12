#version 330 core

struct Material{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec2 TexCoord;
in vec3 Normal;
in vec3 Fragpos;

out vec4 color;

uniform sampler2D m_Tex;
uniform vec3 viewpos;
uniform vec3 BaseColor;
uniform Material material;
uniform Light light;

void main()
{
    // 環境光
    vec3 ambient = material.ambient * light.ambient;

    // 反射光
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - Fragpos);
    float diff = max(dot(norm,lightDir),0.0f);
    vec3 diffuse = (diff * material.diffuse) *  light.diffuse;

    // ハイライト
    vec3 vierDir = normalize(viewpos - Fragpos);
    vec3 reflectdir = reflect(-lightDir,norm);
    float spec = pow(max(dot(vierDir,reflectdir),0.0f),material.shininess);
    vec3 specular = (spec * material.specular)* light.specular;
    
    vec3 result = (ambient + diffuse + specular) * BaseColor;
    color = vec4(result,1.0f) * texture(m_Tex,TexCoord) ;

}