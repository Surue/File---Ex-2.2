#include <map>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "imageManager.h"

texture_manager::texture_manager() : textures_(), resourceDirectories_() {
}

texture_manager::~texture_manager() {
	textures_.clear();
	resourceDirectories_.clear();
}

const sf::Texture& texture_manager::getTexture( const std::string& filename ) {
	// Check, whether the image already exists
	for( auto it = textures_.begin(); it != textures_.end(); ++it) {
		if( filename == it->first ) {
			return it->second;
		}
	}
	
	// The image doesen't exists. Create it and save it.
	sf::Texture texture;

	// Search project's main directory
	if( texture.loadFromFile( filename ) ) {
		textures_[filename] = texture;
		return textures_[filename];
	}

	// If the image has still not been found, search all registered directories
	for( auto it = resourceDirectories_.begin(); it != resourceDirectories_.end(); ++it) {
		if( texture.loadFromFile( (*it) + filename )) {
			textures_[filename] = texture;
			std::cout << "DEBUG_MESSAGE: " << filename << " loading image.\n";
			return textures_[filename];
		}
	}

	std::cout << "GAME_ERROR: Image was not found. It is filled with an empty image.\n";
	textures_[filename] = texture;
	return textures_[filename];
}

void texture_manager::deleteTexture( const sf::Texture& image ) {
	for(auto it = textures_.begin(); it != textures_.end(); ++it) {
		if( &image == &it->second ) {
			textures_.erase( it );
			return;
		}
	}
}

void texture_manager::deleteTexture( const std::string& filename ) {
	auto it = textures_.find( filename );
	if (it != textures_.end()) {
		textures_.erase(it);
	}
}

void texture_manager::addResourceDirectory( const std::string& directory ) {
	// Check whether the path already exists
	for(auto it  = resourceDirectories_.begin(); it != resourceDirectories_.end(); ++it) {
		// The path exists. So it isn't necessary to add id once more.
		if (directory == (*it)) {
			return;
		}
	}

	// insert the directory
	resourceDirectories_.push_back( directory );
}

void texture_manager::removeResourceDirectory( const std::string& directory ) {
	for(auto it  = resourceDirectories_.begin(); it != resourceDirectories_.end(); ) {
		// The path exists. So it isn't necessary to add id once more.
		if (directory == (*it)) {
			it = resourceDirectories_.erase(it);
		}
		else {
			++it;
		}
	}
}