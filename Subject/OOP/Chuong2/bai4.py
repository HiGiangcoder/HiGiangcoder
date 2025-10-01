class Student:
    def __init__(self, student_id, name, sex, math, physics, chemistry):
        self.student_id = student_id
        self.name = name
        self.sex = sex
        self.math = math
        self.physics = physics
        self.chemistry = chemistry
        self.avg = self.__calc_avg()
    
    def __calc_avg(self):
        return (self.math + self.physics + self.chemistry) / 3
    
    def __str__(self):
        return f"Ma hoc sinh: {self.student_id}\nHo ten: {self.name}\nGioi tinh: {self.sex}\nDiem toan: {self.math}\nDiem ly: {self.physics}\nDiem hoa: {self.chemistry}\nDiem trung binh: {self.avg:.2f}"

if __name__ == "__main__":
    print("Nhap thong tin hoc sinh:")
    student_id = input("Ma hoc sinh: ")
    name = input("Ho ten: ")
    sex = input("Gioi tinh: ")
    math = float(input("Diem toan: "))
    physics = float(input("Diem ly: "))
    chemistry = float(input("Diem hoa: "))
    student = Student(student_id, name, sex, math, physics, chemistry)
    
    print("\nThong tin hoc sinh:")
    print(student)