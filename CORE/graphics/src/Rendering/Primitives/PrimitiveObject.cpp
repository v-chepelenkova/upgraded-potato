#include "Rendering/Primitives/PrimitiveObject.hpp"

namespace Engine {
	PrimitiveObject::PrimitiveObject(const glm::vec3& position) :
		m_position(position),
		m_material(std::make_shared<Material>())
	{
		// TODO: add rotation
		m_model_matrix = glm::mat4( 1, 0, 0, 0,
									0, 1, 0, 0,
									0, 0, 1, 0,
									m_position[0], m_position[1], m_position[2], 1);
	}

	PrimitiveObject::~PrimitiveObject() {

	}

	void PrimitiveObject::setShaderProgram(const std::shared_ptr<ShaderProgram>& new_shader_program) {
		m_sp->unbind();
		m_sp = new_shader_program;
	}

	void PrimitiveObject::setMaterial(const std::shared_ptr<Material>& new_material) {
		m_material = new_material;
	}

	void PrimitiveObject::setPosition(const glm::vec3& new_position)
	{
		/*glm::mat4 pos_matrix(	1, 0, 0, 0,
								0, 1, 0, 0,
								0, 0, 1, 0,
								new_position[0], new_position[1], new_position[2], 1);*/
		m_model_matrix[3][0] = new_position[0];
		m_model_matrix[3][1] = new_position[1];
		m_model_matrix[3][2] = new_position[2];
		//m_model_matrix = pos_matrix;
	}
	
	void PrimitiveObject::setScale(const float& new_scale) {
		m_model_matrix[0][0] = new_scale;
		m_model_matrix[1][1] = new_scale;
		m_model_matrix[2][2] = new_scale;
	}
}