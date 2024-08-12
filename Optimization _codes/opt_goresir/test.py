import pylab

# Generate some data
x = pylab.linspace(0, 10, 100)
y = pylab.sin(x)

# Create a plot
pylab.plot(x, y)
pylab.title('Sine Wave')
pylab.xlabel('x')
pylab.ylabel('y')

# Show the plot
pylab.show()
