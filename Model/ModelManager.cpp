#include <stddef.h>
#include "ModelManager.h"
#include <iostream>

#include "../Thread/ObjectLoader.h"

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
	//this->threadPool = new ThreadPool("Model Manager Thread Pool", 5);
	//this->threadPool->startScheduler();

	///*for (int i = 0; i < 5; i++)
	//	this->loadSceneModels(i);*/

	//std::cout << "Model Manager Initialized: "<<this->modelList.size()<<" models loaded." << std::endl;

	sceneModelsData[0] = {
		ModelData("Fish","3D/Fish/fish.obj", {400.f, 0.f, 0.f}, {0.f, 60.f, 0.f}, {3.f, 3.f, 3.f}, "3D/Fish/textures/Fish_Albedo.png"),
		//ModelData("Cabbage","3D/Cabbage/cabbage.obj", {300.f, 0.f, 0.f}, {0.f, 60.f, 0.f}, {3.f, 3.f, 3.f}, "3D/Cabbage/textures/cabbage_albedo.jpeg"),
		////ModelData("Cupcake","3D/Cupcake/cupcake.obj", {400.f, 0.f, 0.f}, {0.f, 60.f, 0.f}, {3.f, 3.f, 3.f}, "3D/Cupcake/textures/model_edited_material_0.jpeg"),
		//ModelData("Toaster","3D/Toaster/toaster.obj", {500.f, 0.f, 0.f}, {0.f, 60.f, 0.f}, {3.f, 3.f, 3.f}, "3D/Toaster/textures/toster_Material_color.png"),
		//ModelData("Red Rose", "3D/Red Rose/red rose.obj", {500.f, 0.f, 0.f}, {0.f, 60.f, 0.f}, {3.f, 3.f, 3.f}, "3D/Red Rose/textures/Red_rose.jpeg")
	};

	sceneModelsData[1] = {
		ModelData("Shoe", "3D/Shoe/shoe.obj", {400.f, 0.f, 0.f}, {0.f, 60.f, 0.f}, {3.f, 3.f, 3.f}, "3D/Shoe/textures/nb574.jpeg"),
		//ModelData("Cup", "3D/Cup/cup.obj", {400.f, 0.f, 0.f}, {0.f, 60.f, 0.f}, {3.f, 3.f, 3.f}, "3D/Cup/textures/cup_albedo.png"),
		//ModelData("Burnt Croissant","3D/Burnt Croissant/BurntCroissant.obj", {200.f, 0.f, 0.f}, {0.f, 60.f, 0.f}, {3.f, 3.f, 3.f}, "3D/Burnt Croissant/textures/BurntCroissant.jpeg"),
		//ModelData("Chili","3D/Chili/chili.obj", {500.f, 0.f, 0.f}, {0.f, 60.f, 0.f}, {3.f, 3.f, 3.f}, "3D/Chili/textures/color.png"),
		//ModelData("Orchid","3D/Orchid/orchid.obj", {400.f, 0.f, 0.f}, {0.f, 60.f, 0.f}, {3.f, 3.f, 3.f}, "3D/Orchid/textures/color.jpeg")
	};

	sceneModelsData[2] = {
		ModelData("Lychee","3D/Lychees/lychee.obj", {400.f, 0.f, 0.f}, {0.f, 60.f, 0.f}, {3.f, 3.f, 3.f}, "3D/Lychees/textures/lychee.jpeg"),
		//ModelData("Bananacat","3D/Cat/banancat.obj", {0.f, 0.f, 0.f}, {0.f, 60.f, 0.f}, {0.5f, 0.5f, 0.5f}, "3D/Cat/banancattex.png"),
		//ModelData("Tank","3D/Tank/M1A1.obj", {-300.f, 0.f, 0.f}, {0.f, 180.f, 0.f}, {0.25f, 0.25f, 0.25f}, "3D/Tank/TankTex.png"),
		//ModelData("Grass","3D/Grass/Grass.obj", {0.f, 0.f, 0.f}, {0.f, 60.f, 0.f}, {0.2f, 0.2f, 0.2f}, "3D/Grass/GrassTex.png"),
		//ModelData("Flowers","3D/Flowers/Flower.obj", {0.f, 0.f, 0.f}, {0.f, 60.f, 0.f}, {250.f, 250.f, 250.f}, "3D/Flowers/FlowerTexA.png")
	};

	sceneModelsData[3] = {
		ModelData("Ant","3D/Ant/ant1.obj", {-150.f, 0.f, -200.f}, {0.f, 60.f, 0.f}, {0.03f, 0.03f, 0.03f}, "3D/Ant/ant_(1).png"),
		//ModelData("Tractor","3D/Car/Tractor.obj", {-100.f, 0.f, 0.f}, {0.f, 60.f, 0.f}, {3.f, 3.f, 3.f}, "3D/Car/TractorTex.jpg"),
		//ModelData("3D/Moon.obj", {-200.f, 0.f, 0.f}, {0.f, 0.f, 0.f}, {10.f, 10.f, 10.f}, "", {238.f / 255.f, 228.f / 255.f, 170.f / 255.f, 1.f}),
		//ModelData("Mouse","3D/Mouse/Mouse.obj", {100.f, 0.f, 0.f}, {0.f, 60.f, 0.f}, {10000.f, 10000.f, 10000.f}, "3D/Mouse/MouseTex.png"),
		//ModelData("Ground","3D/Ground/Ground.obj", {-100.f, 0.f, 0.f}, {0.f, 0.f, 0.f}, {100.f, 100.f, 100.f}, "3D/Ground/AddWater_basecolor.png")
	};

	sceneModelsData[4] = {
		ModelData("Macaron","3D/Macaron/macaron.obj", {400.f, 0.f, 0.f}, {0.f, 60.f, 0.f}, {3.f, 3.f, 3.f}, "3D/Macaron/textures/macaron_albedo.jpeg"),
		//ModelData("Bag","3D/Bag/bag.obj", {400.f, 0.f, 0.f}, {0.f, 60.f, 0.f}, {3.f, 3.f, 3.f}, "3D/Bag/textures/bag.jpeg"),
		//ModelData("Marshmallow","3D/Marshmallows/marshmallows.obj", {400.f, 0.f, 0.f}, {0.f, 60.f, 0.f}, {3.f, 3.f, 3.f}, "3D/Marshmallows/textures/MMW_CO.png"),
		//ModelData("Meat","3D/Meat/meat.obj", {400.f, 0.f, 0.f}, {0.f, 60.f, 0.f}, {3.f, 3.f, 3.f}, "3D/Meat/textures/color.jpeg"),
		//ModelData("Dried Rose", "3D/Dried Rose/dried rose.obj", {400.f, 0.f, 0.f}, {0.f, 60.f, 0.f}, {3.f, 3.f, 3.f}, "3D/Dried Rose/textures/rosa02.jpeg")
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

void ModelManager::loadSceneModels(int id)
{
	switch (id)
	{
	case 0:
		this->loadScene0Models();
		break;
	case 1:
		this->loadScene1Models();
		break;
	case 2:
		this->loadScene2Models();
		break;
	case 3:
		this->loadScene3Models();
		break;
	case 4:
		this->loadScene4Models();
		break;
	}
}

void ModelManager::loadScene0Models()
{
	// 15
	ObjectLoader* fish = new ObjectLoader("3D/Fish/fish.obj", "3D/Fish/textures/Fish_Albedo.png", "3D/Fish/textures/Fish_Normalmap.png", "Fish",
		glm::vec3(400.f, 0.f, 0.f),        //pos
		glm::vec3(3.f),                     //scale
		glm::vec3(0.f, 60.f, 0.f));  //rotate
	threadPool->scheduleTask(fish);

	// 11
	ObjectLoader* cabbage = new ObjectLoader("3D/Cabbage/cabbage.obj", "3D/Cabbage/textures/cabbage_albedo.jpeg", "3D/Cabbage/textures/cabbage_normal.jpeg", "Cabbage",
		glm::vec3(300.f, 0.f, 0.f),        //pos
		glm::vec3(3.f),                     //scale
		glm::vec3(0.f, 60.f, 0.f));  //rotate
	threadPool->scheduleTask(cabbage);

	// 14
	ObjectLoader* cupcake = new ObjectLoader("3D/Cupcake/cupcake.obj", "3D/Cupcake/textures/model_edited_material_0.jpeg", "", "Cupcake",
		glm::vec3(400.f, 0.f, 0.f),        //pos
		glm::vec3(3.f),                     //scale
		glm::vec3(0.f, 60.f, 0.f));  //rotate
	threadPool->scheduleTask(cupcake);

	// 23
	ObjectLoader* toaster = new ObjectLoader("3D/Toaster/toaster.obj", "3D/Toaster/textures/toster_Material_color.png", "", "Toaster",
		glm::vec3(500.f, 0.f, 0.f),        //pos
		glm::vec3(3.f),                     //scale
		glm::vec3(0.f, 60.f, 0.f));  //rotate
	threadPool->scheduleTask(toaster);

	// 24
	ObjectLoader* redRose = new ObjectLoader("3D/Red Rose/red rose.obj", "3D/Red Rose/textures/Red_rose.jpeg", "3D/Red Rose/textures/Red_rose_normal.jpg", "Red Rose",
		glm::vec3(500.f, 0.f, 0.f),        //pos
		glm::vec3(3.f),                     //scale
		glm::vec3(0.f, 60.f, 0.f));  //rotate
	threadPool->scheduleTask(redRose);
}

void ModelManager::loadScene1Models()
{
	// 21
	ObjectLoader* shoe = new ObjectLoader("3D/Shoe/shoe.obj", "3D/Shoe/textures/nb574.jpeg", "3D/Shoe/textures/normals.jpeg", "Shoe",
		glm::vec3(400.f, 0.f, 0.f),        //pos
		glm::vec3(3.f),                     //scale
		glm::vec3(0.f, 60.f, 0.f));  //rotate
	threadPool->scheduleTask(shoe);

	// 13
	ObjectLoader* cup = new ObjectLoader("3D/Cup/cup.obj", "3D/Cup/textures/cup_albedo.png", "3D/Cup/textures/cup_normal.png", "Cup",
		glm::vec3(400.f, 0.f, 0.f),        //pos
		glm::vec3(3.f),                     //scale
		glm::vec3(0.f, 60.f, 0.f));  //rotate
	threadPool->scheduleTask(cup);

	// 10
	ObjectLoader* burntCroissant = new ObjectLoader("3D/Burnt Croissant/BurntCroissant.obj", "3D/Burnt Croissant/textures/BurntCroissant.jpeg", "", "Burnt Croissant",
		glm::vec3(200.f, 0.f, 0.f),        //pos
		glm::vec3(3.f),                     //scale
		glm::vec3(0.f, 60.f, 0.f));  //rotate
	threadPool->scheduleTask(burntCroissant);

	// 25
	ObjectLoader* chili = new ObjectLoader("3D/Chili/chili.obj", "3D/Chili/textures/color.png", "3D/Chili/textures/normal.png", "Chili",
		glm::vec3(500.f, 0.f, 0.f),        //pos
		glm::vec3(3.f),                     //scale
		glm::vec3(0.f, 60.f, 0.f));  //rotate
	threadPool->scheduleTask(chili);

	// 22
	ObjectLoader* orchid = new ObjectLoader("3D/Orchid/orchid.obj", "3D/Orchid/textures/color.jpeg", "", "Orchid",
		glm::vec3(400.f, 0.f, 0.f),        //pos
		glm::vec3(3.f),                     //scale
		glm::vec3(0.f, 60.f, 0.f));  //rotate
	threadPool->scheduleTask(orchid);
}

void ModelManager::loadScene2Models()
{
	// 17
	ObjectLoader* lychees = new ObjectLoader("3D/Lychees/lychee.obj", "3D/Lychees/textures/lychee.jpeg", "3D/Lychees/textures/normals.jpeg", "Lychees",
		glm::vec3(400.f, 0.f, 0.f),        //pos
		glm::vec3(3.f),                     //scale
		glm::vec3(0.f, 60.f, 0.f));  //rotate
	threadPool->scheduleTask(lychees);

	// 3
	ObjectLoader* banancat = new ObjectLoader("3D/Cat/banancat.obj", "3D/Cat/banancattex.png", "", "Banana Cat",
		glm::vec3(0.f, 0, 0.f),		// pos
		glm::vec3(0.5f),				// scale
		glm::vec3(0.f));		// rotate
	threadPool->scheduleTask(banancat);

	// 1
	ObjectLoader* tank = new ObjectLoader("3D/Tank/M1A1.obj", "3D/Tank/TankTex.png", "3D/Tank/TankNorm.png", "Tank",
		glm::vec3(-300.f, 0.f, 0.f),           // pos
		glm::vec3(0.25f),                   // scale
		glm::vec3(0.f, 180.f, 0.f));          // rotate
	threadPool->scheduleTask(tank);

	// 6
	ObjectLoader* grass = new ObjectLoader("3D/Grass/Grass.obj", "3D/Grass/GrassTex.png", "", "Grass",
		glm::vec3(0.f, 0.f, 0.f),      //pos
		glm::vec3(0.2f),                    //scale
		glm::vec3(0.f, 60.f, 0.f));         //rotate
	threadPool->scheduleTask(grass);

	// 8
	ObjectLoader* flower = new ObjectLoader("3D/Flowers/Flower.obj", "3D/Flowers/FlowerTexA.png", "", "Flower",
		glm::vec3(0.f, 0.f, 0.f),        //pos
		glm::vec3(250.f),                   //scale
		glm::vec3(0.f, 60.f, 0.f));         //rotate
	threadPool->scheduleTask(flower);
}

void ModelManager::loadScene3Models()
{
	// 5
	ObjectLoader* ant = new ObjectLoader("3D/Ant/ant1.obj", "3D/Ant/ant_(1).png", "", "Ant",
		glm::vec3(-150.f, 0.f, -200.f),     //pos
		glm::vec3(0.03f),                   //scale
		glm::vec3(0.f, 60.f, 0.f));         //rotate
	threadPool->scheduleTask(ant);

	// 9
	ObjectLoader* tractor = new ObjectLoader("3D/Car/Tractor.obj", "3D/Car/TractorTex.jpg", "", "Tractor",
		glm::vec3(-100.f, 0.f, 0.f),        //pos
		glm::vec3(3.f),                     //scale
		glm::vec3(0.f, 60.f, 0.f));         //rotate
	threadPool->scheduleTask(tractor);

	// 2
	ObjectLoader* moon = new ObjectLoader("3D/Moon.obj", "", "", "Moon",
		glm::vec3(-200.f, 0, 0.f),	// pos
		glm::vec3(10.f),				// scale
		glm::vec3(0.f),               // rotate
		glm::vec4(238.f / 255.f, 228.f / 255.f, 170.f / 255.f, 1.f)); // color
	threadPool->scheduleTask(moon);

	// 7
	ObjectLoader* mouse = new ObjectLoader("3D/Mouse/Mouse.obj", "3D/Mouse/MouseTex.png", "", "Mouse",
		glm::vec3(100.f, 0.f, 0.f),        //pos
		glm::vec3(10000.f),                 //scale
		glm::vec3(0.f, 60.f, 0.f));         //rotate
	threadPool->scheduleTask(mouse);

	// 4
	ObjectLoader* ground = new ObjectLoader("3D/Ground/Ground.obj", "3D/Ground/AddWater_basecolor.png", "3D/Ground/AddWater_normal.png", "Ground",
		glm::vec3(-100.f, 0.f, 0.f),     //pos
		glm::vec3(100.f),                     //scale
		glm::vec3(0.f, 0.f, 0.f));         //rotate
	threadPool->scheduleTask(ground);
}

void ModelManager::loadScene4Models()
{
	// 18
	ObjectLoader* macaron = new ObjectLoader("3D/Macaron/macaron.obj", "3D/Macaron/textures/macaron_albedo.jpeg", "3D/Macaron/textures/macaron_normal.jpeg", "Macaron",
		glm::vec3(400.f, 0.f, 0.f),        //pos
		glm::vec3(3.f),                     //scale
		glm::vec3(0.f, 60.f, 0.f));  //rotate
	threadPool->scheduleTask(macaron);

	// 16
	ObjectLoader* bag = new ObjectLoader("3D/Bag/bag.obj", "3D/Bag/textures/bag.jpeg", "3D/Bag/textures/normal.jpeg", "Bag",
		glm::vec3(400.f, 0.f, 0.f),        //pos
		glm::vec3(3.f),                     //scale
		glm::vec3(0.f, 60.f, 0.f));  //rotate
	threadPool->scheduleTask(bag);

	// 19
	ObjectLoader* marshmallows = new ObjectLoader("3D/Marshmallows/marshmallows.obj", "3D/Marshmallows/textures/MMW_CO.png", "", "Marshmallows",
		glm::vec3(400.f, 0.f, 0.f),        //pos
		glm::vec3(3.f),                     //scale
		glm::vec3(0.f, 60.f, 0.f));  //rotate
	threadPool->scheduleTask(marshmallows);

	// 20
	ObjectLoader* meat = new ObjectLoader("3D/Meat/meat.obj", "3D/Meat/textures/color.jpeg", "", "Meat",
		glm::vec3(400.f, 0.f, 0.f),        //pos
		glm::vec3(3.f),                     //scale
		glm::vec3(0.f, 60.f, 0.f));  //rotate
	threadPool->scheduleTask(meat);

	// 12
	ObjectLoader* driedRose = new ObjectLoader("3D/Dried Rose/dried rose.obj", "3D/Dried Rose/textures/rosa02.jpeg", "3D/Dried Rose/textures/normals.jpeg", "Dried Rose",
		glm::vec3(400.f, 0.f, 0.f),        //pos
		glm::vec3(3.f),                     //scale
		glm::vec3(0.f, 60.f, 0.f));  //rotate
	threadPool->scheduleTask(driedRose);
}

void ModelManager::addObject(Model* model)
{
	model->setActive(false);
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