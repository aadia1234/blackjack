#include "BlackjackJNI.h"
#include <cstdlib>
#include <string>
#include <iostream>
#include "GameLogic.h"

static jlong globalGamePtr = 0;

JNIEXPORT jlong JNICALL Java_src_BlackjackNative_createGameInstance(JNIEnv *env, jobject obj) {
    if (globalGamePtr != 0) {
        GameLogic *oldGame = reinterpret_cast<GameLogic*>(globalGamePtr);
        delete oldGame;
    }
    GameLogic *game = new GameLogic();
    globalGamePtr = reinterpret_cast<jlong>(game);
    return globalGamePtr;
}

JNIEXPORT void JNICALL Java_src_BlackjackNative_destroyGameInstance(JNIEnv *env, jobject obj, jlong gamePtr) {
    GameLogic *game = reinterpret_cast<GameLogic*>(gamePtr);
    delete game;
}

JNIEXPORT void JNICALL Java_src_BlackjackNative_newGame(JNIEnv *env, jobject obj) {
    if (globalGamePtr == 0) return;
    GameLogic *game = reinterpret_cast<GameLogic*>(globalGamePtr);
    game->newGame();
    std::cout << "New game started" << std::endl;
}

JNIEXPORT void JNICALL Java_src_BlackjackNative_placeBet(JNIEnv *env, jobject obj, jint amount) {
    if (globalGamePtr == 0) return;
    GameLogic *game = reinterpret_cast<GameLogic*>(globalGamePtr);
    game->placeBet(amount);
}

JNIEXPORT jboolean JNICALL Java_src_BlackjackNative_playerHit(JNIEnv *env, jobject obj) {
    if (globalGamePtr == 0) return JNI_FALSE;
    GameLogic *game = reinterpret_cast<GameLogic*>(globalGamePtr);
    return static_cast<jboolean>(game->playerHit());
}

JNIEXPORT void JNICALL Java_src_BlackjackNative_playerStand(JNIEnv *env, jobject obj) {
    if (globalGamePtr == 0) return;
    GameLogic *game = reinterpret_cast<GameLogic*>(globalGamePtr);
    game->playerStand();
}

JNIEXPORT jboolean JNICALL Java_src_BlackjackNative_isGameOver(JNIEnv *env, jobject obj) {
    if (globalGamePtr == 0) return JNI_FALSE;
    GameLogic *game = reinterpret_cast<GameLogic*>(globalGamePtr);
    return static_cast<jboolean>(game->isGameOver());
}

JNIEXPORT jobjectArray JNICALL Java_src_BlackjackNative_getPlayerCards(JNIEnv *env, jobject obj) {
    if (globalGamePtr == 0) return nullptr;
    GameLogic *game = reinterpret_cast<GameLogic*>(globalGamePtr);
    std::vector<Card> cards = game->getPlayerCards();
    
    // Find the Card class
    jclass cardClass = env->FindClass("src/Card");
    if (cardClass == nullptr) return nullptr;
    
    // Create the Java array of Card objects
    jobjectArray cardArray = env->NewObjectArray(cards.size(), cardClass, nullptr);
    
    // Get the Card constructor method ID
    jmethodID cardConstructor = env->GetMethodID(cardClass, "<init>", "(Ljava/lang/String;CLjava/lang/String;I)V");
    if (cardConstructor == nullptr) return nullptr;
    
    // Fill the array with Card objects
    for (size_t i = 0; i < cards.size(); i++) {
        jstring face = env->NewStringUTF(cards[i].getFace().c_str());
        jchar suit = cards[i].getSuitSymbol()[0];
        jstring suitName = env->NewStringUTF(cards[i].getSuit().c_str());
        jint value = cards[i].getValue();
        
        jobject cardObject = env->NewObject(cardClass, cardConstructor, face, suit, suitName, value);
        env->SetObjectArrayElement(cardArray, i, cardObject);
        
        env->DeleteLocalRef(face);
        env->DeleteLocalRef(suitName);
        env->DeleteLocalRef(cardObject);
    }
    
    return cardArray;
}

JNIEXPORT jobjectArray JNICALL Java_src_BlackjackNative_getDealerCards(JNIEnv *env, jobject obj) {
    if (globalGamePtr == 0) return nullptr;
    GameLogic *game = reinterpret_cast<GameLogic*>(globalGamePtr);
    std::vector<Card> cards = game->getDealerCards();
    
    // Find the Card class
    jclass cardClass = env->FindClass("src/Card");
    if (cardClass == nullptr) return nullptr;
    
    // Create the Java array of Card objects
    jobjectArray cardArray = env->NewObjectArray(cards.size(), cardClass, nullptr);
    
    // Get the Card constructor method ID
    jmethodID cardConstructor = env->GetMethodID(cardClass, "<init>", "(Ljava/lang/String;CLjava/lang/String;I)V");
    if (cardConstructor == nullptr) return nullptr;
    
    // Fill the array with Card objects
    for (size_t i = 0; i < cards.size(); i++) {
        jstring face = env->NewStringUTF(cards[i].getFace().c_str());
        jchar suit = cards[i].getSuitSymbol()[0];
        jstring suitName = env->NewStringUTF(cards[i].getSuit().c_str());
        jint value = cards[i].getValue();
        
        jobject cardObject = env->NewObject(cardClass, cardConstructor, face, suit, suitName, value);
        env->SetObjectArrayElement(cardArray, i, cardObject);
        
        env->DeleteLocalRef(face);
        env->DeleteLocalRef(suitName);
        env->DeleteLocalRef(cardObject);
    }
    
    return cardArray;
}

JNIEXPORT jboolean JNICALL Java_src_BlackjackNative_shouldHideDealerFirstCard(JNIEnv *env, jobject obj) {
    if (globalGamePtr == 0) return JNI_FALSE;
    GameLogic *game = reinterpret_cast<GameLogic*>(globalGamePtr);
    return static_cast<jboolean>(game->shouldHideDealerFirstCard());
}

JNIEXPORT jint JNICALL Java_src_BlackjackNative_getPlayerMoney(JNIEnv *env, jobject obj) {
    if (globalGamePtr == 0) return 0;
    GameLogic *game = reinterpret_cast<GameLogic*>(globalGamePtr);
    return static_cast<jint>(game->getPlayerMoney());
}

JNIEXPORT jint JNICALL Java_src_BlackjackNative_getCurrentBet(JNIEnv *env, jobject obj) {
    if (globalGamePtr == 0) return 0;
    GameLogic *game = reinterpret_cast<GameLogic*>(globalGamePtr);
    return static_cast<jint>(game->getCurrentBet());
}

JNIEXPORT jint JNICALL Java_src_BlackjackNative_getPlayerHandValue(JNIEnv *env, jobject obj) {
    if (globalGamePtr == 0) return 0;
    GameLogic *game = reinterpret_cast<GameLogic*>(globalGamePtr);
    return static_cast<jint>(game->getPlayerHandValue());
}

JNIEXPORT jint JNICALL Java_src_BlackjackNative_getDealerHandValue(JNIEnv *env, jobject obj) {
    if (globalGamePtr == 0) return 0;
    GameLogic *game = reinterpret_cast<GameLogic*>(globalGamePtr);
    return static_cast<jint>(game->getDealerHandValue());
}

JNIEXPORT jboolean JNICALL Java_src_BlackjackNative_didPlayerWin(JNIEnv *env, jobject obj) {
    if (globalGamePtr == 0) return JNI_FALSE;
    GameLogic *game = reinterpret_cast<GameLogic*>(globalGamePtr);
    return static_cast<jboolean>(game->didPlayerWin());
}

JNIEXPORT jboolean JNICALL Java_src_BlackjackNative_didDealerWin(JNIEnv *env, jobject obj) {
    if (globalGamePtr == 0) return JNI_FALSE;
    GameLogic *game = reinterpret_cast<GameLogic*>(globalGamePtr);
    return static_cast<jboolean>(game->didDealerWin());
}

JNIEXPORT jboolean JNICALL Java_src_BlackjackNative_isTie(JNIEnv *env, jobject obj) {
    if (globalGamePtr == 0) return JNI_FALSE;
    GameLogic *game = reinterpret_cast<GameLogic*>(globalGamePtr);
    return static_cast<jboolean>(game->isTie());
}

JNIEXPORT jstring JNICALL Java_src_BlackjackNative_getGameStateMessage(JNIEnv *env, jobject obj) {
    if (globalGamePtr == 0) return nullptr;
    GameLogic *game = reinterpret_cast<GameLogic*>(globalGamePtr);
    std::string message = game->getGameStateMessage();
    return env->NewStringUTF(message.c_str());
}