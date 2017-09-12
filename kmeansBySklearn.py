from sklearn.cluster import KMeans
import numpy as np
from sklearn.externals import joblib

data = np.random.rand(10,3)  # 生成相应维度的矩阵
print(data)

estimator = KMeans(n_clusters=4)
res = estimator.fit(data)

# 获得上面拟合出的聚类中心
