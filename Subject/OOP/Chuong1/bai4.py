from functools import cmp_to_key

class Staff:
    def __init__(self, staff_id, name, department, base_salary, bonus):
        self.staff_id = staff_id
        self.name = name
        self.department = department
        self.base_salary = base_salary
        self.bonus = bonus
        self.__calculate_actual_salary()
    
    def __calculate_actual_salary(self):
        self.actual_salary = self.base_salary + self.bonus
    def Get_Info(self):
        return f"ID: {self.staff_id};    Name: {self.name};    Department: {self.department};    Base salary: {self.base_salary}:    Bonus: {self.bonus};    Actual salary: {self.actual_salary}"
    
    def Get_Actual_Salary(self):
        return self.actual_salary
    
    def Get_Base_Salary(self):
        return self.base_salary
    
    def Get_Bonus(self):
        return self.bonus
    
    def Get_Department(self):
        return self.department

    @staticmethod
    def compare_staff(staff1, staff2):
        if staff1.Get_Department() < staff2.Get_Department():
            return -1 # staff1 comes before staff2
        elif staff1.Get_Department() > staff2.Get_Department():
            return 1 # staff1 comes after staff2
        else:
            if staff1.staff_id > staff2.staff_id:
                return -1 
            elif staff1.staff_id < staff2.staff_id:
                return 1
            else:
                return 0 # they are equal
    
if __name__ == "__main__":
    Staff_List = [
        Staff("NV1", "Nguyen Van A", "IT", 15000000, 2000000),
        Staff("NV2", "Tran Thi B", "HR", 12000000, 1500000),
        Staff("NV3", "Le Van C", "IT", 15000000, 2500000),
        Staff("NV4", "Pham Thi D", "Finance", 13000000, 1200000),
        Staff("NV5", "Hoang Van E", "HR", 12000000, 1300000)
    ]

    sum_actual_salary = 0
    lowest_base_salary_id = []
    num_high_bonus_staff = 0

    for i, staff in enumerate(Staff_List):
        sum_actual_salary += staff.Get_Actual_Salary()
        
        if not lowest_base_salary_id or staff.Get_Base_Salary() < Staff_List[lowest_base_salary_id[0]].Get_Base_Salary():
            lowest_base_salary_id = [Staff_List.index(staff)]
        elif staff.Get_Base_Salary() == Staff_List[lowest_base_salary_id[0]].Get_Base_Salary():
            lowest_base_salary_id.append(i)
        
        if staff.Get_Bonus() >= 1200000:
            num_high_bonus_staff += 1

    if __name__ == "__main__":
        print(f"Tong thuc lanh thang cua tat ca nhan vien trong cong ty: {sum_actual_salary}")
        print()
        print("Danh sach nhung nhan vien co muc luong co ban thap nhat:")
        for idx in lowest_base_salary_id:
            print(Staff_List[idx].Get_Info()) 
        print()
        print(f"So luong nhan vien co muc thuong >= 1200000: {num_high_bonus_staff}")
        print()
        print("Danh sach cac nhan vien tang dan theo phong an, neu phong ban trung nhau thi giam dan theo ma nhan vien:")
        Staff_List.sort(key=cmp_to_key(Staff.compare_staff))
        for staff in Staff_List:
            print(staff.Get_Info())