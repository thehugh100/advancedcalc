#version 400

out vec4 frag_colour;
in vec2 texCoord;
uniform vec4 col;

void main() {
  vec2 uv = fract(texCoord * 10.);
  vec3 col = vec3(step(.99, uv.x) + step(.99, uv.y));
  frag_colour = vec4(col, 1.);
}
