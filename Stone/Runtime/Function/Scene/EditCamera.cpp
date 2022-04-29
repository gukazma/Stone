#include "Function/Scene/EditCamera.h"
#include "Core/Base/macro.h"
#include "Function/Event/Input.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include <iostream>

#include "Engine.h"
#include "Function/Event/EventSystem.h"
#include "Function/Event/Input.h"
#include "Core/Base/macro.h"
namespace Stone
{
	EditorCamera::EditorCamera()
	{
		// register Event
		PublicSingleton<EventSystem>::getInstance().registerClient("EditCamera_Begin", this);
		PublicSingleton<EventSystem>::getInstance().registerClient("EditCamera_Pan", this);
		PublicSingleton<EventSystem>::getInstance().registerClient("EditCamera_Rotate", this);
		PublicSingleton<EventSystem>::getInstance().registerClient("EditCamera_Zoom", this);
		PublicSingleton<EventSystem>::getInstance().registerClient("EditCamera_End", this);
		m_UniformBuffer = UniformBuffer::create(sizeof(glm::vec3) + sizeof(glm::mat4));
		LOG_INFO("sizeof vec3:{0} sizof mat4: {1}", sizeof(glm::vec3) ,sizeof(glm::mat4))
#ifdef GLM_FORCE_RADIANS
		m_Angle = 0.785398f; //45 degrees
#else
		m_Angle = 45.0f; //45 degrees
#endif
		m_Near = 0.000001f;
		m_Far = 1000.0f;
		m_Pos = glm::vec3(10.0f, 10.0f, 8.0f);
		m_Up = { 0.0f, 1.0f, 0.0f };
		m_FocalPoint = { 0.0f, 0.0f, 0.0f };
		m_AspectRatio = 800.0f / 600.0f;
		m_Near = 0.1f;
		m_Far = 1000.0f;
		genProjMat();
		genViewMat();
		updateBuffer();
	}
	void EditorCamera::bind(size_t index)
	{
		m_UniformBuffer->bind(index);
	}
	void EditorCamera::handleEvent(Event* event)
	{
		MousePos* mousepos = nullptr;
		MouseAngle* mouseangle = nullptr;

		if (event->eventId() == "EditCamera_Begin")
		{
			begin(event);
		}

		if ((event->eventId() == "EditCamera_Rotate") )
		{
			if (mousepos = static_cast<MousePos*>(event->parameter()))
			{
				
				const glm::vec2 mouse = { mousepos->x, mousepos->y };
				if (!m_Begin)
				{
					m_InitialMousePosition = mouse;
					m_Begin = true;
				}
				glm::vec2 delta = (mouse - m_InitialMousePosition) * 0.001f;
				m_InitialMousePosition = mouse;
				rotate(delta);
				genViewMat();
				updateBuffer();
			}
		}
		if (event->eventId() == "EditCamera_Pan")
		{
			if (mousepos = static_cast<MousePos*>(event->parameter()))
			{
				const glm::vec2 mouse = { mousepos->x, mousepos->y };
				if (!m_Begin)
				{
					m_InitialMousePosition = mouse;
					m_Begin = true;
				}
				glm::vec2 delta = (mouse - m_InitialMousePosition) * 0.001f;
				m_InitialMousePosition = mouse;
				pan(delta);
				genViewMat();
				updateBuffer();
			}
		}
		if (event->eventId() == "EditCamera_Zoom")
		{
			if (mouseangle = static_cast<MouseAngle*>(event->parameter()))
			{
				zoom(mouseangle->y);
				genViewMat();
				updateBuffer();
			}
		}

		if (event->eventId() == "EditCamera_End")
		{
			end(event);
		}
	}

	void EditorCamera::setAspectRatio(const float ar)
	{
		m_AspectRatio = ar;
	}

	void EditorCamera::setViewAngle(const float a)
	{
		m_Angle = a;
	}

	void EditorCamera::setNearClipDist(const float d)
	{
		m_Near = d;
	}

	void EditorCamera::setFarClipDist(const float d)
	{
		m_Far = d;
	}

	void EditorCamera::genViewMat()
	{
		m_Pos = calculatePosition();

		glm::quat orientation = getOrientation();

		m_View = glm::translate(glm::mat4(1), m_Pos) * glm::toMat4(orientation);
		m_View = glm::inverse(m_View);
	}

	void EditorCamera::genProjMat()
	{
		m_AspectRatio = m_ViewportWidth / m_ViewportHeight;
		m_Proj = glm::perspective(m_Angle, m_AspectRatio, m_Near, m_Far);
	}
	void EditorCamera::updateBuffer()
	{
		m_UniformBlackData.Pos = calculatePosition();
		m_ProjViewMatrix = m_Proj * m_View;
		m_UniformBlackData.ProjView = m_ProjViewMatrix;
		m_UniformBuffer->setData(&m_UniformBlackData, sizeof(m_UniformBlackData), 0);
	}
	void EditorCamera::rotate(glm::vec2 delta)
	{
		float yawSign = getUpDirection().y > 0 ? -1.0f : 1.0f;
		m_Yaw += yawSign * delta.x * 5.0f;
		m_Pitch += delta.y * 5.0f;
	}
	void EditorCamera::pan(glm::vec2 delta)
	{
		auto [xSpeed, ySpeed] = panSpeed();
		m_FocalPoint -= -getRightDirection() * delta.x * xSpeed * m_Distance * 10.0f;
		m_FocalPoint += getUpDirection() * delta.y * ySpeed * m_Distance * 10.0f;
	}
	std::pair<float, float> EditorCamera::panSpeed() const
	{
		float x = std::min(m_ViewportWidth / 1000.0f, 2.4f); // max = 2.4f
		float xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;

		float y = std::min(m_ViewportHeight / 1000.0f, 2.4f); // max = 2.4f
		float yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;

		return { xFactor, yFactor };
	}
	void EditorCamera::begin(Event* event)
	{
		MousePos* mousepos = nullptr;
		if (!m_Begin)
		{
			if (mousepos = static_cast<MousePos*>(event->parameter()))
			{
				m_InitialMousePosition = { mousepos->x, mousepos->y };
			}
		}
	}

	void EditorCamera::end(Event* event)
	{
		m_Begin = false;
	}

	glm::quat EditorCamera::getOrientation() const
	{
		return glm::quat(glm::vec3(-m_Pitch, -m_Yaw, 0.0f));
	}

	glm::vec3 EditorCamera::getForwardDirection() const
	{
		return glm::rotate(getOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
	}

	glm::vec3 EditorCamera::getRightDirection() const
	{
		return glm::rotate(getOrientation(), glm::vec3(1.0, 0.0, 0.0));
	}

	glm::vec3 EditorCamera::getUpDirection() const
	{
		return glm::rotate(getOrientation(), glm::vec3(0.0, 1.0, 0.0));
	}
	glm::vec3 EditorCamera::calculatePosition()
	{
		return m_FocalPoint - getForwardDirection() * m_Distance;
	}

	void EditorCamera::zoom(float delta)
	{
		delta = delta > 0 ? 0.1 : -0.1;
		m_Distance -= delta * zoomSpeed();
		/*if (m_Distance < 1.0f)
		{
			m_FocalPoint += getForwardDirection();
			m_Distance = 1.0f;
		}*/
	}

	float EditorCamera::zoomSpeed() const
	{
		float distance = m_Distance * 0.2f;
		distance = std::max(distance, 0.0f);
		float speed = distance * distance;
		speed = std::min(speed, 100.0f); // max speed = 100
		return speed;
	}

}