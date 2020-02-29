varying in vec4 vert_pos;

uniform sampler2D texture;
uniform vec2 lightPos;
uniform bool nightEnabled;
uniform float camZoom;

void main()
{
	//Ambient light
	vec4 ambient;
	vec4 lightColour;
	int shadeAlpha;
	if(nightEnabled){ ambient = vec4(0, 0, 0, 1); lightColour = vec4(0.252, 0.188, 0.141, 1); shadeAlpha = 0; }
	else			{ ambient = vec4(1, 1, 1, 1); lightColour = ambient; shadeAlpha = 1; }

	//Convert light to view coords
	lightPos = (gl_ModelViewProjectionMatrix * vec4(lightPos, 0, 1)).xy;
	
	//Calculate the vector from light to pixel (Make circular)
	vec2 lightToFrag = lightPos - vert_pos.xy;
	lightToFrag.y = lightToFrag.y / 1.7;

	//Length of the vector (distance)
	float vecLength = clamp(length(lightToFrag) * 20 * camZoom, 0, 1); // 20 = Light radius!!!!!!!

    // lookup the pixel in the texture
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

    // multiply it by the color and lighting
	gl_FragColor = gl_Color * pixel * lightColour * (clamp(ambient + vec4(1-vecLength, 1-vecLength, 1-vecLength, 1), shadeAlpha, 1));
}