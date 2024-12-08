'''obtain eigenvalues and corresponding eigenvectors for the following matrix
[[4,2,6],[2,4,6],[6,6,40]]'''

import numpy as np

# Given matrix A
A = np.array([[4, 2, 6],
              [2, 4, 6],
              [6, 6, 40]])

# Compute eigenvalues and eigenvectors
eigenvalues, eigenvectors = np.linalg.eig(A)

print("Eigenvalues:\n", eigenvalues)

# Round the eigenvectors to 3 decimal places for better readability
eigenvectors_rounded = np.round(eigenvectors, 3)

# Print eigenvectors in a readable format
print("Eigenvectors (rounded to 3 decimal places):")
for i, eigenvector in enumerate(eigenvectors_rounded.T, 1):  # Transpose to iterate through eigenvectors
    print(f"Eigenvector {i}: {eigenvector}")