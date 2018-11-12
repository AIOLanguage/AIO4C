#ifndef AIO_CLASS_H
#define AIO_CLASS_H

/**
 * 연결.
 */

//lang:
#include <aio_lang/aio_inheritable/aio_inheritable.h>
#include <aio_lang/aio_space/aio_initializable/aio_initializable.h>
#include <ostream>

using namespace lib4aio;

struct aio_class : public aio_initializable, public aio_inheritable<aio_class> {

    explicit aio_class();

    ~aio_class();

    bool operator==(const aio_class &rhs) const;

    bool operator!=(const aio_class &rhs) const;

    static bool compare_classes(const aio_class *c1, const aio_class *c2);

    bool compare(const aio_class *c1, const aio_class *c2) const;

    friend std::ostream &operator<<(std::ostream &os, const aio_class &aClass);
};

#endif //AIO_CLASS_H