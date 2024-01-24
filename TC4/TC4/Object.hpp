#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

const std::string dataPath = "C:\\Users\\halat\\source\\repos\\TC4\\Data\\";
// OBJ
const std::string v = "v";
const std::string vt = "vt";
const std::string vn = "vn";
const std::string f = "f";
const std::string mtllib = "mtllib";
const std::string usemtl = "usemtl";
// MTL
const std::string newmtl = "newmtl";
const std::string Ka = "Ka";
const std::string Kd = "Kd";
const std::string Ke = "Ke";
const std::string Ks = "Ks";
const std::string Ni = "Ni";
const std::string Ns = "Ns";
const std::string d = "d";
const std::string Tr = "Tr";
const std::string illum = "illum";
const std::string map_Kd = "map_Kd";

struct Vertex {
	float x, y, z;
};

struct Texture {
	float x, y;
};

struct Normal {
	float x, y, z;
};

struct Face {
	std::vector<int> vertexIndices;
	std::vector<int> textureIndices;
	std::vector<int> normalIndices;
	long unsigned int materialIndex = 0;
};

struct Material {
	std::string name;
	float ambient[3];
	float diffuse[3];
	float emission[3];
	float specular[3];
	float shininess;
	float opticalDensity;
	float dissolve;
	int illuminationModel;
	std::string diffuseMap;
};

class Object {
public:
	Object();
	~Object();
	std::vector<Vertex> getVertices();
	std::vector<Texture> getTextures();
	std::vector<Material> getMaterials();
	std::vector<Normal> getNormals();
	std::vector<Face> getFaces();

	bool loadOBJ(const std::string path);
	bool loadMTL(const std::string path);

private:
	std::vector<Vertex> vertices;
	std::vector<Texture> textureCoords;
	std::vector<Normal> normals;
	std::vector<Face> faces;
	std::vector<Material> materials;
};