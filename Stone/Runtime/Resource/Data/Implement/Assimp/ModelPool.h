#pragma once
#include <Core/Base/PublicSingleton.h>
#include <map>
#include <string>
#include <memory>
namespace Stone
{
	template<typename T>
	class ModelPool : public PublicSingleton<ModelPool<T>>
	{
	public:
		std::shared_ptr<T> get(const std::string& name)
		{
			if (m_Map.find(name)==m_Map.end())
			{
				m_Map[name] = std::make_shared<T>(name);
			}
			return m_Map[name];
		}
	private:
		std::map<std::string, std::shared_ptr<T>> m_Map;
	};
}