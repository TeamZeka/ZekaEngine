#ifdef ZK_OPENGLES
precision mediump float;
#endif

#define ZK_MAX_TEXTURES 16

out vec4 outColor;

in vec2 UV;
in vec4 Color;
in float TexIdx;

uniform sampler2D u_Textures[ZK_MAX_TEXTURES];

void main()
{
  vec4 texColor = Color;

  switch(int(TexIdx))
  {
  case  0: texColor *= texture(u_Textures[ 0], UV); break;
  case  1: texColor *= texture(u_Textures[ 1], UV); break;
  case  2: texColor *= texture(u_Textures[ 2], UV); break;
  case  3: texColor *= texture(u_Textures[ 3], UV); break;
  case  4: texColor *= texture(u_Textures[ 4], UV); break;
  case  5: texColor *= texture(u_Textures[ 5], UV); break;
  case  6: texColor *= texture(u_Textures[ 6], UV); break;
  case  7: texColor *= texture(u_Textures[ 7], UV); break;
  case  8: texColor *= texture(u_Textures[ 8], UV); break;
  case  9: texColor *= texture(u_Textures[ 9], UV); break;
  case 10: texColor *= texture(u_Textures[10], UV); break;
  case 11: texColor *= texture(u_Textures[11], UV); break;
  case 12: texColor *= texture(u_Textures[12], UV); break;
  case 13: texColor *= texture(u_Textures[13], UV); break;
  case 14: texColor *= texture(u_Textures[14], UV); break;
  case 15: texColor *= texture(u_Textures[15], UV); break;
  }

  outColor = texColor;
}
