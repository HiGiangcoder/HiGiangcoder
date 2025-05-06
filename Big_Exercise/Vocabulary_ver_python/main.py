import json
import random
import time
import sys
import threading  # Thêm thư viện threading để xử lý đa luồng
import signal
import re

class VocabularyLearner:
    def __init__(self):
        self.vocab_file = 'vocabulary.json'
        self.vocabulary = self.load_vocabulary()
        self.colors = {
            'reset': "\033[0m",
            'red': "\033[31m",
            'green': "\033[32m",
            'yellow': "\033[33m",
            'blue': "\033[34m",
            'cyan': "\033[36m",
        }
    
    def color_text(self, text, color):
        return f"{self.colors[color]}{text}{self.colors['reset']}"

    def load_vocabulary(self):
        try:
            with open(self.vocab_file, 'r', encoding='utf-8') as f:
                data = json.load(f)
                if isinstance(data, list):
                    return {'Default': data}
                return data
        except FileNotFoundError:
            return {'Default': []}
            
    def save_vocabulary(self):
        with open(self.vocab_file, 'w', encoding='utf-8') as f:
            json.dump(self.vocabulary, f, ensure_ascii=False, indent=4)
    
    def create_package(self):
        while True:
            package_name = input(self.color_text("Nhập tên gói mới (hoặc 'q' để thoát): ", 'cyan')).strip()
            if package_name.lower() == 'q':
                return
            if not package_name:
                print(self.color_text("Tên gói không được để trống!", 'red'))
                continue
            if package_name in self.vocabulary:
                print(self.color_text("Gói đã tồn tại!", 'red'))
                continue
        
            self.vocabulary[package_name] = []
            self.save_vocabulary()
            print(self.color_text(f"Đã tạo gói '{package_name}' thành công!", 'green'))
            break
    
    def add_word(self):
        package_name = self.select_package()
        if not package_name:
            return
        
        while True:
            word = input(self.color_text("Nhập từ mới (q để thoát): ", 'cyan')).strip()
            if word.lower() == 'q':
                break
            meaning = input("Nhập nghĩa: ").strip()
            example = input("Nhập ví dụ (nếu có): ").strip()
            
            new_word = {'word': word, 'meaning': meaning, 'example': example, 'correct': 0}
            self.vocabulary[package_name].append(new_word)
            self.save_vocabulary()
            print(f"Đã thêm từ '{word}' vào gói '{package_name}' thành công!")
    
    def review_words(self):
        package_name = self.select_package()
        if not package_name:
            return
        
        words = self.vocabulary[package_name]
        if not words:
            print("Gói từ trống!")
            return
        
        print(self.color_text(f"\n--- DANH SÁCH TỪ TRONG GÓI '{package_name.upper()}' ---", 'yellow'))
        for idx, word in enumerate(words, 1):
            print(f"{idx}. {word['word']}: {word['meaning']}")
            if word['example']:
                print(f"   Ví dụ: {word['example']}")
            print(f"   Đúng: {word['correct']} lần\n")
        
        delete_index = input("Nhập số thứ tự từ muốn xóa (q để thoát): ").strip()
        if delete_index.lower() == 'q':
            return
        
        try:
            delete_index = int(delete_index) - 1
            if 0 <= delete_index < len(words):
                removed_word = words.pop(delete_index)
                self.save_vocabulary()
                print(f"Đã xóa từ '{removed_word['word']}' thành công!")
            else:
                print("Số thứ tự không hợp lệ!")
        except ValueError:
            print("Lỗi: Hãy nhập số hợp lệ!")
    
    def select_package(self):
        if not self.vocabulary:
            print("Không có gói nào! Hãy tạo một gói trước.")
            return None
        
        while True:
            print(self.color_text("\n--- DANH SÁCH GÓI ---", 'yellow'))
            for idx, package in enumerate(self.vocabulary.keys(), 1):
                print(f"{idx}. {package}")
            
            package_name = input("Nhập tên gói muốn chọn (hoặc 'q' để thoát): ").strip()
            if package_name.lower() == 'q':
                return None
            if package_name in self.vocabulary:
                return package_name
            print(self.color_text("Gói không tồn tại! Hãy nhập lại.", 'red'))
    
    def quiz(self):
        package_name = self.select_package()
        if not package_name:
            return
            
        words = self.vocabulary[package_name]
        if not words:
            print("Gói từ trống!")
            return
            
        print(self.color_text("\n--- CHẾ ĐỘ KIỂM TRA ---", 'yellow'))
        while True:
            print("Chọn loại kiểm tra:")
            print("1. Trắc nghiệm")
            print("2. Nhập đáp án")
            print("3. Tạo câu")
            print("4. Đảo chữ")
            print("5. Ghép nghĩa")
            print("6. Quiz thời gian")
            print("7. Chọn 1 trong 9 nghĩa") 
            print("q. Thoát")
            choice = input("Lựa chọn của bạn: ").strip().lower()
            
            if choice == 'q':
                break
            elif choice == '1':
                self.multiple_choice_quiz(words, package_name)
            elif choice == '2':
                self.type_answer_quiz(words, package_name)
            elif choice == '3':
                self.sentence_formation_quiz(words, package_name)
            elif choice == '4':
                self.scrambled_words_quiz(words, package_name)
            elif choice == '5':
                self.matching_quiz(words, package_name)
            elif choice == '6':
                self.timed_quiz(words, package_name)
            elif choice == '7': 
                self.nine_meanings_quiz(words, package_name)
            else:
                print(self.color_text("Lựa chọn không hợp lệ!", 'red'))

    def multiple_choice_quiz(self, words, package_name):
        while True:
            question = random.choice(words)
            options = random.sample(
                [w['meaning'] for w in words if w != question], 
                min(3, len(words)-1)
            ) + [question['meaning']]
            random.shuffle(options)
            
            print(f"\nTừ: {question['word']}")
            print("Chọn nghĩa đúng:")
            for i, opt in enumerate(options, 1):
                print(f"{i}. {opt}")
                
            answer = input("\nĐáp án của bạn (1-4/q để thoát): ").strip().lower()
            if answer == 'q':
                break
                
            try:
                answer_num = int(answer)
                if 1 <= answer_num <= 4 and options[answer_num-1] == question['meaning']:
                    print("\033[32mChính xác!\033[0m")
                    question['correct'] += 1
                else:
                    print(f"\033[31mSai rồi! Đáp án đúng là: {question['meaning']}\033[0m")
                self.save_vocabulary()
            except:
                print(self.color_text("Lựa chọn không hợp lệ!"), 'red')

    def type_answer_quiz(self, words, package_name):
        while True:
            question = random.choice(words)
            print(f"\nNghĩa: {question['meaning']}")
            
            answer = input("Nhập từ tiếng Anh (hoặc 'q' để thoát): ").strip().lower()
            if answer == 'q':
                break
                
            if answer == question['word'].lower():
                print("\033[32mChính xác!\033[0m")
                question['correct'] += 1
            else:
                print(f"\033[31mSai rồi! Đáp án đúng là: {question['word']}\033[0m")

            if question['example']:
                print(f"Ví dụ: {question['example']}")
            self.save_vocabulary()
    
    def sentence_formation_quiz(self, words, package_name):
        while True:
            question = random.choice(words)
            if not question['example']:
                continue
            
            words_in_example = question['example'].split()
            random.shuffle(words_in_example)
            print(f"\nSắp xếp các từ sau thành câu hoàn chỉnh:")
            print(" ".join(words_in_example))
            
            answer = input("Nhập câu của bạn (hoặc 'q' để thoát): ").strip()
            if answer.lower() == 'q':
                break
                
            if answer.lower() == question['example'].lower():
                print("\033[32mChính xác!\033[0m")
                question['correct'] += 1
            else:
                print(f"\033[31mSai rồi! Đáp án đúng là: {question['example']}\033[0m")
            print(f"\033[34mTừ vựng: {question['word']}")
            print(f"\033[34mNghĩa: {question['meaning']} \033[0m")

            self.save_vocabulary()
    
    def scrambled_words_quiz(self, words, package_name):
        while True:
            question = random.choice(words)
            original_word = question['word']
            
            # Tách từ thành các từ riêng biệt
            words_list = original_word.split()
            
            # Hoán đổi các chữ cái trong từng từ
            scrambled_words = []
            for word in words_list:
                scrambled_word = list(word)
                random.shuffle(scrambled_word)
                scrambled_words.append(''.join(scrambled_word))
            
            # Kết hợp các từ đã hoán đổi lại thành câu
            scrambled_sentence = ' '.join(scrambled_words)
            
            print(f"\nTừ bị đảo: {scrambled_sentence}, nghĩa của từ: {question['meaning']}")
            
            answer = input("Nhập từ đúng (hoặc 'q' để thoát): ").strip().lower()
            if answer == 'q':
                break
                
            if answer == original_word.lower():
                print("\033[32mChính xác!\033[0m")
                question['correct'] += 1
            else:
                print(f"\033[31mSai rồi! Đáp án đúng là: {original_word}\033[0m")
            
            if question['example']:
                print(f"Ví dụ: {question['example']}")

            self.save_vocabulary()
    
    def matching_quiz(self, words, package_name):
        while True:
            selected_words = random.sample(words, min(4, len(words)))
            meanings = [w['meaning'] for w in selected_words]
            random.shuffle(meanings)
            
            print("\nGhép từ với nghĩa tương ứng:")
            for i, word in enumerate(selected_words, 1):
                print(f"{i}. {word['word']}")
            for i, meaning in enumerate(meanings, 1):
                print(f"{chr(64 + i)}. {meaning}")
                
            answer = input("Nhập đáp án (ví dụ: 1b2d4c3a hoặc 'q' để thoát): ").strip().lower()
            if answer == 'q':
                break
                
            try:
                # Tách các cặp số-chữ từ chuỗi nhập
                pairs = re.findall(r'(\d)([a-d])', answer)
                if len(pairs) != 4:
                    raise ValueError
                
                correct = True
                for num_str, char_str in pairs:
                    word_idx = int(num_str) - 1
                    meaning_idx = ord(char_str.upper()) - 65
                    
                    if word_idx < 0 or word_idx >= 4:
                        raise IndexError
                    if meaning_idx < 0 or meaning_idx >= 4:
                        raise IndexError
                        
                    if selected_words[word_idx]['meaning'] != meanings[meaning_idx]:
                        correct = False
                        break
                
                if correct:
                    print("\033[32mChính xác!\033[0m")
                    for word in selected_words:
                        word['correct'] += 1
                else:
                    print("\033[31mSai rồi!\033[0m")
                    for i, word in enumerate(selected_words):
                        print(f"{i + 1}. {word['word']} -> {word['meaning']}")
                self.save_vocabulary()
                
            except (ValueError, IndexError):
                print(self.color_text("Lỗi: Hãy nhập đúng định dạng (vd: 1b2d3a4c)!", 'red'))

    def timed_quiz(self, words, package_name):
        time_limit = 10  # Giới hạn thời gian cho mỗi câu hỏi (giây)
        while True:
            question = random.choice(words)
            print(f"\nBạn có {time_limit} giây để trả lời:")
            print(f"Nghĩa: {question['meaning']}")
            
            time_up = False  # Biến để kiểm tra xem đã hết thời gian chưa
            user_answer = None  # Biến để lưu đáp án của người dùng
            stop_countdown = False  # Biến để dừng countdown sớm

            # Hàm đếm ngược
            def countdown():
                nonlocal time_up, stop_countdown
                start_time = time.time()
                end_time = start_time + time_limit
                
                while time.time() < end_time and not stop_countdown:
                    time.sleep(0.1)  # Giảm độ trễ để phản ứng nhanh hơn
                
                if not stop_countdown:  # Chỉ xử lý nếu countdown không bị dừng
                    nonlocal time_up
                    time_up = True
                    print("\033[31m\nHết thời gian!\033[0m")  # Hiển thị thông báo màu đỏ
                    print(f"Đáp án đúng là: {question['word']}")
                    sys.stdout.flush()

            # Tạo và chạy luồng đếm ngược
            countdown_thread = threading.Thread(target=countdown)
            countdown_thread.start()

            # Nhập đáp án từ người dùng
            try:
                user_answer = input("Nhập từ tiếng Anh (hoặc 'q' để thoát): ").strip().lower()
            except:
                pass

            # Dừng countdown ngay khi có đáp án
            stop_countdown = True
            countdown_thread.join()  # Đảm bảo luồng countdown đã dừng

            # Kiểm tra xem đã hết thời gian chưa
            if time_up:
                continue  # Bỏ qua phần kiểm tra đáp án nếu đã hết thời gian

            # Xử lý đáp án
            if user_answer == 'q':
                break
            elif user_answer == question['word'].lower():
                print("\033[32mChính xác!\033[0m")
                question['correct'] += 1
            else:
                print(f"\033[31mSai rồi! Đáp án đúng là: {question['word']}\033[0m")

            self.save_vocabulary()


    def nine_meanings_quiz(self, words, package_name):
        while True:
            question = random.choice(words)
            
            # Lấy 8 nghĩa ngẫu nhiên khác (có thể trùng nếu không đủ từ)
            other_meanings = [w['meaning'] for w in words if w != question]
            if len(other_meanings) < 8:
                # Nếu không đủ 8 nghĩa khác, thêm các nghĩa giả
                other_meanings += ["(nghĩa không xác định)"] * (8 - len(other_meanings))
            
            options = random.sample(other_meanings, 8) + [question['meaning']]
            random.shuffle(options)
            
            print(f"\n{self.color_text('Từ:', 'yellow')} {self.color_text(question['word'], 'cyan')}")
            print(self.color_text("Chọn nghĩa đúng từ bảng sau:", 'yellow'))
            
            # Hàm định dạng nghĩa để hiển thị
            def format_meaning(meaning, max_length=20, max_lines=2):
                words = meaning.split()
                lines = []
                current_line = []
                
                for word in words:
                    if len(' '.join(current_line + [word])) <= max_length:
                        current_line.append(word)
                    else:
                        lines.append(' '.join(current_line))
                        current_line = [word]
                        if len(lines) >= max_lines:
                            break
                
                if current_line and len(lines) < max_lines:
                    lines.append(' '.join(current_line))
                
                if len(lines) == 1:
                    lines.append('')  # Thêm dòng trống để căn đều
                    
                return lines[:2]  # Chỉ lấy tối đa 2 dòng

            # Tạo bảng 3x3
            cell_width = 25
            horizontal_line = "+" + ("-" * (cell_width + 2) + "+") * 3
            
            print(horizontal_line)
            for row in range(0, 9, 3):
                # Lấy 3 options cho hàng này
                row_options = options[row:row+3]
                
                # Chuẩn bị các dòng hiển thị
                formatted_options = [format_meaning(opt) for opt in row_options]
                
                # In từng dòng của các ô
                for line in range(2):
                    print("|", end="")
                    for col in range(3):
                        opt_num = row + col + 1
                        text = f" {opt_num:2}. {formatted_options[col][line]}"
                        # Cắt bớt nếu quá dài và thêm dấu "..." nếu cần
                        if len(text) > cell_width:
                            text = text[:cell_width-3] + "..."
                        # Căn đều và thêm màu
                        colored_text = self.color_text(text.ljust(cell_width), 'blue')
                        print(f" {colored_text} |", end="")
                    print()
                
                print(horizontal_line)
                    
            answer = input("\nĐáp án của bạn (1-9/q để thoát): ").strip().lower()
            if answer == 'q':
                break
                    
            try:
                answer_num = int(answer)
                if 1 <= answer_num <= 9:
                    selected_meaning = options[answer_num-1]
                    if selected_meaning == question['meaning']:
                        print(self.color_text("\nChính xác!", 'green'))
                        question['correct'] += 1
                    else:
                        print(self.color_text(f"\nSai rồi! Đáp án đúng là:", 'red'))
                        print(f"{self.color_text(question['word'], 'cyan')}: {self.color_text(question['meaning'], 'green')}")
                    
                    if question['example']:
                        print(f"\n{self.color_text('Ví dụ:', 'yellow')} {question['example']}")
                    
                    self.save_vocabulary()
            except:
                print(self.color_text("Lựa chọn không hợp lệ!", 'red'))


    def run(self):
        while True:
            print(self.color_text("\n--- ENGLISH VOCABULARY LEARNING ---", 'yellow'))
            print(self.color_text("1. Tạo gói từ mới", 'blue'))
            print(self.color_text("2. Thêm từ mới", 'blue'))
            print(self.color_text("3. Xem danh sách từ", 'blue'))
            print(self.color_text("4. Làm quiz", 'blue'))
            print(self.color_text("5. Thoát", 'red'))
            
            choice = input(self.color_text("Chọn chức năng: ", 'cyan')).strip()
            if choice == '1':
                self.create_package()
            elif choice == '2':
                self.add_word()
            elif choice == '3':
                self.review_words()
            elif choice == '4':
                self.quiz()
            elif choice == '5':
                print(self.color_text("Cảm ơn đã sử dụng chương trình!", 'green'))
                break
            else:
                print(self.color_text("Lựa chọn không hợp lệ!", 'red'))
            
            input(self.color_text("\nNhấn Enter để tiếp tục...", 'yellow'))

if __name__ == "__main__":
    app = VocabularyLearner()
    app.run()
