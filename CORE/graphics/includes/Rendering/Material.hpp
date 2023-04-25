#pragma once
#include <memory>


namespace Engine {
	class Texture2D;
	struct Material {
		Material();
		Material(const float& ambient_factor,
				 const float& diffuse_factor,
				 const float& specular_factor,
				 const float& shininess);

		Material(const Material& other);

		~Material();

		Material& operator=(const Material& other);

		float m_ambient_factor = 1.f;
		float m_diffuse_factor = 1.f;
		float m_specular_factor = 1.f;
		float m_shininess = 1.f;
		std::shared_ptr<Texture2D> m_texture = nullptr;
	};
}