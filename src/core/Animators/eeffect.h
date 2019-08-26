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

#ifndef EEFFECT_H
#define EEFFECT_H
#include "staticcomplexanimator.h"

class eEffect : public StaticComplexAnimator {
public:
    eEffect(const QString &name);

    virtual void writeIdentifier(eWriteStream& dst) const = 0;

    void writeProperty(eWriteStream& dst) const;
    void readProperty(eReadStream& src);

    void switchVisible();
    void setVisible(const bool visible);
    bool isVisible() const;
private:
    bool mVisible = true;
};

#endif // EEFFECT_H