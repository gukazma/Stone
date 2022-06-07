#include "AssimpMesh.h"
#include <assimp/cimport.h>
#include <assimp/postprocess.h>
#include <string>
#include <Core/Base/macro.h>

#include<vcg/complex/algorithms/create/platonic.h>

namespace Stone
{
	AssimpMesh::AssimpMesh(const aiMesh* mesh, const aiScene* scene, AssimpScene* assimpscene)
	{
		m_MeshIndex = assimpscene->m_Meshs.size();
		LOG_DEBUG("Mesh index: {0}", m_MeshIndex);
		m_MeshName = mesh->mName.C_Str();
		m_Path = assimpscene->m_Path;
		m_Directory = assimpscene->m_Directory;
		loadMesh(mesh);
		loadTexture(mesh, scene);
		if(mesh->HasBones()) loadBone(mesh, assimpscene);
		updateBuffer();
	}
	void AssimpMesh::loadMesh(const aiMesh* mesh)
	{
		LOG_DEBUG("mesh->mVertices: {0}", mesh->mNumVertices);
		for (size_t i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex v;
			v.px = mesh->mVertices[i].x;
			v.py = mesh->mVertices[i].y;
			v.pz = mesh->mVertices[i].z;
			v.u = mesh->mTextureCoords[0]==nullptr ? 0 : mesh->mTextureCoords[0][i].x;
			v.v = mesh->mTextureCoords[0]==nullptr ? 0 : mesh->mTextureCoords[0][i].y;
			v.nx = mesh->mNormals[i].x;
			v.ny = mesh->mNormals[i].y;
			v.nz = mesh->mNormals[i].z;
			v.type = mesh->mNumBones > 0 ? VERTEX_WITH_BONE : VERTEX_ONLY;
			m_V.push_back(v);
		}

		for (size_t i = 0; i < mesh->mNumFaces; i++)
		{
			const aiFace* face = &mesh->mFaces[i];

			if (face->mNumIndices != 3)
			{
				LOG_ERROR("Stone only support TriMesh")
					return;
			}
			m_I.push_back(face->mIndices[0]);
			m_I.push_back(face->mIndices[1]);
			m_I.push_back(face->mIndices[2]);
		}
	}
	void AssimpMesh::loadTexture(const aiMesh* mesh, const aiScene* scene)
	{
		const aiMaterial* mt = scene->mMaterials[mesh->mMaterialIndex];

		LOG_DEBUG("texture count: {0}", mt->GetTextureCount(aiTextureType_DIFFUSE))

		if (mt->GetTextureCount(aiTextureType_DIFFUSE) == 0) return;

		aiString str;
		mt->GetTexture(aiTextureType_DIFFUSE, 0, &str);


		std::string filename = std::string(str.data);

		filename = m_Directory + '/' + filename;
		LOG_DEBUG("texture filename: {0}", filename);
		m_Texture = PublicSingleton<TexturePool>::getInstance().getTexture(filename);
	}
	void AssimpMesh::loadBone(const aiMesh* mesh, AssimpScene* assimpscene)
	{
		for (size_t i = 0; i < mesh->mNumBones; i++)
		{
			std::string boneName = mesh->mBones[i]->mName.C_Str();
			uint32_t boneIndex = 0;
			if (assimpscene->m_BoneMapping.find(boneName) == assimpscene->m_BoneMapping.end())
			{
				boneIndex = assimpscene->m_NumBone;
				assimpscene->m_BoneMapping[boneName] = boneIndex;
				glm::mat4 boneOffset = glm::mat4(1);
				memcpy(&boneOffset, &mesh->mBones[i]->mOffsetMatrix, sizeof(float) * 4 * 4);
				LOG_DEBUG("boneOffset[0][1]: {0}", boneOffset[0][1]);
				LOG_DEBUG("mesh->mBones[i]->mOffsetMatrix[0][1]: {0}", mesh->mBones[i]->mOffsetMatrix[0][1]);
				assimpscene->m_BoneOffset.push_back(boneOffset);
				assimpscene->m_NumBone++;
			}
			else
			{
				boneIndex = assimpscene->m_BoneMapping[boneName];
			}

			for (size_t j = 0; j < mesh->mBones[i]->mNumWeights; j++)
			{
				uint32_t vertexID = mesh->mBones[i]->mWeights[j].mVertexId;
				float weight = mesh->mBones[i]->mWeights[j].mWeight;
				m_V[vertexID].addBoneData(boneIndex, weight);
				m_V[vertexID].type = VERTEX_WITH_BONE;
			}
		}
	}
	void AssimpMesh::updateBuffer()
	{
		if (!m_NeedUpdateBuffer)
		{
			return;
		}
		if (m_VAO == nullptr || m_VBO == nullptr || m_EBO == nullptr)
		{
			m_VAO = VertexArray::create();
			m_VBO = VertexBuffer::create((void*)m_V.data(), sizeof(float) * m_V.size() * 17);
			m_VBO->setLayout({
			{ ShaderDataType::Float3, "in_Position" },
			{ ShaderDataType::Float3, "in_Normal" },
			{ ShaderDataType::Float2, "in_TexCoord" },
			{ ShaderDataType::Int4, "in_BoneIDs" },
			{ ShaderDataType::Float4, "in_BoneWeights" },
			{ ShaderDataType::Float, "in_VertexType" }
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