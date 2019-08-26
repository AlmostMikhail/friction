// enve - 2D animations software
// Copyright (C) 2016-2019 Maurycy Liebner

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef COLORANIMATOR_H
#define COLORANIMATOR_H

#include "staticcomplexanimator.h"
#include "../colorhelpers.h"
#include "qrealanimator.h"

class ColorAnimator : public StaticComplexAnimator {
    Q_OBJECT
    e_OBJECT
protected:
    ColorAnimator(const QString& name = "color");
public:
    bool SWT_isColorAnimator() const { return true; }

    void writeProperty(eWriteStream& dst) const;
    void readProperty(eReadStream& src);
    void setupTreeViewMenu(PropertyMenu * const menu);

    void qra_setCurrentValue(const QColor &qcolorValue);

    QColor getColor() const;
    QColor getColor(const qreal relFrame);
    void setColor(const QColor& col);

    void setColorMode(const ColorMode colorMode);

    void startVal1Transform();
    void startVal2Transform();
    void startVal3Transform();
    void startAlphaTransform();

    void setCurrentVal1Value(const qreal val1);
    void setCurrentVal2Value(const qreal val2);
    void setCurrentVal3Value(const qreal val3);
    void setCurrentAlphaValue(const qreal alpha);

    void duplicateVal1AnimatorFrom(QrealAnimator *source);
    void duplicateVal2AnimatorFrom(QrealAnimator *source);
    void duplicateVal3AnimatorFrom(QrealAnimator *source);
    void duplicateAlphaAnimatorFrom(QrealAnimator *source);

    ColorMode getColorMode() {
        return mColorMode;
    }

    QrealAnimator *getVal1Animator() {
        return mVal1Animator.get();
    }

    QrealAnimator *getVal2Animator() {
        return mVal2Animator.get();
    }

    QrealAnimator *getVal3Animator() {
        return mVal3Animator.get();
    }

    QrealAnimator *getAlphaAnimator() {
        return mAlphaAnimator.get();
    }
private:
    ColorMode mColorMode = ColorMode::rgb;

    qsptr<QrealAnimator> mVal1Animator =
            QrealAnimator::sCreate0to1Animator("");
    qsptr<QrealAnimator> mVal2Animator =
            QrealAnimator::sCreate0to1Animator("");
    qsptr<QrealAnimator> mVal3Animator =
            QrealAnimator::sCreate0to1Animator("");
    qsptr<QrealAnimator> mAlphaAnimator =
            QrealAnimator::sCreate0to1Animator("alpha");
signals:
    void colorModeChanged(ColorMode);
};

#endif // COLORANIMATOR_H