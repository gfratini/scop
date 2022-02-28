#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;
in float depth;
uniform sampler2D tex;
uniform bool isWireframe;
uniform float isSolid;
uniform float lightLevel;

void main()
{
    float light;
    vec4 col;
    if (!isWireframe) {
        light = (1 / (depth / lightLevel)) ;
        if (light > 1)
            light = 1;
    } else {
        light = 1;
    }
    col = texture(tex, TexCoord);

    FragColor = mix(col, vec4(1.0,1.0,1.0,1.0), isSolid) * light;
}