#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;
in float depth;
uniform sampler2D tex;
uniform bool isWireframe;

void main()
{
    float light;
    if (!isWireframe) {
        light = (1 / (depth / 5)) ;
        if (light > 1)
            light = 1;
    } else {
        light = 1;
    }
    vec4 col = texture(tex, TexCoord) * light;
    FragColor = col;
}