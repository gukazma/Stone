#pragma once
#include <string>
#include <vector>
#include <map>
#include <Function/Render/Interface/VertexArray.h>
namespace Stone
{
	struct Vertex
	{
        float px;
        float py;
        float pz;
        float nx;
        float ny;
        float nz;
        float u;
        float v;
	};

    class Mesh
    {
    public:
        Mesh() = default;
        Mesh(const std::string& path);
        virtual void update();
        virtual void updateBuffer() {}
        virtual ~Mesh();

        std::string getDirectoryPath(const std::string& filepath)
        {
            auto lPos = filepath.find_last_of("/");
            std::string directpath = filepath.substr(0, lPos + 1);
            return directpath;
        }

    public:
        std::shared_ptr<VertexArray> m_VAO = nullptr;
        std::shared_ptr<VertexBuffer> m_VBO = nullptr;
        std::shared_ptr<IndexBuffer> m_EBO = nullptr;
        std::vector<Vertex> m_V;
        std::vector<uint32_t> m_I;
        std::string m_Path;
        std::string m_Directory;

        bool operator==(const Mesh& other) const { return other.m_Path == m_Path; }
    };
}