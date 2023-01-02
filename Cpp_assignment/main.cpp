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

    /*graphics::Brush br;
    br.texture = "assets\\grandBudapest.png";
    br.outline_opacity = 0.0f;

    graphics::drawRect(500, 250, 600, 600, br);*/
    //graphics::setFont(std::string(ASSET_PATH) + "Enchanted.otf");

    //graphics::drawText(500, 250, 250, "sample", br);
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

    return 0;
}