#include <iostream>
#include <event2/event.h>
#include <unistd.h>
using namespace std;

void checkCallback(evutil_socket_t fd, short events, void *ptr) 
{
    int *id = (int*)ptr;
    *id += 1;
    cout << "checkCallback:" << *id <<endl;
}

int main(void)
{

    struct event *checkTimer;
    event_base *base_ = event_base_new();
    int  id = 0;
    checkTimer = event_new(base_, -1, EV_PERSIST, checkCallback, &id);
    struct timeval oneSec = {1, 0};
    event_add(checkTimer, &oneSec);

    // run event dispatch, it will break util all up sessions are available
    event_base_dispatch(base_);

    // get here means: all up sessions are available
    event_del(checkTimer);
    event_free(checkTimer);

    event_base_loopbreak(base_);

    return 1;
}
