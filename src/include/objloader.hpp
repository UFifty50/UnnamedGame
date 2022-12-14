#ifndef OBJLOADER_HPP
#define OBJLOADER_HPP

#include <vector>

#include "glm/glm.hpp"
#include "core.hpp"

bool loadOBJ(
	const char* path, 
	std::vector<glm::vec3> &out_vertices, 
	std::vector<glm::vec2> &out_uvs, 
	std::vector<glm::vec3> &out_normals,
	IMGMODE mode
);

bool loadAssimp(
	const char* path, 
	std::vector<unsigned short> &indices,
	std::vector<glm::vec3> &vertices,
	std::vector<glm::vec2> &uvs,
	std::vector<glm::vec3> &normals
);

#endif
