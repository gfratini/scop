#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D tex;

void main()
{
    vec4 col = texture(tex, TexCoord);
    if (col.a < 0.1)
        discard;
    FragColor = col;
}