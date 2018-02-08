import numpy as np
import matplotlib as plt

class ES(object):
    '''evolution strategy'''
    def __init__(self, popsize, maxiter):
        self.popsize = popsize
        self.maxiter = maxiter
        self.pop = None
    def make_children(self, parent):
        '''cross over both gene and variance'''
        raise NotImplementError
    def _mutate(self, child):
        '''mutate according to variance and probility'''
        raise NotImplementError
    def kill(self, children, parent):
        '''competition amoung population or among children'''
        raise NotImplementError
    def evolve(self):
        pop = self.pop
        for _ in range(self.maxiter):
            children = self.make_children(pop)
            pop = self.kill(children, pop)
