#include "src/graphics/window.h"
#include "src/graphics/shader.h"
#include "src/maths/maths.h"

#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/buffers/vertexarray.h"

#include "src/graphics/renderable2d.h"
#include "src/graphics/simple2drenderer.h"
#include "src/graphics/batchrenderer2D.h"

#include "src/graphics/static_sprite.h"
#include "src/graphics/sprite.h"
#include "src/utils/timer.h"

#include <time.h>

#define BATCH_RENDERER 1
int main()
{
	using namespace sparky;
	using namespace graphics;
	using namespace maths;

	Window window("Sparky!", 960, 540);
	//glClearColor(255.0f, 255.0f, 255.5f, 1.0f);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();
	shader.SetUniformMat4("pr_matrix", ortho);

	std::vector<Renderable2D*> sprites;

	srand(time(NULL));

	for (float y = 0; y < 9.0f; y += 1)
	{
		for (float x = 0; x < 16.0f; x += 1)
		{
			sprites.push_back(new
				#if BATCH_RENDERER
				Sprite(x, y, 0.9f, 0.9, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
			#else 
				StaticSprite(x, y, 0.04f, 0.04f, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1), shader));
			#endif
		}
	}

	#if BATCH_RENDERER
	Sprite sprite(5, 5, 4, 4, maths::vec4(1, 0, 1, 1));
	Sprite sprite2(7, 1, 2, 3, maths::vec4(0.2f, 0, 1, 1));
	BatchRenderer2D renderer;

	#else
	StaticSprite sprite(5, 5, 4, 4, maths::vec4(1, 0, 1, 1), shader);
	StaticSprite sprite2(7, 1, 2, 3, maths::vec4(0.2f, 0, 1, 1), shader);
	Simple2DRenderer renderer;
	#endif

	shader.SetUniform2f("light_pos", vec2(4.0f, 1.5f));
	shader.SetUniform4f("colour", vec4(0.2f, 0.3f, 0.8f, 1.0f));

	Timer time;
	float timer = 0;
	unsigned int frames = 0;
	while (!window.closed())
	{
		window.clear();
		double x, y;
		window.getMousePostion(x, y);
		shader.SetUniform2f("light_pos", vec2((float)(x * 16.0f / 960.0f), (float)(9.0 - y * 9.0f / 540.0f)));
		#if BATCH_RENDERER
		renderer.begin();
		#endif
		for (int i = 0; i < sprites.size(); i++)
		{
			renderer.submit(sprites[i]);
		}
		#if BATCH_RENDERER
		renderer.end();
		#endif
		renderer.flush();
		window.update();
		frames++;
		if (time.elapsed() - timer > 1.0f)
		{
			timer += 1.0f;
			printf("%d  fps\n", frames);
			frames = 0;
		}
	}
}