#ifdef ZK_OPENGLES
precision mediump float;
#endif

out vec4 outColor;

in vec2 UV;
in vec4 Color;

uniform sampler2D u_Texture;

void main()
{
  vec4 totalColor = Color;
  totalColor.a *= texture(u_Texture, UV).r;
  outColor = totalColor;
}
