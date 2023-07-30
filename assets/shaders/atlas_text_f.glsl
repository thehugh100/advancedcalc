
#version 400
out vec4 frag_colour;
in vec2 texCoord;

uniform vec4 col;
uniform sampler2D tex;
uniform vec4 atlasMetrics;
uniform float weight;

void main() {
    float d = texture(tex, (texCoord * atlasMetrics.zw) + atlasMetrics.xy).r;
    float aaf = fwidth(d);
    float alpha = smoothstep(0.5 - aaf, 0.5 + aaf, d + (1.-weight));
    frag_colour = vec4(col.rgb, pow(alpha, (1.0/1.2)) * col.a);
}