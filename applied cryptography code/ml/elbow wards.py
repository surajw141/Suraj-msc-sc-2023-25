import numpy as np
import pandas as pd
import scipy.cluster.hierarchy as sch
import matplotlib.pyplot as plt
from sklearn.cluster import AgglomerativeClustering
from scipy.spatial.distance import pdist, squareform

# Data
data = np.array([[3, 4, 7],
                 [5, 4, 7],
                 [8, 9, 2],
                 [9, 7, 3],
                 [4, 7, 6]])

# Step 1: Calculate the Euclidean distance matrix
distance_matrix = pdist(data, metric='euclidean')

# Step 2: Hierarchical Agglomerative Clustering using Ward's method
Z = sch.linkage(distance_matrix, method='ward')

# Step 3: Dendrogram (visualization)
plt.figure(figsize=(10, 6))
sch.dendrogram(Z)
plt.title("Dendrogram (Ward's Method)")
plt.xlabel('Objects')
plt.ylabel('Euclidean Distance')
plt.show()

# Step 4: Elbow Method - Compute WSS for different number of clusters
wss = []
for k in range(1, 6):
    model = AgglomerativeClustering(n_clusters=k, linkage='ward')
    model.fit(data)
   
    # Calculate WSS for the clusters
    wss_k = 0
    for cluster in range(k):
        cluster_points = data[model.labels_ == cluster]
        cluster_center = np.mean(cluster_points, axis=0)
        wss_k += np.sum((cluster_points - cluster_center) ** 2)
   
    wss.append(wss_k)

# Step 5: Plot WSS for the elbow method
plt.figure(figsize=(8, 6))
plt.plot(range(1, 6), wss, marker='o')
plt.title('Elbow Method for Optimal Number of Clusters')
plt.xlabel('Number of Clusters')
plt.ylabel('WSS (Within-cluster sum of squares)')
plt.show()