#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;
in float depth;
uniform sampler2D tex;

void main()
{
    float light = (15 / (depth * gl_FragCoord.z));
//    if (light > 1)
//        light = 1;
    vec4 col = texture(tex, TexCoord) * light;
    FragColor = col;
}