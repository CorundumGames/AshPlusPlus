#ifndef IFAMILY_H
#define IFAMILY_H

#include <typeinfo>

#include "Declarations.hpp"

using std::type_info;


namespace ash {
namespace core {
/**
 * The interface for classes that are used to manage NodeLists (set as the familyClass property in the Engine object).
 * Most developers don't need to use this since the default implementation is used by default and suits most needs.
 */
template<class T> class IFamily
{
    public:
        virtual ~IFamily() {}

        /**
         * An entity has been added to the engine. It may already have components so test the entity for inclusion in
         * this family's NodeList.
         */
        virtual void newEntity(const Entity&) = 0;

        /**
         * An entity has been removed from the engine. If it's in this family's NodeList it should be removed.
         */
        virtual void removeEntity(const Entity&) = 0;

        /**
         * A component has been added to an entity. Test whether the entity's inclusion in this family's NodeList should
         * be modified.
         */
        virtual void componentAddedToEntity(const Entity&, const type_info&) = 0;

        /**
         * A component has been removed from an entity. Test whether the entity's inclusion in this family's NodeList
         * should be modified.
         */
        virtual void componentRemoveFromEntity(const Entity&, const type_info&) = 0;

        /**
         * The family is about to be discarded. Clean up all properties as necessary. Usually, you will want to empty
         * the NodeList at this time.
         */
        virtual void cleanUp() = 0;

        /**
         * Returns the NodeList managed by this class. This should be a reference that remains valid always since it is
         * retained and reused by Systems that use the list. i.e. never recreate the list, always modify it in place.
         */
        virtual NodeList<T> const& nodeList() const = 0;
};
}
}

#endif // IFAMILY_H
