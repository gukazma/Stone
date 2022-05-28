#pragma once
#include <string>
#include <memory>


namespace Stone
{
    template<typename T>
    class ModelComponent
    {
    public:
        ModelComponent(const std::string& filename)
            : m_ModelName(filename)
        {}

        std::shared_ptr<T> getModel()
        {
            return PublicSingleton<ModelPool<T>>::getInstance().get(m_ModelName);
        }

        ~ModelComponent() {}
        std::string m_ModelName;
    };
}
