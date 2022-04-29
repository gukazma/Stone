#pragma once
#include <string>
#include "Resource/Data/VCGMesh.h"
namespace Stone
{
    struct VCGMeshComponent
    {
        VCGMeshComponent()
            : m_Mesh(new VCGMesh())
        {}
        VCGMeshComponent(const std::string& filename)
            : m_Mesh(new VCGMesh())
        {
            m_Mesh->ReadFile(filename);
            m_Mesh->Update();
        }
        VCGMesh* m_Mesh;
    };
} // namespace kanjing
