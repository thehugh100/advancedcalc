
#version 400
out vec4 frag_colour;
in vec2 texCoord;

uniform vec4 col;
uniform sampler2D tex;

void main() {
    float d = texture(tex, texCoord).r;
    float aaf = fwidth(d);
    float alpha = smoothstep(0.5 - aaf, 0.5 + aaf, d);
    frag_colour = vec4(col.rgb, alpha);
}