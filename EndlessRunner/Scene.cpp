#include "Scene.h"

Scene::Scene()
{

}
Scene::Scene(std::vector<GUIObject*>* objects, ImageLibrary& imageLibrary) : index(0), m_objects(*objects), m_arrow(new GUIArrow((*objects)[0]->m_position, imageLibrary)), m_state(GUIObjectState::GOING_IN), m_transitioning(false)
{
	m_arrow->currentObject = m_objects[0];
	m_arrow->currentObject->ToggleHighlight(true, imageLibrary);
	for (int i = 0; i < m_objects.size(); i++)
	{
		m_objects[i]->SetState(&m_state);
	}
}
Scene::Scene(std::vector<Number>* numbers, ImageLibrary& imageLibrary) : index(0), m_numbers(*numbers), m_arrow(nullptr), m_state(GUIObjectState::GOING_IN), m_transitioning(false)
{
}
Scene::Scene(std::vector<GUIObject*>* objects, std::vector<Number>* numbers, ImageLibrary& imageLibrary) : index(0), m_objects(*objects), m_numbers(*numbers), 
m_arrow(new GUIArrow((*objects)[0]->m_position, imageLibrary)), m_state(GUIObjectState::GOING_IN), m_transitioning(false)
{
	m_arrow->currentObject = m_objects[0];
	m_arrow->currentObject->ToggleHighlight(true, imageLibrary);
	for (int i = 0; i < m_objects.size(); i++)
	{
		m_objects[i]->SetState(&m_state);
	}
}
Scene::Scene(std::vector<GUIObject*>* objects, std::vector<Number>* numbers, std::vector<Word>* words, ImageLibrary& imageLibrary) : index(0), m_objects(*objects), m_numbers(*numbers),
m_arrow(new GUIArrow((*objects)[0]->m_position, imageLibrary)), m_state(GUIObjectState::GOING_IN), m_transitioning(false), m_words(*words)
{
	m_arrow->currentObject = m_objects[0];
	m_arrow->currentObject->ToggleHighlight(true, imageLibrary);
	for (int i = 0; i < m_objects.size(); i++)
	{
		m_objects[i]->SetState(&m_state);
	}
}
Scene::~Scene()
{
	delete m_arrow;
	m_arrow = nullptr;
	for (int i = 0; i < m_objects.size(); i++)
	{
		delete m_objects[i];
	}
}
bool Scene::Update(ImageLibrary& imageLibrary)
{
	for (int i = 0; i < m_objects.size(); i++)
	{
		if (m_objects[i]->Update(imageLibrary))
		{
			m_transitioning = false;
			return true;
		}
	}
	if (m_objects.size() != 0)
	{
		if (m_objects[m_objects.size() - 1]->m_position.m_position.x >= m_objects[m_objects.size() - 1]->m_menuscreen.m_position.x && !m_transitioning)
		{
			m_state = GUIObjectState::STILL;
			if (!m_arrow->m_active)
			{
				m_arrow->ToggleArrow();
				m_arrow->Move();
			}
		}
		if (m_objects[m_objects.size() - 1]->m_position.m_position.x <= m_objects[m_objects.size() - 1]->m_offscreen.m_position.x
			&& m_transitioning)
		{
			m_state = GUIObjectState::STILL;
		}
	}
	return false;
}
void Scene::OnKeyDown(KeyCode key, RenderManager& renderManager, ImageLibrary& imageLibrary)
{
	if (m_arrow != nullptr && m_arrow->m_active)
	{
		if (m_objects.size() > 0)
		{
			switch (key)
			{
			case KeyCode::UP_ARROW:
				m_arrow->currentObject->ToggleHighlight(false, imageLibrary);
				index--;
				if (index < 0) { index = m_objects.size() - 1; };
				m_arrow->currentObject = m_objects[index];
				m_arrow->Move();
				m_arrow->currentObject->ToggleHighlight(true, imageLibrary);
				break;
			case KeyCode::DOWN_ARROW:
				m_arrow->currentObject->ToggleHighlight(false, imageLibrary);
				index++;
				index %= m_objects.size();
				m_arrow->currentObject = m_objects[index];
				m_arrow->Move();
				m_arrow->currentObject->ToggleHighlight(true, imageLibrary);
				break;
			}
		}
		if (m_arrow->currentObject->OnKeyDown(key, renderManager))
		{
			m_transitioning = true;
			m_arrow->ToggleArrow();
		}
	}
}
void Scene::Render(RenderManager& rM)
{
	for (unsigned int i = 0; i < m_objects.size(); i++)
	{
		m_objects[i]->Render(rM);
	}
	for (unsigned int i = 0; i < m_numbers.size(); i++)
	{
		m_numbers[i].Render(rM);
	}
	for (unsigned int i = 0; i < m_words.size(); i++)
	{
		m_words[i].Render(rM);
	}
	if (m_arrow)
	{
		m_arrow->Render(rM);
	}
}
