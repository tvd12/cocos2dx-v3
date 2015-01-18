#include "AppDelegate.h"
#include "BirdSprite.h"
#include "UserRecord.h"
#include "LoadingScene.h"

USING_NS_CC;

typedef struct tagResource {
    Size size;
    char directory[100];
} Resource;

static Resource iPhoneResource              = { Size(320, 480),     "iPhonehd" };
static Resource iPhoneRetinaResource        = { Size(640, 960),     "iPhone3inch" };
static Resource iPhoneRetina4InchResource   = { Size(640, 1136),    "iPhone4inch" };
static Resource iPhone6Resource             = { Size(750, 1334),    "iPhone6"};
static Resource iPhone6PlusResource         = { Size(1242, 2208),   "iPhone6Plus"};
static Resource iPadResource                = { Size(768, 1024),    "iPadhd"   };
static Resource iPadRetinaResource          = { Size(1536, 2048),   "iPadhd" };

static Size iPhoneDesignSize            = Size(320, 480);
static Size iPhoneRetinaDesignSize      = Size(320, 480);
static Size iPhoneRetina4InchDesignSize = Size(320, 568);
static Size iPhone6DesignSize           = Size(375, 667);
static Size iPhone6PlusDesignSize       = Size(414, 736);
static Size iPadDesignSize              = Size(768, 1024);
static Size iPadRetinaDesignSize        = Size(768, 1024);

static Size designResolutionSize        = Size(320, 480);

void AppDelegate::setResourceSearchResolution() {
    std::vector<std::string> paths;
    paths.push_back("fonts");
    paths.push_back("image");
    paths.push_back("sounds");
    FileUtils::getInstance()->setSearchResolutionsOrder(paths);
    FileUtils::getInstance()->setSearchPaths(paths);
    
    Resource resources[] = {
        iPhoneResource,
        iPhoneRetinaResource,
        iPhoneRetina4InchResource,
        iPhone6Resource,
        iPadResource,
        iPhone6PlusResource,
        iPadRetinaResource,
    };
    
    Size designSizes[] = {
        iPhoneDesignSize,
        iPhoneRetinaDesignSize,
        iPhoneRetina4InchDesignSize,
        iPhone6DesignSize,
        iPadDesignSize,
        iPhone6PlusDesignSize,
        iPadRetinaDesignSize,
    };
    
    
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    Size frameSize = glview->getFrameSize();
    
    for(int i = 0 ; i < 7 ; i ++) {
        Size resourceSize   = resources[i].size;
        if(resourceSize.width >= frameSize.width
           && resourceSize.height >= frameSize.height) {
            designResolutionSize = designSizes[i];
            break;
        }
    }
    
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
        glview = GLViewImpl::create("Earlybird");
        director->setOpenGLView(glview);
    }
    
    Size frameSize = glview->getFrameSize();
    
    glview->setDesignResolutionSize(288, 512, ResolutionPolicy::SHOW_ALL);
    
    // set the resource directory
    setResourceSearchResolution();

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    UserRecord::getInstance();
    
    BirdSprite::getInstance()->init();

    // create a scene. it's an autorelease object
    auto scene = LoadingScene::create();

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
