#pragma once



class Model;
class Mesh;
struct Vertex;


class GameObject
{
public:
    GameObject() ;
    GameObject(std::string name, std::weak_ptr<Model> model);
	GameObject(std::vector<Vertex> _vertices, std::vector<unsigned int> _indices);
	~GameObject();


    void setModel(std::shared_ptr<Model> model);
    void setName(std::string name);
	void setPosition(glm::vec3 pos);
	void moveBy(glm::vec3 pos);
	void moveXBy(float pos);
	void moveYBy(float pos);
	void moveZBy(float pos);
	void setScale(const glm::vec3 scale);
	void scaleBy(const glm::vec3 scale);
	void setAngle(float angle, const glm::vec3 axis);
	void rotateBy(float angle, const glm::vec3 axis);
	void updateModelMatrix();

	std::string getName();
	glm::vec3 getPosition() const;
	glm::vec3 getScale() const;
	glm::mat4 getModelMatrix();



    GameObject& operator=(const GameObject& gameObject);
	std::shared_ptr<Model> _model;
	protected:

    

	private:
        std::string GOName = "";
	glm::vec3 _position = { 0.0f, 0.0f, 0.0f };
	glm::vec3 _scale = { 1.f, 1.f, 1.f };
	glm::quat _orientation = {1.f, 0.f, 0.f, 0.f};
	bool _isModelNULL = false;

    glm::mat4 _modelMatrix = {};
	bool _isModelMatrixOutdated = false;
};


