#pragma once

class Texture {
public:
	Texture(const char* filePath);
	~Texture();

	void Bind(unsigned int unit = 0) const;
	unsigned int GetID() const;


private:
	unsigned int m_texture = 0;
	const char* filePath = "";
};