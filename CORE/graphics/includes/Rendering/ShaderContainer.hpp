#pragma once

namespace Engine {
	// BASIC SHADERS
	namespace Shaders {

	// VERTEX SHADER (vertex_pos - vertex_norm - texture_coords)
	static constexpr const char* VERTEX_SHADER_WITH_BASIC_LIGHTNING =
		R"(#version 460
			layout(location = 0) in vec3 vertex_position;
			layout(location = 1) in vec3 vertex_normal;
			layout(location = 2) in vec2 texture_coord;
           
			uniform mat4 model_matrix;
			uniform mat4 view_projection_matrix;
			uniform int current_frame; 
           
			out vec2 tex_coord_smile;
			out vec2 tex_coord_quads;
			out vec3 frag_position;
			out vec3 frag_normal;
			
			void main() {
				tex_coord_smile = texture_coord;
				tex_coord_quads = texture_coord; // + vec2(current_frame / 1000.f, current_frame / 1000.f);
				frag_normal = mat3(transpose(inverse(model_matrix))) * vertex_normal;
				vec4 vertex_position_world = model_matrix * vec4(vertex_position, 1.0);
				frag_position = vertex_position_world.xyz;
				gl_Position = view_projection_matrix * vertex_position_world;
			}
        )";
	// FRAGMENT SHADER
	static const char* FRAGMENT_SHADER_WITH_BASIC_LIGHTNING =
		R"(#version 460
			in vec2 tex_coord_smile;
			in vec2 tex_coord_quads;
			in vec3 frag_position;
			in vec3 frag_normal;
			
			layout (binding = 0) uniform sampler2D InTexture_Quads;
			
			uniform vec3 camera_position;
			uniform vec3 light_position;
			uniform vec3 light_color;
			uniform float ambient_factor;
			uniform float diffuse_factor;
			uniform float specular_factor;
			uniform float shininess;
			
			out vec4 frag_color;
			
			void main() {
				// ambient
				vec3 ambient = ambient_factor * light_color;
				
				// diffuse
				vec3 normal = normalize(frag_normal);
				float light_magnitude = length(light_position - frag_position);
				vec3 light_dir = normalize(light_position - frag_position);
				float diffuse_value = max(dot(normal, light_dir), 0.0);			
				vec3 diffuse = diffuse_factor * light_color * diffuse_value;
				
				vec3 specular = vec3(0.f, 0.f, 0.f);
				if(diffuse_value != 0.0f) {
					// specular
					vec3 view_dir = normalize(camera_position - frag_position);
					vec3 halfway_dir = normalize(light_dir + view_dir);
					float specular_value = pow(max(dot(normal, halfway_dir), 0.0), shininess);
					specular = specular_factor * specular_value * light_color;
				}
				frag_color = texture(InTexture_Quads, tex_coord_quads) * vec4((ambient + diffuse + specular) / light_magnitude, 1.f);
			}
        )";

	// LIGHT SOURCE SHADERS

	// VERTEX SHADER (vertex_pos - vertex_color)
	static constexpr const char* vertex_shader_light_source =
		R"(#version 460
			layout(location = 0) in vec3 vertex_position;
			layout(location = 1) in vec3 vertex_color;

			uniform mat4 model_matrix;
			uniform mat4 view_projection_matrix;
           
			void main() {
              gl_Position = view_projection_matrix * model_matrix * vec4(vertex_position, 1.0);
           }
        )";

	// FRAGMENT SHADER
	static constexpr const char* fragment_shader_light_source =
		R"(#version 460
			out vec4 frag_color;
			
			uniform vec3 light_color;
			
			void main() {
				frag_color = vec4(light_color, 1.f);
			}
        )";
	

	//lineshady
	static constexpr const char* line_fragment =
		R"(#version 460
		
			in vec3 v_colors;
			out vec4 out_color;
			void main() {
		 		out_color = vec4(v_colors, 1.0);
		
			}
		)";

	static constexpr const char* line_vertex =
		R"(#version 460
		
			 
			layout(location = 0) in vec3 vertex_position;
			layout(location = 1) in vec3 vertex_color;

			
			uniform mat4 view_projection_matrix;
			
			out vec3 v_colors;

			void main() {
              gl_Position = view_projection_matrix * vec4(vertex_position, 1.0);
			  v_colors = vertex_color;
           }
		)";
	}
}