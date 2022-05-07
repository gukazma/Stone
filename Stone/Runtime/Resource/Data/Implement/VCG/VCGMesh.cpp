#include "Resource/Data/Implement/VCG/VCGMesh.h"
#include "Core/Base/macro.h"
#include <wrap/io_trimesh/import_obj.h>
#include <wrap/io_trimesh/import_ply.h>
#include <glad/glad.h>
namespace Stone
{
    VCGMesh::VCGMesh(const std::string& filename)
        : Mesh(filename)
    {
        read(filename);
        update();
    }
    void VCGMesh::update()
    {
        m_V.clear();
        m_V.reserve(m_Mesh.VN());
        vcg::tri::RequirePerVertexNormal<BaseTriMesh>;
        vcg::tri::UpdateNormal<BaseTriMesh>::PerVertexNormalizedPerFace(m_Mesh);
        for each (auto & vert in m_Mesh.vert)
        {
            Vertex v;
            v.px = vert.P().X();
            v.py = vert.P().Y();
            v.pz = vert.P().Z();
            v.u = vert.T().u();
            v.v = vert.T().v();
            v.nx = vert.N().X();
            v.ny = vert.N().Y();
            v.nz = vert.N().Z();
            m_V.push_back(v);
        }
        m_I.clear();
        m_I.reserve((m_Mesh.FN() * 3));
        for each (auto& face in m_Mesh.face)
        {
            if (!face.IsD())
            {
                for (size_t i = 0; i < 3; i++)
                {
                    m_I.push_back(vcg::tri::Index(m_Mesh, face.V(i)));
                }
            }
        }

        m_NeedUpdateBuffer = true;
    }
    void VCGMesh::read(const std::string& filename)
    {
        auto pointPos = filename.find_last_of(".");
        auto lPos = filename.find_last_of("/");
        std::string meshName = filename.substr(lPos + 1, pointPos - 1 - lPos);
        std::string extendName = filename.substr(pointPos + 1);
        LOG_INFO("mesh Name = {0}", meshName);
        LOG_INFO("mesh extenName = {0}", extendName);
        if (extendName == "obj")
        {
            vcg::tri::io::ImporterOBJ<BaseTriMesh>::Info info;
            if ((vcg::tri::io::ImporterOBJ<BaseTriMesh>::Open(m_Mesh, filename.c_str(), info) == vcg::tri::io::ImporterOBJ<BaseTriMesh>::E_NOERROR))
            {
                LOG_INFO("Input mesh: {0}", meshName);
                LOG_INFO("Mesh file type: {0}", extendName);
            }
            else
            {
                LOG_ERROR("Can't read FIle : {0}", filename);
            }
        }
        else if (extendName == "ply")
        {
            if (vcg::tri::io::ImporterPLY<BaseTriMesh>::Open(m_Mesh, filename.c_str()) == 0)
            {
                LOG_INFO("Input mesh: {0}", meshName);
                LOG_INFO("Mesh file type: {0}", extendName);
            }
            else
            {
                LOG_INFO("Can't read FIle : {0}", filename);
            }
        }

        else
        {
            LOG_ERROR("Editor can't suport format :{0}", extendName);
        }

    }
    void VCGMesh::updateBuffer()
    {
        if (!m_NeedUpdateBuffer)
        {
            return;
        }
        if (m_VAO == nullptr|| m_VBO == nullptr || m_EBO == nullptr)
        {
            m_VAO = VertexArray::create();
            m_VBO = VertexBuffer::create((void*)m_V.data(), sizeof(float) * m_V.size() * 8);
            m_VBO->setLayout({
            { ShaderDataType::Float3, "aPos" },
            { ShaderDataType::Float3, "aNormal" },
            { ShaderDataType::Float2, "aTexCoord" }
                });
            m_EBO = IndexBuffer::create(m_I.data(), m_I.size());
            m_VAO->addVertexBuffer(m_VBO);
            m_VAO->setIndexBuffer(m_EBO);
        }
        else
        {
            m_VBO->setData((void*)m_V.data(), sizeof(float) * m_V.size() * 8);
        }

        m_NeedUpdateBuffer = false;
    }
    
}