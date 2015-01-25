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
//  GoogleAnalyticsHelper.m
//  google-analytics
//
//  Created by Dung Ta Van on 1/20/15.
//  Copyright (c) 2015 Dung Ta Van. All rights reserved.
//

#include "GoogleAnalyticsHelper.h"
#include "GAI.h"
#include "GAIDictionaryBuilder.h"
#include "GAIFields.h"

namespace tvd { namespace plugin {
    
    void GoogleAnalyticsHelper::init() {
        [GAI sharedInstance].trackUncaughtExceptions = YES;
        // Optional: automatically send uncaught exceptions to Google Analytics.
        [GAI sharedInstance].trackUncaughtExceptions = YES;
        
        // Optional: set Google Analytics dispatch interval to e.g. 20 seconds.
        [GAI sharedInstance].dispatchInterval = 20;
        
        // Optional: set Logger to VERBOSE for debug information.
        [[[GAI sharedInstance] logger] setLogLevel:kGAILogLevelVerbose];
        
        // Initialize tracker. Replace with your tracking ID.
        [[GAI sharedInstance] trackerWithTrackingId:
         [NSString stringWithUTF8String:getTrackingId().c_str()]];
        
        id<GAITracker> tracker = [[GAI sharedInstance] defaultTracker];
        [tracker set:kGAIAppName value:[NSString stringWithUTF8String:getAppName().c_str()]];
        [tracker set:kGAIAppVersion value:[NSString stringWithUTF8String:getAppVersion().c_str()]];
    }
    
    void GoogleAnalyticsHelper::sendScreenView(const string &screenView) {
        // May return nil if a tracker has not already been initialized with a
        // property ID.
        id<GAITracker> tracker = [[GAI sharedInstance] defaultTracker];
        
        // This screen name value will remain set on the tracker and sent with
        // hits until it is set to a new value or to nil.
        [tracker set:kGAIScreenName
               value:[NSString stringWithUTF8String: screenView.c_str()]];
        
        // Previous V3 SDK versions
        // [tracker send:[[GAIDictionaryBuilder createAppView] build]];
        
        // New SDK versions
        [tracker send:[[GAIDictionaryBuilder createScreenView] build]];
    }
    
    void GoogleAnalyticsHelper::sendEvent(const string &category,
                   const string &action,
                   const string &label,
                   long long value) {
        
        // May return nil if a tracker has not already been initialized with a property
        // ID.
        id<GAITracker> tracker = [[GAI sharedInstance] defaultTracker];
        
        NSString *categoryStr = [NSString stringWithUTF8String: category.c_str()];
        NSString *actionStr = [NSString stringWithUTF8String: action.c_str()];
        NSString *labelStr = [NSString stringWithUTF8String: label.c_str()];
        NSNumber *valueNumber = [NSNumber numberWithLongLong: value];
        
        [tracker send:[[GAIDictionaryBuilder
                        createEventWithCategory:categoryStr     // Event category (required)
                        action: actionStr  // Event action (required)
                        label: labelStr          // Event label
                        value: valueNumber] build]];    // Event value
    }
    
    void GoogleAnalyticsHelper::startSession(const string &screenView) {
        
        // May return nil if a tracker has not yet been initialized.
        id<GAITracker> tracker = [[GAI sharedInstance] defaultTracker];
        
        // Start a new session with a screenView hit.
        GAIDictionaryBuilder *builder = [GAIDictionaryBuilder createScreenView];
        [builder set:@"start" forKey:kGAISessionControl];
        [tracker set:kGAIScreenName value: [NSString stringWithUTF8String: screenView.c_str()]];
        [tracker send:[builder build]];
    }
    
    void GoogleAnalyticsHelper::endSession(const string &screenView) {
        // There should be no need to end a session explicitly.  However, if you do
        // need to indicate end of session with a hit, simply add the following line
        // of code to add the parameter to the builder:
        id<GAITracker> tracker = [[GAI sharedInstance] defaultTracker];
        GAIDictionaryBuilder *builder = [GAIDictionaryBuilder createScreenView];
        [builder set:@"end" forKey:kGAISessionControl];
        [tracker set:kGAIScreenName value: [NSString stringWithUTF8String: screenView.c_str()]];
        [tracker send:[builder build]];
    }
    
    /**
     * @function sendUserTimings
     * @param category: i.e "resources"
     * @param interval: i.e 1000
     * @param name: i.e "high scores"
     * @param label:
     */
    /*
     * Called after a list of high scores finishes loading.
     *
     * @param loadTime The time it takes to load a resource.
     */
    void GoogleAnalyticsHelper::sendUserTimings(long loadTime,
                         const string &category,
                         long interval,
                         const string &name,
                         const string &label) {
        // May return nil if a tracker has not already been initialized with a
        // property ID.
        id<GAITracker> tracker = [[GAI sharedInstance] defaultTracker];
        
        NSNumber* loadTimeNumber = [NSNumber numberWithLong: loadTime];
        
        [tracker send:[[GAIDictionaryBuilder
                        // Timing category (required)
                        createTimingWithCategory: [NSString stringWithUTF8String: category.c_str()]
                        // Timing interval (required)
                        interval: loadTimeNumber
                        // Timing name
                        name: [NSString stringWithUTF8String: name.c_str()]
                        // Timing label
                        label: [NSString stringWithUTF8String: label.c_str()]] build]];
    }
    
    /**
     * An example method called when a user signs in to an authentication system.
     *
     * @param user represents a generic User object returned by an authentication system on sign in.
     */
    void GoogleAnalyticsHelper::signInWithUser(const string &userId,
                        const string &category,
                        const string &label,
                        long long value) {
        id<GAITracker> tracker = [[GAI sharedInstance] defaultTracker];
        
        // You only need to set User ID on a tracker once. By setting it on the tracker, the ID will be
        // sent with all subsequent hits.
        
        
        
        [tracker set:@"&uid" value: [NSString stringWithUTF8String: userId.c_str()]];
        
        // This hit will be sent with the User ID value and be visible in User-ID-enabled views (profiles).
        // Event category (required)
        [tracker send:[[GAIDictionaryBuilder
                        createEventWithCategory: [NSString stringWithUTF8String: category.c_str()]
                        // Event action (required)
                        action:@"user_sign_in"
                        // Event label
                        label: [NSString stringWithUTF8String: label.c_str()]
                        // Event value
                        value: [NSNumber numberWithLongLong: value]] build]];
    }

    
}}