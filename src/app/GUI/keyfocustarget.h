#ifndef KEYFOCUSTARGET_H
#define KEYFOCUSTARGET_H
#include <QKeyEvent>
#include <QWidget>

class KeyFocusTarget {
public:
    KeyFocusTarget();
    virtual ~KeyFocusTarget();

    bool KFT_hasFocus() {
        return KFT_mCurrentTarget == this;
    }

    static bool KFT_handleKeyEvent(QKeyEvent *e);
    virtual bool KFT_handleKeyEventForTarget(QKeyEvent *e) = 0;

    void KFT_setFocus() {
        KFT_setCurrentTarget(this);
        KFT_setFocusToWidget();
    }

    static KeyFocusTarget *KFT_getCurrentTarget();

    static void KFT_setCurrentTarget(KeyFocusTarget *target);
protected:
    virtual void KFT_setFocusToWidget() = 0;
    virtual void KFT_clearFocus() = 0;
private:
    static KeyFocusTarget *KFT_mCurrentTarget;
    static QList<KeyFocusTarget*> KFT_mAllTargets;
};

#endif // KEYFOCUSTARGET_H