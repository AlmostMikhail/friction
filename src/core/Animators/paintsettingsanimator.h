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

#ifndef PAINTSETTINGSANIMATOR_H
#define PAINTSETTINGSANIMATOR_H

#include "Animators/qrealanimator.h"
#include "coloranimator.h"
#include "colorhelpers.h"
#include "skia/skiaincludes.h"
#include "smartPointers/ememory.h"
#include "Animators/gradient.h"
#include "Animators/staticcomplexanimator.h"
#include "paintsettings.h"

class PathBox;
class SkStroke;

class GradientPoints;

class PaintSettingsAnimator : public ComplexAnimator {
protected:
    PaintSettingsAnimator(const QString &name,
                          GradientPoints * const grdPts,
                          PathBox * const parent);

    PaintSettingsAnimator(
            const QString &name,
            GradientPoints * const grdPts,
            PathBox * const parent,
            const QColor &colorT,
            const PaintType paintTypeT,
            Gradient * const gradientT = nullptr);

    virtual void showHideChildrenBeforeChaningPaintType(
            const PaintType newPaintType);
public:
    void writeProperty(eWriteStream& dst) const;
    void readProperty(eReadStream& src);

    QColor getColor() const;
    PaintType getPaintType() const;
    Gradient *getGradient() const;
    void setGradient(Gradient *gradient);
    void setCurrentColor(const QColor &color);
    void setPaintType(const PaintType paintType);
    ColorAnimator *getColorAnimator();
    void setGradientPoints(GradientPoints * const gradientPoints);
    void setGradientPointsPos(const QPointF& pt1, const QPointF& pt2);

    void duplicateColorAnimatorFrom(ColorAnimator *source);
    void setGradientVar(Gradient * const grad);
    QColor getColor(const qreal relFrame) const;
    GradientType getGradientType() { return mGradientType; }
    void setGradientType(const GradientType type) {
        if(mGradientType == type) return;
        mGradientType = type;
        prp_afterWholeInfluenceRangeChanged();
    }
private:
    GradientType mGradientType = GradientType::LINEAR;
    PaintType mPaintType = NOPAINT;

    PathBox * const mTarget_k;
    qptr<GradientPoints> mGradientPoints;
    qsptr<ColorAnimator> mColor = enve::make_shared<ColorAnimator>();
    qptr<Gradient> mGradient;
};

class FillSettingsAnimator : public PaintSettingsAnimator {
    e_OBJECT
public:
    bool SWT_isFillSettingsAnimator() const { return true; }
protected:
    FillSettingsAnimator(GradientPoints * const grdPts,
                         PathBox * const parent) :
        FillSettingsAnimator(grdPts, parent, QColor(0, 0, 0),
                             PaintType::NOPAINT, nullptr) {}

    FillSettingsAnimator(GradientPoints * const grdPts,
                         PathBox * const parent,
                         const QColor &color,
                         const PaintType paintType,
                         Gradient * const gradient = nullptr) :
        PaintSettingsAnimator("fill", grdPts, parent, color,
                              paintType, gradient) {}
};

struct UpdatePaintSettings {
    UpdatePaintSettings(const QColor &paintColorT,
                        const PaintType paintTypeT);
    UpdatePaintSettings();

    virtual ~UpdatePaintSettings();

    virtual void applyPainterSettingsSk(SkPaint *paint);

    void updateGradient(const QGradientStops &stops,
                        const QPointF &start,
                        const QPointF &finalStop,
                        const GradientType gradientType);
    PaintType fPaintType;
    QColor fPaintColor;
    sk_sp<SkShader> fGradient;
};

struct UpdateStrokeSettings : UpdatePaintSettings {
    UpdateStrokeSettings(
            const qreal width,
            const QColor &paintColorT,
            const PaintType paintTypeT,
            const QPainter::CompositionMode &outlineCompositionModeT);
    UpdateStrokeSettings();

    void applyPainterSettingsSk(SkPaint *paint);

    QPainter::CompositionMode fOutlineCompositionMode =
            QPainter::CompositionMode_Source;

    qreal fOutlineWidth;
};

#endif // PAINTSETTINGSANIMATOR_H