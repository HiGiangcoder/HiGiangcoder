#pragma
#include <string>
using namespace std;

class Lesson {
protected:
    int id;
    string title;
public:
    Lesson(int id, const string& title);
    virtual void start() = 0; // Phuong thuc truu tuong
    virtual void showResult() = 0;
    virtual ~Lesson() = default;
};

Lesson::Lesson(int id, const string& title) : id(id), title(title) {}

Lesson::~Lesson() {}
