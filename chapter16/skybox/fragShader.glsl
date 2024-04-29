#version 430

layout (binding = 0) uniform sampler2D tex;

in vec2 uv;

out vec4 fragColor;

void main()
{
    fragColor = vec4(texture(tex, uv).rgb, 1.0);
}
