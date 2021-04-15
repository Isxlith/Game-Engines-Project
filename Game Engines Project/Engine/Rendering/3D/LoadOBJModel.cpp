#include "LoadOBJModel.h"

LoadOBJModel::LoadOBJModel() : vertices(vector<vec3>()), normals(vector<vec3>()), textureCoords(vector<vec2>()), indices(vector<unsigned int>()), normalIndices(vector<unsigned int>()), 
textureIndices(vector<unsigned int>()), meshVertices(vector<Vertex>()), subMeshes(vector<SubMesh>()), currentMaterial(Material())
{
	vertices.reserve(200);
	normals.reserve(200);
	textureCoords.reserve(200);
	indices.reserve(200);
	normalIndices.reserve(200);
	textureIndices.reserve(200);
	meshVertices.reserve(200);
	subMeshes.reserve(10);
}

LoadOBJModel::~LoadOBJModel()
{
	vertices.clear();
	normals.clear();
	textureCoords.clear();
	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();
	subMeshes.clear();
}

void LoadOBJModel::LoadModel(const string& objFilePath_, const string& mtlFilePath_)
{
	LoadMaterialLibrary(mtlFilePath_);
	LoadModel(objFilePath_);
}

vector<SubMesh> LoadOBJModel::GetSubMeshes()
{
	return subMeshes;
}

void LoadOBJModel::LoadModel(const string& filePath_)
{
	ifstream in(filePath_.c_str(), ios::in);
	if (!in)
	{
		Debug::Error("Cannot open OBJ file: " + filePath_, "LoadOBJModel.cpp", __LINE__);
		return;
	}

	string line;
	boundingBox.maxVert = vec3(-1000.0f);
	boundingBox.minVert = vec3(1000.0f);

	while (getline(in, line))
	{
		// Vertex Data
		if (line.substr(0, 2) == "v ")
		{
			stringstream v(line.substr(2));
			float x, y, z;
			v >> x >> y >> z;
			vertices.push_back(vec3(x, y, z));

			if (x > boundingBox.maxVert.x)
			{
				boundingBox.maxVert.x = x;
			}

			if (y > boundingBox.maxVert.y)
			{
				boundingBox.maxVert.y = y;
			}

			if (z > boundingBox.maxVert.z)
			{
				boundingBox.maxVert.z = z;
			}

			if (x < boundingBox.minVert.x)
			{
				boundingBox.minVert.x = x;
			}

			if (y < boundingBox.minVert.y)
			{
				boundingBox.minVert.y = y;
			}

			if (z < boundingBox.minVert.z)
			{
				boundingBox.minVert.z = z;
			}
		}

		// Normal Data
		else if (line.substr(0, 3) == "vn ")
		{
			stringstream vn(line.substr(2));
			float x, y, z;
			vn >> x >> y >> z;
			normals.push_back(vec3(x, y, z));
		}

		// Texture Data
		else if (line.substr(0, 3) == "vt ")
		{
			stringstream vt(line.substr(2));
			float x, y;
			vt >> x >> y;
			textureCoords.push_back(vec2(x, y));
		}

		// Face Data
		else if (line.substr(0, 2) == "f ")
		{
			stringstream f;
			unsigned int index[3], texCoord[3], norm[3];
			string str = line.substr(2);

			for (int i = 0; i < 6; i++)
			{
				str.replace(str.find("/"), 1, " ");
			}

			f << str;
			f >> index[0] >> texCoord[0] >> norm[0] >> index[1] >> texCoord[1] >> norm[1] >> index[2] >> texCoord[2] >> norm[2];

			indices.push_back(index[0] - 1);
			indices.push_back(index[1] - 1);
			indices.push_back(index[2] - 1);
			textureIndices.push_back(texCoord[0] - 1);
			textureIndices.push_back(texCoord[1] - 1);
			textureIndices.push_back(texCoord[2] - 1);
			normalIndices.push_back(norm[0] - 1);
			normalIndices.push_back(norm[1] - 1);
			normalIndices.push_back(norm[2] - 1);
		}

		else if (line.substr(0, 7) == "usemtl ")
		{
			if (indices.size() > 0)
			{
				PostProcessing();
			}
			LoadMaterial(line.substr(7));
		}
	}
	PostProcessing();
}

void LoadOBJModel::PostProcessing()
{
	for (unsigned int i = 0; i < indices.size(); i++)
	{
		Vertex vert;
		vert.pos = vertices[indices[i]];
		vert.normal = normals[normalIndices[i]];
		vert.textureCoords = textureCoords[textureIndices[i]];
		meshVertices.push_back(vert);
	}
	SubMesh mesh;
	mesh.vertexList = meshVertices;
	mesh.meshIndices = indices;
	mesh.material = currentMaterial;

	subMeshes.push_back(mesh);

	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();

	currentMaterial = Material();
}

void LoadOBJModel::LoadMaterial(const string& matName_)
{
	currentMaterial = MaterialHandler::GetInstance()->GetMaterial(matName_);
}

void LoadOBJModel::LoadMaterialLibrary(const string& matFilePath_)
{
	MaterialLoader::LoadMaterial(matFilePath_);
}