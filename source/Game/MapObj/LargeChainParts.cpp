#include "Game/MapObj/LargeChainParts.h"
#include "Game/Util/ActorSensorUtil.h"
#include "Game/Util/EffectUtil.h"
#include "Game/Util/LiveActorUtil.h"
#include "Game/Util/ObjUtil.h"
#include "Game/Util/SoundUtil.h"

LargeChainParts::LargeChainParts(const char* pName) : LiveActor(pName) {}

void LargeChainParts::breakChainParts() {
    kill();
}

void LargeChainParts::initChainParts(TVec3f* pPos, TVec3f* pRot, TVec3f* pScale, bool isFixedPoint) {
    mTranslation.set(*pPos);
    mRotation.set(*pRot);
    mScale.set(*pScale);

    if (isFixedPoint) {
        initModelManagerWithAnm("LargeChainFixPoint", nullptr, nullptr, false);
    }
    else {
        initModelManagerWithAnm("LargeChain", nullptr, nullptr, false);
    }

    MR::connectToSceneMapObj(this);

    initHitSensor(1);
    MR::addBodyMessageSensorMapObj(this);

    if (isFixedPoint) {
        MR::initCollisionParts(this, "LargeChainFixPoint", getSensor("body"), nullptr);
    }
    else {
        MR::initCollisionParts(this, "LargeChain", getSensor("body"), nullptr);
    }

    initEffectKeeper(0, "LargeChain", false);
    initSound(2, false, nullptr, TVec3f(0.0f));

    makeActorAppeared();
}

void LargeChainParts::kill() {
    MR::emitEffect(this, "Break");

    MR::startSound(this, "SE_OJ_LARGE_CHAIN_BREAK");

    LiveActor::kill();
}
