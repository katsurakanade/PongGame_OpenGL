#pragma once

class Resource;
class Camera;

enum Layer {
	_Camera,_3D,_Light,_2D
};

class Application
{

protected:

	std::list<Resource*> mGameObject[4];
	std::vector<std::string> mRenderLayerString{ "Camera","3D","Light","2D" };

	bool mGameActive;
	Camera* cm;

public:
	
	bool Init();
	void Uninit();
	void Update();
	void Render();

	template <typename T>
	T* AddGameObject(int layer) {
		T* gameObject = new T();
		mGameObject[layer].emplace_back(gameObject);
		gameObject->Init();
		return gameObject;
	};
	template <typename T>
	T* GetGameObject(int layer) {
		for (Resource* obj : mGameObject[layer]) {
			if (typeid(*obj) == typeid(T)) {
				return (T*)obj;
			}
		}
		return NULL;
	};
	template <typename T>
	std::vector<T*> GetGameObjects(int layer) {
		std::vector<T*> objects;
		for (Resource* obj : mGameObject[layer]) {
			if (typeid(*obj) == typeid(T)) {
				objects.emplace_back((T*)obj);
			}
		}
		return objects;
	};
	template <typename T>
	T* GetGameObjectWithName(int layer,std::string name) {
		for (Resource* obj : mGameObject[layer]) {
			if (typeid(*obj) == typeid(T)) {
				if (obj->Name == name)
					return (T*)obj;
			}
		}
		return NULL;
	};

};

