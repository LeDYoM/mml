#define _CRTDBG_MAP_ALLOC

#include <ml.h>
#include <graph/graph.h>

#include <stdlib.h>
#include <crtdbg.h>

class WindowController : public ml::graph::ManagedWindow
{
public:
	ml::graph::Texture *t;// = new ml::graph::Texture("test.png");
	ml::graph::Shape *sp;// = { ml::Rectanglef32(-0.5, -1.0, 0.5f, 0.5), t };
	ml::graph::Image *sptm;
	ml::graph::BMFont *font;

	ml::graph::BMFont *Snap = nullptr;
	ml::graph::BMFont *Times = nullptr;
	ml::graph::BMFont *Lucida = nullptr;

	ml::graph::BMText *txt1 = nullptr;
	ml::graph::BMText *txt2 = nullptr;
	ml::graph::BMText *txt3 = nullptr;
	ml::graph::BMText *txt4 = nullptr;
	ml::graph::BMText *txt5 = nullptr;
	ml::graph::BMText *txt6 = nullptr;

	ml::graph::Shape *circle;

	WindowController()
	{

	}

	virtual void onResized(const ml::Size&size)
	{
		renderManager->setViewPort(ml::Rectangleu32(0, 0, size));
	}
	virtual void onMouseCursorMoved(const ml::MousePosition &newPos)
	{
//		LOG_DEBUG("Mouse pos:"<<newPos.x<<","<<newPos.y);
	}

	virtual void onMouseButtons(const ml::MouseButtons&buttonState,const ml:: MouseButtonId buttonChanged)
	{
		LOG_DEBUG("Left button state: " << buttonState.pressed[ml::MouseButtonId::LeftButton]);
		LOG_DEBUG("Right button state: " << buttonState.pressed[ml::MouseButtonId::RightButton]);
		LOG_DEBUG("Center button state: " << buttonState.pressed[ml::MouseButtonId::CenterButton]);
		LOG_DEBUG("Button changed: " << buttonChanged);
	}

	virtual void onRenderModel()
	{
		//view.Render(renderManager);
		//glRotatef((float)getTime() * 50.f, 0.f, 0.f, 1.f);
		//renderer->Render(va);
//		renderer->Render(*sp);
//		renderer->Render(c);
//		renderer->Render(*font, "Ajabcde", ml::Vector2d<ml::f32>(-0.4f, 0.5f));

//		txt1->Render(renderFuncs);
//		txt2->Render(renderFuncs);
		txt3->Render(*renderManager);
//		txt4->Render(renderFuncs);
//		txt5->Render(renderFuncs);
//		txt6->Render(renderFuncs);

//		circle.Render();
//		renderer->Render(circle);
	}

	virtual void onInitialized()
	{
		setDrawFPS(true);
		renderManager->setViewPort(ml::Rectangleu32(0, 0, getWindowSize()));
//		view.setViewLogicalSize(ml::Rectanglef32(-1.0f, 1.0f, 1.0f, -1.0f));
		renderManager->setPerspective(ml::Rectanglef32(0.0f, 480.0f, 640.0f, 0.0f));

		sptm = new ml::graph::Image("test.png");
		t = ml::graph::Texture::fromImage(*sptm);
//		sp = _NEW ml::graph::Sprite(ml::Rectanglef32(-0.5, -0.5, 0.5f, 0.5), t );

//		font = _NEW ml::graph::BMFont;
//		Snap = _NEW ml::graph::BMFont;
//		Times = _NEW ml::graph::BMFont;
//		Lucida = _NEW ml::graph::BMFont;

		Lucida = resourceManager->loadResource<ml::graph::BMFont>("lucida");
//		Lucida->Load("lucida");
		Snap = resourceManager->loadResource<ml::graph::BMFont>("snap");
//		Snap->Load("snap");
//		Times->Load("times");
		Times = resourceManager->loadResource<ml::graph::BMFont>("times");

		Times->SetColor(ml::Color(0.8f, 0.9f, 0.8f, 1.0f));
		txt1 = resourceManager->print(Times, "A different font, centered. Kerning: To Ti");
		txt1->setPositionXY(10, 280);

		Lucida->SetColor(ml::Color(0.8f, 0.9f, 0.4f, 1.0f));
		txt2 = resourceManager->print(Lucida, "This is another font.");
		//		txt2 = Lucida->print("This is another font.");
		txt2->setPositionXY(10, 240);

		Snap->SetColor(ml::Color(1.0f, 1.0f, 1.0f, 1.0f));
		txt3 = resourceManager->print(Snap, "This is another font.");
		//		txt3 = Snap->print("This is standard printing.");
		txt3->setPositionXY(20, Snap->height() * 3);
		txt3->setScaleXY(1.35f);

		/*
		txt4 = Snap->print("Scaling makes it Big!");
		txt4->setPositionXY(2, Snap->height() / 4);
		txt4->setScaleXY(1.35f);

		txt5 = Snap->print("Or it can make it smaller!");
		txt5->setPositionXY(2, Snap->height() * 4);
		txt5->setScaleXY(0.7f);

		Snap->SetColor(ml::Color(1.0f, 1.0f, 1.0f, 1.0f));
		txt6 = Snap->print("Centered printing:To Ti");
		txt6->setPositionXY(10, 320);
		txt6->setScaleXY(1.0f);
		*/

//		= ml::graph::VertexArray::getCircle(1, 32);
//		c.circle(200, 10);
//		circle.setTriangleList(ml::graph::TriangleList().addCircle(10, 20));
	}

	virtual void onKey(const ml::KeyCodeType& keyCode, const ml::KeyCodeType& modif, const ml::KeyActionType& action) override
	{
		LOG_DEBUG("Key. Code:" << keyCode << " Modificators:" << modif << " Action: " << action);
	}
};

int main(void)
{
	ml::LoadCore();
	ml::Core *core = ml::getCore();
	WindowController *win = new WindowController;
//	core->setVsync(true);
	ml::WindowCreationOptions wco;
	core->registerWindow(win,wco);

	core->enterMainLoop();

	core->unregisterWindow(win);
//	core->deleteWindow(win);
	delete win;
	core->finish();

	ml::UnLoadCore();
	_CrtDumpMemoryLeaks();

}
