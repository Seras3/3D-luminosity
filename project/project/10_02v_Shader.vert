// Shader-ul de varfuri  
 #version 400

layout(location=0) in vec3 in_Position;
layout(location=1) in vec3 in_Normal;
layout(location=2) in vec2 texCoord;
 
out vec4 ex_Color;
out vec2 tex_Coord;

uniform mat4 myMatrix;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 objectColor;
uniform vec3 lightColor;

uniform int codCol;
uniform mat4 matrUmbra;


uniform int tex_code;
uniform sampler2D myTexture;

void main(void)
  {

   vec3 color = objectColor;

    if(tex_code == 1) {
		vec3 texColor =  texture(myTexture, texCoord).xyz;
		color = texColor;
	}

    // aplicare transformari si determinare pozitii
    gl_Position = projection*view*myMatrix*vec4(in_Position, 1.0);
    vec3 Normal=vec3(projection*view*vec4(in_Normal,0.0)); 
    vec3 inLightPos= vec3(projection*view* vec4(lightPos, 1.0f));
    vec3 inViewPos=vec3(projection*view* vec4(viewPos, 1.0f));
    vec3 FragPos = vec3(gl_Position);

    // Ambient
    float ambientStrength = 0.2f;
    vec3 ambient_light = ambientStrength * lightColor;  // ambient_light=ambientStrength*lightColor 
    vec3 ambient_term= ambient_light * color; // ambient_material=objectColor
  	
    // Diffuse 
    vec3 norm = normalize(Normal); // vectorul s 
    vec3 lightDir = normalize(inLightPos - FragPos); // vectorul L
    float diff = max(dot(norm, lightDir), 0.0); // 
    vec3 diffuse_light = lightColor; // diffuse_light=lightColor;
    vec3 diffuse_term = diff * diffuse_light * color; // diffuse_material=objectColor

    // Specular
    float specularStrength = 0.5f;
    float shininess = 1.0f;
    vec3 viewDir = normalize(inViewPos - FragPos); // versorul catre observator
    vec3 reflectDir = normalize(reflect(-lightDir, norm));  // versorul vectorului R 
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess); 
    vec3 specular_light = specularStrength  * lightColor; // specular_light=specularStrength  * lightColor
    vec3 specular_term = spec * specular_light * color;   // specular_material=objectColor
       
    // Culoarea finala 
    vec3 result = (ambient_term + diffuse_term + specular_term);
	ex_Color = vec4(result, 1.0f);

    tex_Coord = texCoord;

    if ( codCol==1 ){
		gl_Position = projection*view*matrUmbra*myMatrix*vec4(in_Position, 1.0);
        ex_Color = vec4(vec3(gl_Position), 1.0f);
        }
   }  
