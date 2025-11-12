#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "EnglishApp.h"
#include "Lesson.h"
#include "VocabularyLesson.h"
#include "Word.h"

namespace py = pybind11;

PYBIND11_MODULE(englishapp, m) {
    py::class_<Word>(m, "Word")
        .def(py::init<const std::string&, const std::string&>())
        .def("getText", &Word::getText)
        .def("getMeaning", &Word::getMeaning);

    py::class_<Lesson>(m, "Lesson")
        .def("getId", &Lesson::getId)
        .def("getTitle", &Lesson::getTitle)
        .def("getType", &Lesson::getType)
        .def("showResult", &Lesson::showResult);

    py::class_<VocabularyLesson, Lesson>(m, "VocabularyLesson")
        .def(py::init<int, const std::string&, std::vector<Word>>())
        .def("start", &VocabularyLesson::start)
        .def("showResult", &VocabularyLesson::showResult)
        .def("getWords", &VocabularyLesson::getWords);

    py::class_<EnglishApp>(m, "EnglishApp")
        .def(py::init<>())
        .def("run", &EnglishApp::run)
        .def("getLessons", &EnglishApp::getLessons);
}
