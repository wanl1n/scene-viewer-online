#include <stddef.h>
#include "ModelManager.h"
#include <iostream>
#include <random>

ModelManager* ModelManager::sharedInstance = NULL;

ModelManager* ModelManager::getInstance() {
	if (sharedInstance == NULL) {
		//initialize
		sharedInstance = new ModelManager();
	}

	return sharedInstance;
}

void ModelManager::initialize()
{
	sceneModelsData[0] = {
		ModelData("Fish","3D/Fish/fish.obj", ModelManager::randomPos(), {0.f, 60.f, 0.f}, {3.f, 3.f, 3.f}, "3D/Fish/textures/Fish_Albedo.png"),
		ModelData("Cabbage","3D/Cabbage/cabbage.obj", ModelManager::randomPos(), {0.f, 60.f, 0.f}, {3.f, 3.f, 3.f}, "3D/Cabbage/textures/cabbage_albedo.jpeg"),
		ModelData("Cupcake","3D/Cupcake/cupcake.obj", ModelManager::randomPos(), {0.f, 60.f, 0.f}, {3.f, 3.f, 3.f}, "3D/Cupcake/textures/model_edited_material_0.jpeg"),
		ModelData("Toaster","3D/Toaster/toaster.obj", ModelManager::randomPos(), {0.f, 60.f, 0.f}, {3.f, 3.f, 3.f}, "3D/Toaster/textures/toster_Material_color.png"),
		ModelData("Red Rose", "3D/Red Rose/red rose.obj", ModelManager::randomPos(), {0.f, 60.f, 0.f}, {3.f, 3.f, 3.f}, "3D/Red Rose/textures/Red_rose.jpeg")
	};

	sceneModelsData[1] = {
		ModelData("Shoe", "3D/Shoe/shoe.obj", ModelManager::randomPos(), {0.f, 0.f, 0.f}, {3.f, 3.f, 3.f}, "3D/Shoe/textures/nb574.jpeg"),
		ModelData("Cup", "3D/Cup/cup.obj", ModelManager::randomPos(), {0.f, 60.f, 0.f}, {3.f, 3.f, 3.f}, "3D/Cup/textures/cup_albedo.png"),
		ModelData("Burnt Croissant","3D/Burnt Croissant/BurntCroissant.obj", ModelManager::randomPos(), {0.f, 60.f, 0.f}, {30.f, 30.f, 30.f}, "3D/Burnt Croissant/textures/BurntCroissant.jpeg"),
		ModelData("Chili","3D/Chili/chili.obj", ModelManager::randomPos(), {0.f, 60.f, 0.f}, {3.f, 3.f, 3.f}, "3D/Chili/textures/color.png"),
		ModelData("Orchid","3D/Orchid/orchid.obj", ModelManager::randomPos(), {0.f, 60.f, 0.f}, {3.f, 3.f, 3.f}, "3D/Orchid/textures/color.jpeg")
	};

	sceneModelsData[2] = {
		ModelData("Lychee","3D/Lychees/lychee.obj", ModelManager::randomPos(), {0.f, 60.f, 0.f}, {30.f, 30.f, 30.f}, "3D/Lychees/textures/lychee.jpeg"),
		ModelData("Bananacat","3D/Cat/banancat.obj", ModelManager::randomPos(), {0.f, 60.f, 0.f}, {0.5f, 0.5f, 0.5f}, "3D/Cat/banancattex.png"),
		ModelData("Tank","3D/Tank/M1A1.obj", ModelManager::randomPos(), {0.f, 180.f, 0.f}, {0.25f, 0.25f, 0.25f}, "3D/Tank/TankTex.png"),
		ModelData("Grass","3D/Grass/Grass.obj", ModelManager::randomPos(), {0.f, 60.f, 0.f}, {0.2f, 0.2f, 0.2f}, "3D/Grass/GrassTex.png"),
		ModelData("Flowers","3D/Flowers/Flower.obj", ModelManager::randomPos(), {0.f, 60.f, 0.f}, {250.f, 250.f, 250.f}, "3D/Flowers/FlowerTexA.png")
	};

	sceneModelsData[3] = {
		ModelData("Ant","3D/Ant/ant1.obj", ModelManager::randomPos(), {0.f, 60.f, 0.f}, {0.03f, 0.03f, 0.03f}, "3D/Ant/ant_(1).png"),
		ModelData("Tractor","3D/Car/Tractor.obj", ModelManager::randomPos(), {0.f, 60.f, 0.f}, {3.f, 3.f, 3.f}, "3D/Car/TractorTex.jpg"),
		ModelData("Moon", "3D/Moon.obj", ModelManager::randomPos(), {0.f, 0.f, 0.f}, {10.f, 10.f, 10.f}, ""),
		ModelData("Mouse","3D/Mouse/Mouse.obj", ModelManager::randomPos(), {0.f, 60.f, 0.f}, {1000.f, 1000.f, 1000.f}, "3D/Mouse/MouseTex.png"),
		ModelData("Ground","3D/Ground/Ground.obj", ModelManager::randomPos(), {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f}, "3D/Ground/AddWater_basecolor.png")
	};

	sceneModelsData[4] = {
		ModelData("Macaron","3D/Macaron/macaron.obj", ModelManager::randomPos(), {0.f, 60.f, 0.f}, {3.f, 3.f, 3.f}, "3D/Macaron/textures/macaron_albedo.jpeg"),
		ModelData("Bag","3D/Bag/bag.obj", ModelManager::randomPos(), {0.f, 60.f, 0.f}, {3.f, 3.f, 3.f}, "3D/Bag/textures/bag.jpeg"),
		ModelData("Marshmallow","3D/Marshmallows/marshmallows.obj", ModelManager::randomPos(), {0.f, 60.f, 0.f}, {100.f, 100.f, 100.f}, "3D/Marshmallows/textures/MMW_CO.png"),
		ModelData("Meat","3D/Meat/meat.obj", ModelManager::randomPos(), {0.f, 60.f, 0.f}, {3.f, 3.f, 3.f}, "3D/Meat/textures/color.jpeg"),
		ModelData("Dried Rose", "3D/Dried Rose/dried rose.obj", ModelManager::randomPos(), {0.f, 60.f, 0.f}, {3.f, 3.f, 3.f}, "3D/Dried Rose/textures/rosa02.jpeg")
	};
}

Model* ModelManager::findObjectByName(std::string name)
{
	if (this->modelMap[name] != NULL) {
		return this->modelMap[name];
	}
	else {
		//std::cout << "Object " << name << " not found!";
		return nullptr;
	}
}

List ModelManager::getRandomModels(int sceneID)
{
	List randomModels;
	int startingIndex = 5 * (sceneID);
	if (startingIndex + 5 > this->modelList.size()) 
		return std::vector<Model*>(this->modelList.size()%5, nullptr);
	
	for (int i = startingIndex; i < startingIndex+5; i++) {
		randomModels.push_back(this->modelList[i]);
	}

	return randomModels;
}

List ModelManager::getModelsByName(std::vector<std::string> names)
{
	List models(5, nullptr);

	for (int i = 0; i < 5; i++)
	{
		Model* model = findObjectByName(names[i]);
		models[i] = model;
	}

	return models;
}

List ModelManager::getAllObjects()
{
	return this->modelList;
}

int ModelManager::activeObjects()
{
	return this->modelList.size();
}

std::unordered_map<int, std::vector<ModelData>> ModelManager::getSceneModelsData()
{
	return this->sceneModelsData;
}

void ModelManager::update(float deltaTime)
{
	//std::cout << "Delta time: " << deltaTime.asSeconds() << "\n";
	for (int i = 0; i < this->modelList.size(); i++) {
		if (this->modelList[i]->isActive())
		{
			this->modelList[i]->update(deltaTime);
			//std::cout << "Model " << modelList[i]->getName() << " updating." << std::endl;
		}
	}
}

void ModelManager::draw(GLuint* shaderProgram, bool texExists)
{
	for (int i = 0; i < this->modelList.size(); i++) {
		if (this->modelList[i]->isActive())
		{
			this->modelList[i]->draw(shaderProgram, texExists);
			//std::cout << "Drawing " << this->modelList[i]->getName() << std::endl;
		}
	}
}

void ModelManager::addObject(Model* model)
{
	//model->setActive(false);
	//also initialize the oject
	this->modelMap[model->getName()] = model;
	this->modelList.push_back(model);
	//this->modelMap[model->getName()]->initialize();
}

void ModelManager::deleteObject(Model* model)
{
	this->modelMap.erase(model->getName());

	int index = -1;
	for (int i = 0; i < this->modelList.size(); i++) {
		if (this->modelList[i] == model) {
			index = i;
			break;
		}
	}

	if (index != -1) {
		this->modelList.erase(this->modelList.begin() + index);
	}

	delete model;
}

void ModelManager::deleteObjectByName(std::string name)
{
	Model* object = this->findObjectByName(name);

	if (object != NULL) {
		this->deleteObject(object);
	}
}

std::string ModelManager::getModelBuffer(std::string modelPath)
{
	std::string modelData = "";

	std::ifstream file(modelPath, std::ios::binary);
	if (file)
	{
		std::ostringstream ss;
		ss << file.rdbuf();
		modelData = ss.str(); 
		file.close();
	}
	else
	{
		std::cerr << "Failed to open OBJ file: " << modelPath << std::endl;
	}

	return modelData;
}

std::tuple<std::vector<uint8_t>, int, int> ModelManager::getTextureDataAndSize(std::string texPath)
{
	int img_width, img_height, color_channels;

	unsigned char* text_bytes = stbi_load(texPath.c_str(), &img_width, &img_height, &color_channels, 0);

	if (text_bytes == nullptr) {
		std::cerr << "Failed to load texture: " << texPath << std::endl;
		return {};
	}

	size_t dataSize = img_width * img_height * color_channels;

	std::vector<uint8_t> textureData(text_bytes, text_bytes + dataSize);

	stbi_image_free(text_bytes);

	return std::make_tuple(textureData, img_width, img_height);
}

glm::vec3 ModelManager::randomPos()
{
	float x = ModelManager::randomFloat(-300, 300);
	float y = ModelManager::randomFloat(-100, 100);
	float z = ModelManager::randomFloat(-300, 300);
	return glm::vec3(x, y, z);
}

float ModelManager::randomFloat(float min, float max)
{
	static std::random_device rd;  // Seed generator
	static std::mt19937 rng(rd()); // Random number engine
	std::uniform_real_distribution<float> dist(min, max);
	return dist(rng);
}