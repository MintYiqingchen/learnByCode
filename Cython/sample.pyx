# defination for wrapper function for C functions
cimport csample

# import C stdlib
from cpython.pycapsule cimport *
from libc.stdlib cimport malloc, free

def gcd(unsigned int x, unsigned int y):
    return csample.gcd(x, y)

def divide(x, y):
    cdef int rem
    quot = csample.divide(x,y,&rem)
    return quot, rem

def avg(double[:] a):
    cdef:
        int sz
        double result
    sz=a.size
    with nogil:
        res = csample.avg(<double*> &a[0], sz)
    return res

# object destructor
cdef del_Point(object obj):
    pt=<csample.Point *> PyCapsule_GetPointer(obj, "Point")
    free(<void *> pt)

# Point object as capsule
def Point(double x, double y):
    cdef csample.Point *p
    p=<csample.Point *>malloc(sizeof(csample.Point))
    if p==NULL:
        raise MemoryError("No memory to make a point")
    p.x=x
    p.y=y
    return PyCapsule_New(<void*>p, "Point", <PyCapsule_Destructor>del_Point)

def distance(p1,p2):
    pt1=<csample.Point *>PyCapsule_GetPointer(p1, "Point")
    pt2=<csample.Point *>PyCapsule_GetPointer(p2, "Point")
    return csample.distance(pt1, pt2)