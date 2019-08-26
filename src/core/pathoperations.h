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

#ifndef PATHOPERATIONS_H
#define PATHOPERATIONS_H
#include <QPainterPath>
class PathBox;
class SkPath;
class PathAnimator;

extern void gApplyOperation(const qreal relFrame, const SkPath &src,
                            SkPath * const dst, PathBox * const srcBox,
                            PathBox * const dstBox, const QString &operation);

extern void gSolidify(const qreal widthT,
                      const SkPath &src,
                      SkPath * const dst);

#endif // PATHOPERATIONS_H