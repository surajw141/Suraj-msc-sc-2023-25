class Student:
    def getStudentDetails(self):
        self.rollno=input("Enter Roll Number : ")
        self.name = input("Enter Name : ")
        self.physics =int(input("Enter Physics Marks : "))
        self.chemistry = int(input("Enter Chemistry Marks : "))
        self.maths = int(input("Enter Math Marks : "))

    def printResult(self):
        self.percentage = (int)( (self.physics + self.chemistry + self.maths) / 300 * 100 ); 
        print(self.rollno,self.name, self.percentage)

S1=Student()
S1.getStudentDetails()

print("Result : ")
S1.printResult()

S1.physics += 9

print("result after adding grace marks...")
S1.printResult()