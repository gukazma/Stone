#include "OpenGLParticle.h"
#include <glad/glad.h>
#include "particle_vert.h"
#include "particle_geom.h"
#include "particle_frag.h"

#include "Core/Base/macro.h"
namespace Stone
{
	OpenGLParticle::OpenGLParticle()
	{
		m_VBO1 = VertexBuffer::create(MAX_PARTICLE_NUM * sizeof(Particle));
		m_VBO1->setLayout({
			{ ShaderDataType::Float, "aV" },
			});
		m_VBO2 = VertexBuffer::create(MAX_PARTICLE_NUM * sizeof(Particle));
		m_VBO2->setLayout({
			{ ShaderDataType::Float, "aV" },
			});

		m_VAO1 = VertexArray::create();
		m_VAO2 = VertexArray::create();

		m_VAO1->addVertexBuffer(m_VBO1);
		m_VAO2->addVertexBuffer(m_VBO2);
		glGenQueries(1, &m_Query);

		m_ParticleShader = Shader::create("m_ParticleShader");
		auto vershader = m_ParticleShader->create(particle_vert, sizeof(particle_vert), Shader::ShaderType::Vertex_Shader);
		m_ParticleShader->attach(vershader);
		auto geoshader = m_ParticleShader->create(particle_geom, sizeof(particle_geom), Shader::ShaderType::Geometry_Shader);
		m_ParticleShader->attach(geoshader);
		const GLchar* feedbackVaryings[] = { "outValue" };
		glTransformFeedbackVaryings(m_ParticleShader->getRenderID(), 1, feedbackVaryings, GL_INTERLEAVED_ATTRIBS);
		auto fragshader = m_ParticleShader->create(particle_frag, sizeof(particle_frag), Shader::ShaderType::Fragment_Shader);
		m_ParticleShader->attach(fragshader);
		m_ParticleShader->link();
	}
	void OpenGLParticle::logictick()
	{
		m_ParticleShader->bind();
		m_Primitives = m_IsFirst ? m_Particles.size() : m_Primitives;
		glEnable(GL_RASTERIZER_DISCARD);
	 	m_SwapFlag ? m_VAO1->bind() : m_VAO2->bind();
		m_SwapFlag ? m_VBO2->bindTransformFeedback(0) : m_VBO1->bindTransformFeedback(0);
		glBeginQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN, m_Query);
		glBeginTransformFeedback(GL_POINTS);
		glDrawArrays(GL_POINTS, 0, m_Primitives);
		glEndTransformFeedback();
		glEndQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN);

		glFlush();

		glGetQueryObjectuiv(m_Query, GL_QUERY_RESULT, &m_Primitives);
		GLfloat feedback[5];
		glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER, 0, sizeof(feedback), feedback);
		for (size_t i = 0; i < 5; i++)
		{
		    LOG_DEBUG("feedback: {0}", feedback[i]);
		}
		LOG_DEBUG("{0} primitives written!", m_Primitives);
		glDisable(GL_RASTERIZER_DISCARD);
		m_SwapFlag = ! m_SwapFlag;
	}
	void OpenGLParticle::rendertick()
	{
		/*m_ParticleShader->bind();
		m_SwapFlag ? m_VAO1->bind() : m_VAO2->bind();
		glDrawArrays(GL_POINTS, 0, m_Primitives);
		m_SwapFlag != m_SwapFlag;*/
	}
	void OpenGLParticle::add(const std::vector<Particle>& particles)
	{
	}
	void OpenGLParticle::add(const Particle particle)
	{
		m_Particles.push_back(particle);
		m_VBO1->setData(m_Particles.data(), MAX_PARTICLE_NUM * sizeof(Particle));
	}
}