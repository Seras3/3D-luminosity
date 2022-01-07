// Shader-ul de fragment / Fragment shader  
#version 400

in vec4 ex_Color; 
out vec4 out_Color;

in vec2 tex_Coord;


uniform int tex_code;
uniform sampler2D myTexture;

uniform int codCol; 

void main(void)
  { 
	out_Color = ex_Color;

	if(tex_code == 1) {
		vec4 texColor =  texture(myTexture, tex_Coord);
		out_Color = texColor;
	}

	if ( codCol==1 )
		out_Color=vec4 (0.0, 0.0, 0.0, 0.0);
  }
 