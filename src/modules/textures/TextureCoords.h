#pragma once

#include "Texture.h"
#include <string>
#include <sstream>

class TextureCoords {
private:
	inline void calc(const TextureRect& rect, int width, int height, bool mirror) {
		const int x1 = rect.x;
		const int y1 = rect.y;
		const int x2 = rect.x + rect.w;
		const int y2 = rect.y + rect.h;

		texCoords[0] = x1 / (float) width;
		texCoords[1] = y1 / (float) height;

		texCoords[2] = x2 / (float) width;
		texCoords[3] = y1 / (float) height;

		texCoords[4] = x2 / (float) width;
		texCoords[5] = y2 / (float) height;

		texCoords[6] = x1 / (float) width;
		texCoords[7] = y2 / (float) height;
		if (mirror) {
			std::swap(texCoords[0], texCoords[2]);
			std::swap(texCoords[4], texCoords[6]);
		}
	}
public:
	float texCoords[8];

	TextureCoords(const Texture* texture) {
		calc(texture->getSourceRect(), texture->getFullWidth(), texture->getFullHeight(), texture->isMirror());
	}

	TextureCoords(const TextureRect& rect, int width, int height, bool mirror = false) {
		calc(rect, width, height, mirror);
	}

	inline std::string toString() const {
		std::stringstream s;
		s << "TextureCoords[";
		for (int i = 0; i < 8; i += 2) {
			s << "(" << texCoords[i + 0] << "," << texCoords[i + 1] << ")";
		}
		s << "]";
		return s.str();
	}
};
