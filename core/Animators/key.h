#ifndef KEY_H
#define KEY_H
#include "smartPointers/sharedpointerdefs.h"
#include "pointhelpers.h"

#include <QtCore>
class QPainter;
class KeyCloner;
class Animator;

class KeysClipboardContainer;

class Key : public StdSelfRef {
    friend class Animator;
    friend class KeysClipboardContainer;
public:
    Key(Animator * const parentAnimator);
    Key(const int &frame, Animator * const parentAnimator);

//    QrealPoint *mousePress(qreal frameT, qreal valueT,
//                    qreal pixelsPerFrame, qreal pixelsPerValue);

    virtual void startFrameTransform();
    virtual void finishFrameTransform();

    virtual void deleteKey() {
        removeFromAnimator();
    }

    virtual bool differsFromKey(Key* key) const = 0;
    virtual void writeKey(QIODevice *target);
    virtual void readKey(QIODevice *target);


    virtual void cancelFrameTransform();
    virtual void scaleFrameAndUpdateParentAnimator(
            const int &relativeToFrame,
            const qreal &scaleFactor,
            const bool& useSavedFrame);

    virtual bool isSelected() const;
    virtual void addToSelection(QList<qptr<Animator>> &toSelect);
    virtual void removeFromSelection(QList<qptr<Animator>> &toRemove);
    virtual bool isDescendantSelected() const { return isSelected(); }


    int getAbsFrame() const;

    bool hasPrevKey() const;
    bool hasNextKey() const;
    void incFrameAndUpdateParentAnimator(const int &inc);
    void setRelFrameAndUpdateParentAnimator(const int &relFrame);
    template <class T = Animator>
    T* getParentAnimator() const {
        return static_cast<T*>(mParentAnimator.data());
    }
    void removeFromAnimator();

    void setSelected(const bool &bT);

    bool isHovered() const {
        return mHovered;
    }

    void setHovered(const bool &bT) {
        mHovered = bT;
    }

    int getRelFrame() const;
    void setAbsFrame(const int &frame);

    Key* getNextKey() const;
    Key* getPrevKey() const;

    template <class T>
    T* getNextKey() const {
        return static_cast<T*>(getNextKey());
    }

    template <class T = Key>
    T* getPrevKey() const {
        return static_cast<T*>(getPrevKey());
    }

    bool differesFromNextKey() const {
        return differsFromKey(getNextKey());
    }

    bool differesFromPrevKey() const {
        return differsFromKey(getPrevKey());
    }

    void afterKeyChanged();

    int getPrevKeyRelFrame() const {
        auto prevKey = getPrevKey();
        if(!prevKey) return mRelFrame;
        return prevKey->getRelFrame();
    }

    int getNextKeyRelFrame() const {
        auto nextKey = getNextKey();
        if(!nextKey) return mRelFrame;
        return getNextKey()->getRelFrame();
    }

    int relFrameToAbsFrame(const int relFrame) const;
    int absFrameToRelFrame(const int absFrame) const;
    qreal relFrameToAbsFrameF(const qreal relFrame) const;
    qreal absFrameToRelFrameF(const qreal absFrame) const;
protected:
    virtual void setRelFrame(const int &frame);
    bool mIsSelected = false;
    bool mHovered = false;

    int mRelFrame;
    int mSavedRelFrame;

    QPointer<Animator> mParentAnimator;
};

#endif // KEY_H
