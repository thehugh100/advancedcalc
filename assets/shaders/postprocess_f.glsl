
#version 400
out vec4 frag_colour;
in vec2 texCoord;

uniform vec3 col;
uniform sampler2D tex;

void main() {
  vec3 s = vec3(0);
  vec2 pixelSize = vec2(1.) / textureSize(tex, 0);

  int range = 2;
  int halfRange = range / 2;

  for(int y = -halfRange; y <= halfRange; y++) {
    for(int x = -halfRange; x <= halfRange; x++) {
      s += texture(tex, texCoord + vec2(x * pixelSize.y, y * pixelSize.y)).rgb;
    }
  }

  s /= pow(range, 2);

  frag_colour = vec4(s, 1.);
}
