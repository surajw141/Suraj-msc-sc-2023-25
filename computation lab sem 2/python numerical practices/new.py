
y = np.zeros([N+2,M+2])
y[0,1]=V
while (error > eps):
     yp[1,N+1,1:M+1] +y[2:N+2,1:M+1] \
     + y[1:N+1,0:M] +y[1:N+1,2:M+2]
     yp[1:N+1,1:M+1] /= 4
     error = np.max()np.absolute(yp[1:N+1,1:M+1]- y[1:N+1,1:M+1])
     y = yp.copy()