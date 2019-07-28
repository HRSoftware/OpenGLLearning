 #version 440 core
layout(lines)in;
layout(line_strip, max_vertices=2)out;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
const int half_tileSize = 100;


void addNewPoint(vec4 newPoint){
	gl_Position=gl_in[0].gl_Position + (projection * view * model * newPoint);
	EmitVertex();
	
}


void generateLine()
{
			gl_Position=projection*view*model*gl_in[0].gl_Position;
	
			// +X direction is "North", -X direction is "South"
			// +Y direction is "Up",    -Y direction is "Down"
			// +Z direction is "East",  -Z direction is "West"
			//                                    				 N/S   U/D   E/W
			// vec4 NEU=projection	* view * model * 	vec4	(.1,	  0,	  	1,		0.);
			// vec4 NED=projection	* view * model * 	vec4	( 1,		0,		  1,		0.);
			// vec4 NWU=projection	* view * model * 		vec4	( 1,		0,		 -1,		0.);
			// vec4 NWD=projection	* view * model * 		vec4	( 1,		0,		 -1,		0.);
			// vec4 SEU=projection	* view * model * 		vec4	(-1,	  0,		  1,		0.);
			// vec4 SED=projection	* view * model * 		vec4	(-1,	  0,	  	1,		0.);
			// vec4 SWU=projection	* view * model * 		vec4	(-1,	  0,		 -1,		0.);
			// vec4 SWD=projection	* view * model * 		vec4	(-1,	  0,		 -1,		0.);


			for(int i = 0; i < 100; i++){
				for(int j = 0; j < 100; j++){
					addNewPoint(vec4(i * 10, i * j, j * 10 , 0));
				}
			}

			// Create a cube centered on the given point.
			// gl_Position=gl_in[0].gl_Position+NED;
			// EmitVertex();

			// gl_Position=gl_in[0].gl_Position+NWD;
			// EmitVertex();

			// gl_Position=gl_in[0].gl_Position+SWD;
			// EmitVertex();

			// gl_Position=gl_in[0].gl_Position+SED;
			// EmitVertex();

			// gl_Position=gl_in[0].gl_Position+SEU;
			// EmitVertex();

			// gl_Position=gl_in[0].gl_Position+SWU;
			// EmitVertex();

			// gl_Position=gl_in[0].gl_Position+NWU;
			// EmitVertex();

			// gl_Position=gl_in[0].gl_Position+NEU;
			// EmitVertex();

			// gl_Position=gl_in[0].gl_Position+NED;
			// EmitVertex();

			// gl_Position=gl_in[0].gl_Position+SED;
			// EmitVertex();

			// gl_Position=gl_in[0].gl_Position+SEU;
			// EmitVertex();

			// gl_Position=gl_in[0].gl_Position+NEU;
			// EmitVertex();

			// gl_Position=gl_in[0].gl_Position+NWU;
			// EmitVertex();

			// gl_Position=gl_in[0].gl_Position+NWD;
			// EmitVertex();

			// gl_Position=gl_in[0].gl_Position+SWD;
			// EmitVertex();

			// gl_Position=gl_in[0].gl_Position+SWU;
			// EmitVertex();

			EndPrimitive();
}

void main()
{
	//generateLine();


}


