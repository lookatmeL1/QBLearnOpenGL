#version 330 core
in vec3 aPos;
in vec2 aUV;
out vec4 m_color;
out vec2 uv;
void main()
{
	 gl_Position = vec4(aPos, 1.0f);
	 m_color = vec4(1.0f, 0.5f, 0.2f, 1f);
	 uv = aUV;
}