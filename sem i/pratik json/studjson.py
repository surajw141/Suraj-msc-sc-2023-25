import json

# Initialize an empty list to store student data
student_data = []

# Loop to get input from the user for each student
for i in range(5):  # Assuming you want data for 5 students
    fina = input("Enter first name: ")
    mina = input("Enter middle name: ")
    lana = input("Enter last name: ")
    sem = input("Enter semester: ")
    sub = input("Enter subject: ")
    domain = input("Enter domain: ")

    # Create a dictionary for the current student
    student = {
        "fina": fina,
        "mina": mina,
        "lana": lana,
        "sem": sem,
        "sub": sub,
        "domain": domain
    }

    # Append the student dictionary to the list
    student_data.append(student)

# Convert the list of dictionaries to a JSON-formatted string
json_data = json.dumps(student_data, indent=2)

# Print the JSON data
print(json_data)

with open("student.json","w") as studs:
    json.dump(student_data, studs)
print("JSON created.....")