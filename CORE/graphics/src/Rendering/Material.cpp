#include "Rendering/Material.hpp"

namespace Engine {
	
	Material::Material() {

	}

	Material::Material(const float& ambient_factor, const float& diffuse_factor, const float& specular_factor, 
		const float& shininess, const std::shared_ptr<Texture2D>& texture) :
		m_ambient_factor(ambient_factor),
		m_diffuse_factor(diffuse_factor),
		m_specular_factor(specular_factor),
		m_shininess(shininess),
		m_texture(texture)
	{}

	Material::Material(const Material& other) {
		if (this != &other)
		{
			m_ambient_factor = other.m_ambient_factor;
			m_diffuse_factor = other.m_diffuse_factor;
			m_specular_factor = other.m_specular_factor;
			m_shininess = other.m_shininess;
			m_texture = other.m_texture;
		}
	}

	Material::~Material() {

	}

	Material& Material::operator=(const Material& other) {
		if (this != &other)
		{
			m_ambient_factor = other.m_ambient_factor;
			m_diffuse_factor = other.m_diffuse_factor;
			m_specular_factor = other.m_specular_factor;
			m_shininess = other.m_shininess;
			m_texture = other.m_texture;
		}
		return *this;
	}
}