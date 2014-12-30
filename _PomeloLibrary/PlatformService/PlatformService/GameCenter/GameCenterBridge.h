//
//  GameCenterBridge.h
//  PlatformService
//
//  Created by MeYouGames on 13-8-14.
//  Copyright (c) 2013年 MeYouGames. All rights reserved.
//

#ifndef __PlatformService__GameCenterBridge__
#define __PlatformService__GameCenterBridge__

class GameCenterBridge {
private:
    static bool mAuthenticated;
public:
    GameCenterBridge();
    ~GameCenterBridge();
    
    static void authenticateLocalPlayer();
    static void showLeaderBoard(const char* Category, int scope);
    static void reportScore(const char* Category, int score);
    static void loadState();
    static void saveState();
};

#endif /* defined(__PlatformService__GameCenterBridge__) */
