//
//  GameCenterBridge.cpp
//  PlatformService
//
//  Created by MeYouGames on 13-8-14.
//  Copyright (c) 2013年 MeYouGames. All rights reserved.
//

#include "GameCenterBridge.h"
#include "GameCenterManager.h"

bool GameCenterBridge::mAuthenticated =false;

GameCenterBridge::GameCenterBridge() {
}

GameCenterBridge::~GameCenterBridge() {
    
}

void GameCenterBridge::authenticateLocalPlayer() {
    if(mAuthenticated == false) {
        [[GameCenterManager sharedGameCenterManager ]authenticateLocalPlayer];
        mAuthenticated = true;
    }
}

void GameCenterBridge::showLeaderBoard(const char* Category, int scope) {
    [[GameCenterManager sharedGameCenterManager ]showLeaderboardForCategory:[[NSString alloc] initWithCString:Category encoding:NSUTF8StringEncoding] andTimeScope:scope];
}

void GameCenterBridge::reportScore(const char* Category, int score) {
    [[GameCenterManager sharedGameCenterManager ]reportScore:score forCategory:[[NSString alloc] initWithCString:Category encoding:NSUTF8StringEncoding]];
}

void GameCenterBridge::loadState(){
    [GameCenterManager loadState];
}

void GameCenterBridge::saveState(){
    [GameCenterManager saveState];
}
