#pragma once
#include "PrimitiveObject.hpp"

namespace Engine {

	class Line : public PrimitiveObject {
	public:
		Line(const glm::vec3& position, const unsigned int resolution);
		Line(const Line& other) = delete;
		Line(Line&& other) = delete;
		~Line();
		virtual void draw() override;

		void addPointToLine(const glm::vec3& newPoint); // add new point to the 

		bool hasShaderProgram() const;

	protected:
		virtual void configureObject() override;

	private:
		void reconfigureLine();
      const unsigned int m_max_allowed_resolution = 1000;
      const unsigned int m_resolution;
      unsigned int m_current_cell = 0;
      float* m_line_points;
      unsigned int* m_line_indices;
	};
}