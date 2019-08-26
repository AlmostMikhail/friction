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

#ifndef GRADIENTPOINTS_H
#define GRADIENTPOINTS_H
#include "Animators/staticcomplexanimator.h"
class GradientPoint;
class MovablePoint;
class PathBox;
class QPointFAnimator;
#include "skia/skiaincludes.h"

class GradientPoints : public StaticComplexAnimator {
    e_OBJECT
protected:
    GradientPoints(PathBox * const parent);
public:
    void drawCanvasControls(SkCanvas *const canvas,
                            const CanvasMode mode,
                            const float invScale,
                            const bool ctrlPressed);

    void enable();
    void disable();

    void setColors(const QColor &startColor, const QColor &endColor);

    void setPositions(const QPointF &startPos, const QPointF &endPos);

    QPointF getStartPointAtRelFrame(const int relFrame);
    QPointF getEndPointAtRelFrame(const int relFrame);
    QPointF getStartPointAtRelFrameF(const qreal relFrame);
    QPointF getEndPointAtRelFrameF(const qreal relFrame);

    bool enabled() const {
        return mEnabled;
    }
private:
    bool mEnabled;

    qsptr<QPointFAnimator> mStartAnimator;
    qsptr<QPointFAnimator> mEndAnimator;

    stdsptr<GradientPoint> mStartPoint;
    stdsptr<GradientPoint> mEndPoint;

    PathBox* const mParent_k;
};

#endif // GRADIENTPOINTS_H