import numpy as np
import matplotlib.pyplot as plt
DNA_SIZE=10		# DNA长度
POP_SIZE=100	# 种群样本总数
CROSSOVER_RATE=0.8	# 交配率
MUTATION_RATE=0.003	# 变异率
N_GENERATIONS=200
X_BOUND=[0,5]	# 最终结果的上下界
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

plt.ion()       # something about plotting
x = np.linspace(*X_BOUND, 200)
plt.plot(x, object_F(x))

pop = np.random.randint(2,size=(POP_SIZE,DNA_SIZE))
for _ in range(N_GENERATIONS):
	scores = get_fitness(translateDNA(pop))

	if 'sca' in globals(): 
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