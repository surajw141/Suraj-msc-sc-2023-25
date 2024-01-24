student_details = []

for i in range(3):
  student = {}

  student["roll"] = int(input("Enter roll number for student {}: ".format(i + 1)))
  student["name"] = input("Enter name for student {}: ".format(i + 1))
  student["marks1"] = float(input("Enter marks for subject 1 for student {}: ".format(i + 1)))
  student["marks2"] = float(input("Enter marks for subject 2 for student {}: ".format(i + 1)))
  student["marks3"] = float(input("Enter marks for subject 3 for student {}: ".format(i + 1)))

  student_details.append(student)

for student in student_details:
  avg_marks = (student["marks1"] + student["marks2"] + student["marks3"]) / 3

  result = "pass" if avg_marks >= 60 else "fail"

  print(
    "roll no: {}\tstudent name: {}\taverage marks: {:.2f}\tresult: {}".format(
      student["roll"], student["name"], avg_marks, result
    )
  )