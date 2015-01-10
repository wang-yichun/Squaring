//
//  GameCenterManager.m
//
//  Created by Nathan Demick on 4/17/11.
//  Copyright 2011 Ganbaru Games. All rights reserved.
//

#import "GameCenterManager.h"

#define SYSTEM_VERSION_EQUAL_TO(v)                  ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedSame)
#define SYSTEM_VERSION_GREATER_THAN(v)              ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedDescending)
#define SYSTEM_VERSION_GREATER_THAN_OR_EQUAL_TO(v)  ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] != NSOrderedAscending)
#define SYSTEM_VERSION_LESS_THAN(v)                 ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedAscending)
#define SYSTEM_VERSION_LESS_THAN_OR_EQUAL_TO(v)     ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] != NSOrderedDescending)

@implementation GameCenterManager

@synthesize hasGameCenter, unsentScores;

SYNTHESIZE_SINGLETON_FOR_CLASS(GameCenterManager);

- (id)init 
{
	if ((self = [super init]))
	{
		// Initialize any class properties here
		if ([self isGameCenterAPIAvailable])
			hasGameCenter = YES;
		else
			hasGameCenter = NO;		
	}
	return self;
}

/**
 Check to see if installed OS supports Game Center
 */
- (BOOL)isGameCenterAPIAvailable
{
	// Check for presence of GKLocalPlayer class
	BOOL localPlayerClassAvailable = (NSClassFromString(@"GKLocalPlayer")) != nil;
	
	// Device must be running 4.1 or later
	NSString *reqSysVer = @"4.1";
	NSString *currSysVer = [[UIDevice currentDevice] systemVersion];
	BOOL osVersionSupported = ([currSysVer compare:reqSysVer options:NSNumericSearch] != NSOrderedAscending);
	
	return (localPlayerClassAvailable && osVersionSupported);
}

/**
 Attempt to authenticate a Game Center user. Will automatically present a modal login window.
 */
- (void)authenticateLocalPlayer
{
	if (hasGameCenter)
	{
		GKLocalPlayer *localPlayer = [GKLocalPlayer localPlayer];
        
        if (SYSTEM_VERSION_GREATER_THAN_OR_EQUAL_TO(@"6.0")) {
            // iOS 6
            localPlayer.authenticateHandler = ^(UIViewController *viewController, NSError *error){
                if (viewController != nil)
                {
                    myViewController = [[[UIViewController alloc] init] autorelease];
                    [myViewController presentViewController:viewController animated:false completion:nil];
                }
                else if (localPlayer.isAuthenticated)
                {
                    /* Perform additional tasks for the authenticated player here */
                    
                    // If unsent scores array has length > 0, try to send saved scores
                    if ([unsentScores count] > 0)
                    {
                        // Create new array to help remove successfully sent scores
                        NSMutableArray *removedScores = [NSMutableArray array];
                        
                        for (GKScore *score in unsentScores)
                        {
                            [score reportScoreWithCompletionHandler:^(NSError *error) {
                                if (error != nil)
                                {
                                    // If there's an error reporting the score (again!), leave the score in the array
                                }
                                else
                                {
                                    // If success, mark score for removal
                                    [removedScores addObject:score];
                                }
                            }];
                        }
                        
                        // Remove successfully sent scores from stored array
                        [unsentScores removeObjectsInArray:removedScores];
                    }
                }
                else
                {
                    hasGameCenter = NO;
                }
            };
        } else {
            // iOS 5
            [localPlayer authenticateWithCompletionHandler:^(NSError *error) {
                if (localPlayer.isAuthenticated)
                {
                    /* Perform additional tasks for the authenticated player here */
                    
                    // If unsent scores array has length > 0, try to send saved scores
                    if ([unsentScores count] > 0)
                    {
                        // Create new array to help remove successfully sent scores
                        NSMutableArray *removedScores = [NSMutableArray array];
                        
                        for (GKScore *score in unsentScores)
                        {
                            [score reportScoreWithCompletionHandler:^(NSError *error) {
                                if (error != nil)
                                {
                                    // If there's an error reporting the score (again!), leave the score in the array
                                }
                                else
                                {
                                    // If success, mark score for removal
                                    [removedScores addObject:score];
                                }
                            }];
                        }
                        
                        // Remove successfully sent scores from stored array
                        [unsentScores removeObjectsInArray:removedScores];
                    }
                }
                else {
                    hasGameCenter = NO;
                }
            }];
        }
        
        
//		[localPlayer authenticateWithCompletionHandler:^(NSError *error) {
//			if (localPlayer.isAuthenticated)
//			{
//				
//			}
//			else
//			{
//				// Disable Game Center methods - player not authenticated
//				hasGameCenter = NO;
//			}
//		}];
	}
}

/**
 Send an integer score to Game Center for a particular category (set up category in iTunes Connect)
 */
- (void)reportScore:(int64_t)score forCategory:(NSString *)category
{
	// Only execute if OS supports Game Center & player is logged in
	if (hasGameCenter)
	{
		// Create score object
		GKScore *scoreReporter = [[[GKScore alloc] initWithCategory:category] autorelease];
		
		// Set the score value
		scoreReporter.value = score;
		
		// Try to send
		[scoreReporter reportScoreWithCompletionHandler:^(NSError *error) {
			if (error != nil)
			{
				// Handle reporting error here by adding object to a serializable array, to be sent again later
				[unsentScores addObject:scoreReporter];
			}
		}];
	}
}

/**
 Show the "green felt" leaderboard view for a particular category
 */
- (void)showLeaderboardForCategory:(NSString *)category andTimeScope:(GKLeaderboardTimeScope)scope
{
	// Only execute if OS supports Game Center & player is logged in
	if (hasGameCenter)
	{
		// Create leaderboard view w/ default Game Center style
		GKLeaderboardViewController *leaderboardController = [[GKLeaderboardViewController alloc] init];
		
		// If view controller was successfully created...
		if (leaderboardController != nil)
		{
			// Leaderboard config
			leaderboardController.leaderboardDelegate = self;	// The leaderboard view controller will send messages to this object
			leaderboardController.category = category;	// Set category here
			leaderboardController.timeScope = scope;	// GKLeaderboardTimeScopeToday, GKLeaderboardTimeScopeWeek, GKLeaderboardTimeScopeAllTime
			
			// Create an additional UIViewController to attach the GKLeaderboardViewController to
			myViewController = [[UIViewController alloc] init];
			
			// Add the temporary UIViewController to the main OpenGL view
            [[[UIApplication sharedApplication ] keyWindow ] addSubview:myViewController.view ];
			
			// Tell UIViewController to present the leaderboard
//			[myViewController presentModalViewController:leaderboardController animated:YES];
            [myViewController presentViewController:leaderboardController animated:YES completion:nil];
		}
	}
}

/**
 Since this singleton is the GKLeaderboardViewControlerDelegage, it intercepts this method and removes the view
 */
- (void)leaderboardViewControllerDidFinish:(GKLeaderboardViewController *)viewController
{
    [viewController dismissViewControllerAnimated:YES completion:^{
        [myViewController.view removeFromSuperview];
        [myViewController release];
    }];
}

#pragma mark -
#pragma mark Loading/Saving State

+ (void)loadState
{
	@synchronized([GameCenterManager class]) 
	{
		// just in case loadState is called before GameCenterManager inits
		if (!sharedGameCenterManager)
			[GameCenterManager sharedGameCenterManager];
		
		NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
		NSString *documentsDirectory = [paths objectAtIndex:0];
		NSString *file = [documentsDirectory stringByAppendingPathComponent:@"GameCenterManager.bin"];
		Boolean saveFileExists = [[NSFileManager defaultManager] fileExistsAtPath:file];
		
		if (saveFileExists) 
		{
			// don't need to set the result to anything here since we're just getting initwithCoder to be called.
			// if you try to overwrite sharedGameCenterManager here, an assert will be thrown.
			[NSKeyedUnarchiver unarchiveObjectWithFile:file];
		}
	}
}

+ (void)saveState
{
	@synchronized([GameCenterManager class]) 
	{  
		GameCenterManager *state = [GameCenterManager sharedGameCenterManager];
		
		NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
		NSString *documentsDirectory = [paths objectAtIndex:0];
		NSString *saveFile = [documentsDirectory stringByAppendingPathComponent:@"GameCenterManager.bin"];
		[NSKeyedArchiver archiveRootObject:state toFile:saveFile];
	}
}

#pragma mark -
#pragma mark NSCoding Protocol Methods

- (void)encodeWithCoder:(NSCoder *)coder
{
	[coder encodeBool:self.hasGameCenter forKey:@"hasGameCenter"];
	[coder encodeObject:self.unsentScores forKey:@"unsentScores"];
}

- (id)initWithCoder:(NSCoder *)coder
{
	if ((self = [super init]))
	{
		self.hasGameCenter = [coder decodeBoolForKey:@"hasGameCenter"];
		self.unsentScores = [coder decodeObjectForKey:@"unsentScores"];
	}
	return self;
}

@end
