// Source code of fragment shader
#version 130

// Attributes passed from the vertex shader
in vec4 color_interp;
in vec2 uv_interp;

// Texture sampler
uniform sampler2D onetex;

void main()
{
    vec4 color = vec4(1.0, 0.0, 0.0, 1.0);
    gl_FragColor = color;

    vec2 coord = uv_interp - vec2(0.5, 0.5);
    float r = 0.3;
    if (length(coord) > r){
        color.a = 0.0;
    }

    // Check for transparency
    if(color.a < 1.0)
    {
         discard;
    }
}
