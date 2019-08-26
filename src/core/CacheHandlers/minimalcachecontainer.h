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

#ifndef MINIMALCACHECONTAINER_H
#define MINIMALCACHECONTAINER_H
#include "smartPointers/stdselfref.h"

class CacheContainer : public StdSelfRef {
protected:
    CacheContainer();
public:
    ~CacheContainer();

    virtual void noDataLeft_k() = 0;
    virtual int getByteCount() = 0;
    virtual int free_RAM_k() {
        const int bytes = getByteCount();
        noDataLeft_k();
        return bytes;
    }

    void setInUse(const bool inUse) {
        if(inUse == mInUse) return;
        mInUse = inUse;
        if(mInUse) removeFromMemoryManagment();
        else addToMemoryManagment();
    }

    bool handledByMemoryHandler() const {
        return mHandledByMemoryHandler;
    }

    bool inUse() const {
        return mInUse;
    }
protected:
    void addToMemoryManagment();
    void removeFromMemoryManagment();
    void updateInMemoryManagment();
private:
    bool mHandledByMemoryHandler = false;
    bool mInUse = false;
};

#endif // MINIMALCACHECONTAINER_H