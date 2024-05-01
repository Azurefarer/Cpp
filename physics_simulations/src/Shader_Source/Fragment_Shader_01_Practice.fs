#version 330 core
out vec4 FragColor;
in vec2 TexCoord;
in vec3 UV;
uniform sampler2D Texture01;
uniform sampler2D Texture02;

void main()
{
    // vec3 shift_UV = vec3(UV.x + 1.0, UV.y + 1.0, UV.z);

    FragColor = mix(texture(Texture01, TexCoord), texture(Texture02, TexCoord), 0.5);
}