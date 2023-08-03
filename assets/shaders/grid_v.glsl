#version 400
in vec3 vp;
uniform mat4 mvp;
in vec2 aTexCoord;
out vec2 texCoord;

void main() {
    gl_Position = mvp * vec4(vp, 1.0);
    texCoord = aTexCoord;
}
