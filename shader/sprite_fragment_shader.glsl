// Source code of fragment shader
#version 130

// Attributes passed from the vertex shader
in vec4 color_interp;
in vec2 uv_interp;

// Texture sampler
uniform sampler2D onetex;

uniform bool debug_mode;

void main()
{
	// Sample texture
	vec4 color;
	if (debug_mode && (uv_interp.x == 0 || uv_interp.y == 0 || uv_interp.x == 1 || uv_interp.y == 1)) {
		color = vec4(1.0, 1.0, 1.0, 1.0); // Highlight edges of render area
	} else {
		color = texture2D(onetex, uv_interp);
	}
	
	// Assign color to fragment
	gl_FragColor = vec4(color.r, color.g, color.b, color.a);
	
	// Check for transparency
	if(color.a < 1.0)
	{
		 discard;
	}
}
