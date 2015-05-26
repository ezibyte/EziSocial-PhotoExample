#import <UIKit/UIKit.h>
#import <EziSocialSDK/EziSocialManager.h>

@class RootViewController;

@interface AppController : NSObject <UIApplicationDelegate> {
    UIWindow *window;
}

@property(nonatomic, readonly) RootViewController* viewController;

@end

