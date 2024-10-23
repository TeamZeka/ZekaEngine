in vec3 a_Pos;
in vec2 a_UV;
in vec4 a_Color;
in float a_TexIdx;

uniform UBO
{
  mat4 ProjectionViewMatrix;
} u_Data;

out vec2 UV;
out vec4 Color;
out float TexIdx;

void main()
{
  gl_Position = u_Data.ProjectionViewMatrix * vec4(a_Pos, 1.0);

  UV = a_UV;
  Color = a_Color;
  TexIdx = a_TexIdx;
}
