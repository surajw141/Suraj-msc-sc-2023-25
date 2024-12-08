'''consider the data of the five objects o1, o2, o3, o4, o5 in table
perform agglomerative clustering using average linkage and obtain the dendogram,
further decide the optional number of clusters using the elbow method
objects : variables
  : x1, x2, x3
o1: 7,6,7
o2: 9,7,8
o3: 1,2,4
o4: 2,4,6
o5: 3,4,5'''


import numpy as np
import scipy.cluster.hierarchy as sch
import matplotlib.pyplot as plt
from scipy.spatial.distance import pdist

# Data for objects o1, o2, o3, o4, o5
data = np.array([
  [7, 6, 7], # o1
  [9, 7, 8], # o2
  [1, 2, 4], # o3
  [2, 4, 6], # o4
  [3, 4, 5]  # o5
])

# Calculate the condensed distance matrix (Euclidean distance)
dist_matrix = pdist(data) # pdist automatically gives the condensed distance matrix

# Perform agglomerative clustering using average linkage
Z = sch.linkage(dist_matrix, method='average')

# Plot the dendrogram
plt.figure(figsize=(10, 7))
sch.dendrogram(Z)
plt.title("Dendrogram - Agglomerative Clustering (Average Linkage)")
plt.xlabel("Object Index")
plt.ylabel("Distance")
plt.show()

# To determine the optimal number of clusters using the elbow method:
# We can visualize the change in distance at each merge step using a linkage matrix.