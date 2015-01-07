#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "SqliteTestScene.h"
#include "MapManager.h"
#include "Sqlite3Helper.h"
#include "LobbyLayerView.h"
#include "WordLayer.h"

USING_NS_CC;

static Size designResolutionSize =          Size(480, 320);

std::vector<std::string> getSearchPaths(Director* director, Size frameSize)
{
    std::vector<std::string> searchPaths;
    float contentScaleFactor = 2.0f;
    director->setContentScaleFactor(contentScaleFactor);
    
    return searchPaths;
}

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("My Game");
        director->setOpenGLView(glview);
    }
    
    // turn on display FPS
    //    director->setDisplayStats(true);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
//    Size frameSize = glview->getFrameSize();
//    getSearchPaths(director, frameSize);
    director->setContentScaleFactor(2.0f);
    
    glview->setDesignResolutionSize(designResolutionSize.width,
                                    designResolutionSize.height,
                                    ResolutionPolicy::SHOW_ALL);
    Sqlite3Helper::getInstance()->openConnection();
    MapManager::getInstance()->init();
    
    // create a scene. it's an autorelease object
        auto scene = HelloWorld::scene();
    //    auto scene = SqliteTestScene::scene();
//    auto scene = TestController::createScene();
    
    // run
    director->runWithScene(scene);
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
