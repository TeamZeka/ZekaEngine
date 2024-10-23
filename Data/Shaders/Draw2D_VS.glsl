in vec2 a_Pos;
in vec2 a_UV;
in vec4 a_Color;

uniform UBO
{
  mat4 ProjectionMatrix;
} u_Data;

out vec2 UV;
out vec4 Color;

void main()
{
  gl_Position = u_Data.ProjectionMatrix * vec4(a_Pos, 0.0, 1.0);

  UV = a_UV;
  Color = a_Color;
}
