#include "MaterialLoader.h"

MaterialLoader::~MaterialLoader() {}

void MaterialLoader::LoadMaterial(string filePath_)
{
	ifstream in(filePath_.c_str(), ios::in);
	if (!in)
	{
		Debug::Error("Cannot open MTL file: " + filePath_, "MaterialLoader.cpp", __LINE__);
		return;
	}

	Material m = Material();
	string matName = "";
	string line;

	while (getline(in, line))
	{
		if (line.substr(0, 7) == "newmtl ")
		{
			if (m.diffuseMap != 0)
			{
				MaterialHandler::GetInstance()->AddMaterial(m);
				m = Material();
			}
			matName = line.substr(7);
			m.diffuseMap = LoadTexture(matName);
			m.name = matName;
		}

		else if (line.substr(0, 4) == "	Ns ")
		{
			stringstream ns(line.substr(4));
			ns >> m.shininess;
		}

		else if (line.substr(0, 3) == "	d ")
		{
			stringstream d(line.substr(3));
			d >> m.transparency;
		}

		else if (line.substr(0, 4) == "	Ka ")
		{
			stringstream ka(line.substr(4));
			ka >> m.ambient.x >> m.ambient.y >> m.ambient.z;
		}

		else if (line.substr(0, 4) == "	Kd ")
		{
			stringstream kd(line.substr(4));
			kd >> m.diffuse.x >> m.diffuse.y >> m.diffuse.z;
		}

		else if (line.substr(0, 4) == "	Ks ")
		{
			stringstream ks(line.substr(4));
			ks >> m.specular.x >> m.specular.y >> m.specular.z;
		}
	}

	if (m.diffuseMap != 0)
	{
		MaterialHandler::GetInstance()->AddMaterial(m);
	}
	in.close();
}

GLuint MaterialLoader::LoadTexture(string fileName_)
{
	GLuint currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
	if (currentTexture == 0)
	{
		TextureHandler::GetInstance()->CreateTexture(fileName_, "./Resources/Textures/" + fileName_ + ".png");
		currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
	}
	return currentTexture;
}