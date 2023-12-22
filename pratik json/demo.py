import json

def get_student_data():
    stock_name = input("Enter stock name: ")
    age = int(input("Enter student age: "))
    grade = input("Enter student grade: ")

    # Creating a dictionary with student data
    student_data = {
        "Name": stock_name,
        "Age": age,
        "Grade": grade
    }

    return student_data

def write_to_json(data, filename="student_data.json"):
    with open(filename, "w") as json_file:
        json.dump(data, json_file, indent=2)
    print(f"Data has been written to {filename}")

# Get student data from the user
student_data = get_student_data()

# Write student data to a JSON file
write_to_json(student_data)
