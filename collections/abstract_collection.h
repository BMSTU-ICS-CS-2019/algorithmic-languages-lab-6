#ifndef LAB_6_ABSTRACT_COLLECTION_H
#define LAB_6_ABSTRACT_COLLECTION_H

#include "collection.h"

namespace collections {

    template<typename T>
    class AbstractCollection : Collection<T> {
    protected:
        size_t size_ = 0;

    public:
        [[nodiscard]] size_t size() const override {
            return size_;
        }
    };
}


#endif //LAB_6_ABSTRACT_COLLECTION_H
