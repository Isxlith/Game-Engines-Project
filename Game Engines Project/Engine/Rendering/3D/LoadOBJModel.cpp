#include "LoadOBJModel.h"

LoadOBJModel::LoadOBJModel() : vertices(vector<vec3>()), normals(vector<vec3>()), textureCoords(vector<vec2>()), indices(vector<unsigned int>()), normalIndices(vector<unsigned int>()), 
textureIndices(vector<unsigned int>()), meshVertices(vector<Vertex>()), subMeshes(vector<SubMesh>()), currentTexture(0)
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

	while (getline(in, line))
	{
		// Vertex Data
		if (line.substr(0, 2) == "v ")
		{
			stringstream v(line.substr(2));
			float x, y, z;
			v >> x >> y >> z;
			vertices.push_back(vec3(x, y, z));
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
			stringstream f(line.substr(2));
			int set1, set2, set3;
			int counter = 0;

			f >> set1 >> set2 >> set3;
			cout << set1 << endl;

			//while (getline(f1, segment, '/'))
			//{
			//	//cout << segment << endl;
			//	if (counter == 0)
			//	{
			//		cout << "Index "<< segment << endl;
			//		counter++;
			//	}
			//	else if (counter == 1)
			//	{
			//		cout << "Texture " << segment << endl;
			//		counter++;
			//	}
			//	else if (counter == 2)
			//	{
			//		cout << "Normal " << segment << endl;
			//		counter = 0;
			//	}
			//}

			/*indices.push_back(index[0]);
			indices.push_back(index[1]);
			indices.push_back(index[2]);
			textureIndices.push_back(texCoord[0]);
			textureIndices.push_back(texCoord[1]);
			textureIndices.push_back(texCoord[2]);
			normalIndices.push_back(norm[0]);
			normalIndices.push_back(norm[1]);
			normalIndices.push_back(norm[2]);*/
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
	mesh.textureID = currentTexture;

	subMeshes.push_back(mesh);

	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();

	currentTexture = 0;
}

void LoadOBJModel::LoadMaterial(const string& matName_)
{
	currentTexture = TextureHandler::GetInstance()->GetTexture(matName_);
	if (currentTexture == 0)
	{
		TextureHandler::GetInstance()->CreateTexture(matName_, "Resources/Textures/" + matName_ + ".png");
		currentTexture = TextureHandler::GetInstance()->GetTexture(matName_);
	}
}

void LoadOBJModel::LoadMaterialLibrary(const string& matFilePath_)
{
	ifstream in(matFilePath_.c_str(), ios::in);
	if (!in)
	{
		Debug::Error("Cannot open MTL file: " + matFilePath_, "LoadOBJModel.cpp", __LINE__);
	}
	string line;

	while (getline(in, line))
	{
		if (line.substr(0, 7) == "newmtl ")
		{
			LoadMaterial(line.substr(7));
		}
	}
}