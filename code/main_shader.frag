#version 330 core

out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform int has_color;
uniform int immune;
uniform vec3 color;

void main()
{
    vec4 objectColor;
    vec4 red = vec4(1.0, 0.0, 0.0, 1.0);
    if(has_color == 0)
    {
        objectColor = texture(texture1, TexCoord).xyzw; 
        if(objectColor.a < 0.5) discard;
    }
    else
    {
        objectColor = vec4(color, 1.0);
    }
    if(immune == 1)
    {
        FragColor = mix(objectColor, red, 0.5);
    }
    else
    {
        FragColor = objectColor;
    }
}
