//
//  FriendScene.cpp
//  PhotoExample
//
//  Created by Paras Mendiratta on 25/05/15.
//
//

#include "FriendScene.h"
#include "EziFacebookFriend.h"

USING_NS_CC;

Scene* FriendScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = FriendScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool FriendScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    // Add Friend Name
    friendName = LabelTTF::create("Unknown Friend", "Arial", 24);
    friendName->setPosition(visibleSize.width/2, visibleSize.height - 30);
    this->addChild(friendName);
    
    
    // Add Friend Photo
    friendPhoto = Sprite::create("CloseSelected.png");

    friendPhoto->setPosition(visibleSize.width/2, visibleSize.height - 200);
    this->addChild(friendPhoto);
    
    // Add Menu
    auto playingFriendMenuItem = MenuItemFont::create("Get random friend playing this game", CC_CALLBACK_1(FriendScene::playingFriendCallback, this));
    
    auto nonPlayingFriendMenuItem = MenuItemFont::create("Get random friend NOT playing this game", CC_CALLBACK_1(FriendScene::nonPlayingFriendCallback, this));
    
    
    Menu *friendMenu = Menu::create(playingFriendMenuItem, nonPlayingFriendMenuItem, NULL);
    friendMenu->alignItemsVertically();
    
    this->addChild(friendMenu, 1);
    
    EziSocialObject::sharedObject()->setFacebookDelegate(this);
    
    return true;
}


void FriendScene::playingFriendCallback(cocos2d::Ref* pSender)
{
    EziSocialObject::sharedObject()->getFriends(EziSocialWrapperNS::FB_FRIEND_SEARCH::ONLY_INSTALLED, 0, 1);
}

void FriendScene::nonPlayingFriendCallback(cocos2d::Ref* sender)
{
    EziSocialObject::sharedObject()->getFriends(EziSocialWrapperNS::FB_FRIEND_SEARCH::ONLY_NOT_INSTALLED, 0, 1);
}

void FriendScene::applyPhoto(Ref* sender, Sprite* photo)
{
    CCLOG("Got friend's photo.");
    
    if (photo != nullptr){
        
        // Apply photo texture
        friendPhoto->setTexture(photo->getTexture());
    }
    
}

void FriendScene::fbFriendsCallback(int responseCode, const char* responseMessage, const std::vector<EziFacebookFriend*> friends)
{
    //MessageBox(responseMessage, "Friend's Callback");
    
    if (friends.size() > 0)
    {
        for (int i=0; i<1; i++) {
            
            EziFacebookFriend* tempFriend = friends.at(i);
            friendName->setString(tempFriend->getName());
            Sprite* tempSprite = nullptr;
            
            // Will release in callback. Need to retain otherwise, reference will be lost during download. May not be ideal way.
            tempFriend->retain();
            
            tempSprite = tempFriend->getPhoto(CC_CALLBACK_2(FriendScene::applyPhoto, this), false, 50, 50);
            
            if (tempSprite)
            {
                this->applyPhoto(this, tempSprite);
            }
        }
    }
}

void FriendScene::fbPhotoCallback(int responseCode, cocos2d::Sprite* userSprite, EziFacebookUserBase* fbUser)
{
    if (userSprite)
    {
        this->applyPhoto(this, userSprite);
    }
}
