#ifndef LAB_6_COLLECTION_H
#define LAB_6_COLLECTION_H


#include <cstddef>

namespace collections {

    template<typename T>
    class Collection {

    public:
        [[nodiscard]] virtual size_t size() const = 0;

        virtual bool contains(const T &value) const = 0;
    };
}


#endif //LAB_6_COLLECTION_H
