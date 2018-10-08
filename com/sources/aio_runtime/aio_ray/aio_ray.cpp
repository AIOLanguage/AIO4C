#include <aio_runtime/aio_ray/aio_ray.h>

aio_ray::aio_ray()
{

}

aio_ray::~aio_ray()
{

}

void aio_ray::complete()
{

}

aio_ray *aio_ray::perform(const aio_schemable *schemable)
{
    return nullptr;
}

array_list<aio_variable> *aio_ray::get_variables() const
{
    return nullptr;
}

const aio_ray_state aio_ray::get_state() const
{
    return *this->state;
}

void aio_ray::set_ray_state(aio_ray_state ray_state)
{
    *this->state = ray_state;
}