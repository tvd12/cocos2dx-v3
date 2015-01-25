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

//
//  GoogleAnalyticsHelper.h
//  google-analytics
//
//  Created by Dung Ta Van on 1/20/15.
//  Copyright (c) 2015 Dung Ta Van. All rights reserved.
//

#ifndef __google_analytics__GoogleAnalyticsHelper__
#define __google_analytics__GoogleAnalyticsHelper__

#include <string>

using namespace std;

#define SYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) const { return varName; }\
public: virtual void set##funName(varType var){ varName = var; }

namespace tvd { namespace plugin {
    
    class GoogleAnalyticsHelper {
    public:
        static GoogleAnalyticsHelper* getInstance() {
            static GoogleAnalyticsHelper sInstance;
            
            return &sInstance;
        }
        
        void init();
        
        void sendScreenView(const string &screenView);
        
        void sendEvent(const string &category,
                       const string &action,
                       const string &label,
                       long long value);
        
        void startSession(const string &screenView);
        
        void endSession(const string &screenView);
        
        /**
         * @function sendUserTimings
         * @param category: i.e "resources"
         * @param interval: i.e 1000
         * @param name: i.e "high scores"
         * @param label:
         */
        void sendUserTimings(long loadTime,
                             const string &category,
                             long interval,
                             const string &name,
                             const string &label);
        
        void signInWithUser(const string &userId,
                            const string &category,
                            const string &label,
                            long long value);
        
        void startSession() {
            sendScreenView("Home Screen");
        }
        
        void signInWithUser(const string &userId,
                            const string &label,
                            long long value) {
            signInWithUser(userId, "UX", label, value);
        }
        
        SYNTHESIZE(string, mAppName, AppName);
        SYNTHESIZE(string, mAppVersion, AppVersion);
        SYNTHESIZE(string, mTrackingId, TrackingId);
        
    private:
        GoogleAnalyticsHelper(const GoogleAnalyticsHelper &) = delete;
        void operator = (const GoogleAnalyticsHelper &) = delete;
        
        GoogleAnalyticsHelper() :
        mAppName("My App"),
        mAppVersion("1.0"),
        mTrackingId("") {};
    };
    
}
}
#endif /* defined(__google_analytics__GoogleAnalyticsHelper__) */
