# python declaration for C extension
# file name must be cxxxxx.pxd
cdef extern from "sample.h":
    int gcd(int, int)
    int divide(int,int, int*)
    double avg(double*, int) nogil

    ctypedef struct Point:
        double x
        double y

    double distance(Point*, Point*)