# Circular Buffer

STL is a compatible "Circ Buffer" container, extensible and fixed in size.

[Circular buffer](https://en.wikipedia.org/wiki/Circular_buffer) is a data structure that is often used for buffering in tasks of transmitting and processing data streams.

Two classes:
CCirtucalBuffer and CCircularBufferExt - for circular buffer and circular buffer with extensibility.

A circular buffer for storing arbitrary data types in the form of an stl-compatible container.
The template class(es) are parameterized by the type of the stored value and the allocator.

The container satisfies [the following requirements](https://en.cppreference.com/w/cpp/named_req/Container) for a stl container.
And also [requirements for a sequential container](https://en.cppreference.com/w/cpp/named_req/SequenceContainer)

Excluding rvalue and move semantics.

## Iterator

Represents a random access iterator.

## Ring buffer with maximum size extension.

The CCircularBufferExt class has functionality to extend its maximum size.
The following behavior has been implemented: if the size of the ring buffer reaches its maximum possible size, the value of the maximum size is doubled.

## Tests

The implementation of the Ring Buffer is covered with tests using the Google Test framework.

## Restrictions

* Standard containers are not used
