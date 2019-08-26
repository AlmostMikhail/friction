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

#ifndef CUSTOMHANDLER_H
#define CUSTOMHANDLER_H
#include <QList>
#include <QLibrary>
#include "smartPointers/ememory.h"
#include "typemenu.h"
#include "customidentifier.h"

template <typename B, typename C>
class CustomHandler {
public:
    typedef qsptr<C> (*CCreatorNewFunc)();
    typedef qsptr<C> (*CCreatorFunc)(const CustomIdentifier &identifier);
    typedef QString (*CNameFunc)();
    typedef CustomIdentifier (*CIdentifierFunc)();
    typedef bool (*CSupport)(const CustomIdentifier&);

    CustomHandler(const CCreatorNewFunc& creatorNew,
                  const CCreatorFunc& creator,
                  const CNameFunc& name,
                  const CIdentifierFunc& identifier,
                  const CSupport& support) :
        mCreatorNew(creatorNew), mCreator(creator), mName(name),
        mIdentifier(identifier), mSupport(support) {}

    static void sLoadCustom(const QString& libPath);

    static qsptr<C> sCreateForIdentifier(
            const CustomIdentifier &identifier) {
        for(const auto& creator : sCreators) {
            if(!creator.mSupport(identifier)) continue;
            return creator.mCreator(identifier);
        }
        return nullptr;
    }

    template <typename U>
    static void sAddToMenu(PropertyMenu * const menu,
                           const U &adder) {
        for(const auto& creator : sCreators)
            sAddToMenu(menu, creator, adder);
    }
private:
    template <typename U>
    static void sAddToMenu(PropertyMenu * const menu,
                           const CustomHandler<B, C>& creator,
                           const U &adder) {
        menu->addPlainAction<BoundingBox>(creator.mName(),
        [adder, creator](BoundingBox * const box) {
            const auto cEffect = creator.mCreatorNew();
            (box->*adder)(qSharedPointerCast<B>(cEffect));
        });
    }
    static QList<CustomHandler<B, C>> sCreators;

    CCreatorNewFunc mCreatorNew;
    CCreatorFunc mCreator;
    CNameFunc mName;
    CIdentifierFunc mIdentifier;
    CSupport mSupport;
};

template <typename B, typename C>
QList<CustomHandler<B, C>> CustomHandler<B, C>::sCreators;

template <typename B, typename C>
void CustomHandler<B, C>::sLoadCustom(const QString &libPath) {
    QLibrary lib(libPath);

    const auto creatorNewFunc = reinterpret_cast<CCreatorNewFunc>(
                lib.resolve("eCreateNewestVersion"));
    if(!creatorNewFunc) RuntimeThrow("Could not resolve 'eCreateNewestVersion' symbol");

    const auto creatorFunc = reinterpret_cast<CCreatorFunc>(
                lib.resolve("eCreate"));
    if(!creatorFunc) RuntimeThrow("Could not resolve 'eCreate' symbol");

    const auto nameFunc = reinterpret_cast<CNameFunc>(
                lib.resolve("eName"));
    if(!nameFunc) RuntimeThrow("Could not resolve 'eName' symbol");

    const auto identifierFunc = reinterpret_cast<CIdentifierFunc>(
                lib.resolve("eIdentifier"));
    if(!identifierFunc) RuntimeThrow("Could not resolve 'eIdentifier' symbol");

    const auto supportFunc = reinterpret_cast<CSupport>(
                lib.resolve("eSupports"));
    if(!supportFunc) RuntimeThrow("Could not resolve 'eSupports' symbol");

    CustomHandler handler(creatorNewFunc, creatorFunc, nameFunc,
                          identifierFunc, supportFunc);
    sCreators.append(handler);
}


#endif // CUSTOMHANDLER_H