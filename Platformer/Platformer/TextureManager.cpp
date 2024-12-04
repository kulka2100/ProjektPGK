#include "stdafx.h"
#include "TextureManager.h"

void TextureManager::loadTexture(const std::string filename, const std::string textureName) {
	if (textures.find(textureName) == textures.end()) {
		sf::Texture texture;
		if (texture.loadFromFile(filename)) {
			textures[textureName] = texture;
		}
		else {
			std::cerr << "Nie udalo sie zaladowac textury " << filename << std::endl;
		}
	}
	else {
		std::cerr << "Textura juz istnieje " << filename << std::endl;
	}
}


sf::Texture* TextureManager::getTexture(const std::string& textureName) {
	auto it = textures.find(textureName);

	if (it != textures.end()) {
		// Zwraca wskaŸnik do tekstury
		return &it->second;
	}
	// W przypadku braku tekstury zwraca nullptr
	return nullptr;
}