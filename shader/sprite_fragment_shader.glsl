in vec4 color_interp;
in vec2 uv_interp;

// Uniform to indicate if the object is in "ghost" mode
uniform bool is_ghost;

// Uniform to indicate if the texture should be tiled
uniform bool tile_texture;

// Texture sampler
uniform sampler2D onetex;

void main()
{
    // Sample texture with or without tiling based on the tile_texture uniform
    vec2 uv = uv_interp;
    if (tile_texture) {
        uv = uv_interp * 10; 
    }
    vec4 color = texture2D(onetex, uv); 

    // Convert an object to gray if it is a ghost
    if (is_ghost) {
        float gray = dot(color.rgb, vec3(0.3, 0.6, 0.1));
        color.rgb = vec3(gray);
    } 

    // Assign color to fragment
    gl_FragColor = vec4(color.rgb, color.a);

    // Check for transparency
    if(color.a < 0.1)
    {
         discard;
    }
}