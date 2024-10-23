#ifdef ZK_OPENGLES
precision mediump float;
#endif

out vec4 outColor;

in vec2 UV;
in vec4 Color;

void main()
{
  outColor = Color;
}
