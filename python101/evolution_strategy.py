import numpy as np
import matplotlib.pyplot as plt
from pprint import pprint

class ES(object):
    '''evolution strategy'''
    def __init__(self, dna_size, popsize, maxiter, objf):
        self.popsize = popsize
        self.maxiter = maxiter
        self.pop = None
        self.dna_size = dna_size
        self.objectf = objf
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
            #print('evolve: ',pop['gene'])
            pop = self.kill(children, pop)
            yield pop['gene']

class FunctionOptim(ES):
    def __init__(self, dna_size, popsize, maxiter, objf, bound=[0,5]):
        super(FunctionOptim, self).__init__(dna_size, popsize, maxiter, objf)
        self.bound = bound
        self.pop = self._rand_generate()
    def _rand_generate(self):
        return {'gene':
                np.random.rand(self.popsize,self.dna_size)*(self.bound[1]-self.bound[0])+self.bound[0],
                'variance':
                np.random.randn(self.popsize,self.dna_size)}
    def make_children(self, parent):
        children = {'gene':[], 'variance':[]}
        for p in zip(parent['gene'],parent['variance']):
            if np.random.rand() < 0.8:
                idx = np.random.choice(range(self.popsize))
                other = (parent['gene'][idx], parent['variance'][idx])
                cpoint = np.random.randint(0,2,size=self.dna_size, dtype=np.bool) 
                childd = np.empty_like(p[0]); childv=np.empty_like(p[1])
                childd[cpoint]=p[0][cpoint].copy(); 
                childd[~cpoint]=other[0][~cpoint].copy()
                childv[cpoint]=p[1][cpoint].copy(); 
                childd[~cpoint]=other[1][~cpoint].copy()
                childd, childv = self._mutate(childd, childv)
                children['gene'].append(childd.copy()); children['variance'].append(childv.copy())
        children['gene'] = np.array(children['gene']); children['variance'] = np.array(children['variance'])
        #print('parent shape:{}, children shape:{}'.format(parent['gene'].shape, children['gene'].shape))
        return children
    def _mutate(self, gene, variance):
        variance = np.maximum(variance+np.random.rand(self.dna_size)-0.5,0)
        gene += variance*np.random.randn(self.dna_size)
        gene = np.clip(gene, *self.bound)
        return gene, variance
    def kill(self, children, parent):
        #print('kill: parent {} scores:'.format(parent))
        pop = {'gene': np.vstack((children['gene'], parent['gene'])),
                'variance': np.vstack((children['variance'], parent['variance']))}
        scores = self.objectf(pop['gene']).flatten()
        rank = np.argsort(scores).flatten()
        #print('kill: rank {} scores:{}'.format(rank,scores))
        pop['gene']=pop['gene'][rank][-self.popsize:]
        pop['variance']=pop['variance'][rank][-self.popsize:]
        #print('kill: pop {} scores:'.format(pop))
        #print('pop shape:{}, rank:{}'.format(pop['gene'].shape, rank.shape))
        return pop

def demo():
    f = lambda x:np.sin(10*x)*x+np.cos(2*x)*x
    plt.ion()       # something about plotting
    x = np.linspace(0, 5, 200)
    plt.plot(x, f(x))
    sca = None
    se = FunctionOptim(1, 100, 200, f)
    for pop in se.evolve():
        scores = f(pop)
        if sca:
            sca.remove()
        sca = plt.scatter(pop, scores, lw=0, c='red', alpha=0.5);
        plt.pause(0.05)
        #print(pop)
        print('value:{} point:{}'.format(max(scores), pop[np.argmax(scores)]))
    plt.ioff(); plt.show()

demo()