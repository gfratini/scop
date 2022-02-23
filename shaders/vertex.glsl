#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

out float depth;

uniform mat4 transform;
uniform mat4 perspective;
uniform mat4 view;

void main()
{
    gl_Position = perspective * view * transform * vec4(aPos, 1.0f);
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
    depth = gl_Position.z;
}