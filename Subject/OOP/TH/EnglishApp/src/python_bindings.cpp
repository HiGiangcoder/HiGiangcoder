#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "EnglishApp.h"
#include "Lesson.h"
#include "VocabularyLesson.h"
#include "GrammarLesson.h"
#include "Word.h"
#include "User.h" // Thêm dòng này

namespace py = pybind11;

PYBIND11_MODULE(englishapp, m) {
    m.doc() = "English Learning App Python Bindings";
    
    // Đăng ký User TRƯỚC EnglishApp
    py::class_<User>(m, "User")
        .def(py::init<const std::string&, const std::string&>())
        .def("getName", &User::getName)
        .def("getLessonCount", &User::getLessonCount)
        .def("completeLesson", &User::completeLesson)
        .def("authenticate", &User::authenticate);

    py::class_<Word>(m, "Word")
        .def(py::init<const std::string&, const std::string&>())
        .def("getText", &Word::getText)
        .def("getMeaning", &Word::getMeaning)
        .def("display", &Word::display);

    py::class_<Lesson>(m, "Lesson")
        .def("getId", &Lesson::getId)
        .def("getTitle", &Lesson::getTitle)
        .def("getType", &Lesson::getType)
        .def("start", &Lesson::start)
        .def("showResult", &Lesson::showResult);

    py::class_<VocabularyLesson, Lesson>(m, "VocabularyLesson")
        .def(py::init<int, const std::string&, std::vector<Word>>())
        .def("getWords", &VocabularyLesson::getWords);

    py::class_<GrammarLesson, Lesson>(m, "GrammarLesson")
        .def(py::init<int, const std::string&, std::vector<std::string>>())
        .def("getRules", &GrammarLesson::getRules);

    py::class_<EnglishApp>(m, "EnglishApp")
        .def(py::init<>())
        .def("getLessons", &EnglishApp::getLessons)
        .def("getUser", &EnglishApp::getUser, py::return_value_policy::reference_internal); // Sửa policy
}