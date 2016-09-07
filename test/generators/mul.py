#!/usr/bin/env python2

import sys

MAXIMUM_VALUE = 10 ** 100
MAXIMUM_DIVISOR_EXPONENT = 200
MAXIMUM_FACTORS = 100
COUNT = 1

from decimal import Decimal, DefaultContext
from random import randrange, choice
from operator import mul

def randomDecimal():
    return Decimal(randrange(MAXIMUM_VALUE + 1)) / 10 ** randrange(MAXIMUM_DIVISOR_EXPONENT + 1) * choice([1, -1])

def decimalToString(d):
    d.normalize()

    if d == 0:
        return "0"

    neg = (d < 0)
    if neg:
        s = "(- "
        d = -d
    else:
        s = ""

    ipart = int(d)
    s += str(ipart)
    d -= ipart

    if d != 0:
        s += "."

    while d != 0:
        d = 10 * d
        ipart = int(d)
        s += str(ipart)
        d -= ipart

    if neg:
        s += ")"

    return s

for i in xrange(COUNT):
    n = randrange(MAXIMUM_FACTORS + 1)
    factors = [randomDecimal() for j in xrange(n)]
    product = reduce(mul, factors, Decimal(1))

    print "(* %s) ; = %s" % (" ".join(decimalToString(f) for f in factors), decimalToString(product))
    sys.stderr.write(decimalToString(product) + "\n")
