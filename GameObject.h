#pragma once
class GameObject;
class Transform;
class Component;
extern char debug[3][128];
extern char error[128];
class Transform
{
	typedef struct tagPOSITION {
		float x;
		float y;
	}POSITION;
	typedef struct tagScale {
		int width;
		int height;
	}SCALE;

public:
	Transform();
	~Transform();
	POSITION position;
	SCALE size;
	vector<Transform*> child;
	Transform* parent;
	GameObject* gameObject;
	int siblingIdx;
	bool Move(float x, float y);
	bool MoveX(float x);
	bool MoveY(float y);
	bool CheckCollision(float tempX, float tempY);
	int GetChildCount() { return child.size(); }
	Transform* GetChild(int i);
	void AddChild(GameObject* gameObject);
	void AddChild(Transform* transform);
	void DetachChild(int idx);
	void DetachParent();


	void SetX(float x) { position.x = x; }
	void SetY(float y) { position.y = y; }
	void SetPosition(float x, float y) { position.x = x; position.y = y; }
	float GetX() { return position.x;}
	float GetY() { return position.y; }

	void SetWidth(int width) { size.width = width; }
	void SetHeight(int height) { size.height = height; }
	void SetSize(int width, int height) { size.width = width, size.height = height; }
	int GetWidth() { return size.width; }
	int GetHeight() { return size.height; }

};

class Component
{
public:
	Component();
	Component(GameObject* gameObject);
	~Component();
	GameObject* gameObject;
	Transform* transform;
	bool enable;
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void OnEnable();
	virtual void OnDisable();
	virtual void OnCollision(GameObject* gameObject);
	virtual void OnTriggerEnter(GameObject* gameObject);
	virtual void OnTriggerStay(GameObject* gameObject);
	virtual void OnTriggerExit(GameObject* gameObject);
};

class GameObject
{
private:
	int component_num;
public:
	GameObject();
	~GameObject();
	Transform* transform;
	vector<Component*> components;
	string name;
	bool isActive;
	int tag;
	void Init();
	void Update();
	void Render();
	Component* AddComponent(Component* component);
	template <typename T>
	T* GetComponent();
	void MoveX(float x) { transform->MoveX(x); }
	void MoveY(float y) { transform->MoveY(y); }
	void Move(float x, float y) { transform->Move(x, y); }
	void OnEnable();
	void OnDisable();
	void OnCollision(GameObject* gameObject);
	void OnTriggerEnter(GameObject* gameObject);
	void OnTriggerStay(GameObject* gameObject);
	void OnTriggerExit(GameObject* gameObject);
	
	void SetActive(bool active);
};

template<typename T>
inline T* GameObject::GetComponent()
{
	for (int i = 0; i < component_num; i++) {
		const char* inputClass = typeid(T*).name();
		T* result = dynamic_cast<T*>(components[i]);
		if (result != nullptr) {
			return result;
		}
	}
	return nullptr;
}
