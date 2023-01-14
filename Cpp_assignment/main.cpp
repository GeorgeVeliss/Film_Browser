#include "graphics.h"
#include "browser.h"
#include "config.h"


void update(float ms)
{
    Browser* browser = reinterpret_cast<Browser*>(graphics::getUserData());
    browser->update();
}

void draw()
{
    Browser* browser = reinterpret_cast<Browser*>(graphics::getUserData());
    browser->draw();
}

int main()
{
    Browser filmBrowser;

    graphics::createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Film Browser");

    graphics::setUserData(&filmBrowser);

    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    filmBrowser.init();
    graphics::startMessageLoop();
    graphics::stopMessageLoop();

    return 0;
}