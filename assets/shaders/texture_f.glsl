#version 400
out vec4 frag_colour;
in vec2 texCoord;

uniform vec4 col;
uniform sampler2D tex;

void main() {
  frag_colour = col * texture(tex, texCoord);
}
