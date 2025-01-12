#pragma once

/**
 * @brief Klasa odpowiedzialna za zarzadzanie teksturami w grze.
 * Umozliwia ladowanie tekstur i dostep do nich po nazwie.
 */
class TextureManager
{
private:
	std::map<std::string, sf::Texture> textures; // Mapa tekstur

public:
	/**
	 * @brief Laduje teksture z pliku.
	 * Funkcja wczytuje teksture i zapisuje ja pod podana nazwa.
	 * @param filename Sciezka do pliku tekstury.
	 * @param textureName Nazwa, pod ktora tekstura bedzie zapisana.
	 */
	void loadTexture(const std::string filename, const std::string textureName);

    /**
	 * @brief Zwraca wskaznik do tekstury o podanej nazwie.
	 * Jesli tekstura nie istnieje, zwraca nullptr.
	 * @param textureName Nazwa tekstury.
	 * @return Wskaznik do tekstury lub nullptr, jesli tekstura nie istnieje.
	 */
	sf::Texture* getTexture(const std::string& textureName);

};

