/*
#define INCLUDE_OPENGL

#include "ml/include/ml.h"
#include "ml/include/graph/VertexArray.h"

ml::graph::VertexArray va(
{ 
	ml::Vertex(ml::Point(-0.6f, -0.4f), ml::Color(1.0f, 0, 0)),
	ml::Vertex(ml::Point(0.6f, -0.4f), ml::Color(0, 1.0f, 0)),
	ml::Vertex(ml::Point(0.f, 0.6f), ml::Color(0, 0, 1.0f)),
} );

class WindowController : public ml::Window
{
public:
	virtual void onResize(const ml::Size&)
	{
	}

	virtual void onRender()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		ml::Size s(getWindowSize());
		glViewport(0, 0, s.width, s.height);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		//		glOrtho(view.x, view.x2, view.y, view.y2, 1.0f, -1.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotatef((float)getTime() * 50.f, 0.f, 0.f, 1.f);
		va.Render();
	}

	virtual bool onCloseRequested()
	{
		return true;
	}

};

int main_(void)
{
	ml::LoadCore();
	ml::Core *core = ml::getCore();
	WindowController *win = _NEW WindowController;
	core->registerWindow(win);

	core->enterMainLoop();

	core->unregisterWindow(win);

	core->finish();
	ml::UnLoadCore();
	return 0;
}
*/
