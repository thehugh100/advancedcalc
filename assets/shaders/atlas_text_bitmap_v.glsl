#version 400
in vec3 vp;
in vec2 aTexCoord;
uniform mat4 mvp;

out vec2 texCoord;

void main() {
    gl_Position = mvp * vec4(vp, 1.0);
    texCoord = aTexCoord;
}