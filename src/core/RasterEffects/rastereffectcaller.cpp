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

#include "rastereffectcaller.h"


RasterEffectCaller::RasterEffectCaller(const HardwareSupport hwSupport,
                                       const bool forceMargin,
                                       const QMargins &margin) :
    fForceMargin(forceMargin), fHwSupport(hwSupport), fMargin(margin) {}

RasterEffectCaller::RasterEffectCaller(const HardwareSupport hwSupport) :
    RasterEffectCaller(hwSupport, false, QMargins()) {}

void RasterEffectCaller::processGpu(QGL33 * const gl,
                                    GpuRenderTools &renderTools,
                                    GpuRenderData &data) {
    Q_UNUSED(gl);
    Q_UNUSED(renderTools);
    Q_UNUSED(data);
}

void RasterEffectCaller::processCpu(CpuRenderTools &renderTools,
                                    const CpuRenderData &data) {
    Q_UNUSED(renderTools);
    Q_UNUSED(data);
}

int RasterEffectCaller::cpuThreads(const int available,
                                   const int area) const {
    return qMin(area/(150*150) + 1, available);
}
#include "skia/skqtconversions.h"
void RasterEffectCaller::setSrcRect(const SkIRect &srcRect,
                                    const SkIRect &clampRect) {
    const int sl = srcRect.left();
    const int st = srcRect.top();
    const int sr = srcRect.right();
    const int sb = srcRect.bottom();

    const int ml = fMargin.left();
    const int mt = fMargin.top();
    const int mr = fMargin.right();
    const int mb = fMargin.bottom();

    const int l = sl - ml;
    const int t = st - mt;
    const int r = sr + mr;
    const int b = sb + mb;

    const int cl = clampRect.left();
    const int ct = clampRect.top();
    const int cr = clampRect.right();
    const int cb = clampRect.bottom();

    if(fForceMargin) {
        fSrcRect = SkIRect::MakeLTRB(qMax(l, cl - ml),
                                     qMax(t, ct - mt),
                                     qMin(r, cr + mr),
                                     qMin(b, cb + mb));
        fDstRect = fSrcRect;
    } else {
        fSrcRect = srcRect;
        fDstRect = SkIRect::MakeLTRB(qMax(l, cl), qMax(t, ct),
                                     qMin(r, cr), qMin(b, cb));
    }
}