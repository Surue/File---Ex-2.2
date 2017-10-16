#ifndef TEXTURE_MANAGER_H_
#define TEXTURE_MANAGER_H_
class texture_manager {
private:
	texture_manager( const texture_manager& );
	texture_manager& operator =( const texture_manager& );
	std::map< std::string, sf::Texture > textures_;
	std::vector< std::string > resourceDirectories_;

public:
	texture_manager();
	~texture_manager();

	const sf::Texture& getTexture( const std::string&);
	void deleteTexture( const sf::Texture&);
	void deleteTexture( const std::string&);
	void addResourceDirectory( const std::string&);
	void removeResourceDirectory( const std::string&);
};
#endif