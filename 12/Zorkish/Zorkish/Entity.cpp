#include "Entity.h"
#include "Components.h"
#include "Messenger.h"

using namespace std;

bool Entity::addComponent(string _id, Component * _comp)
{
	map<string, Component*>::iterator it;
	it = components.find(_id);
	if (it != components.end())
	{
		components.erase(it);
		return false; //already have this component
	}
	components[_id] = _comp;
	return true;
}

bool Entity::removeComponent(string _identifier)
{
	map<string, Component*>::iterator it;
	it = components.find(_identifier);
	if (it != components.end())
	{
		components.erase(it);
		return true;
	}
	return false;
}

Component * Entity::getComponent(string _identifier)
{
	map<string, Component*>::iterator it;
	it = components.find(_identifier);
	if (it != components.end())
	{
		return it->second;
	}
	return nullptr;
}

bool Entity::hasComponent(string _identifier)
{
	map<string, Component*>::iterator it;
	it = components.find(_identifier);
	if (it != components.end())
	{
		return true;
	}
	return false;
}

void Entity::handleMessage(Message* _msg)
{
	switch (_msg->getTag())
	{
	case HEALTH:
		if (hasComponent(HealthComponent::IDENTIFIER))
		{
			HealthComponent* comp = dynamic_cast<HealthComponent*>(getComponent(HealthComponent::IDENTIFIER));
			if (comp != 0)
			{
				int health = 0;
				try
				{
					health = stoi(_msg->getContents());
				}
				catch (const std::exception&)
				{
					//dang
				}
				comp->addHealth(health);
			}
		}
		break;
	case DAMAGE:
		if (hasComponent(DamageableComponent::IDENTIFIER) && hasComponent(HealthComponent::IDENTIFIER))
		{
			HealthComponent* comp = dynamic_cast<HealthComponent*>(getComponent(HealthComponent::IDENTIFIER));
			if (comp != 0)
			{
				int dmg = 0;
				try
				{
					dmg = stoi(_msg->getContents());
				}
				catch (const std::exception&)
				{
					//dang
				}
				comp->takeHealth(dmg);
			}
		}
		break;
	}
}

void Entity::checkBlackboard()
{
	map<int, Message*> blackboardMessages = Messenger::instance().viewBlackboard();

}
