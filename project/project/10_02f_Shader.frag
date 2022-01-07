// Shader-ul de fragment / Fragment shader  
 #version 400

in vec3 FragPos;  
in vec3 Normal; 
in vec3 inLightPos;
in vec3 inViewPos;

out vec4 out_Color;

uniform vec3 objectColor;
uniform vec3 lightColor;

in vec2 tex_Coord;

uniform int codCol;

uniform int tex_code;
uniform sampler2D myTexture;


void main(void)
  {

  vec3 color = objectColor;

  if(tex_code == 1) {
		vec3 texColor =  texture(myTexture, tex_Coord).xyz;
		color = texColor;
	}

    // Ambient
    float ambientStrength = 0.2f;
    vec3 ambient_light = ambientStrength * lightColor;  
    vec3 ambient_term= ambient_light * color;
  	
    // Diffuse 
    vec3 norm = normalize(Normal); 
    vec3 lightDir = normalize(inLightPos - FragPos); 
    float diff = max(dot(norm, lightDir), 0.0); 
    vec3 diffuse_light = lightColor; 
    vec3 diffuse_term = diff * diffuse_light * color; 
    
    // Specular
    float specularStrength = 0.5f;
    float shininess = 100.0f;
    vec3 viewDir = normalize(inViewPos - FragPos); // versorul catre observator
    vec3 reflectDir = normalize(reflect(-lightDir, norm));  // versorul vectorului R 
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess); 
    vec3 specular_light = specularStrength  * lightColor; // specular_light=specularStrength  * lightColor
    vec3 specular_term = spec * specular_light * color;   // specular_material=objectColor
       
    // Culoarea finala 
      vec3 emission=vec3(0.0, 0.0, 0.0);
    //vec3 emission=vec3(1.0,0.8,0.4);
    vec3 result = emission + (ambient_term + diffuse_term + specular_term);
	out_Color = vec4(result, 1.0f);

    if ( codCol==1 )
		out_Color=vec4 (0.0, 0.0, 0.0, 0.0);
    }