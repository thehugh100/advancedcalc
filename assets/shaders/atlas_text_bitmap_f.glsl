
#version 400
out vec4 frag_colour;
in vec2 texCoord;

uniform vec4 col;
uniform sampler2D tex;
uniform vec4 atlasMetrics;
uniform float weight;

void main() {
    float d = texture(tex, (texCoord * atlasMetrics.zw) + atlasMetrics.xy).r;
    d = pow(d, (1.0/1.2));
    frag_colour = vec4(col.rgb, d);
}