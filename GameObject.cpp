#include "GameObject.h"

std::vector< GameObject* > GameObject::s_vUpdateList;
std::vector< GameObject* > GameObject::s_vDrawList;
std::vector< GameObject* > GameObject::s_vNewGameObjects;

GameObject::GameObject(Point2f pos)
{
	m_pos = pos;
	// Add any new gameobjects to new object vector
	s_vNewGameObjects.push_back(this);
}

GameObject::~GameObject()
{
	s_vDrawList.erase(std::find(s_vDrawList.begin(), s_vDrawList.end(), this));
	s_vUpdateList.erase(std::find(s_vUpdateList.begin(), s_vUpdateList.end(), this));
}

void GameObject::UpdateAll(GameState& gState)
{
	// Add new objects from previous loop to update and draw vectors
	s_vUpdateList.insert(s_vUpdateList.end(), s_vNewGameObjects.begin(), s_vNewGameObjects.end());
	s_vDrawList.insert(s_vDrawList.end(), s_vNewGameObjects.begin(), s_vNewGameObjects.end());
	// Clear the new object vector each loop
	s_vNewGameObjects.clear();

	std::sort(s_vUpdateList.begin(), s_vUpdateList.end(), GameObject::UpdateOrder);
	// Loop through update list, update each object and delete any inactive objects
	for (size_t n = 0; n < s_vUpdateList.size(); n++)
	{
		s_vUpdateList[n]->Update(gState);

		if (!s_vUpdateList[n]->m_active)
			delete s_vUpdateList[n--];
	}
}

void GameObject::DrawAll(GameState& gState)
{
	std::sort(s_vDrawList.begin(), s_vDrawList.end(), GameObject::DrawOrder);
	// Loop through draw list and call object specific draw function
	for (size_t n = 0; n < s_vDrawList.size(); n++)
		s_vDrawList[n]->Draw(gState);
}

int GameObject::GetObjectCount(GameObject::Type type)
{
	int count = 0;

	for (GameObject* p : s_vUpdateList)
	{
		if (p->m_type == type || type == OBJ_ALL)
			count++;
	}

	return count;
}

int GameObject::GetObjectList(GameObject::Type type, std::vector< GameObject* >& vList)
{
	vList.clear();

	for (GameObject* p : s_vUpdateList)
	{
		if (p->m_type == type || type == OBJ_ALL)
			vList.push_back(p);
	}

	return vList.size();
}

void GameObject::DestroyAll()
{
	for (size_t n = 0; n < s_vDrawList.size(); n++)
		delete s_vUpdateList[n--];
}

