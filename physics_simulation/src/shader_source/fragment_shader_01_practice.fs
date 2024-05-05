#version 330 core
out vec4 FragColor;
in vec2 TexCoord;
in vec3 UV;
// uniform sampler2D Texture01;
// uniform sampler2D Texture02;

void main()
{
    FragColor = vec4(0.2, 0.8863, 0.349, 1.0);
    // FragColor = mix(texture(Texture01, TexCoord), texture(Texture02, TexCoord), 0.5);
}