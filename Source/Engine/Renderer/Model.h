#pragma once
#include "Framework/Resource/Resource.h"
#include "VertexBuffer.h"
#include "Material.h"

struct aiNode;
struct aiMesh;
struct aiScene;

namespace nc
{
	class Model : public Resource
	{
	public:
		// vertex attributes
		struct vertex_t
		{
			glm::vec3 position;
			glm::vec2 texcoord;
			glm::vec3 normal;
			glm::vec3 tangent;
		};

	public:
		bool Create(std::string filename, ...) override;
		bool Load(const std::string& filename);
		void Draw(GLenum primitve = GL_TRIANGLES); //primitive <set the default parameter to GL_TRIANGLE>)

		void SetMaterial(res_t<Material> material) { m_material = material; } //<set the class material> 
		res_t<Material> GetMaterial() { return m_material; } //<return the class material>

	private:
		void ProcessNode(aiNode* node, const aiScene* scene);
		void ProcessMesh(aiMesh* mesh, const aiScene* scene);

	private:
		res_t<VertexBuffer> m_vertexBuffer;
		res_t<Material> m_material;
	};
}