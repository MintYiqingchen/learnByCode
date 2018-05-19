import numpy as np
import matplotlib.pyplot as plt
from pprint import pprint
DNA_SIZE=10     # DNA长度
POP_SIZE=100    # 种群样本总数
CROSSOVER_RATE=0.8  # 交配率
MUTATION_RATE=0.003 # 变异率
N_GENERATIONS=200
X_BOUND=[0,5]   # 最终结果的上下界
def get_fitness(pred):
    v = object_F(pred)
    return v

def crossover(parent, pop):
    ''' father and mother '''
    child = parent
    if np.random.rand() < CROSSOVER_RATE:
        other = pop[np.random.choice(range(POP_SIZE))]
        logits = np.random.randint(2,size=DNA_SIZE).astype(bool)
        child = np.where(logits, parent, other)
    return child

def mutate(child):
    b=np.random.rand(DNA_SIZE)
    child = np.where(b<MUTATION_RATE, 1-child, child)
    return child

def select(pop, fitness):
    fitness = fitness-np.min(fitness)+1e-3
    logits = np.random.choice(range(POP_SIZE), POP_SIZE, p=fitness/fitness.sum())
    return pop[logits]
def translateDNA(pop):
    '''将01DNA序列转化为有意义的目标结果'''
    tmp = np.array([2**x for x in range(DNA_SIZE)], dtype=np.int)
    tmp = pop.dot(tmp.T)
    return X_BOUND[0]+tmp/float(2**DNA_SIZE-1) * X_BOUND[1]

def object_F(x):
    '''目标函数'''
    return np.sin(10*x)*x+np.cos(2*x)*x

def demo():
    plt.ion()       # something about plotting
    x = np.linspace(*X_BOUND, 200)
    plt.plot(x, object_F(x))
    sca = None
    pop = np.random.randint(2,size=(POP_SIZE,DNA_SIZE))
    for _ in range(N_GENERATIONS):
        scores = get_fitness(translateDNA(pop))
        if sca:
            sca.remove()
        sca = plt.scatter(translateDNA(pop), scores, lw=0, c='red', alpha=0.5);
        plt.pause(0.05)

        # GA part (evolution)
        print("Most fitted DNA: ", pop[np.argmax(scores), :], np.max(scores))
        parent = select(pop, scores)
        pop = parent.copy()
        for i,p in enumerate(pop):
            child = crossover(p, parent)
            child = mutate(child)
            pop[i]=child
    plt.ioff(); plt.show()

class GA(object):
    def __init__(self, dnas,popsize, maxgeneration):
        self.popsize = popsize
        self.maxiter = maxgeneration
        self.dna_size = dnas
        self.output_value = self._objectf
    def _crossover(self,p, parents):
        raise NotImplementedError
    def _objectf(self,x):
        raise NotImplementedError
    def _fitness(self,x):
        res = self._objectf(x)
        res = res-min(res)+1e-3
        return res
    def _select(self,pop, fitness):
        #print('sum:',fitness.sum())
        idx = np.random.choice(range(self.popsize), size=self.popsize, p = fitness/fitness.sum())
        pop = pop[idx]
        return pop

    def _mutate(self,child):
        raise NotImplementedError
    def _translate(self,pop):
        raise NotImplementedError
    def _rand_generate(self):
        '''default method '''
        return np.random.randint(0,2, size=(self.popsize, self.dna_size))
    def evolve(self):
        pop = self._rand_generate()
        for _ in range(self.maxiter):
            x = self._translate(pop)
            scores = self._fitness(x)
            yield {'result':x[np.argmin(scores)],
                    'score':self.output_value([x[np.argmin(scores)]])[0]}
            pop = self._select(pop, scores)
            parent = pop.copy()
            for i,p in enumerate(pop):
                child = self._crossover(p, parent)
                child = self._mutate(child)
                pop[i]=child

class TradeMan(GA):
    def __init__(self,dnas,popsize,maxgeneration, adj):
        super(TradeMan,self).__init__(dnas,popsize,maxgeneration)
        self.adj = adj
        self.dna_size = adj.shape[0]
        self.output_value = self._getdistance
        self.pop = self._rand_generate()
    def _getdistance(self,x):
        res=np.zeros(len(x))
        for i in range(len(x)):
            cost = 0.0
            for j in range(len(x[i])):
                if j==len(x[i])-1:
                    cost += self.adj[x[i][j]][x[i][0]]
                else:
                    cost += self.adj[x[i][j]][x[i][j+1]]
            res[i]=cost
        return res
    def _objectf(self,x):
        res = self._getdistance(x)
        return np.exp(1/res)
    def _translate(self,pop):
        return pop
    def _crossover(self,p, parents):
        if np.random.rand()<CROSSOVER_RATE:
            idx = np.random.choice(range(len(parents)))
            other = parents[idx]
            b = np.random.randint(0,2,size=self.dna_size,dtype=np.bool)
            child = np.where(b, p, [-1]*self.dna_size)
            remain_city = [x for x in other if x not in child]
            for i in range(len(child)):
                if child[i]==-1:
                    child[i]=remain_city.pop(0)
            return child
        else:
            return p
    def _mutate(self,child):
        if np.random.rand()<0.003:
            i,j = np.random.choice(range(self.dna_size),size=2)
            child[i], child[j] = child[j], child[i]
        return child
    def _rand_generate(self):
        pop = np.array([np.random.permutation(self.dna_size) for _ in range(self.popsize)])
        return pop


    def _crossover_loser(self, loser_winner):
        logic = np.random.rand(self.dna_size)
        logic = np.where(logic<CROSSOVER_RATE)[0]
        child = np.zeros(self.dna_size, dtype=np.int)-1
        child[logic] = loser_winner[1][logic].copy()
        logic = sorted(set(range(self.dna_size))-set(logic.tolist()))
        for i, city in enumerate(loser_winner[0]):
            if city not in child:
                j = logic.pop(0)
                child[j] = city
        return child

    def microbe_evolve(self):
        '''only cross and mutate loser subject'''
        pop = self.pop
        for _ in range(self.maxiter):
            x=self._translate(pop)
            scores = self._fitness(x)
            yield {'result':x[np.argmin(scores)],
                'score':self.output_value([x[np.argmin(scores)]])[0]}
            # choose two sample and compare their advantage
            idx = np.random.choice(range(self.popsize),size=2)
            loser_winner_idx = sorted(idx, key=lambda x:scores[x])
            loser_winner = pop[loser_winner_idx]
            # crossover and mutate loser
            child = self._crossover_loser(loser_winner)
            child = self._mutate(child)
            pop[loser_winner_idx[0]]=child
def trademan_demo():
    np.random.seed(7)
    graph = np.random.rand(10,10)*10
    pprint(graph)
    for i in range(10):
        graph[i][i] = 0.0
    tm = TradeMan(10,100,2000,graph)
    #tm.evolve = tm.microbe_evolve
    for a in tm.evolve():
        print(a)

if __name__ == '__main__':
    demo()
    #trademan_demo()
