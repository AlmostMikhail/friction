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

#include "boxrendercontainer.h"
#include "boxrenderdata.h"
#include "skia/skiahelpers.h"

void RenderContainer::drawSk(SkCanvas * const canvas, SkPaint * const paint) {
    if(!mSrcRenderData) return;
    canvas->save();
    canvas->concat(toSkMatrix(mPaintTransform));
    if(paint) {
        const auto blendMode = paint->getBlendMode();
        if(blendMode == SkBlendMode::kDstIn ||
           blendMode == SkBlendMode::kSrcIn ||
           blendMode == SkBlendMode::kDstATop) {
            SkPaint bPaint;
            bPaint.setBlendMode(paint->getBlendMode());
            bPaint.setColor(SK_ColorTRANSPARENT);
            SkPath path;
            path.addRect(SkRect::MakeXYWH(mGlobalRect.x(), mGlobalRect.y(),
                                          mImageSk->width(),
                                          mImageSk->height()));
            path.toggleInverseFillType();
            canvas->drawPath(path, bPaint);
        }
    }
    canvas->drawImage(mImageSk, mGlobalRect.x(), mGlobalRect.y(), paint);
    canvas->restore();
}

void RenderContainer::updatePaintTransformGivenNewTotalTransform(
                                    const QMatrix &totalTransform) {
    mPaintTransform = mTransform.inverted()*totalTransform;
    const qreal invRes = 1/mResolutionFraction;
    mPaintTransform.scale(invRes, invRes);
    mPaintTransform = mRenderTransform*mPaintTransform;
}

void RenderContainer::setSrcRenderData(BoxRenderData * const data) {
    mTransform = data->fTransform;
    mResolutionFraction = data->fResolution;
    mImageSk = data->fRenderedImage;
    mGlobalRect = data->fGlobalRect;
    mRelFrame = data->fRelFrame;
    mPaintTransform.reset();
    mPaintTransform.scale(1/mResolutionFraction, 1/mResolutionFraction);
    mRenderTransform = data->fRenderTransform;
    mPaintTransform = mRenderTransform*mPaintTransform;
    mSrcRenderData = data->ref<BoxRenderData>();
}