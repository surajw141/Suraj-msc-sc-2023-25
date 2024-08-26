class City
    def __init__(self,x,y,name)
        self.x = x
        self.y = y
        self.name = name
        def __repr(self):
            return self.name + " (" + str(self.x)+","+ str(self.y)+")"
    
    def getDistance(self, city x)
    return sqrt((c.x-self.x)**2+(c.y-self.y)**2)
    
    
    readcities(_____)
    citylist = []
    #loop to read city & get x,y co-ordinate
    city.append(city(x=<x-cord>, y = <y-cord>, named city)
                
class Fitness :
                def __init__(self. route)
                    self.route = route
                    self.distance= 0.0
                    self.fitness=0.0
                
                def routeDistance(self):
                    self.distance=getTotalDistance(self.route)
                def getfitness(self):
                    self.fitness = 1.0/ self.distance
                    return self.fitness

                
def createRoute(cityList):
                route = randome.sample(cityList, len(cityList))
                return route
def initialPopulation(popSize, cityList):
                population=[]
                for i in range(0,popSize):
                    population.append(createRoute(cityList))
                return population
                
                #popsize=tempreture
                
def rankRoutes(population)
                fitnessResult={}
                for i in range(0, len())
                    fitnessResult[i] = Fitness(population[i]).getFitness()
                return sorted(fitnessResult.fitness(), key=operator.itemgeter(), reverse=true)
'''               
numpy 
random
matplotlib pyplot
geopy
'''             
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                