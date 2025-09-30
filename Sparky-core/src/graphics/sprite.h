#pragma once

#include "Renderable2D.h"

namespace sparky::graphics {

	class Sprite : public Renderable2D
	{
	private:
	public:
		Sprite(float x, float y, float width, float height, const maths::vec4& color);
	};

}
