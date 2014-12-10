//
//  Level.m
//  HelloSpriteBuilder
//
//  Created by Dung Ta Van on 12/10/14.
//  Copyright (c) 2014 Apportable. All rights reserved.
//

#import "Level.h"

@implementation Level

-(void)launchBird: (id)sender
{
    float rotationRadians = CC_DEGREES_TO_RADIANS(_launcher.rotation);
    
    CGPoint directionVector = ccp(sinf(rotationRadians), cosf(rotationRadians));
    CGPoint ballOffset = ccpMult(directionVector, 50);
    
    CCNode *ball = [CCBReader load:@"Bird"];
    ball.position = ccpAdd(_launcher.position, ballOffset);
    
    [_physicsNode addChild:ball];
    
    CGPoint force = ccpMult(directionVector, 50000);
    [ball.physicsBody applyForce:force];
}

@end
