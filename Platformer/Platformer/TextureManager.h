#pragma once
class TextureManager
{
private:
	std::map<std::string, sf::Texture> textures; // Mapa tekstur

public:
	void loadTexture(const std::string filename, const std::string textureName);

	// Zwraca wska�nik do tekstury, je�li istnieje, inaczej nullptr
	sf::Texture* getTexture(const std::string& textureName);

};

