namespace lib4aio
{

#ifndef POINT_WATCHER_H
#define POINT_WATCHER_H

    class point_watcher
    {

        typedef enum point_watcher_mode
        {
            POINT_WATCHER_UNDEFINED_MODE, POINT_WATCHER_PASSIVE_MODE, POINT_WATCHER_ACTIVE_MODE
        } point_watcher_mode;

    public:

        unsigned pointer;

        unsigned start;

        unsigned end;

        enum point_watcher_mode mode;

        point_watcher();

        void reset();

        char *substring(const char *string);

        ~point_watcher();

    };

#endif //POINT_WATCHER_H

}