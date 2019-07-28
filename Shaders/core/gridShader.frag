#version 440 core
out vec4 FragColor;

in vec2 TexCoords;
uniform sampler2D gridTexture;

void main()
{
    FragColor = texture(gridTexture, TexCoords);
}

