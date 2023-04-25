#include "Rendering/Primitives/Sphere.hpp"
#include "Log.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Rendering/Primitives/Line.hpp"

namespace Engine {

    Line::Line(const glm::vec3& position, const unsigned int resolution) :
        PrimitiveObject(position),
		m_resolution(resolution <= m_max_allowed_resolution ? resolution : m_max_allowed_resolution)
    {
		configureObject();
    }

	Line::~Line()
	{
		delete[] m_line_points;
		delete[] m_line_indices;
	}

	void Line::draw() {
		if (m_vao != nullptr) {
			// RendererOpenGL functions here
			if (m_sp != nullptr) {
				m_sp->bind();
				m_sp->setMatrix4("model_matrix", m_model_matrix);
			}
			else {
				LOG_ERROR("No shader");
			}
			RendererOpenGL::draw(m_vao, RendererOpenGL::RenderRegime::LINE_STRIP);
		}
		else {
			LOG_ERROR("No vao");
		}
    }

	void Line::addPointToLine(const glm::vec3& newPoint) {
		for (unsigned int i = 0; i < 3; i++) {
			*(m_line_points + 6 * m_current_cell + i) = newPoint[i]; // updating only coordinates
		}
		m_current_cell++;
		if (m_current_cell == m_resolution) {
			m_current_cell = 0; // if we reach the end of memory - rewrite data from the start
		}
		
		unsigned int last_elem = *(m_line_indices + m_resolution - 1);
		for (unsigned int i = m_resolution - 1; i > 0; i--) {
			
			*(m_line_indices + i) = *(m_line_indices + i - 1); // shifting array to the right
		}
		*(m_line_indices) = last_elem;

		reconfigureLine();
	}

    void Line::configureObject() {
		// array object initialization here
		const unsigned int nPoints = m_resolution;
		
		m_line_points = new GLfloat[6 * nPoints]; // the structure as follows -- [x, y, z, r, g, b] for each vertex
		for (int i = 0; i < nPoints; i++) {
			*(m_line_points + i * 6 + 0) = m_position.x; // x
			*(m_line_points + i * 6 + 1) = m_position.y; // y
			*(m_line_points + i * 6 + 2) = m_position.z; // z
			
			*(m_line_points + i * 6 + 3) = 1.f; // r
			*(m_line_points + i * 6 + 4) = 0.f; // g
			*(m_line_points + i * 6 + 5) = 0.f; // b
		}
		
		m_line_indices = new unsigned int[nPoints];
		for (unsigned int i = 0; i < nPoints; i++) {
			*(m_line_indices + i) = nPoints - 1 - i;
		}

		BufferLayout buffer_layout_vec3_vec3
		{
			ShaderDataType::Float3, // vertex pos
			ShaderDataType::Float3, // colors
		};
		m_vao = std::make_shared<VertexArray>();
		m_vbo = std::make_shared<VertexBuffer>(m_line_points, 4*6*m_resolution, buffer_layout_vec3_vec3);
		m_ib = std::make_shared<IndexBuffer>(m_line_indices, 4*m_resolution / sizeof(unsigned int));

		m_vao->addVertexBuffer(m_vbo);
		m_vao->setIndexBuffer(m_ib);
    }

	void Line::reconfigureLine() {
		BufferLayout buffer_layout_vec3_vec3
		{
			ShaderDataType::Float3, // vertex pos
			ShaderDataType::Float3, // colors
		};
		//m_vbo->unbind();
		//m_ib->unbind();
		m_vbo = std::make_shared<VertexBuffer>(m_line_points, 4 * 6 * m_resolution, buffer_layout_vec3_vec3);
		m_ib = std::make_shared<IndexBuffer>(m_line_indices, 4 * m_resolution / sizeof(unsigned int));

		
		m_vao->addVertexBuffer(m_vbo);
		m_vao->setIndexBuffer(m_ib);
	}
}