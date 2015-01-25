/**
 * Copyright (c) 2014 Dung Ta Van. All rights reserved.
 *
 * This file is part of Google analytics plugin.
 * Google analytics plugin is free library: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Google analytics plugin is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Google analytics plugin.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * GoogleAnalyticsHelper.cpp
 *
 *  Created on: Jan 21, 2015
 *      Author: dungtavan
 */

#include "GoogleAnalyticsHelper.h"

#include <jni.h>
#include <string>
#include "../../../cocos2d/plugin/protocols/platform/android/PluginJniHelper.h"

using namespace cocos2d;

namespace tvd { namespace plugin {

void GoogleAnalyticsHelper::init() {

}

void GoogleAnalyticsHelper::sendScreenView(const string &screenView) {
	PluginJniMethodInfo t;
	if (PluginJniHelper::getStaticMethodInfo(t,
			"com/tvd/android/plugin/GoogleAnalyticsHelper",
			"sSendScreenView",
			"(Ljava/lang/String;)V"))
	{
		jstring screenName = t.env->NewStringUTF(screenView.c_str());
		t.env->CallStaticVoidMethod(t.classID, t.methodID, screenName);
		t.env->DeleteLocalRef(t.classID);
		return;
	}
}

void GoogleAnalyticsHelper::sendEvent(const string &category,
                   const string &action,
                   const string &label,
                   long long value) {

	PluginJniMethodInfo t;
    if(PluginJniHelper::getStaticMethodInfo(t,
                                       "com/tvd/android/plugin/GoogleAnalyticsHelper",
                                       "sSendEvent",
                                       "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;J)V")) {
        jstring eventCategory = t.env->NewStringUTF(category.c_str());
        jstring eventAction = t.env->NewStringUTF(action.c_str());
        jstring eventLabel = t.env->NewStringUTF(label.c_str());
        jlong   eventValue = (jlong)value;
        t.env->CallStaticVoidMethod(t.classID, t.methodID, eventCategory,
                                    eventAction, eventLabel, eventValue);
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(eventCategory);
        t.env->DeleteLocalRef(eventLabel);
    } else {

    }
}

void GoogleAnalyticsHelper::startSession(const string &screenView) {
	PluginJniMethodInfo t;
	if(PluginJniHelper::getStaticMethodInfo(t,
	                                  "com/tvd/android/plugin/GoogleAnalyticsHelper",
	                                  "sStartSession",
	                                  "(Ljava/lang/String;)V")) {
		jstring eventScreenView = t.env->NewStringUTF(screenView.c_str());
		t.env->CallStaticVoidMethod(t.classID, t.methodID, eventScreenView);
		t.env->DeleteLocalRef(t.classID);
	} else {

	}
}

void GoogleAnalyticsHelper::endSession(const string &screenView) {

}

void GoogleAnalyticsHelper::sendUserTimings(long loadTime,
                         const string &category,
                         long interval,
                         const string &name,
                         const string &label) {
	PluginJniMethodInfo t;
	if(PluginJniHelper::getStaticMethodInfo(t,
	                                  "com/tvd/android/plugin/GoogleAnalyticsHelper",
	                                  "sSendUserTimings",
	                                  "(J;Ljava/lang/String;J;Ljava/lang/String;Ljava/lang/String;)V")) {
		jlong eventLoadTime 	= (jlong)loadTime;
		jstring eventCategory 	= t.env->NewStringUTF(category.c_str());
		jlong eventInterval 	= (jlong)interval;
		jstring eventName 		= t.env->NewStringUTF(name.c_str());
		jstring eventLabel		= t.env->NewStringUTF(label.c_str());

		t.env->CallStaticVoidMethod(t.classID, t.methodID, eventLoadTime,
				eventCategory, eventInterval, eventName, eventLabel);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(eventCategory);
		t.env->DeleteLocalRef(eventName);
		t.env->DeleteLocalRef(eventLabel);
	} else {

	}
}

void GoogleAnalyticsHelper::signInWithUser(const string &userId,
                        const string &category,
                        const string &label,
                        long long value) {
	PluginJniMethodInfo t;
	if (PluginJniHelper::getStaticMethodInfo(t,
		                                  "com/tvd/android/plugin/GoogleAnalyticsHelper",
		                                  "sSignInWithUser",
		                                  "(J;Ljava/lang/String;J;Ljava/lang/String;Ljava/lang/String;)V")) {
			jstring eventUserId 		= t.env->NewStringUTF(userId.c_str());
			jstring eventCategory 	= t.env->NewStringUTF(category.c_str());
			jstring eventLabel		= t.env->NewStringUTF(label.c_str());
			jlong eventInterval 	= (jlong)value;

			t.env->CallStaticVoidMethod(t.classID, t.methodID, eventUserId,
					eventCategory, eventLabel, eventInterval);
			t.env->DeleteLocalRef(t.classID);
			t.env->DeleteLocalRef(eventUserId);
			t.env->DeleteLocalRef(eventCategory);
			t.env->DeleteLocalRef(eventLabel);
	} else {

	}
}

}}
