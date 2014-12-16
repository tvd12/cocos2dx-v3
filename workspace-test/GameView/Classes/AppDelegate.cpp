#include "AppDelegate.h"


#include "GameParams.h"
#include "CCLocalization.h"
#include "SceneController.h"
#include "SoundManager.h"
#include "NativeHelper.h"

#ifndef CC_TARGET_OS_IPHONE
#include <jni.h>
#include "jni/JniHelper.h"
#include "TdgServer.h"
#include "HourlyBonusInfo.h"
#endif

USING_NS_CC;

extern "C" {

typedef struct tagResource {
    CCSize size;
    char directory[100];
} Resource;

static Resource iPhoneResource              = { CCSize(320, 480),   "iphone" };
static Resource iPhoneRetinaResource        = { CCSize(640, 960),   "iPhone3inch" };
static Resource iPhoneRetina4InchResource   = { CCSize(640, 1136),  "iPhone4inch" };
static Resource iPadResource                = { CCSize(768, 1024),  "ipadhd"   };
static Resource iPadRetinaResource          = { CCSize(1536, 2048), "ipadhd" };
static CCSize designResolutionSize          = CCSize(320, 480);

std::vector<std::string> getSearchPaths(CCDirector* director, CCSize frameSize)
{
    std::vector<std::string> searchPaths;
    float contentScaleFactor = 2.0f;

#ifdef CC_TARGET_OS_IPHONE
    // IOS define
    // ipad retina
    if (frameSize.height > iPhoneRetina4InchResource.size.height) {
        searchPaths.push_back(iPadRetinaResource.directory);
        GPARAMS().initIpadParams();
    }
    // iphone 4 inch retina
    else if (frameSize.height > iPadResource.size.height) {
        searchPaths.push_back(iPhoneRetina4InchResource.directory);
        searchPaths.push_back("demohd");
        GPARAMS().initIphone5Params();
    }
    // ipad
    else if (frameSize.height > iPhoneRetinaResource.size.height) {
        contentScaleFactor = 2.0f;
        searchPaths.push_back(iPadResource.directory);
        GPARAMS().initIpadParams();
    }
    // iphone 3 inch retina
    else if (frameSize.height > iPhoneResource.size.height) {
        searchPaths.push_back(iPhoneRetinaResource.directory);
        searchPaths.push_back("demohd");
        GPARAMS().initIphone4Params();
    }
    
#else
    // ANDROID define
    float screenRatio = frameSize.height / frameSize.width;
    float ratioHD = iPhoneRetina4InchResource.size.height / iPhoneRetina4InchResource.size.width;
    float ratio = iPhoneResource.size.height / iPhoneResource.size.width;
    float delta1 = fabsf(screenRatio - ratio);
    float delta2 = fabsf(screenRatio - ratioHD);
    
    if (delta1 > delta2) {
        searchPaths.push_back(iPhoneRetina4InchResource.directory);
        searchPaths.push_back("demohd");
        GPARAMS().initIphone5Params();
    }
    else {
        searchPaths.push_back(iPhoneRetinaResource.directory);
        searchPaths.push_back("demohd");
        GPARAMS().initIphone4Params();
    }
#endif

    director->setContentScaleFactor(contentScaleFactor);
    return searchPaths;
}

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	
    // turn on display FPS
//    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    CCSize frameSize = pEGLView->getFrameSize();
#ifdef CC_TARGET_OS_IPHONE
    if(frameSize.height == 1024 || frameSize.height == 1024*2) {
        designResolutionSize = CCSize(768, 1024);
    } else {
        //do nothing
        if (frameSize.height == 1136) {
            designResolutionSize = CCSize(320, 568);
        }
    }
#else
    float screenRatio = frameSize.height / frameSize.width;
    float ratioHD = iPhoneRetina4InchResource.size.height / iPhoneRetina4InchResource.size.width;
    float ratio = iPhoneResource.size.height / iPhoneResource.size.width;
    float delta1 = fabsf(screenRatio - ratio);
    float delta2 = fabsf(screenRatio - ratioHD);
    
    if (delta1 > delta2) {
        designResolutionSize = CCSize(320, 568);
    }
#endif

    // Set the design resolution
    pEGLView->setDesignResolutionSize(designResolutionSize.width,
                                     designResolutionSize.height,
                                     kResolutionShowAll);
    
    std::vector<std::string> searchPaths = getSearchPaths(pDirector, frameSize);
    
    CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
    
    // init localization
//    CCLocalization::sharedLocalization()->addAndroidStrings("en", "videopoker_en.xml");
    CCLocalization::sharedLocalization()->addAndroidStrings("vi", "videopoker_vi.xml");

    // create a scene. it's an autorelease object
    NATIVE();
    SOUND();
    SCONTROL();
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SOUND().pauseBackgroundMusicIfNeed();
    
#ifndef CC_TARGET_OS_IPHONE
    if (HOURLYBONUS()->getCurrentBonus() == 0) {
        return;
    }
    
    int timeToBonus = (HOURLYBONUS()->getBonusMax() - HOURLYBONUS()->getCurrentBonus());
    timeToBonus = (int)((float)timeToBonus / HOURLYBONUS()->getChipsPerSecond());

    JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t,
                                       "com/tdgc/videopokerjackpot/utils/TDGAndroidUtils",
                                       "showLocalNotification",
                                       "(Ljava/lang/String;II)V")) {
        jstring stringArg = t.env->NewStringUTF("Your free Chips are ready! Collect them now?");
		t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg, timeToBonus, 1000);
		t.env->DeleteLocalRef(t.classID);
    }
#endif
    
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SOUND().resumeBackgroundMusic();
}
    
}
