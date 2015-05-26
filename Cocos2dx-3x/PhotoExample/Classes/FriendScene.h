//
//  FriendScene.h
//  PhotoExample
//
//  Created by Paras Mendiratta on 25/05/15.
//
//

#ifndef __PhotoExample__FriendScene__
#define __PhotoExample__FriendScene__

#include "cocos2d.h"
#include "EziSocialObject.h"
#include "EziSocialDelegate.h"


class FriendScene : public cocos2d::Layer, public EziFacebookDelegate
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void playingFriendCallback(cocos2d::Ref* pSender);
    void nonPlayingFriendCallback(cocos2d::Ref* sender);
    
    void applyPhoto(Ref* sender, Sprite* photo);
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(FriendScene);
    
    // New Virtual Method
    virtual void fbFriendsCallback(int responseCode, const char* responseMessage, const std::vector<EziFacebookFriend*> friends);
    
    virtual void fbPhotoCallback(int responseCode, cocos2d::Sprite* userSprite, EziFacebookUserBase* fbUser);
    
private:
    
    LabelTTF* friendName;
    Sprite* friendPhoto;
    EziFacebookFriend* myFriend;
};

#endif /* defined(__PhotoExample__FriendScene__) */
